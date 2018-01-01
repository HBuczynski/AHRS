#include "DataHandlerVisitor.h"

#include <iostream>

using namespace std;
using namespace communication;

DataHandlerVisitor::DataHandlerVisitor()
{}

DataHandlerVisitor::~DataHandlerVisitor()
{}

void DataHandlerVisitor::visit(ImuData &data)
{
    cout << "Otrzymano IMUData" << endl;
}

void DataHandlerVisitor::visit(GpsData &data)
{

}
