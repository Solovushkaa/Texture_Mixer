#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

std::wstring conf[4] = { L"", L"", L"", L"" };

std::wstring PathAdjustment(std::wstring str)
{
    for (unsigned int i = str.size(); i > 0; --i)
    {
        if (str[i] == '\\')
        {
            str.erase(i + 1, str.size() - i);
            break;
        }
    }
    return str;
}

std::wstring* SearchFilesInFolder(std::wstring str)
{
    str = PathAdjustment(str);

    std::vector<std::wstring> paths;
    unsigned int counter = 0;
    for (const auto& entry : std::filesystem::directory_iterator(str))
    {
        paths.push_back(entry.path());
        ++counter;
    }

    unsigned int size = 3;
    std::wstring* RGB_paths = new std::wstring[size]; unsigned int RGB_count = 0;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < paths.size(); ++j)
        {
            if (paths[j].find(conf[i], 0) != std::string::npos)
            {
                RGB_paths[RGB_count] = paths[j];
                ++RGB_count;
                break;
            }
        }
        if (size == RGB_count) { break; }
    }
    return RGB_paths;
}