#pragma once
#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include "Row.h"
namespace metrics
{
    class MetricsCalculator
    {
        public:
            explicit MetricsCalculator(const std::vector<row::Row>& data);
            void SetTickerType(const std::string& tickerType);
            uint64_t VolumeSum();
            std::vector<double> AskSubBid();
        private:
            std::vector<row::Row> m_data;
            std::string m_tickerType;
    };
}



