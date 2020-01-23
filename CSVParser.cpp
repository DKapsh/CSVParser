#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include "CSVParser.h"
#include "ParserUtils.h"

parser::CSVParser::CSVParser(std::stringstream& in)
{   
    m_lines = utils::ReadRows(in);
}

void parser::CSVParser::Read(std::map<std::string, std::vector<row::Quote>>& inputData)
{
    for(auto& line : m_lines)
    {
        utils::SetRow(utils::SplitString(line), inputData);
    }
}

void parser::CSVParser::Write(const std::map<std::string, std::vector<row::Quote>>& outputData, std::stringstream & out)
{
    auto tickerType = outputData.begin();
    for(auto iter = outputData.begin(); iter != outputData.end(); ++iter)
    {
        out << utils::FormedOutputData(iter->first, iter->second);
    }
    
}