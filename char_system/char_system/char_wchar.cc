
#include <stdio.h>
#include <string.h>


#ifdef _MSC_VER
#include <windows.h>

static char * multi_bytes_to_allocated_utf8(char * multi_bytes)
{
    int len = MultiByteToWideChar(CP_ACP, 0, multi_bytes, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len];
    memset(wstr, 0, sizeof(wchar_t) * (len));
    MultiByteToWideChar(CP_ACP, 0, multi_bytes, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = (char*)malloc(len);
    memset(str, 0, len);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    if (wstr) {
        delete[] wstr;
    }
    return str;
}

static char * utf8_to_allocated_multi_bytes(char * utf8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len];
    memset(wstr, 0, sizeof(wchar_t) * (len));
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = (char*)malloc(len);
    memset(str, 0, len);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    if (wstr) {
        delete[] wstr;
    }
    return str;
}
#endif

int main()
{
    printf("sizeof(char):%d, sizeof(wchar_t):%d.\n", sizeof(char), sizeof(wchar_t));

    char * str = "中国abc";
    printf("[local]str->%s, strlen(str):%d.\n", str, strlen(str));

#ifdef _MSC_VER

    char* multi_bytes_str = utf8_to_allocated_multi_bytes(str);
    printf("[ mbsc]str->%s, strlen(str):%d.\n", multi_bytes_str, strlen(multi_bytes_str));

    char * utf8_str = multi_bytes_to_allocated_utf8(multi_bytes_str);
    printf("[utf-8]str->%s, strlen(str):%d.\n", utf8_str, strlen(utf8_str));

    free(utf8_str);
    free(multi_bytes_str);

    //wait before return
    printf("Please press any key to continue...");
    char a;
    scanf_s("%c", &a, (int)sizeof(a));
#endif
    return 0;
}


