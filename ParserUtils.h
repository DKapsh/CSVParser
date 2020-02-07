#pragma once
#include <vector>
#include <stdio.h>
#include <sstream>
#include <map>
#include "Row.h"
namespace utils
{
    std::vector<std::string> SplitStringByDelimiter(const std::string& input, char delimiter);
    std::vector<std::string> ReadRows(std::istream& ss);
    void SetRow(const std::vector<std::string>& splitedString, std::map<std::string, std::vector<row::Quote>>& inputData); 
    std::string FormedOutputData(const std::string& ticker, const std::vector<row::Quote>& inputData);
}


