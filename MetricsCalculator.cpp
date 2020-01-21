#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "MetricsCalculator.h"

metrics::MetricsCalculator::MetricsCalculator(const std::vector<row::Row>& data):m_data(data)
{
}

uint64_t metrics::MetricsCalculator::VolumeSum(const std::vector<row::Quote>& data)
{
    uint64_t sum = 0;
    for(const auto& row : data)
    {
        sum += row.volume;
    }
    return sum;
}

void metrics::MetricsCalculator::SetTickerType(const std::string& tickerType)
{
    m_tickerType = tickerType;
}

std::vector<double> metrics::MetricsCalculator::AskSubBid(const std::vector<row::Quote>& data)
{
    std::vector<double> result;
    for(const auto& row : data)
    {
        result.push_back(row.ask - row.bid);
    }
    return result;
}

double metrics::MetricsCalculator::GetMin(const std::vector<double>& data)
{
    if (data.empty())
    {
        throw std::runtime_error {"Input vector is empty"};
    }
    return *(std::min_element(data.begin(), data.end()));
}

double metrics::MetricsCalculator::GetMax(const std::vector<double>& data)
{
    if (data.empty())
    {
        throw std::runtime_error {"Input vector is empty"};
    }
    return *(std::max_element(data.begin(), data.end()));
}

double metrics::MetricsCalculator::GetRatio(const std::vector<row::Quote>& data)
{
    double numerator = 0;
    double denumerator = 0;
    for(const auto& row : data)
    {
        numerator += row.bid * row.askSize + row.ask * row.bidSize;
        denumerator += row.askSize+row.bidSize;
    }
    return numerator/denumerator;
}