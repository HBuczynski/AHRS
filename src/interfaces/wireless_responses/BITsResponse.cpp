#include "BITsResponse.h"
#include "ResponseVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

BITsResponse::BITsResponse(const BitsInformation &bits)
        : Response(10, ResponseType::BITs_STATUS),
          bits_(bits)
{ }

BITsResponse::~BITsResponse()
{ }

vector<uint8_t> BITsResponse::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));

    const auto bitsInBytes = BytesConverter::appendStructToVectorOfUINT8(bits_);
    frame.insert(frame.end(), bitsInBytes.begin(), bitsInBytes.end());

    return frame;
}

string BITsResponse::getName()
{
    return string("BITsResponse");
}

void BITsResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}

const BitsInformation &BITsResponse::getBits() const
{
    return bits_;
}

void BITsResponse::setBITs(const BitsInformation &bits)
{
    bits_ = bits;
}

void BITsResponse::initializeDataSize()
{
    uint16_t dataSize = sizeof(responseType_);
    dataSize += sizeof(bits_);

    setDataSize(dataSize);
}
