
#ifndef FLV_TAG_H_
#define FLV_TAG_H_

#include "FlvCommon.h"
#include "FlvTagHeader.h"

class FlvTagData{};

enum FlvTagType{
    kFlyTagTypeAudio = 8,
    kFlyTagTypeVideo = 9,
    kFlyTagTypeScriptData = 18,
};

class FlvTag : public FlvBase{
public:
    explicit FlvTag(char* buff, int len);
    ~FlvTag();

public:
    void Dump();

    const static int kMinTagLength {11};    //until StreamID 
public:
    static uint32_t FetchPreviousTagSize(char * buff, int len);
    const static int kPreviousTagSizeTypeLength {4};

    FlvTagType GetTagType();
    char * GetDataPointer();
    int GetTagDataLength();

private:
    uint8_t reserved_ : 2;
    uint8_t filter_ : 1;
    uint8_t tag_type_ : 5;
    uint32_t data_size_;
    uint32_t timestamp_;
    uint32_t stream_id_;
    FlvTagHeader * tag_header_ {nullptr};
    FlvTagData * tag_data_ {nullptr};

    char * data_pointer_{ nullptr };
    int data_length_{ 0 };
};

#endif