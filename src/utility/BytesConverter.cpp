#include "BytesConverter.h"

using namespace utility;
using namespace std;

std::vector<uint8_t> BytesConverter::fromUINT16toVectorOfUINT8(uint16_t number)
{
    vector<uint8_t > vec;

    vec.push_back(static_cast<uint8_t >(static_cast<int8_t >((number >> 8) & 0x00FF)));
    vec.push_back(static_cast<uint8_t >(static_cast<int8_t >((number) & 0x00FF)));

    return vec;
}

uint16_t BytesConverter::fromVectorOfUINT8toUINT16(vector<uint8_t> vec)
{
    uint16_t number;

    number = static_cast<uint16_t>(static_cast<int16_t >(vec[0] << 8) & 0xFF00);
    number = number | static_cast<uint16_t>(static_cast<int16_t >(vec[1]) & 0x00FF);

    return number;
}

std::vector<uint8_t> BytesConverter::fromUINT32toVectorOfUINT8(uint32_t number)
{
    vector<uint8_t > vec;


    return vec;;
}

uint32_t BytesConverter::fromVectorOfUINT8toUINT32(vector<uint8_t> vec)
{
    uint32_t number;

    return number;
}

std::vector<uint8_t> BytesConverter::fromUINT64toVectorOfUINT8(uint64_t number)
{
    vector<uint8_t> vec;

    return vec;
}

uint64_t BytesConverter::fromVectorOfUINT8toUINT64(vector<uint8_t> vec)
{
    uint64_t number;

    return number;
}


