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

std::vector<row::Row> parser::CSVParser::ParseData()
{
    std::vector<row::Row> result;
    for(auto& line : m_lines)
    {
        result.push_back(utils::SetRow(utils::SplitString(line)));
    }
    return result;
}