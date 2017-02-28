

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <librtmp/rtmp.h>

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


    int nRead = 0;
    unsigned long long totalBytes = 0;
    while (nRead = RTMP_Read(rtmp, buff, buff_size)){
        int nWrite = fwrite(buff, 1, nRead, fp);
        assert(nWrite == nRead);

        totalBytes += nRead;
        printf("This Recv Bytes: %d, total: %llu\n", nRead, totalBytes);
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

