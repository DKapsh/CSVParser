#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include "MetricsCalculator.h"

metrics::MetricsCalculator::MetricsCalculator(const std::vector<row::Row>& data):m_data(data)
{
}

uint64_t metrics::MetricsCalculator::VolumeSum()
{
    uint64_t sum = 0;
    for(const auto& row : m_data)
    {
        if(row.ticker == m_tickerType)
        {
            sum += row.volume;
        }
    }
    return sum;
}

void metrics::MetricsCalculator::SetTickerType(const std::string& tickerType)
{
    m_tickerType = tickerType;
}
 