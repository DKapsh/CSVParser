#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include "CSVParser.h"
#include "ParserUtils.h"

parser::CSVParser::CSVParser(std::istream& in)
{   
    m_lines = utils::ReadRows(in);
}

void parser::CSVParser::Read(std::map<std::string, std::vector<row::Quote>>& inputData)
{
    for(auto& line : m_lines)
    {
        utils::SetRow(utils::SplitStringByDelimiter(line, ','), inputData);
    }
}

void parser::CSVParser::CalculateMetrics(const std::map<std::string, std::vector<row::Quote>>& outputData, std::string& out)
{
    for(auto iter = outputData.begin(); iter != outputData.end(); ++iter)
    {
        out += utils::FormedOutputData(iter->first, iter->second);
    }
}

void parser::CSVParser::Write(const std::string& outData, std::ostream & out)
{ 
    out << outData;
}