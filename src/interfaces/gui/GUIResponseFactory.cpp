#include "GUIResponseFactory.h"

#include "GUIPlaneBuilder.h"
#include "GUIWindowResponseBuilder.h"
#include "GUIWirelessComWrapperBuilder.h"
#include "GUIStartAcqBuilder.h"
#include "GUIStopAcqBuilder.h"
#include "GUIRestartResponseBuilder.h"
#include "GUIShutdownResponseBuilder.h"

using namespace std;
using namespace communication;

GUIResponseFactory::GUIResponseFactory()
{}

GUIResponseFactory::~GUIResponseFactory()
{}

unique_ptr<GUIResponse> GUIResponseFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<GUIResponseType >(commandInBytes[Frame::RESPONSE_TYPE_POSITION]);

    switch (type)
    {
        case GUIResponseType::SET_PLANE :
            builder_ = make_unique<GUIPlaneBuilder>();
            return move(builder_->create(commandInBytes));

        case GUIResponseType::WINDOWS_TYPE :
            builder_ = make_unique<GUIWindowResponseBuilder>();
            return move(builder_->create(commandInBytes));

        case GUIResponseType::WRAPPER :
            builder_ = make_unique<GUIWirelessComWrapperBuilder>();
            return move(builder_->create(commandInBytes));

        case GUIResponseType::GUI_START_ACQ :
            builder_ = make_unique<GUIStartAcqBuilder>();
            return move(builder_->create(commandInBytes));

        case GUIResponseType::GUI_STOP_ACQ :
            builder_ = make_unique<GUIStopAcqBuilder>();
            return move(builder_->create(commandInBytes));

        case GUIResponseType::GUI_RESTART :
            builder_ = make_unique<GUIRestartResponseBuilder>();
            return move(builder_->create(commandInBytes));

        case GUIResponseType::GUI_SHUTDOWN :
            builder_ = make_unique<GUIShutdownResponseBuilder>();
            return move(builder_->create(commandInBytes));

        default:
            throw invalid_argument("Received command does not register in factory.");
    }
}
