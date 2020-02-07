#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "MetricsCalculator.h"

metrics::MetricsCalculator::MetricsCalculator()
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

std::vector<float> metrics::MetricsCalculator::AskSubBid(const std::vector<row::Quote>& data)
{
    std::vector<float> result;
    for(const auto& row : data)
    {
        result.push_back(row.ask - row.bid);
    }
    return result;
}

float metrics::MetricsCalculator::GetMin(const std::vector<float>& data)
{
    if (data.empty())
    {
        throw std::runtime_error {"Input vector is empty"};
    }
    return *(std::min_element(data.begin(), data.end()));
}

float metrics::MetricsCalculator::GetMax(const std::vector<float>& data)
{
    if (data.empty())
    {
        throw std::runtime_error {"Input vector is empty"};
    }
    return *(std::max_element(data.begin(), data.end()));
}

float metrics::MetricsCalculator::GetRatio(const std::vector<row::Quote>& data)
{
    float numerator = 0;
    float denumerator = 0;
    for(const auto& row : data)
    {
        numerator += row.bid * row.askSize + row.ask * row.bidSize;
        denumerator += row.askSize+row.bidSize;
    }
    return numerator/denumerator;
}

uint64_t metrics::MetricsCalculator::GetMaxDifferenceBetweenTimestamps(const std::vector<row::Quote>& data)
{
    std::vector<uint64_t> difference;
    for(int i = 0; i < data.size() -1; ++i)
    {
        difference.push_back(data[i+1].timestamp - data[i].timestamp);
    }
    return *(std::max_element(difference.begin(), difference.end()));   
}