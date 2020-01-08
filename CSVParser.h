#pragma once
#include <vector>
#include <stdio.h>
#include <sstream>
#include "Row.h"
namespace parser
{
    class CSVParser
    {
        public:
            explicit CSVParser(std::stringstream& in);
            std::vector<row::Row> ParseData();
            
        private:
            std::vector<std::string> m_lines;
    };  
}


