#ifndef AHRS_SHAREDMEMORYWRAPPER_H
#define AHRS_SHAREDMEMORYWRAPPER_H

#include <string>
#include <vector>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>

namespace communication
{
    class SharedMemoryWrapper
    {
    public:
        SharedMemoryWrapper(std::string name, uint32_t size);
        SharedMemoryWrapper(std::string name);
        ~SharedMemoryWrapper();

        void write(std::vector<uint8_t>& msg);
        std::vector<uint8_t> read();

        void clear();

    private:
        void checksum(std::vector<uint8_t> &msg);

        std::string name_;
        uint32_t size_;

        std::unique_ptr <boost::interprocess::named_mutex> sharedMemoryMutex_;
        std::unique_ptr <boost::interprocess::shared_memory_object> sharedMemory_;
        std::unique_ptr <boost::interprocess::mapped_region> mappedMemoryRegion_;
    };
}

#endif
