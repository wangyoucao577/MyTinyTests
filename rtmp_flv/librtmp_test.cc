

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <librtmp/rtmp.h>

using namespace std;

#include "FlvHeader.h"
#include "FlvTag.h"
#include "FlvCommon.h"



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

    int64_t start_time_us = FlvCommonUtils::GetCurrentTimeMillseconds();
    int nRead = 0;
    bool first_read = true;
    int offset = 0;
    bool next_previous_tag_size = true;
    while (nRead = RTMP_Read(rtmp, buff + offset, buff_size - offset)){

        //FLV写文件
        int nWrite = fwrite(buff + offset, 1, nRead, fp);
        assert(nWrite == nRead);
        printf("this recv bytes: %d\n", nRead);

        //FLV解析
        int useful_bytes = nRead + offset;
        offset = 0;
        while (offset < useful_bytes) {
            try {
                if (first_read) {
                    FlvHeader fh(buff + offset, useful_bytes - offset);
                    assert(fh.Verify());
                    fh.Dump();
                    offset += fh.cost_bytes();
                }
                first_read = false;

                if (next_previous_tag_size) {
                    printf("previous tag size: %u\n", FlvTag::FetchPreviousTagSize(buff + offset, useful_bytes - offset));
                    offset += FlvTag::kPreviousTagSizeTypeLength;
                }
                else {
                    FlvTag ft(buff + offset, useful_bytes - offset);
                    ft.Dump();
                    offset += ft.cost_bytes();
                }
                next_previous_tag_size = !next_previous_tag_size;
            }
            catch (FlvException& e) {
                //cout << "FlvException catched, err:" << e.ErrorCode() << ", msg:" << e.msg() << endl;
                cout << e << endl;
                cout << "useful bytes: " << useful_bytes << ", offset: " << offset << endl;
                break;
            }
        }
        if (offset >= useful_bytes) {
            offset = 0;
        }

        //码率统计
        thisRecvedBytes += nRead;
        int64_t curr_time_us = FlvCommonUtils::GetCurrentTimeMillseconds();
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

