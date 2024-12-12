/**
 * @file parameterFolding.cpp
 * @author tanjiongyu
 * @brief 通过模板参数和折叠表达式，实现数据结构序列化字节流的编码解码。
 * @note g++ ./parameterFolding.cpp  -o ./parameterFolding -std=c++11
 * @version 0.1
 * @date 2024-12-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <memory>

#define PROTO_ERR(...) printf("[ERR] " __VA_ARGS__)
#define PROTO_INFO(...) printf("[INFO] " __VA_ARGS__)

#ifndef __cpp_lib_make_unique
#pragma message "std::make_unique is not defined, use myself std::make_unique."
namespace std
{
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
std::unique_ptr<T[]> make_unique(std::size_t size) {
    return std::unique_ptr<T[]>(new T[size]());
}

template <typename T, typename... Args>
void make_unique(T*, Args...) = delete;
} // namespace std
#endif

namespace Proto
{

struct BaseFmt
{
    BaseFmt(const std::string& name) : name_(name){}
    virtual int32_t decode(const std::vector<uint8_t>& data){return -1;}
    virtual int32_t decode(const std::vector<uint8_t>& data, 
                            const int32_t offset)
                            {return -1;}
    virtual int32_t encode(std::vector<uint8_t>& data){return -1;}
    std::string name() const
    {
        return name_;
    }
    void operator=(const BaseFmt& other)
    {
        name_ = other.name_;
    }
private:
    std::string name_;
};

template<typename T>
struct SysDataType : public BaseFmt
{
    SysDataType()
    : BaseFmt(typeid(T).name())
    {}

    SysDataType(T value)
    : value_(value)
    , BaseFmt(typeid(T).name())
    {}

    int32_t decode(const std::vector<uint8_t>& data, const int32_t offset) override
    {
        memcpy(&value_, data.data()+offset, sizeof(T));
        return (sizeof(T));
    }

    int32_t encode(std::vector<uint8_t>& data) override
    {
        std::vector<uint8_t> byte_array(sizeof(T));
        std::memcpy(byte_array.data(), &value_, sizeof(T));
        std::copy(byte_array.begin(), byte_array.end(), std::back_inserter(data));
        return sizeof(T);
    }

    void operator=(const T value)
    {
        value_ = value;
    }

    T value() const
    {
        return value_;
    }
private:
    T value_;
};

using U8 = SysDataType<uint8_t>;
using I8 = SysDataType<int8_t>;
using U16 = SysDataType<uint16_t>;
using I16 = SysDataType<int16_t>;
using U32 = SysDataType<uint32_t>;
using I32 = SysDataType<int32_t>;
using U64 = SysDataType<uint64_t>;
using I64 = SysDataType<int64_t>;
using Float = SysDataType<float>;
using Double = SysDataType<double>;

struct Sequence : public BaseFmt
{
    template<typename... Members>
    Sequence(const std::string& name, Members&&... members)
    : BaseFmt(name)
    , members_{std::forward<Members>(members)...}
    {}
    Sequence(const Sequence& other) = delete;
    Sequence(const Sequence&& other) = delete;
    Sequence& operator=(const Sequence&& other) = delete;

    Sequence& operator=(const Sequence& other) 
    {
        PROTO_INFO("%s operator=&\n", name().c_str());

        if (this == &other) return *this;

        auto it = members_.begin();
        auto it_other = other.members_.begin();
        while (it != members_.end())
        {
            // PROTO_ERR("%p %p\n", *it, *it_other);
            **it = **it_other;
            it++;
            it_other++;
        }
        return *this;
    }

    int32_t decode(const std::vector<uint8_t>& data, const int32_t offset_) override
    {
        int32_t offset = offset_;
        int32_t subOffset = 0;

        for(auto item : members_)
        {
            subOffset = item->decode(data, offset);
            if(subOffset < 0)
            {
                PROTO_ERR("%s decode failed: %d.", item->name().c_str(), subOffset);
                return subOffset;
            }
            // PROTO_ERR("subOffset %d\n", subOffset);
            offset += subOffset;
        }
        
        return (offset - offset_);
    }

    int32_t decode(const std::vector<uint8_t>& data) override
    {
        return decode(data, 0);
    }

    int32_t encode(std::vector<uint8_t>& data) override
    {
        int32_t len = 0;
        int32_t tmpLen = 0;

        for(auto item : members_)
        {
            tmpLen = item->encode(data);
            if(tmpLen < 0)
            {
                PROTO_ERR("%s encode failed: %d.", item->name().c_str(), tmpLen);
                return tmpLen;
            }
            // PROTO_ERR("tmpLen %d\n", tmpLen);
            len += tmpLen;
        }
        return len;
    }

    void echo()
    {
        for(auto iter : members_)
        {
            PROTO_INFO("%p\n", iter);
        }
    }
    std::list<BaseFmt*> members_;
};

template<typename T>
struct SequenceOf : public BaseFmt
{
    SequenceOf() : BaseFmt("SequenceOf")
    {
        container.clear();
    }

    int32_t decode(const std::vector<uint8_t>& data) override
    {
        // TODO
        return -1;
    }

    int32_t encode(std::vector<uint8_t>& data) override
    {
        int32_t len = 0;
        int32_t tmpLen = 0;

        // TODO: 编码长度

        for(auto& item : container)
        {
            tmpLen = item->encode(data);
            if(tmpLen < 0)
            {
                PROTO_ERR("%s encode failed: %d.", item->name().c_str(), tmpLen);
                return tmpLen;
            }
            len += tmpLen;
        }
        return len;
    }

    std::list<std::unique_ptr<T>>container;
};


} // namespace Proto

int main(int argc, char const *argv[])
{
    struct TestData : public Proto::Sequence{
        Proto::I32 a;
        Proto::Float b;
        Proto::Double c;
        TestData() : Proto::Sequence("TestData", &a, &b, &c){}
    };

    std::vector<uint8_t> encodeData;
    TestData testData;
    testData.a = 1;
    testData.b = 0.015;
    testData.c = 10.1;

    if(0 > testData.encode(encodeData))
    {
        PROTO_ERR("%s encode failed.", testData.name().c_str());
        return -1;
    }

    PROTO_INFO("encode:\n");
    for(auto i : encodeData)
    {
        printf("%02x ", i);
    }
    printf("\n");

    std::vector<uint8_t> decodeData = encodeData;
    TestData testData2;
    PROTO_INFO("testData2 type(%s)\n", testData2.name().c_str());
    if(0 > testData2.decode(decodeData))
    {
        PROTO_ERR("%s decode failed.", testData2.name().c_str());
        return -1;
    }

    auto _echoStruct = [](const TestData& _data)
    {
        PROTO_INFO("a %p type(%s) : %d\n", &(_data.a), _data.a.name().c_str(), _data.a.value());
        PROTO_INFO("b %p type(%s) : %f\n", &(_data.b), _data.b.name().c_str(), _data.b.value());
        PROTO_INFO("c %p type(%s) : %f\n", &(_data.c), _data.c.name().c_str(), _data.c.value());
    }; 

    PROTO_INFO("decode:\n");
    _echoStruct(testData2);
    testData2.echo();
 
    TestData testData3;
    testData3 = testData2;
    testData3.a = 2;
    testData3.c = 0.02;
    _echoStruct(testData3);
    testData3.echo();

    Proto::SequenceOf<TestData> testSequenceOf;
    {
        auto ptr = std::make_unique<TestData>();
        ptr->a = 3;
        ptr->b = 0.03;
        ptr->c = 0.003;
        testSequenceOf.container.emplace_back(std::move(ptr));
    }

    {
        auto ptr = std::make_unique<TestData>();
        ptr->a = 4;
        ptr->b = 0.04;
        ptr->c = 0.004;
        testSequenceOf.container.emplace_back(std::move(ptr));
    }

    auto _echoPtr = [](const TestData* pData)
    {
        PROTO_INFO("a %p type(%s) : %d\n", &(pData->a), pData->a.name().c_str(), pData->a.value());
        PROTO_INFO("b %p type(%s) : %f\n", &(pData->b), pData->b.name().c_str(), pData->b.value());
        PROTO_INFO("c %p type(%s) : %f\n", &(pData->c), pData->c.name().c_str(), pData->c.value());
    }; 

    for(auto& item : testSequenceOf.container)
    {
        PROTO_INFO("=========================\n");
        _echoPtr(item.get());
        item->echo();
    }

    return 0;
}
