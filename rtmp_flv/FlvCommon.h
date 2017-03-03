
#ifndef FLV_COMMON_H_
#define FLV_COMMON_H_

#include <stdint.h>
#include <string>
#include <iostream>

#define FLV_VNAME(name) (#name)

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

class FlvBase {
public:
    virtual ~FlvBase(){}
public:
    uint32_t cost_bytes() { return cost_bytes_; }

protected:
    uint32_t cost_bytes_{0};
};

class FlvCommonUtils {
public:
    static int64_t GetCurrentTimeMillseconds();
};


#endif
