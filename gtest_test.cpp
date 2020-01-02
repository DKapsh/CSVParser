#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <gtest/gtest.h>
namespace
{
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
    const std::string s_marketData = "15051420,T,47.47,10,47.51,14,10253\n"
                                     "15051420,BC,77.71,12,79.13,12,14\n"
                                     "15051420,R,90,10,99.23,13,13\n"
                                     "15051420,QTM,16.21,137,17.05,13,13\n"
                                     "15051420,S,21.23,18,21.3,12,1505";
    const std::vector<Row>s_rows = {{15051420, "T", 47.47, 10, 47.51, 14, 10253}, 
                                    {15051420, "BC", 77.71, 12, 79.13, 12, 14},
                                    {15051420, "R", 90, 10, 99.23, 13, 13}, 
                                    {15051420, "QTM", 16.21, 137, 17.05, 13,13}, 
                                    {15051420, "S", 21.23, 18, 21.3, 12, 1505}};
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
    bool operator== (const Row& lhv, const Row& rhv)
    {
        if(lhv.timestamp == rhv.timestamp &&
           lhv.ticker == rhv.ticker &&
           abs(lhv.bid - rhv.bid) < 0.001 &&
           lhv.bidSize == rhv.bidSize &&
           abs(lhv.ask - rhv.ask) < 0.001 &&
           lhv.askSize == rhv.askSize &&
           lhv.volume == rhv.volume)
        {
            return true;
        }
        return false;
    }
    Row SetRow(const std::vector<std::string>& splitedString)
    {
        Row result;
        result.timestamp = atoi(splitedString[0].data());
        result.ticker = splitedString[1];
        result.bid = atof(splitedString[2].data());
        result.bidSize = atoi(splitedString[3].data());
        result.ask = atof(splitedString[4].data());
        result.askSize = atoi(splitedString[5].data());
        result.volume = atoi(splitedString[6].data());
        return result;
    }

    class CSVParser
    {
        public:
            explicit CSVParser(std::stringstream& in)
            {
                std::vector<std::string> lines = ReadRows(in);
                for(auto& line : lines)
                {
                    m_data.push_back(SetRow(SplitString(line)));
                }
            }
            std::vector<Row> GetData()
            {
                return m_data;
            }
        private:
            std::vector<Row> m_data;
    };
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

TEST(CSVParser, SetRowStructFromSplitedString)
{
    std::vector<std::string> splitedRow = {"15051420", "T", "47.47", "10", "47.51", "14", "10253"};
    Row row = {15051420, "T", 47.47, 10, 47.51, 14, 10253};
    EXPECT_EQ(row, SetRow(splitedRow));
}

TEST(CSVParser, SetVectorOfRowsFromStream)
{
    std::stringstream in (s_marketData);
    CSVParser parser(in);
    EXPECT_EQ(s_rows, parser.GetData());
}

