#include "GUIBITSCommand.h"
#include "GUICommandVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

GUIBITSCommand::GUIBITSCommand(const BitsInformation &bitsInformation)
        : GUICommand(10, GUICommandType::INFORMATION_WINDOW),
          bitsInfo_(bitsInformation)
{}

GUIBITSCommand::~GUIBITSCommand()
{}

vector<uint8_t> GUIBITSCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    const auto tempFrame = BytesConverter::appendStructToVectorOfUINT8(bitsInfo_);
    frame.insert(frame.end(), tempFrame.begin(), tempFrame.end());

    return frame;
}

string GUIBITSCommand::getName()
{
    return string("GUIBITSCommand");
}

void GUIBITSCommand::accept(GUICommandVisitor &visitor)
{
    visitor.visit(*this);
}

void GUIBITSCommand::setBitsInfo(const BitsInformation &info) noexcept
{
    bitsInfo_ = info;
}

const BitsInformation& GUIBITSCommand::getBitsInfo() const noexcept
{
    return bitsInfo_;
}

void GUIBITSCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_) + sizeof(bitsInfo_));
}

