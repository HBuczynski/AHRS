#include "DataHandlerVisitor.h"

#include <iostream>

using namespace std;
using namespace utility;
using namespace communication;

DataHandlerVisitor::DataHandlerVisitor()
    : logger_(Logger::getInstance())
{}

DataHandlerVisitor::~DataHandlerVisitor()
{}

void DataHandlerVisitor::visit(ImuData &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("DataHandlerVisitor :: Received ImuData.") + to_string((data.getMeasurement()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

}

void DataHandlerVisitor::visit(GpsData &data)
{

}
