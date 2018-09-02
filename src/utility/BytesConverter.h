#ifndef AHRS_BLACK_BOX_BYTES_CONVERTER_H
#define AHRS_BLACK_BOX_BYTES_CONVERTER_H

#include <vector>
#include <string>
#include <cstdint>

namespace utility
{
    class BytesConverter
    {
    public:
        static void appendUINT16toVectorOfUINT8(uint16_t number, std::vector<uint8_t>& vec);
        static uint16_t fromVectorOfUINT8toUINT16(const std::vector<uint8_t> &vec, uint16_t variablePosition);

        static void appendUINT32toVectorOfUINT8(uint32_t number, std::vector<uint8_t>& vec);
        static uint32_t fromVectorOfUINT8toUINT32(const std::vector<uint8_t> &vec, uint16_t variablePosition);

        static void appendUINT64toVectorOfUINT8(uint64_t number, std::vector<uint8_t>& vec);
        static uint64_t fromVectorOfUINT8toUINT64(const std::vector<uint8_t> &vec, uint16_t variablePosition);

        static void appendStringToVectorOfUINT8(std::string data, std::vector<uint8_t>& vec);
        static std::string fromVectorOfUINT8toString(const std::vector<uint8_t> &vec, uint16_t variablePosition);

        template<typename T>
        static std::vector<uint8_t> appendStructToVectorOfUINT8(T &data)
        {
            std::vector<uint8_t> vec(sizeof(T));

            const uint8_t *start = reinterpret_cast<const uint8_t *>(std::addressof(data));
            const uint8_t *end = start + sizeof(data);

            std::copy(start, end, std::begin(vec));

            return vec;
        }

        template<typename T>
        static void fromVectorOfUINT8toStruct(const std::vector<uint8_t> &vec, uint16_t variablePosition, T& data)
        {
            uint8_t *object = reinterpret_cast<uint8_t *>(std::addressof(data));
            const uint8_t *start = reinterpret_cast<const uint8_t *>(vec.data()) + variablePosition;
            const uint8_t *end = start + sizeof(T);

            std::copy(start, end, object);
        }
    };
}
#endif
