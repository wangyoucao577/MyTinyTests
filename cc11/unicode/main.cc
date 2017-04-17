
#include "comm_include.h"

#ifdef _MSC_VER //G++居然还没有提供这几个接口..
//TODO: 接口完善, 及异常处理
void C11_ConvertUTF16ToMBCS(const u16string& src, string& dst) {

    //C Style UTF16->MBCS

    //TODO: set locale

    mbstate_t ps{ 0 };
    for (auto& i : src)
    {
        char tmp[8] = { 0 };
        int ret = c16rtomb(tmp, i, &ps);
        if (-1 == ret) {
            cout << "c16rtomb failed, errno " << errno << endl;
            throw "convert failed";
        }
        dst += tmp;
        //cout << ret << ", " << mbcs << ", " << ps._Wchar << ", " << ps._Byte << ", " << ps._State << endl;
    }
    cout << dst << endl;
}

void C11_ConvertMBCSToUTF16(const string& src, u16string& dst) {

    //C Style MBCS->UTF16

    int src_bytes = src.size();
    const char* psrc = src.c_str();

    mbstate_t ps{ 0 };
    int offset = 0;
    while (offset < src_bytes) {
        char16_t tmp[128] = { 0 };
        int ret = mbrtoc16(tmp, psrc + offset, src_bytes - offset, &ps);
        if (ret <= 0) {
            cout << "c16rtomb failed, errno " << errno << endl;
            throw "convert failed";
        }
        dst += tmp;
        offset += ret;
        //cout << ret << ", " << mbcs << ", " << ps._Wchar << ", " << ps._Byte << ", " << ps._State << endl;
    }
}
#endif

void CheckCodecvtSupport(const locale& lc) {
    
    bool can_cvt = has_facet<codecvt<wchar_t, char, mbstate_t>>(lc);
    if (!can_cvt) {
        cout << "Do not support char-wchar_t facet!" << endl;
    }
    else {
        cout << "Support char-wchar_t facet" << endl;
    }

    can_cvt = has_facet<codecvt<char, char, mbstate_t>>(lc);
    if (!can_cvt) {
        cout << "Do not support char-char facet!" << endl;
    }
    else {
        cout << "Support char-char facet" << endl;
    }

#if !defined(_MSC_VER)
    can_cvt = has_facet<codecvt<char16_t, char, mbstate_t>>(lc);
    if (!can_cvt) {
        cout << "Do not support char-char16_t facet!" << endl;
    }
    else {
        cout << "Support char-char16_t facet" << endl;
    }

    can_cvt = has_facet<codecvt<char32_t, char, mbstate_t>>(lc);
    if (!can_cvt) {
        cout << "Do not support char-char32_t facet!" << endl;
    }
    else {
        cout << "Support char-char32_t facet" << endl;
    }
#endif
}

void TestCase1() {
    ENTER_FUNC;
    char utf8[] = u8"\u4F60\u597D\u554A";   //与utf8_2中的表述是等价的, 只是用utf-16的方式来描述中文字
    //char utf8_2[] = u8"你好啊";
    char16_t utf16[] = u"hello";
    char32_t utf32[] = U"hello equals \u4F60\u597D\u554A";

    cout << utf8 << ", sizeof: " << sizeof(utf8) << endl;
    //cout << utf8_2 << ", sizeof: " << sizeof(utf8_2) << endl;
    cout << utf16 << ", sizeof: " << sizeof(utf16) << endl;
    cout << utf32 << ", sizeof: " << sizeof(utf32) << endl;

#ifdef _MSC_VER
    //C11 style 的转换接口
    u16string u16src(utf16);
    string out;
    C11_ConvertUTF16ToMBCS(u16src, out);
    u16string u16out;
    C11_ConvertMBCSToUTF16(out, u16out);
    assert(u16src == u16out);
#endif

    //C++11 style 的转换接口
    locale lc;
    locale::global(lc);
    cout << "current locale: " << lc.name() << endl;
#if !defined(_MSC_VER)
    lc = locale("en_US.UTF-8");
#endif
    CheckCodecvtSupport(lc);

    //TODO: C++11 style 的接口示例, 需要系统性地梳理清楚

    EXIT_FUNC;
}


int main() {

    TestCase1();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
    return 0;
}