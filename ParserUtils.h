#pragma once
#include <vector>
#include <stdio.h>
#include <sstream>
#include "Row.h"
namespace utils
{
    std::vector<std::string> SplitString(const std::string& input);
    std::vector<std::string> ReadRows(std::stringstream& ss);
    row::Row SetRow(const std::vector<std::string>& splitedString); 
}


