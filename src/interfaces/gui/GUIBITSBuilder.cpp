#include "GUIBITSBuilder.h"
#include "GUIBITSCommand.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

GUIBITSBuilder::GUIBITSBuilder()
{}

GUIBITSBuilder::~GUIBITSBuilder()
{}

unique_ptr<GUICommand> GUIBITSBuilder::create(const vector<uint8_t> &commandInBytes)
{
    int16_t position = Frame::INITIAL_DATA_POSITION;

    BitsInformation bitsInformation;
    BytesConverter::fromVectorOfUINT8toStruct(commandInBytes, position, bitsInformation);

    auto command = make_unique<GUIBITSCommand>(bitsInformation);

    return move(command);
}
