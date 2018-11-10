#ifndef AHRS_CHECKSUM_H
#define AHRS_CHECKSUM_H

#include <vector>
#include <cstdint>

namespace utility
{
    class Checksum
    {
    public:
        static uint8_t parityBit(const std::vector<uint8_t>& frame);
        static uint32_t crc32(const std::vector<uint8_t>& frame);

    private:
        static uint8_t parityInUInt8_t(uint8_t value, uint8_t size);

        static const uint8_t SIZE_OF_UINT8 = 8;
        static const uint8_t MASK = 0xFF;
    };
}

#endif //AHRS_CHECKSUM_H
