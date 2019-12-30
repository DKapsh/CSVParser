#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <gtest/gtest.h>
namespace
{
    std::vector<std::string> SplitString(const std::string& input)
    {
        std::vector<std::string> row;
        int posPrev = 0;
        int posNext = 0;
        while(posNext < input.length())
        {   
            posNext = input.find(',', posPrev);
            if(posNext == std::string::npos)
            {
                posNext == input.length();
            }
            row.push_back(input.substr(posPrev, posNext- posPrev));
            posPrev = posNext + 1;
        }
        return row;
    }

    std::vector<std::string> ReadRows(std::stringstream& ss)
    {
        return {};
    }
}

TEST(CSVParser, ParseTwoValueInAString)
{
    std::string inputString = "15051420,T";
    std::vector<std::string> row = {"15051420", "T"};
    EXPECT_EQ(row, SplitString(inputString));
}

TEST(CSVParser, ParseThreeValueInAString)
{
    std::string inputString = "15051420,T,47.47";
    std::vector<std::string> row = {"15051420", "T", "47.47"};
    EXPECT_EQ(row, SplitString(inputString));
}

TEST(CSVParser, ParseAllValuesInAString)
{
    std::string inputString = "15051420,T,47.47,10,47.51,14,10253";
    std::vector<std::string> row = {"15051420", "T", "47.47", "10", "47.51", "14", "10253"};
    EXPECT_EQ(row, SplitString(inputString));
}

TEST(CSVParser, GetTwoRowFromStream)
{
    std::stringstream in ("15051420,T,47.47,10,47.51,14,10253\n15051420,BC,77.71,12,79.13,12,14");
    std::vector<std::string> rows = {"15051420,T,47.47,10,47.51,14,10253", "15051420,BC,77.71,12,79.13,12,14"};
    EXPECT_EQ(rows, ReadRows(in));
}

