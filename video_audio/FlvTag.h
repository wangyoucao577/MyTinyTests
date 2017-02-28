
#ifndef FLV_TAG_H_
#define FLV_TAG_H_

#include <stdint.h>

class FlvTagHeader{};

class FlvTag{
public:
    explicit FlvTag(char* buff, int len);

public:
    void Dump();

    const static int kMinTagLength {11};    //until StreamID 
public:
    static uint32_t FetchPreviousTagSize(char * buff, int len);
    const static int kPreviousTagSizeTypeLength {4};

private:
    uint8_t reserved_ : 2;
    uint8_t filter_ : 1;
    uint8_t tag_type_ : 5;
    uint32_t data_size_;
    uint32_t timestamp_;
    uint32_t stream_id_;
    FlvTagHeader * tag_header_ {nullptr};
};

#endif