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
            explicit MetricsCalculator();
            uint64_t VolumeSum(const std::vector<row::Quote>& data);
            std::vector<double> AskSubBid(const std::vector<row::Quote>& data);
            double GetMin(const std::vector<double>& data);
            double GetMax(const std::vector<double>& data);
            double GetRatio(const std::vector<row::Quote>& data);
    };
}



