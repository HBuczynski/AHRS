#ifndef GPS_TEST_RS232INTERFACE_H
#define GPS_TEST_RS232INTERFACE_H

#include <string>
#include <vector>

class RS232Interface
{
public:
    RS232Interface(const std::string& name);

    void initialize();
    void closeSerial();

    void writeData(const std::vector<uint8_t>& data);
    std::vector<uint8_t> readData();

private:

    std::string name_;
    int fd_;
};


#endif //GPS_TEST_RS232INTERFACE_H
