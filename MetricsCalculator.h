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
            uint64_t VolumeSum(const std::vector<row::Quote>& data);
            std::vector<double> AskSubBid(const std::vector<row::Quote>& data);
            double GetMin(const std::vector<double>& data);
            double GetMax(const std::vector<double>& data);
            double GetRatio();
        private:
            std::vector<row::Row> m_data;
            std::string m_tickerType;
    };
}



