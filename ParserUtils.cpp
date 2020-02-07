#include <vector>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <string>
#include "ParserUtils.h"
#include "MetricsCalculator.h"

std::vector<std::string> utils::SplitStringByDelimiter(const std::string& input, char delimiter)
{
    std::vector<std::string> row;
    int posPrev = 0;
    int posNext = 0;
    while(posNext < input.length())
    {   
        posNext = input.find(delimiter, posPrev);
        if(posNext == std::string::npos)
        {
            posNext == input.length();
        }
        row.push_back(input.substr(posPrev, posNext- posPrev));
        posPrev = posNext + 1;
    }
    return row;
}

std::vector<std::string> utils::ReadRows(std::istream& ss)
{
    std::string tmp;
    std::vector<std::string> result;
    while(std::getline(ss, tmp))
    {
        result.push_back(tmp);
    }
    return result;
}

void utils::SetRow(const std::vector<std::string>& splitedString, std::map<std::string, std::vector<row::Quote>>& inputData)
{
    row::Quote tmp;
    tmp.timestamp = atoi(splitedString[0].data());
    tmp.bid = atof(splitedString[2].data());
    tmp.bidSize = atoi(splitedString[3].data());
    tmp.ask = atof(splitedString[4].data());
    tmp.askSize = atoi(splitedString[5].data());
    tmp.volume = atoi(splitedString[6].data());
    auto tickerIter = inputData.find(splitedString[1]);
    if ( tickerIter == inputData.end())
    {
        inputData.insert({splitedString[1],{tmp}});
    } 
    else
    {
        (tickerIter->second).push_back(tmp);
    }   
}

std::string utils::FormedOutputData(const std::string& ticker, const std::vector<row::Quote>& inputData)
{
    std::string tmp = ticker +",";
    metrics::MetricsCalculator calculator;
    tmp += std::to_string(calculator.GetMax(calculator.AskSubBid(inputData))) + ",";
    tmp += std::to_string(calculator.GetMin(calculator.AskSubBid(inputData)))+ ",";
    tmp += std::to_string(calculator.VolumeSum(inputData))+ ",";
    tmp += std::to_string(calculator.GetMaxDifferenceBetweenTimestamps(inputData))+ ",";
    tmp += std::to_string(calculator.GetRatio(inputData))+'\n';
    return tmp;
}



