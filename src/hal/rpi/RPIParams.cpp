#include "../include/RPIParams.h"

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

float RPIParams::getTemp()
{
    std::string cmd("vcgencmd measure_temp");

    std::string file_name = "result.txt" ;
    std::system( (cmd + " > " + file_name ).c_str() ) ; // redirect output to file

    // open file for input, return string containing characters in the file
    std::ifstream file(file_name) ;
    string result{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() } ;

    return stof(result.substr(5,4));
}

