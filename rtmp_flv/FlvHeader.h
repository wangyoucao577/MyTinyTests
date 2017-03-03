
#ifndef FLV_HEADER_H_
#define FLV_HEADER_H_

#include "FlvCommon.h"

class FlvHeader : public FlvBase {
public:
    explicit FlvHeader(char* buff, int len);

public:
    bool Verify();
    void Dump();

public:
    bool VideoExist();
    bool AudioExist();

public:
    const static int kFlvHeaderLength {9};

private:
    uint8_t signature_f_;
    uint8_t signature_l_;
    uint8_t signature_v_;
    uint8_t version_;
    uint8_t type_flags_reserved_5_ : 5;
    uint8_t type_flags_audio_ : 1;
    uint8_t type_flags_reserved_1_ : 1;
    uint8_t type_flags_video_ : 1;
    uint32_t data_offset_;
};

#endif
