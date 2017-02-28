
#ifndef FLV_COMMON_H_
#define FLV_COMMON_H_

#include <stdint.h>
#include <string>

enum FlvErrorCode{
    kFlvErrorOK = 0,

    kFlvErrorNotImplemented,
    kFlvErrorBufferEmptyOrTooLessData,
    kFlvErrorTagTypeInvalid,

}

class FlvException{
public:
    std::string explicit FlvException(FlvErrorCode err, std::string msg);

public:
    string msg(){return msg_;}
    FlvErrorCode ErrorCode(){return error_code_;}

private:
    FlvErrorCode error_code_;
    string msg_;
}

#endif