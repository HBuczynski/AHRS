#ifndef AHRS_BLACK_BOX_BYTES_CONVERTER_H
#define AHRS_BLACK_BOX_BYTES_CONVERTER_H

#include <vector>
#include <cstdint>

namespace utility
{
    class BytesConverter
    {
        static std::vector<uint8_t> fromUINT16toVectorOfUINT8(uint16_t number);
        static uint16_t fromVectorOfUINT8toUINT16(std::vector<uint8_t> number);

        static std::vector<uint8_t> fromUINT32toVectorOfUINT8(uint32_t number);
        static uint32_t fromVectorOfUINT8toUINT32(std::vector<uint8_t> number);

        static std::vector<uint8_t> fromUINT64toVectorOfUINT8(uint64_t number);
        static uint64_t fromVectorOfUINT8toUINT64(std::vector<uint8_t> number);
    };
}
#endif
