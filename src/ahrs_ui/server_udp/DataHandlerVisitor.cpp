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
    string message = string("DataHandlerVisitor :: Received ImuData.");
    logger_.writeLog(LogType::INFORMATION_LOG, message);

}

void DataHandlerVisitor::visit(GpsData &data)
{

}
