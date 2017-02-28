
#include <assert.h>
#include <string.h>
#include <arpa/inet.h>

#include <iostream>
#include <typeinfo>

#include "FlvTag.h"
#include "FlvCommon.h"

FlvTag::FlvTag(char* buff, int len){
    if (NULL == buff || len < kMinTagLength) {
        throw FlvException(kFlvErrorBufferEmptyOrTooLessData, "Don't have enough data to construct FlvTag.");
    }

    filter_ = buff[0] & 0x20;

    //TODO: 暂未支持Encryption和FilterParams
    if (0 != filter_) {
        throw FlvException(kFlvErrorNotImplemented, "EncryptionHeader and FilterParam are not implemented.");
    }

    tag_type_ = buff[0] & 0x1F;
    if (kFlyTagTypeAudio != (FlvTagType)tag_type_
        && kFlyTagTypeVideo != (FlvTagType)tag_type_
        && kFlyTagTypeScriptData != (FlvTagType)tag_type_) {
        throw FlvException(kFlvErrorTagTypeInvalid, "Unknown TagType Value: " + std::to_string(tag_type_));
    }

    data_size_ = ((buff[1] & 0xFF) << 16) | ((buff[2] & 0xFF) << 8) | (buff[3] & 0xFF);
    
    memcpy(&timestamp_, buff + 4, sizeof(timestamp_));
    timestamp_ = ntohl(timestamp_);

    stream_id_ = ((buff[8] & 0xFF) << 16) | ((buff[9] & 0xFF) << 8) | (buff[10] & 0xFF);   //always 0

    //TODO: construct audio/video/script_data
    if ((FlvTagType)tag_type_ == kFlyTagTypeAudio){

    }else if ((FlvTagType)tag_type_ == kFlyTagTypeVideo){

    }else{  //script data

    }
}

FlvTag::~FlvTag(){

    if (tag_header_){
        delete tag_header_;
        tag_header_ = nullptr;
    }
    if (tag_data_){
        delete tag_data_;
        tag_data_ = nullptr;
    }
}

void FlvTag::Dump()
{
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(filter_) << ": " << static_cast<int>(filter_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(tag_type_) << ": " << static_cast<int>(tag_type_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(data_size_) << ": " << data_size_ << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(timestamp_) << ": " << timestamp_ << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(stream_id_) << ": " << stream_id_ << std::endl;
}

uint32_t FlvTag::FetchPreviousTagSize(char * buff, int len){
    if (NULL == buff || len < kPreviousTagSizeTypeLength) {
        throw FlvException(kFlvErrorBufferEmptyOrTooLessData, "Don't have enough data to FetchPreviousTagSize.");
    }

    uint32_t size;
    memcpy(&size, buff, sizeof(size));
    size = ntohl(size);
    return size;
}