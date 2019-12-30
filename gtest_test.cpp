#include <string>
#include <vector>
#include <stdio.h>
#include <gtest/gtest.h>
namespace
{
    std::vector<std::string> ParseRow(const std::string& input)
    {
        std::vector<std::string> row;
        int posPrev = 0;
        int posNext = input.find(',', posPrev);
        row.push_back(input.substr(posPrev, posNext));
        posPrev = posNext + 1;
        posNext = input.find(',', posPrev);
        if(posNext == std::string::npos)
        {
            posNext == input.length();
            row.push_back(input.substr(posPrev, posNext - posPrev));
            return row;
        }
        row.push_back(input.substr(posPrev, posNext - posPrev));
        posPrev = posNext + 1;
        row.push_back(input.substr(posPrev, input.length() - posPrev));
        printf("%s\n", row[1].data());
        return row;
    }
}

TEST(CSVParser, ParseTwoValueInAString)
{
    std::string inputString = "15051420,T";
    std::vector<std::string> row = {"15051420", "T"};
    EXPECT_EQ(row, ParseRow(inputString));
}

TEST(CSVParser, ParseThreeValueInAString)
{
    std::string inputString = "15051420,T,47.47";
    std::vector<std::string> row = {"15051420", "T", "47.47"};
    EXPECT_EQ(row, ParseRow(inputString));
}
