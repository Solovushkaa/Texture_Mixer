#pragma once

#include <string>
#include <list>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void SearchFilesInFolder(std::wstring str)
{ 
    for (unsigned int i = str.size(); i > 0; --i)
    {
        if (str[i] == '\\')
        {
            str.erase(i + 1, str.size() - i);
            break;
        }
    }
    std::ifstream find_config("file_config.txt");
    std::list<std::wstring>;
    for (const auto& entry : fs::directory_iterator(str));
        //output << entry.path() << std::endl;
}

void SearchFilesInFoldersOfFolders()
{

}