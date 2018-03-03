#ifndef AHRS_ERROR_DETECTING_CODE_H
#define AHRS_ERROR_DETECTING_CODE_H

#include <vector>
#include <string>
#include <cstdint>

namespace utility
{
    class ErrorDetectingCode
    {
    public:
        ErrorDetectingCode();
        ~ErrorDetectingCode();

        bool calculateCRC(const std::vector<uint8_t> &vec);
        bool calculateChecksum(const std::vector<uint8_t> &vec);

    };
}
#endif
