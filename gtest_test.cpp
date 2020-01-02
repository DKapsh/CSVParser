#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <gtest/gtest.h>
namespace
{
    const std::string s_marketData = "15051420,T,47.47,10,47.51,14,10253\n"
                                     "15051420,BC,77.71,12,79.13,12,14\n"
                                     "15051420,R,90,10,99.23,13,13\n"
                                     "15051420,QTM,16.21,137,17.05,13,13\n"
                                     "15051420,S,21.23,18,21.3,12,1505";
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
        std::string tmp;
        std::vector<std::string> result;
        while(std::getline(ss, tmp))
        {
            result.push_back(tmp);
        }
        return result;
    }

    struct Row
    {
        uint64_t timestamp;
        std::string ticker;
        double bid;
        uint64_t bidSize;
        double ask;
        uint64_t askSize;
        uint64_t volume;
    };
    bool operator== (const Row& lhv, const Row& rhv)
    {
        return false;
    }
    Row SetRow(const std::vector<std::string>& splitedString)
    {
        Row result;
        return result;
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

TEST(CSVParser, GetFiveRowFromStream)
{
    std::stringstream in (s_marketData);
    std::vector<std::string> rows = {"15051420,T,47.47,10,47.51,14,10253", 
                                     "15051420,BC,77.71,12,79.13,12,14",
                                     "15051420,R,90,10,99.23,13,13",
                                     "15051420,QTM,16.21,137,17.05,13,13",
                                     "15051420,S,21.23,18,21.3,12,1505"
                                     };
    EXPECT_EQ(rows, ReadRows(in));
}

TEST(CSVParser, SetRowStruct)
{
    std::vector<std::string> splitedRow = {"15051420", "T", "47.47", "10", "47.51", "14", "10253"};
    Row row;
    EXPECT_EQ(row, SetRow(splitedRow));
}

