#pragma once
#include <vector>
#include <stdio.h>
#include <sstream>
#include <map>
#include "Row.h"
namespace utils
{
    std::vector<std::string> SplitString(const std::string& input);
    std::vector<std::string> ReadRows(std::stringstream& ss);
    void SetRow(const std::vector<std::string>& splitedString, std::map<std::string, std::vector<row::Quote>>& inputData); 
    row::Row SetRow(const std::vector<std::string>& splitedString); 
}


