
#ifndef FLV_TAG_HEADER_H_
#define FLV_TAG_HEADER_H_

#include "FlvCommon.h"

class FlvTagHeader : public FlvBase
{
public:
    virtual ~FlvTagHeader(){}
    virtual void Dump() = 0;
};

enum FlvFrameType { //4bits
    kFlvFrameTypeKeyFrame = 1,
    kFlvFrameTypeInterFrame = 2,
    kFlvFrameTypeDisposableInterFrame = 3,
    kFlvFrameTypeGeneratedKeyFrame = 4,
    kFlvFrameTypeVideoInfoOrCommandFrame = 5,
};

enum FlvCodecID { //4bits
    kFlvCodecIDSorensonH263 = 2,
    kFlvCodecIDScreenVideo = 3,
    kFlvCodecIDOn2VP6 = 4,
    kFlvCodecIDOn2VP6WithAlphaChannel = 5,
    kFlvCodecIDScreenVideoVersion2 = 6,
    kFlvCodecIDAVC = 7,
};

enum FlvAVCPacketType { //8bits
    kFlvAVCPacketTypeAVCSequenceHeader = 0,
    kFlvAVCPacketTypeAVCNALU = 1,
    kFlvAVCPakcetTypeAVCEndOfSequence = 2,
};

class FlvVideoTagHeader : public FlvTagHeader {
public:
    explicit FlvVideoTagHeader(char* buff, int len);
    virtual void Dump() override;

public:
    FlvFrameType GetFrameType();
    FlvCodecID GetCodecID();
    FlvAVCPacketType GetAVCPacketType();
    int composition_time();

private:
    uint8_t frame_type_;
    uint8_t codec_id_;
    uint8_t avc_packet_type_;
    int composition_time_{ 0 };

private:
    const static int kMinLength{ 1 };   //1Byte
    const static int kAVCPacketTypeLength{ 1 };//1Byte
    const static int kCompositionTimeLength{ 3 };   //3Bytes
};


enum FlvSoundFormat {  //4bits in the FLV standard
    kFlvSoundFormatLinearPCMPlatformEndian = 0,
    kFlvSoundFormatADPCM = 1,
    kFlvSoundFormatMP3 = 2,
    kFlvSoundFormatLinearPCMLittleEndian = 3,
    kFlvSoundFormatNellymoser16KHzMono = 4,
    kFlvSoundFormatNellymoser8KHzMono = 5,
    kFlvSoundFormatNellymoser = 6,
    kFlvSoundFormatG711AlawLogarithmicPCM = 7,
    kFlvSoundFormatG711MulawLogarithmicPCM = 8,
    kFlvSoundFormatReserved = 9,    //reserved
    kFlvSoundFormatAAC = 10,
    kFlvSoundFormatSpeex = 11,
    kFlvSoundFormatReserved_12 = 12,    //reserved
    kFlvSoundFormatReserved_13 = 13,    //reserved
    kSoundFormatMP3_8KHz = 14,
    kSoundFormatDeviceSpecificSound = 15,
};

enum FlvSoundRate { //2bits
    kFlvSoundRate_5Dot5KHz = 0, //5.5KHz
    kFlvSoundRate_11KHz = 1,
    kFlvSoundRate_22KHz = 2,
    kFlvSoundRate_44KHz = 3,
};

enum FlvSoundSize { //1bit
    kFlvSoundSize_8bitSamples = 0,
    kFlvSoundSize_16bitSamples = 1,
};

enum FlvSoundType { //1bit
    kFlvSoundTypeMono = 0,
    kFlvSoundTypeStereo = 1,
};

enum FlvAACPacketType { //8bits
    kFlvAACPacketTypeSequenceHeader = 0,
    kFlvAACPacketTypeRaw = 1,
};

class FlvAudioTagHeader : public FlvTagHeader {
public:
    explicit FlvAudioTagHeader(char* buff, int len);

    virtual void Dump() override;

public:
    FlvSoundFormat GetSoundFormat();
    FlvSoundRate GetSoundRate();
    FlvSoundSize GetSoundSize();
    FlvSoundType GetSoundType();
    FlvAACPacketType GetAACPacketType();

private:
    uint8_t sound_format_;
    uint8_t sound_rate_;
    uint8_t sound_size_;
    uint8_t sound_type_;
    uint8_t aac_packet_type_{0};

private:
    const static int kMinLength = 1;    //1Byte
    const static int kAACPacketTypeLength = 1;  //1Byte
};

#endif