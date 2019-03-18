#include "../include/RS232Interface.h"

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

RS232Interface::RS232Interface(const string &name)
    : name_(name),
      fd_(-2)
{}

void RS232Interface::initialize()
{
    fd_ = open(name_.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

    if(fd_ < 0)
    {
        cout << "lol" << endl;
    }

    termios options;

    tcgetattr(fd_, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;

    tcflush(fd_, TCIFLUSH);
    tcsetattr(fd_, TCSANOW, &options);
}

void RS232Interface::writeData(const vector<uint8_t> &data)
{
    if (fd_ != -1)
    {
        int count = write(fd_, data.data(), data.size());

        if (count < 0)
        {
            //TODO: handle errors...
        }
    }
}

vector<uint8_t> RS232Interface::readData()
{
    char frameElement;
    vector<uint8_t> frame;

    int length = -1;

    while(1) {

        length = read(fd_, (void*)(&frameElement), 1);

        if (length <= 0)
        {
            this_thread::sleep_for(std::chrono::milliseconds(2));
        }
        else
        {
            if (frameElement == '\n')
            {
                frame.push_back('\0');
                break;
            }
            frame.push_back(frameElement);
        }
    }

    return frame;
}

void RS232Interface::closeSerial()
{
    close(fd_);
}
