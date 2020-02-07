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
            explicit CSVParser(std::istream& in);
            void Read(std::map<std::string, std::vector<row::Quote>>& inputData);
            void CalculateMetrics(const std::map<std::string, std::vector<row::Quote>>& outputData, std::string& out);
            void Write(const std::string& outputData, std::ostream & out);
            
        private:
            std::vector<std::string> m_lines;
    };  
}


