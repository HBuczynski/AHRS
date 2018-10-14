#include "GUIInformationWindowCommand.h"
#include "GUICommandVisitor.h"

using namespace std;
using namespace communication;

GUIInformationWindowCommand::GUIInformationWindowCommand(uint8_t masterConnection, uint8_t redundantConnection, uint8_t bitsPerformance)
        : GUICommand(10, GUICommandType::INFORMATION_WINDOW),
          masterConnection_(masterConnection),
          redundantConnection_(redundantConnection),
          bitsPerformance_(bitsPerformance)
{}

GUIInformationWindowCommand::~GUIInformationWindowCommand()
{}

vector<uint8_t> GUIInformationWindowCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(masterConnection_));
    frame.push_back(static_cast<uint8_t>(redundantConnection_));
    frame.push_back(static_cast<uint8_t>(bitsPerformance_));

    return frame;
}

string GUIInformationWindowCommand::getName()
{
    return string("GUIInformationWindowCommand");
}

void GUIInformationWindowCommand::accept(GUICommandVisitor &visitor)
{
    visitor.visit(*this);
}

void GUIInformationWindowCommand::setMasterConnection(uint8_t state)
{
    masterConnection_ = state;
}

uint8_t GUIInformationWindowCommand::getMasterConnection() const
{
    return masterConnection_;
}

void GUIInformationWindowCommand::setRedundantConnection(uint8_t state)
{
    redundantConnection_ = state;
}

uint8_t GUIInformationWindowCommand::getRedundantConnection() const
{
    return redundantConnection_;
}

void GUIInformationWindowCommand::setBitsPerformance(uint8_t state)
{
    bitsPerformance_ = state;
}

uint8_t GUIInformationWindowCommand::getBitsPerformance() const
{
    return bitsPerformance_;
}

void GUIInformationWindowCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_) + sizeof(masterConnection_) + sizeof(redundantConnection_) + sizeof(bitsPerformance_));
}
