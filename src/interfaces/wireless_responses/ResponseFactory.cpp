#include "ResponseFactory.h"

#include "DataResponseBuilder.h"
#include "AckResponseBuilder.h"
#include "CalibratingStatusBuilder.h"

using namespace std;
using namespace communication;

ResponseFactory::ResponseFactory()
{}

ResponseFactory::~ResponseFactory()
{}

unique_ptr<Response> ResponseFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<ResponseType >(commandInBytes[RESPONSE_DATA_TYPE_POSITION]);

    switch (type)
    {
        case ResponseType::DATA :
            builder_ = make_unique<DataResponseBuilder>();
            return move(builder_->create(commandInBytes));
        case ResponseType::ACK:
            builder_ = make_unique<AckResponseBuilder>();
            return move(builder_->create(commandInBytes));
        case ResponseType::CALIBRATING_STATUS:
            builder_ = make_unique<CalibratingStatusBuilder>();
            return move(builder_->create(commandInBytes));
        default:
            throw invalid_argument("Received command does not register in factory.");
    }
}