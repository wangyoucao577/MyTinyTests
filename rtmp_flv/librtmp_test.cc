

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <librtmp/rtmp.h>

using namespace std;

#include "FlvHeader.h"
#include "FlvTag.h"
#include "FlvCommon.h"

#define DUMP_FLV_FILE
#define DUMP_ES_FILE


int main(int argc, char* argv[]){
    if (argc < 2){
        cout << "Usage:" << endl;
        cout << "librtmp_test <rtmp_url>" << endl;
        return 0;
    }

#ifdef DUMP_FLV_FILE
    FILE *fp = fopen("rtmp.flv", "wb");
    if (!fp){
        cout << "Open file rtmp.flv failed" << endl;
        return -1;
    }
#endif
#ifdef DUMP_ES_FILE
    FILE *fp_es = fopen("video_audio.es", "wb");
    if (!fp_es) {
        cout << "Open file video_audio_es failed" << endl;
        return -1;
    }
#endif


    RTMP* rtmp = RTMP_Alloc();
    RTMP_Init(rtmp);
    rtmp->Link.timeout = 10;

    if (!RTMP_SetupURL(rtmp, argv[1])){
        cout << "SetupURL error" << endl;
        RTMP_Free(rtmp);
        return -1;
    }
    rtmp->Link.lFlags |= RTMP_LF_LIVE;
    RTMP_SetBufferMS(rtmp, 3600*1000);  //1hour

    if (!RTMP_Connect(rtmp, NULL)){
        cout << "RTMP_Connect error" << endl;;
        RTMP_Free(rtmp);
        return -1;
    }

    if (!RTMP_ConnectStream(rtmp, 0)){
        cout << "RTMP_ConnectStream error" << endl;
        RTMP_Close(rtmp);
        RTMP_Free(rtmp);
        return -1;
    }

    unsigned long long thisRecvedBytes = 0;
    int buff_size = 5*1000*1000;//5MB
    char* buff = new char[buff_size];
    memset(buff, 0, buff_size);
    

    int64_t start_time_us = FlvCommonUtils::GetCurrentTimeMillseconds();
    int nRead = 0;
    bool first_read = true;
    int offset = 0;
    bool next_previous_tag_size = true;
    while (nRead = RTMP_Read(rtmp, buff + offset, buff_size - offset)){
        cout << "this recv bytes: " << nRead <<  endl;

#ifdef DUMP_FLV_FILE
        //FLV写文件
        int nWrite = fwrite(buff + offset, 1, nRead, fp);
        assert(nWrite == nRead);
#endif

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
                    cout << "previous tag size: " << FlvTag::FetchPreviousTagSize(buff + offset, useful_bytes - offset) << endl;
                    offset += FlvTag::kPreviousTagSizeTypeLength;
                }
                else {
                    FlvTag ft(buff + offset, useful_bytes - offset);
                    ft.Dump();

                    if (ft.GetTagType() == kFlyTagTypeAudio) {

#ifdef DUMP_ES_FILE
                        //write ES
                        //TODO: write的ES文件是否正确?? 待验证
                        int es_write = fwrite(ft.GetDataPointer(), 1, ft.GetTagDataLength(), fp_es);
                        assert(es_write == ft.GetTagDataLength());
#endif

                    }

                    offset += ft.cost_bytes();  //for header
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
            cout << "[rtmp recv kbps:" << thisRecvedBytes * 8 * 1000 / delta_us << "]" << endl;
            start_time_us = curr_time_us;
            thisRecvedBytes = 0;
        }
        
    }

#ifdef DUMP_FLV_FILE
    if (fp){
        fclose(fp);
    }
#endif
#ifdef DUMP_ES_FILE
    if (fp_es) {
        fclose(fp_es);
    }
#endif

    if (buff){
        delete[] buff;
        buff = nullptr;
    }

    if (rtmp){
        RTMP_Close(rtmp);
        RTMP_Free(rtmp);
    }

    return 0;
}

