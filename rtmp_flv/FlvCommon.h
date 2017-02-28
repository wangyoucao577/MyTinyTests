
#ifndef FLV_COMMON_H_
#define FLV_COMMON_H_

#include <stdint.h>
#include <string>
#include <iostream>

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
    const std::string& msg(){return msg_;}
    const FlvErrorCode& error_code(){return error_code_;}

private:
    FlvErrorCode error_code_;
    std::string msg_;
};
std::ostream & operator << (std::ostream& out, FlvException& e);

class FlvCommonUtils {
public:
    static int64_t GetCurrentTimeMillseconds();
};


#endif
