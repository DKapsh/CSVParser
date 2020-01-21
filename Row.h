#pragma once
#include <string>
namespace row
{
    struct Quote
    {
        uint64_t timestamp;
        double bid;
        uint64_t bidSize;
        double ask;
        uint64_t askSize;
        uint64_t volume;

        bool operator== (const Quote& rhv) const
        {
            if(this->timestamp == rhv.timestamp &&
            abs(this->bid - rhv.bid) < 0.001 &&
            this->bidSize == rhv.bidSize &&
            abs(this->ask - rhv.ask) < 0.001 &&
            this->askSize == rhv.askSize &&
            this->volume == rhv.volume)
            {
                return true;
            }
            return false;
        }
    };   
}