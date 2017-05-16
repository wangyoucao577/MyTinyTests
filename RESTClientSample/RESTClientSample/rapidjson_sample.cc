
#include <stdio.h>
#include <assert.h>
#include "json_samples.h"
#include "rapidjson\document.h"

using namespace rapidjson;

void rapid_unserialize_sample_1() {

    const char * str = "{    \"hello\": \"world\",    \"t\": true ,   \"f\": false, \"n\": null,\"i\": 123, \"pi\": 3.1416,\"a\": [1, 2, 3, 4]}";
    Document doc;
    doc.Parse(str);

    assert(doc.HasMember("hello"));
    assert(doc["hello"].IsString());
    printf("hello = %s\n", doc["hello"].GetString());
    
    assert(doc["t"].IsBool() && doc["t"].IsBool());
    printf("t = %s\n", doc["t"].GetBool() ? "true" : "false");
    printf("f = %s\n", doc["f"].GetBool() ? "true" : "false");

    assert(doc["i"].IsInt());
    assert(doc["i"].IsInt64());
    assert(doc["i"].IsNumber());
    printf("i = %d %lld\n", doc["i"].GetInt(), doc["i"].GetInt64());

    assert(doc["n"].IsNull());

    assert(doc["pi"].IsDouble());
    printf("pi = %f\n", doc["pi"].GetDouble());

    assert(doc["a"].IsArray());
    const Value& arr = doc["a"];
    printf("arr is %s empty, capacity %d\n", arr.Empty() ? "" : "not", arr.Capacity());
    for (SizeType i = 0; i < arr.Size(); ++i) {
        printf("a[%d] = %d\n", i, arr[i].GetInt());
    }
    for (auto& v : arr.GetArray()) {    //c++11 style
        printf("a next = %d\n", v.GetInt());
    }
    
    // 直接迭代整个json DOM
    for (Value::ConstMemberIterator it = doc.MemberBegin(); it != doc.MemberEnd(); ++it)
    {
        printf("type of member %s is %d\n", it->name.GetString(), it->value.GetType());
    }
    for (auto& m : doc.GetObject()) {   //c++11 style
        printf("type of member %s is %d\n", m.name.GetString(), m.value.GetType());
    }


    //modify 
    doc["hello"].SetString(" not world");
    printf("hello = %s\n", doc["hello"].GetString());

    Document::AllocatorType& allocator = doc.GetAllocator();
    doc["a"].PushBack(6, allocator);
    // fluent interface
    doc["a"].PushBack("120", allocator).PushBack(Value(doc["hello"].GetString(), allocator).Move(), allocator);

    for (auto& v : doc["a"].GetArray()) {    //c++11 style
        if (v.IsInt()) {
            printf("a next = %d\n", v.GetInt());
        }
        else if (v.IsString()) {
            printf("a next = %s\n", v.GetString());
        }
    }

    //add/remove members
    Value contact(kObjectType);
    contact.AddMember("name", "Milo", doc.GetAllocator());
    contact.AddMember("married", false, doc.GetAllocator());

    doc.AddMember("Contact sample", contact, doc.GetAllocator());
    doc.RemoveMember("t");
    printf("doc empty: %s\n", doc.ObjectEmpty() ? "true" : "false");
}




void rapidjson_sample() {

    rapid_unserialize_sample_1();
}