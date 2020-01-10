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
        private:
            std::vector<row::Row> m_data;
    };
}



