
#include <typeinfo>

#include "FlvTagHeader.h"

FlvAudioTagHeader::FlvAudioTagHeader(char* buff, int len)
{
    if (NULL == buff || len < kMinLength) {
        throw FlvException(kFlvErrorBufferEmptyOrTooLessData, "Don't have enough data to construct FlvAudioTagHeader.");
    }

    sound_format_ = (buff[0] & 0xF0) >> 4;
    sound_rate_ = (buff[0] & 0xC) >> 2;
    sound_size_ = (buff[0] & 0x2) >> 1;
    sound_type_ = (buff[0] & 0x1);
    cost_bytes_ += kMinLength;

    if (sound_format_ == static_cast<int>(kFlvSoundFormatAAC)) {
        if (len < kMinLength + kAACPacketTypeLength) {
            throw FlvException(kFlvErrorBufferEmptyOrTooLessData, "Don't have enough data to construct AACPacketType in FlvAudioTagHeader.");
        }
        aac_packet_type_ = buff[1] & 0xFF;
        cost_bytes_ += kAACPacketTypeLength;
    }

    //TODO: verify whether values valid
}

FlvSoundFormat FlvAudioTagHeader::GetSoundFormat() {
    return static_cast<FlvSoundFormat>(sound_format_);
}
FlvSoundRate FlvAudioTagHeader::GetSoundRate() {
    return static_cast<FlvSoundRate>(sound_rate_);
}
FlvSoundSize FlvAudioTagHeader::GetSoundSize() {
    return static_cast<FlvSoundSize>(sound_size_);
}
FlvSoundType FlvAudioTagHeader::GetSoundType() {
    return static_cast<FlvSoundType>(sound_type_);
}
FlvAACPacketType FlvAudioTagHeader::GetAACPacketType() {
    return static_cast<FlvAACPacketType>(aac_packet_type_);
}

void FlvAudioTagHeader::Dump() {
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(sound_format_) << ": " << static_cast<int>(sound_format_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(sound_rate_) << ": " << static_cast<int>(sound_rate_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(sound_size_) << ": " << static_cast<int>(sound_size_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(sound_type_) << ": " << static_cast<int>(sound_type_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(aac_packet_type_) << ": " << static_cast<int>(aac_packet_type_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(cost_bytes_) << ": " << cost_bytes_ << std::endl;

}

FlvVideoTagHeader::FlvVideoTagHeader(char* buff, int len) {
    if (NULL == buff || len < kMinLength) {
        throw FlvException(kFlvErrorBufferEmptyOrTooLessData, "Don't have enough data to construct FlvVideoTagHeader.");
    }

    frame_type_ = (buff[0] & 0xF0) >> 4;
    codec_id_ = (buff[0] & 0xF);
    cost_bytes_ += kMinLength;

    if (codec_id_ == static_cast<int>(kFlvCodecIDAVC)) {
        if (len < kMinLength + kAVCPacketTypeLength + kCompositionTimeLength) {
            throw FlvException(kFlvErrorBufferEmptyOrTooLessData, "Don't have enough data to construct AACPacketType in FlvVideoTagHeader.");
        }
        avc_packet_type_ = buff[1];
        composition_time_ = ((buff[2] & 0xFF) << 16) | ((buff[3] & 0xFF) << 8) | (buff[4] & 0xFF);
        cost_bytes_ += (kAVCPacketTypeLength + kCompositionTimeLength);
    }

    //TODO: verify whether values valid
}

FlvFrameType FlvVideoTagHeader::GetFrameType() {
    return static_cast<FlvFrameType>(frame_type_);
}
FlvCodecID FlvVideoTagHeader::GetCodecID() {
    return static_cast<FlvCodecID>(codec_id_);
}
FlvAVCPacketType FlvVideoTagHeader::GetAVCPacketType() {
    return static_cast<FlvAVCPacketType>(avc_packet_type_);
}
int FlvVideoTagHeader::composition_time() {
    return composition_time_;
}

void FlvVideoTagHeader::Dump() {
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(frame_type_) << ": " << static_cast<int>(frame_type_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(codec_id_) << ": " << static_cast<int>(codec_id_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(avc_packet_type_) << ": " << static_cast<int>(avc_packet_type_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(composition_time_) << ": " << static_cast<int>(composition_time_) << std::endl;
    std::cout << "<" << typeid(*this).name() << "::" << __func__ << "> " << FLV_VNAME(cost_bytes_) << ": " << static_cast<int>(cost_bytes_) << std::endl;
}