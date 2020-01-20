#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <gtest/gtest.h>
#include "CSVParser.h"
#include "ParserUtils.h"
#include "MetricsCalculator.h"

namespace 
{
    const std::string s_marketData = "15051420,T,47.47,10,47.51,14,10253\n"
                                     "15051420,BC,77.71,12,79.13,12,14\n"
                                     "15051420,R,90,10,99.23,13,13\n"
                                     "15051420,QTM,16.21,137,17.05,13,13\n"
                                     "15051420,S,21.23,18,21.3,12,1505";
    const std::vector<row::Row>s_rows = {{15051420, "T", 47.47, 10, 47.51, 14, 10253}, 
                                    {15051420, "BC", 77.71, 12, 79.13, 12, 14},
                                    {15051420, "R", 90, 10, 99.23, 13, 13}, 
                                    {15051420, "QTM", 16.21, 137, 17.05, 13,13}, 
                                    {15051420, "S", 21.23, 18, 21.3, 12, 1505}};
    const std::map<std::string, std::vector<row::Quote>> s_tickerData = {{"T",  {{15051420, 47.47, 10, 47.51, 14, 10253}}},
                                                                         {"BC", {{15051420, 77.71, 12, 79.13, 12, 14}}},
                                                                         {"R",  {{15051420, 90, 10, 99.23, 13, 13}}},
                                                                         {"QTM",{{15051420, 16.21, 137, 17.05, 13,13}}},
                                                                         {"S",  {{15051420, 21.23, 18, 21.3, 12, 1505}}}};
    const std::vector<row::Row>s_rowsWithQTMTiker = { {15051420, "QTM", 16.21, 137, 17.05, 13, 13},
                                                      {15051421, "QTM", 16.21, 137, 17.05, 13, 13}};
    const std::vector<row::Row>s_qtmTikerWithDifferentBid = {{15051420, "QTM", 16.21, 137, 17.05, 13, 13},
                                                             {15051777, "QTM", 17, 11, 17.05, 19, 54341}};
                                                
}

TEST(CSVParser, ParseTwoValueInAString)
{
    std::string inputString = "15051420,T";
    std::vector<std::string> row = {"15051420", "T"};
    EXPECT_EQ(row, utils::SplitString(inputString));
}

TEST(CSVParser, ParseThreeValueInAString)
{
    std::string inputString = "15051420,T,47.47";
    std::vector<std::string> row = {"15051420", "T", "47.47"};
    EXPECT_EQ(row, utils::SplitString(inputString));
}

TEST(CSVParser, ParseAllValuesInAString)
{
    std::string inputString = "15051420,T,47.47,10,47.51,14,10253";
    std::vector<std::string> row = {"15051420", "T", "47.47", "10", "47.51", "14", "10253"};
    EXPECT_EQ(row, utils::SplitString(inputString));
}

TEST(CSVParser, GetTwoRowFromStream)
{
    std::stringstream in ("15051420,T,47.47,10,47.51,14,10253\n15051420,BC,77.71,12,79.13,12,14");
    std::vector<std::string> rows = {"15051420,T,47.47,10,47.51,14,10253", "15051420,BC,77.71,12,79.13,12,14"};
    EXPECT_EQ(rows, utils::ReadRows(in));
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
    EXPECT_EQ(rows, utils::ReadRows(in));
}

TEST(CSVParser, SetRowStructFromSplitedStringInEmptyMap)
{
    std::vector<std::string> splitedRow = {"15051420", "T", "47.47", "10", "47.51", "14", "10253"};
    row::Quote row = {15051420, 47.47, 10, 47.51, 14, 10253};
    std::map<std::string, std::vector<row::Quote>> inputMap;
    std::map<std::string, std::vector<row::Quote>> outputMap = {{"T", {{row}}}};
    utils::SetRow(splitedRow, inputMap);
    EXPECT_EQ(outputMap, inputMap);
}

TEST(CSVParser, SetRowStructFromSplitedStringInMapWithOneElement)
{
    std::vector<std::string> splitedRow = {"15051420", "T", "47.47", "10", "47.51", "14", "10253"};
    row::Quote row = {15051420, 47.47, 10, 47.51, 14, 10253};
    std::map<std::string, std::vector<row::Quote>> inputMap = {{"T", {row}}};
    std::map<std::string, std::vector<row::Quote>> outputMap = {{"T", {row, row}}};
    utils::SetRow(splitedRow, inputMap);
    EXPECT_EQ(outputMap, inputMap);
}

