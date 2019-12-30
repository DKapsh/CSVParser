#include <string>
#include <gtest/gtest.h>
namespace
{
    struct Row
    {
       
    };
    Row ParseRow(const std::string& input)
    {
        Row row;
        return row;
    }
    bool operator== (const Row& lhv, const Row& rhv)
    {     
        return false;
    }
}

TEST(CSVParser, ParseTwoValueInAString)
{
    std::string inputString = "15051420,T";
    Row row;
    EXPECT_EQ(row, ParseRow(inputString));
}

