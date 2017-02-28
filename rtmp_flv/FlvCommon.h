
#ifndef FLV_COMMON_H_
#define FLV_COMMON_H_

#include <stdint.h>
#include <string>

enum FlvErrorCode {
    kFlvErrorOK = 0,

    kFlvErrorNotImplemented,
    kFlvErrorBufferEmptyOrTooLessData,
    kFlvErrorTagTypeInvalid,

};

class FlvException{
public:
    explicit FlvException(FlvErrorCode err, std::string msg):error_code_(err), msg_(msg){}

public:
    std::string msg(){return msg_;}
    FlvErrorCode ErrorCode(){return error_code_;}

private:
    FlvErrorCode error_code_;
    std::string msg_;
};

#endif
