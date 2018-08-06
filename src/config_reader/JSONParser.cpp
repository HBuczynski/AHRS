#include "JSONParser.h"

using namespace std;
using namespace utility;
using namespace config;

JSONParser::JSONParser(const string &fileName)
    : fileName_(fileName),
      logger_(Logger::getInstance())
{
    file_.open(fileName_.c_str());

    if(file_.is_open())
    {
        file_ >> fileRoot_;
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("JSONParser :: File - ") + fileName_ + string(" was not open correctly.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
        throw invalid_argument("Configuration file name is incorrect.");
    }
}

JSONParser::~JSONParser()
{
    file_.close();
}

void JSONParser::getUINT8t(const std::vector<std::string> &hierarchyQueue, uint8_t &value)
{
    value = static_cast<uint8_t>(getFromLeaf(hierarchyQueue).asUInt64());
}

void JSONParser::getUINT16t(const std::vector<std::string> &hierarchyQueue, uint16_t &value)
{
    value = static_cast<uint16_t>(getFromLeaf(hierarchyQueue).asUInt64());
}

void JSONParser::getUINT32t(const std::vector<std::string> &hierarchyQueue, uint32_t &value)
{
    value = static_cast<uint32_t>(getFromLeaf(hierarchyQueue).asUInt64());
}

void JSONParser::getUINT64t(const std::vector<std::string> &hierarchyQueue, uint64_t &value)
{
    value = getFromLeaf(hierarchyQueue).asUInt64();
}

void JSONParser::getString(const std::vector<std::string> &hierarchyQueue, string &value)
{
    value = getFromLeaf(hierarchyQueue).asString();
}

Json::Value JSONParser::getFromLeaf(const vector<string> &hierarchyQueue)
{
    if(hierarchyQueue.size() == 1)
    {
        Json::Value value = fileRoot_[hierarchyQueue[0].c_str()];
        return value;
    }
    else if(hierarchyQueue.size() == 2)
    {
        Json::Value value = fileRoot_[hierarchyQueue[0].c_str()][hierarchyQueue[1].c_str()];
        return value;
    }
    else if(hierarchyQueue.size() == 3)
    {
        Json::Value value = fileRoot_[hierarchyQueue[0].c_str()][hierarchyQueue[1].c_str()][hierarchyQueue[2].c_str()];
        return value;
    }
    else if(hierarchyQueue.size() == 4)
    {
        Json::Value value = fileRoot_[hierarchyQueue[0].c_str()][hierarchyQueue[1].c_str()][hierarchyQueue[2].c_str()][hierarchyQueue[3].c_str()];
        return value;
    }
    else if(hierarchyQueue.size() == 5)
    {
        Json::Value value = fileRoot_[hierarchyQueue[0].c_str()][hierarchyQueue[1].c_str()][hierarchyQueue[2].c_str()][hierarchyQueue[3].c_str()][hierarchyQueue[4].c_str()];
        return value;
    }
    else if(hierarchyQueue.size() == 6)
    {
        Json::Value value = fileRoot_[hierarchyQueue[0].c_str()][hierarchyQueue[1].c_str()][hierarchyQueue[2].c_str()][hierarchyQueue[3].c_str()][hierarchyQueue[4].c_str()][hierarchyQueue[5].c_str()];
        return value;
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("JSONParser:: Hierarchy vector contains wrong number of arguments.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        throw invalid_argument("Hierarchy vector contains wrong number of arguments");
    }
}

void JSONParser::setString(const vector<std::string> &hierarchyQueue, string &value)
{

}
