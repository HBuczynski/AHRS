#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Utility.h"

using namespace std;
using namespace utility;

vector<string> Utility::getFilesInDir(const string &directoryPath)
{
    vector<string> files;

    DIR* dir = opendir(directoryPath.c_str());
    dirent *dirChild;

    while ( (dirChild = readdir(dir)) != NULL )
    {
        if((dirChild->d_type == DT_DIR && dirChild->d_name[0] == '.'))
            continue;

        files.emplace_back(dirChild->d_name);
    }

    closedir(dir);

    return files;
}

vector<string> Utility::getFilesNamesInDir(const string &directoryPath)
{
    auto files = Utility::getFilesInDir(directoryPath);
    const string dot{'.'};

    for(auto& file : files)
    {
        file.erase(file.find(dot));
    }

    return files;
}
