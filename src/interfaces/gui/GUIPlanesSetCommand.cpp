#include "GUIPlanesSetCommand.h"
#include "GUICommandVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

GUIPlanesSetCommand::GUIPlanesSetCommand(const string &dataset)
    : GUICommand(10, GUICommandType::PLANE_DATASET),
      dataset_(dataset)
{ }

GUIPlanesSetCommand::~GUIPlanesSetCommand()
{ }

vector<uint8_t> GUIPlanesSetCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    BytesConverter::appendStringToVectorOfUINT8(dataset_, frame);

    return frame;
}

void GUIPlanesSetCommand::initializeDataSize()
{
    dataSize_ = sizeof(commandType_);
    dataSize_ += sizeof(char)*dataset_.size();
}

string GUIPlanesSetCommand::getName()
{
    return string("GUIPlanesSetCommand");
}

void GUIPlanesSetCommand::setDataset(const string&  dataset)
{
    dataset_ = dataset;
}

string GUIPlanesSetCommand::getDataset() const
{
    return dataset_;
}

void GUIPlanesSetCommand::accept(GUICommandVisitor &visitor)
{
    visitor.visit(*this);
}
