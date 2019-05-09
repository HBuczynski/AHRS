#include "DatabaseNameBuilder.h"
#include "DatabaseNameNotification.h"

using namespace std;
using namespace communication;

DatabaseNameBuilder::DatabaseNameBuilder()
{}

DatabaseNameBuilder::~DatabaseNameBuilder()
{}

unique_ptr<UINotification> DatabaseNameBuilder::create(const vector<uint8_t> &commandInBytes)
{
    config::UICommunicationMode mode = static_cast<config::UICommunicationMode>(commandInBytes[Frame::INITIAL_DATA_POSITION]);
    auto command = make_unique<DatabaseNameNotification>(mode);

    return move(command);
}
