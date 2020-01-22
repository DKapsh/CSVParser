#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include "CSVParser.h"
#include "ParserUtils.h"

parser::CSVParser::CSVParser(std::stringstream& in, std::stringstream& out)
{   
    m_lines = utils::ReadRows(in);
}

void parser::CSVParser::ParseData(std::map<std::string, std::vector<row::Quote>>& inputData)
{
    for(auto& line : m_lines)
    {
        utils::SetRow(utils::SplitString(line), inputData);
    }
}

void parser::CSVParser::Write(const std::map<std::string, std::vector<row::Quote>>& outputData)
{

}