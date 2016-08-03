
#include <stdio.h>
#include "json/json.h"

using namespace std;

void unserialize_sample_1()
{
    printf("Enter %s.\n", __FUNCTION__);

    Json::Reader json_reader;
    Json::Value root_value;

    string strValue = "{\"key1\":\"value\", \"array\":[{\"key2\":\"value2\"}, {\"key2\":\"value3\"}, {\"key2\":\"value4\"}]}";
    if (json_reader.parse(strValue, root_value)) {
        printf("key1-->%s.\n", root_value["key1"].asCString());

        Json::Value array_value = root_value["array"];
        printf("array--->");
        for (int i = 0; i < (int)array_value.size(); ++i)
        {
            printf("%s", (array_value[i])["key2"].asCString());
            if (i + 1 == array_value.size()) {
                printf("\n");
            }
            else {
                printf(", ");
            }
        }

    }
    else {
        printf("Json parse failed, original string:\n%s\n\nError message:%s\n",
            strValue.c_str(), json_reader.getFormattedErrorMessages().c_str());
    }

    printf("\n\n");
}

void unserialize_sample_2()
{
    printf("Enter %s.\n", __FUNCTION__);

    string strValue = "{ \"encoding\" : \"UTF-8\", \
\"plug-ins\" : [\"python\",\"c++\",\"ruby\"], \
\"indent\" : { \"length\" : 3, \"use_space\" : true }}";

    Json::Reader json_reader;
    Json::Value root_value;

    if (json_reader.parse(strValue, root_value)) {
        printf("encoding:%s.\n", root_value["encoding"].asCString());
        Json::Value plug_ins = root_value["plug-ins"];
        for (int i = 0; i < (int)plug_ins.size(); ++i)
        {
            printf("%s ", plug_ins[i].asCString());
        }
        printf("\n");
        Json::Value indent_value = root_value["indent"];
        printf("indent len:%d, use_space:%s.\n", indent_value["length"].asInt(), indent_value["use_space"].asBool() == true ? "true" : "false");
        
        //deal with exceptions
        if (root_value["test_key"].empty()) {
            printf("No \"test_key\" in this json.\n");
        }
        else {
            printf("ERROR: parse \"test_key\" failed.\n");
        }

        if (root_value["length"].empty()) {
            printf("No \"length\" in this json root.\n");
        }
        else {
            printf("ERROR: parse \"length\" failed.\n");
        }

        Json::Value test_key_value = root_value.get("test_key", (Json::Value)"Nothing").asString();
        printf("Get test_key return %s.\n", test_key_value.asCString());
        
        
    }
    else {
        printf("Json parse failed, original string:\n%s\n\nError message:%s\n", 
            strValue.c_str(), json_reader.getFormattedErrorMessages().c_str());
    }

    printf("\n\n");
}

void serialize_sample_1()
{
    printf("Enter %s.\n", __FUNCTION__);

    Json::Value root_value;
    Json::Value plug_ins_value;
    Json::Value indent_value;
    
    root_value["encoding"] = "UTF-8";

    plug_ins_value.append("Python");
    plug_ins_value.append("C++");
    plug_ins_value.append("Java");
    root_value["plug-ins"] = plug_ins_value;

    indent_value["lentgh"] = 3;
    indent_value["use_space"] = true;
    root_value["indent"] = indent_value;

    printf("%s\n\n", root_value.toStyledString().c_str());
    printf("\n\n");
}

void serialize_sample_2(char * buff, int buff_len)
{
    printf("Enter %s.\n", __FUNCTION__);

    Json::Value root_value;
    Json::Value header_value;
    Json::Value body_value;
    Json::Value source_info;
    Json::Value extraAttribute;

    header_value["requestID"] = "dddddddddddddddddddd";
    header_value["requestTime"] = "20160801 12-12-12";
    root_value["header"] = header_value;

    body_value["requestID"] = "bbbbbbbbbbbbbbbbbb";
    body_value["requestTime"] = "20160801 12-12-22";
    root_value["bodyInfo"] = body_value;

    extraAttribute["Name"] = "status";
    extraAttribute["Value"] = "0";
    root_value["ExtraAttribute"] = extraAttribute;

    source_info["hostName"] = "127.0.0.1";
    source_info["subSystem"] = "Cogent";
    root_value["sourceInfo"] = source_info;

    printf("%s\n\n", root_value.toStyledString().c_str());
    if (NULL != buff) {
        sprintf_s(buff, buff_len, "%s", root_value.toStyledString().c_str());
    }
    printf("\n\n");
}

void json_samples()
{
    printf("Enter %s.\n\n", __FUNCTION__);

    unserialize_sample_1();
    unserialize_sample_2();
    serialize_sample_1();
    serialize_sample_2(NULL, 0);

    printf("Exit %s.\n\n", __FUNCTION__);
}

