

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <librtmp/rtmp.h>

#include <iostream>
using namespace std;

#include "FlvHeader.h"
#include "FlvTag.h"
#include "FlvCommon.h"

int64_t get_current_time_us(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t us = (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
    return us;
}

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Usage:\n");
        printf("librtmp_test <rtmp_url>\n");
        return 0;
    }

    FILE *fp = fopen("rtmp.flv", "wb");
    if (!fp){
        printf("Open file rtmp.flv failed\n");
        return -1;
    }


    RTMP* rtmp = RTMP_Alloc();
    RTMP_Init(rtmp);
    rtmp->Link.timeout = 10;

    if (!RTMP_SetupURL(rtmp, argv[1])){
        printf("SetupURL error\n");
        RTMP_Free(rtmp);
        return -1;
    }
    rtmp->Link.lFlags |= RTMP_LF_LIVE;
    RTMP_SetBufferMS(rtmp, 3600*1000);  //1hour

    if (!RTMP_Connect(rtmp, NULL)){
        printf("RTMP_Connect error\n");
        RTMP_Free(rtmp);
        return -1;
    }

    if (!RTMP_ConnectStream(rtmp, 0)){
        printf("RTMP_ConnectStream error\n");
        RTMP_Close(rtmp);
        RTMP_Free(rtmp);
        return -1;
    }

    int buff_size = 5*1000*1000;//5MB
    char* buff = (char*)malloc(buff_size);
    memset(buff, 0, buff_size);

    
    unsigned long long thisRecvedBytes = 0;

    int64_t start_time_us = get_current_time_us();
    int nRead = 0;
    bool first_read = true;
    while (nRead = RTMP_Read(rtmp, buff, buff_size)){
        int nWrite = fwrite(buff, 1, nRead, fp);
        assert(nWrite == nRead);

        if (first_read){

            try {
                FlvHeader fh(buff, nRead);
                assert(fh.Verify());
                fh.Dump();

                printf("first previous tag size: %u\n", FlvTag::FetchPreviousTagSize(buff + fh.kFlvHeaderLength, nRead - fh.kFlvHeaderLength));

                FlvTag ft(buff + FlvHeader::kFlvHeaderLength + FlvTag::kPreviousTagSizeTypeLength,
                    nRead - FlvHeader::kFlvHeaderLength - FlvTag::kPreviousTagSizeTypeLength);
                ft.Dump();
            }
            catch (FlvException& e) {
                //cout << "FlvException catched, err:" << e.ErrorCode() << ", msg:" << e.msg() << endl;
                cout << e << endl;
            }

            
        }
        first_read = false;

        thisRecvedBytes += nRead;

        int64_t curr_time_us = get_current_time_us();
        int64_t delta_us = curr_time_us - start_time_us;
        if (delta_us >= 1000000){
            printf("[rtmp recv kbps:%llu]\n", thisRecvedBytes * 8 * 1000 / delta_us);
            start_time_us = curr_time_us;
            thisRecvedBytes = 0;
        }
        
    }

    if (fp){
        fclose(fp);
    }

    if (buff){
        free(buff);
    }

    if (rtmp){
        RTMP_Close(rtmp);
        RTMP_Free(rtmp);
    }

    return 0;
}

