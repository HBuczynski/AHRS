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
    std::ifstream in("vcgencmd measure_temp");
    
    std::string line;
    std::getline(in, line)

    cout << line << endl;

    return 67.0;
}

