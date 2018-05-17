#ifndef AHRS_INTERPROCESSDATA_H
#define AHRS_INTERPROCESSDATA_H

const std::string COMMUNICATION_BINARY_FILE_NAME = "communication_process_ui";

const uint16_t MESSAGE_QUEUE_DATA_SIZE = 1000;
const uint16_t MESSAGE_QUEUE_NUMBER = 1000;

const std::string RECEIVING_QUEUE_NAME_FIRST_PROC = "receiving_queue_first";
const std::string RECEIVING_QUEUE_NAME_SECOND_PROC = "receiving_queue_second";

const uint16_t SHARED_MEMORY_SIZE = 1000;
const std::string SHARED_MEMORY_NAME = "shared_memmory";
const std::string SHARED_MEMORY_MUTEX_NAME = "shared_memory_mutex";

#endif //AHRS_INTERPROCESSDATA_H
