#pragma once
#include <vector>
#include <stdio.h>
#include <sstream>
#include <map>
#include "Row.h"
namespace parser
{
    class CSVParser
    {
        public:
            explicit CSVParser(std::stringstream& in);
            void ParseData(std::map<std::string, std::vector<row::Quote>>& inputData);
            void Write(const std::map<std::string, std::vector<row::Quote>>& outputData, std::stringstream & out);
            
        private:
            std::vector<std::string> m_lines;
    };  
}


