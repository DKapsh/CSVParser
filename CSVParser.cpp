#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include "CSVParser.h"
#include "ParserUtils.h"

parser::CSVParser::CSVParser(char delimiter)
{   
    m_delimiter = delimiter;
}

void parser::CSVParser::Read(std::istream& in, std::map<std::string, std::vector<row::Quote>>& inputData)
{
    std::vector<std::string> lines = utils::ReadRows(in);
    for(auto& line : lines)
    {
        utils::SetRow(utils::SplitStringByDelimiter(line, m_delimiter), inputData);
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