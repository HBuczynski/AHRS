#include "BytesConverter.h"

using namespace utility;
using namespace std;

void BytesConverter::appendUINT16toVectorOfUINT8(uint16_t number, std::vector<uint8_t> &vec)
{
    vec.push_back(static_cast<uint8_t >(static_cast<int8_t >((number >> 8) & 0x00FF)));
    vec.push_back(static_cast<uint8_t >(static_cast<int8_t >((number) & 0x00FF)));
}

uint16_t BytesConverter::fromVectorOfUINT8toUINT16(const std::vector<uint8_t> &vec, uint16_t variablePosition)
{
    uint16_t number;

    number = static_cast<uint16_t>(static_cast<int16_t >(vec[variablePosition]) << 8);
    number = number | static_cast<uint16_t>(static_cast<int16_t >(vec[++variablePosition]));

    return number;
}

void BytesConverter::appendUINT32toVectorOfUINT8(uint32_t number, std::vector<uint8_t> &vec)
{
    for(int i=24; i >=0; i=i-8)
    {
        vec.push_back(static_cast<uint8_t >(static_cast<int8_t >((number >> i))));
    }
}

uint32_t BytesConverter::fromVectorOfUINT8toUINT32(const std::vector<uint8_t> &vec, uint16_t variablePosition)
{
    uint32_t number = 0;

    for(int i=24; i >=0; i=i-8)
    {
        number = number | static_cast<uint32_t>(static_cast<int32_t >(vec[variablePosition++]) << i);
    }

    return number;
}

void BytesConverter::appendUINT64toVectorOfUINT8(uint64_t number, std::vector<uint8_t> &vec)
{
    for(int i=56; i >=0; i=i-8)
    {
        vec.push_back(static_cast<uint8_t >(static_cast<int8_t >((number >> i))));
    }
}

uint64_t BytesConverter::fromVectorOfUINT8toUINT64(const std::vector<uint8_t> &vec, uint16_t variablePosition)
{
    uint64_t number = 0;

    for(int i=56; i >=0; i=i-8)
    {
        number = number | static_cast<uint64_t>(static_cast<int64_t >(vec[variablePosition++]) << i);
    }

    return number;
}
