#include <iostream>

#include <checksum/Checksum.h>
#include <utility/BytesConverter.h>
#include <interfaces/frame/Frame.h>

#include "SharedMemoryWrapper.h"

using namespace std;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

SharedMemoryWrapper::SharedMemoryWrapper(std::string name, uint32_t size)
    :   name_(name),
        size_(size)
{
    // Creating shared memory's mutex.
    named_mutex::remove(name_.c_str());
    sharedMemoryMutex_ = std::make_unique<named_mutex>(open_or_create, name_.c_str());

    // Creating shared memory.
    shared_memory_object::remove(name_.c_str());
    sharedMemory_ = std::make_unique<shared_memory_object>(open_or_create, name_.c_str(), read_write);

    // Resize shared memory.
    sharedMemory_->truncate(size_);
    mappedMemoryRegion_ = std::make_unique<mapped_region>(*sharedMemory_, read_write);
}

SharedMemoryWrapper::SharedMemoryWrapper(std::string name)
    :   name_(name),
        size_(0)
{
    // Creating shared memory's mutex.
    sharedMemoryMutex_ = make_unique<named_mutex>(open_or_create, name_.c_str());
    // Creating shared memory.
    sharedMemory_ = make_unique<shared_memory_object>(open_or_create, name_.c_str(), read_write);
    // Mapped shared memory.
    mappedMemoryRegion_ = make_unique<mapped_region>(*sharedMemory_, read_write);
}

SharedMemoryWrapper::~SharedMemoryWrapper()
{ }

void SharedMemoryWrapper::write(vector<uint8_t> &msg)
{
    auto parityBit = Checksum::parityBit(msg);
    const auto crc32 = Checksum::crc32(msg);

    msg.push_back(parityBit);
    BytesConverter::appendUINT32toVectorOfUINT8(crc32, msg);

    uint8_t *pointerToMemory = nullptr;
    {
        scoped_lock<named_mutex> lock(*sharedMemoryMutex_.get());
        pointerToMemory = reinterpret_cast<uint8_t*>(mappedMemoryRegion_->get_address());
        copy(msg.begin(), msg.end(), pointerToMemory);
    }
}

vector<uint8_t> SharedMemoryWrapper::read()
{
    vector<uint8_t> frame;
    frame.resize(mappedMemoryRegion_->get_size());

    uint8_t *memory = nullptr;
    {
        scoped_lock<named_mutex> lock(*sharedMemoryMutex_.get());
        memory = reinterpret_cast<uint8_t* >(mappedMemoryRegion_->get_address());
        memcpy(frame.data(), memory, mappedMemoryRegion_->get_size());
    }

    checksum(frame);

    return frame;
}

void SharedMemoryWrapper::checksum(std::vector<uint8_t> &msg)
{
    const auto dataSize = BytesConverter::fromVectorOfUINT8toUINT16(msg, Frame::DATA_SIZE_UINT16_POSITION);
    const auto totalCommandSize = dataSize + Frame::HEADER_SIZE;

    const auto crcFromFrame = BytesConverter::fromVectorOfUINT8toUINT32(msg, totalCommandSize+sizeof(uint8_t));
    const auto parityFromFrame = msg[totalCommandSize];

    const auto commandFrame = vector<uint8_t>(msg.begin(), msg.begin() + totalCommandSize);
    const auto parityBit = Checksum::parityBit(commandFrame);
    const auto crc32 = Checksum::crc32(commandFrame);

    if(crcFromFrame != crc32 || parityFromFrame != parityBit)
    {
        throw logic_error("Checksum is incorrect.");
    }
}

void SharedMemoryWrapper::clear()
{
    vector<uint8_t> emptyPacket(100, 0);

    write(emptyPacket);
}
