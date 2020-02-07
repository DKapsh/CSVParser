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
            std::vector<float> AskSubBid(const std::vector<row::Quote>& data);
            float GetMin(const std::vector<float>& data);
            float GetMax(const std::vector<float>& data);
            float GetRatio(const std::vector<row::Quote>& data);
            uint64_t GetMaxDifferenceBetweenTimestamps(const std::vector<row::Quote>& data);
    };
}



