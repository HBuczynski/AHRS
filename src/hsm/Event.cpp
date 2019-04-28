#include "Event.h"

using namespace std;
using namespace hsm;

Event::Event(const string &key)
    : key_(move(key))
{}

const string& Event::getKey() const noexcept
{
    return key_;
}