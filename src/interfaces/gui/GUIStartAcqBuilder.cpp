#include "GUIStartAcqBuilder.h"
#include "GUIStartAcqResponse.h"

using namespace std;
using namespace communication;

GUIStartAcqBuilder::GUIStartAcqBuilder()
{}

GUIStartAcqBuilder::~GUIStartAcqBuilder()
{}

unique_ptr<GUIResponse> GUIStartAcqBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<GUIStartAcqResponse>();

    return move(command);
}
