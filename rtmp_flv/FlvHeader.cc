
#include <assert.h>
#include <string.h>
#include <arpa/inet.h>

#include <iostream>
#include <typeinfo>

#include "FlvHeader.h"

FlvHeader::FlvHeader(char* buff, int len){
    if (NULL == buff || len < kFlvHeaderLength) {
        throw FlvException(kFlvErrorBufferEmptyOrTooLessData, "Don't have enough data to construct FlvHeader.");
    }

    signature_f_ = buff[0];
    signature_l_ = buff[1];
    signature_v_ = buff[2];
    version_ = buff[3];
    type_flags_reserved_5_ = 0;
    type_flags_audio_ = (buff[4] & 0x4) >> 2;   //reference the standard
    type_flags_reserved_1_ = 0;
    type_flags_video_ = buff[4] & 0x1;   //reference the standard

    memcpy(&data_offset_, buff + 5, sizeof(data_offset_));
    data_offset_ = ntohl(data_offset_);

    cost_bytes_ = kFlvHeaderLength;
}

bool FlvHeader::Verify(){
    if (    signature_f_ == 'F'
        &&  signature_l_ == 'L'
        &&  signature_v_ == 'V'
        &&  data_offset_ == kFlvHeaderLength){
        return true;
    }
    return false;
}

void FlvHeader::Dump(){
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(kFlvHeaderLength) << ": " << kFlvHeaderLength << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(signature_f_) << ": " << signature_f_ << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(signature_l_) << ": " << signature_l_ << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(signature_v_) << ": " << signature_v_ << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(version_) << ": " << static_cast<int>(version_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(type_flags_reserved_5_) << ": " << static_cast<int>(type_flags_reserved_5_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(type_flags_audio_) << ": " << static_cast<int>(type_flags_audio_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(type_flags_reserved_1_) << ": " << static_cast<int>(type_flags_reserved_1_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(type_flags_video_) << ": " << static_cast<int>(type_flags_video_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(data_offset_) << ": " << static_cast<int>(data_offset_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(cost_bytes_) << ": " << cost_bytes_ << std::endl;

}

bool FlvHeader::VideoExist(){
    if (1 == type_flags_video_){
        return true;
    }
    return false;
}
bool FlvHeader::AudioExist(){
    if (1 == type_flags_audio_){
        return true;
    }
    return false;
}
