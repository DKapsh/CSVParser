#include <vector>
#include <stdio.h>
#include <sstream>
#include "ParserUtils.h"
#include "MetricsCalculator.h"


std::vector<std::string> utils::SplitString(const std::string& input)
{
    std::vector<std::string> row;
    int posPrev = 0;
    int posNext = 0;
    while(posNext < input.length())
    {   
        posNext = input.find(',', posPrev);
        if(posNext == std::string::npos)
        {
            posNext == input.length();
        }
        row.push_back(input.substr(posPrev, posNext- posPrev));
        posPrev = posNext + 1;
    }
    return row;
}

std::vector<std::string> utils::ReadRows(std::stringstream& ss)
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

std::vector<row::Output> utils::FormedOutputData(const std::string& ticker, const std::vector<row::Quote>& inputData)
{
    row::Output tmp;
    metrics::MetricsCalculator calculator;
    tmp.ticker = ticker;
    tmp.max = calculator.GetMax(calculator.AskSubBid(inputData));
    tmp.min = calculator.GetMin(calculator.AskSubBid(inputData));
    tmp.sum = calculator.VolumeSum(inputData);
    tmp.ratio = calculator.GetRatio(inputData);

    return {tmp};
}



