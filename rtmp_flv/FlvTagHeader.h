
#ifndef FLV_TAG_HEADER_H_
#define FLV_TAG_HEADER_H_

#include "FlvCommon.h"

class FlvTagHeader : public FlvBase
{
public:
    virtual ~FlvTagHeader(){}
};

class FlvVideoTagHeader : public FlvTagHeader {
public:
    explicit FlvVideoTagHeader(char* buff, int len){}
};

class FlvAudioTagHeader : public FlvTagHeader {
public:
    explicit FlvAudioTagHeader(char* buff, int len) {}
};

#endif