#include <string>
#include <gtest/gtest.h>
namespace
{
    struct Row
    {
       std::string timestamp;
       std::string ticker;
    };
    Row ParseRow(const std::string& input)
    {
        Row row;
        row.timestamp = input.substr(0, input.find(','));
        row.ticker = input.substr(input.find(',')+1, input.length() - row.timestamp.length() -1);
        return row;
    }
    bool operator== (const Row& lhv, const Row& rhv)
    {     
        if(lhv.timestamp == rhv.timestamp && lhv.ticker == rhv.ticker)
        {
            return true;
        }
        return false;
    }
}

TEST(CSVParser, ParseTwoValueInAString)
{
    std::string inputString = "15051420,T";
    Row row = {"15051420", "T"};
    EXPECT_EQ(row, ParseRow(inputString));
}

