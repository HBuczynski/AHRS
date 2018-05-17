#ifndef AHRS_RESPONSEFACTORY_H
#define AHRS_RESPONSEFACTORY_H

#include "ResponseBuilder.h"

namespace communication
{
    class ResponseFactory
    {
    public:
        ResponseFactory();
        ~ResponseFactory();
        std::unique_ptr<Response> createCommand(const std::vector<uint8_t> &commandInBytes);

    private:
        std::unique_ptr<ResponseBuilder> builder_;

        const uint8_t RESPONSE_DATA_TYPE_POSITION = 5;

    };
}

#endif //AHRS_RESPONSEFACTORY_H
