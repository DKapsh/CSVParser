#include <string>
#include <vector>
#include <gtest/gtest.h>
namespace
{
    std::vector<std::string> ParseRow(const std::string& input)
    {
        std::vector<std::string> row;
        row.push_back(input.substr(0, input.find(',')));
        row.push_back(input.substr(input.find(',')+1, input.length() - row[0].length() -1));
        return row;
    }
}

TEST(CSVParser, ParseTwoValueInAString)
{
    std::string inputString = "15051420,T";
    std::vector<std::string> row = {"15051420", "T"};
    EXPECT_EQ(row, ParseRow(inputString));
}