TEST(CSVParser, SetVectorOfRowsFromStream)
{
    std::stringstream in (s_marketData);
    parser::CSVParser parser(in);
    std::map<std::string, std::vector<row::Quote>> tickerMap;
    parser.ParseData(tickerMap);
    EXPECT_EQ(s_tickerData, tickerMap);
}

TEST(MetricsCounter, ReturnCorrectVolumeSummIfTickerT)
{
    metrics::MetricsCalculator calculator(s_rows);
    uint64_t volumeSum = 10253;
    calculator.SetTickerType("T");
    EXPECT_EQ(volumeSum, calculator.VolumeSum());
}

TEST(MetricsCounter, ReturnCorrectVolumeSummIfTickerQTM)
{
    metrics::MetricsCalculator calculator(s_rowsWithQTMTiker);
    uint64_t volumeSum = s_rowsWithQTMTiker[0].volume+ s_rowsWithQTMTiker[1].volume;
    calculator.SetTickerType("QTM");
    EXPECT_EQ(volumeSum, calculator.VolumeSum());
}

TEST(MetricsCounter, SubAskBid_Return0_04IfTickerTypeT)
{
    metrics::MetricsCalculator calculator(s_rows);
    std::vector<double> askSubBid = {0.04};
    calculator.SetTickerType("T");
    const double absError = 0.001;
    EXPECT_NEAR(askSubBid[0], calculator.AskSubBid()[0], absError);
}

TEST(MetricsCounter, SubAskBid_ReturnCorrectResultsIfTickerTypeQTM)
{
    metrics::MetricsCalculator calculator(s_qtmTikerWithDifferentBid);
    std::vector<double> askSubBid = {0.84, 0.05};
    calculator.SetTickerType("QTM");
    const double absError = 0.001;
    EXPECT_NEAR(askSubBid[0], calculator.AskSubBid()[0], absError);
    EXPECT_NEAR(askSubBid[1], calculator.AskSubBid()[1], absError);
}

TEST(MetricsCounter, MinOfSubAskAndBid_Return0_05IfTickerTypeQTM)
{
    metrics::MetricsCalculator calculator(s_qtmTikerWithDifferentBid);
    double min = 0.05;
    calculator.SetTickerType("QTM");
    const double absError = 0.001;
    EXPECT_NEAR(min, calculator.GetMin(calculator.AskSubBid()), absError);
}

TEST(MetricsCounter, MaxOfSubAskAndBid_Return0_84IfTickerTypeQTM)
{
    metrics::MetricsCalculator calculator(s_qtmTikerWithDifferentBid);
    double max = 0.84;
    calculator.SetTickerType("QTM");
    const double absError = 0.001;
    EXPECT_NEAR(max, calculator.GetMax(calculator.AskSubBid()), absError);
}

TEST(MetricsCounter, MaxOfSubAskAndBid_ThrowIfDataIsEmpty)
{
    metrics::MetricsCalculator calculator({});
    EXPECT_THROW(calculator.GetMax({}), std::exception);
}

TEST(MetricsCounter, MinOfSubAskAndBid_ThrowIfDataIsEmpty)
{
    metrics::MetricsCalculator calculator({});
    EXPECT_THROW(calculator.GetMin({}), std::exception);
}

TEST(MetricsCounter, RatioOfAmountsReturnCorrectResultForOneQuote)
{
    row::Row qtmTiker = {15051420, "QTM", 16.21, 137, 17.05, 13, 13};
    metrics::MetricsCalculator calculator({qtmTiker});
    double result = (qtmTiker.bid*qtmTiker.askSize + qtmTiker.bidSize*qtmTiker.ask)/(qtmTiker.askSize+qtmTiker.bidSize);
    const double absError = 0.001;
    EXPECT_NEAR(result, calculator.GetRatio(), absError);
}

TEST(MetricsCounter, RatioOfAmountsReturnCorrectResultForTwoQuote)
{
    metrics::MetricsCalculator calculator(s_qtmTikerWithDifferentBid);
    double correctRatioForqtmTicker = 16.984;
    const double absError = 0.0001;
    EXPECT_NEAR(correctRatioForqtmTicker, calculator.GetRatio(), absError);
}

TEST(CSVParser, FormedCorrectOutputString_SingleQTMTicker)
{

}