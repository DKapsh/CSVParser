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
    const std::map<std::string, std::vector<row::Quote>> s_tickerData = {{"T",  {{15051420, 47.47, 10, 47.51, 14, 10253}}},
                                                                         {"BC", {{15051420, 77.71, 12, 79.13, 12, 14}}},
                                                                         {"R",  {{15051420, 90, 10, 99.23, 13, 13}}},
                                                                         {"QTM",{{15051420, 16.21, 137, 17.05, 13,13}}},
                                                                         {"S",  {{15051420, 21.23, 18, 21.3, 12, 1505}}}};
    const std::vector<row::Quote>s_QTMTikers = { {15051420, 16.21, 137, 17.05, 13, 13},
                                                 {15051421, 16.21, 137, 17.05, 13, 13}};
    const std::vector<row::Quote>s_qtmTikersWithDifferentBid = {{15051420, 16.21, 137, 17.05, 13, 13},
                                                                {15051777, 17, 11, 17.05, 19, 54341}};
                                                
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
    std::stringstream in (s_marketData), out;
    parser::CSVParser parser(in);
    std::map<std::string, std::vector<row::Quote>> tickerMap;
    parser.Read(tickerMap);
    EXPECT_EQ(s_tickerData, tickerMap);
}

TEST(MetricsCounter, ReturnCorrectVolumeSummIfTickerT)
{
    metrics::MetricsCalculator calculator;
    const std::vector<row::Quote> tickersT = {{15051420, 47.47, 10, 47.51, 14, 10253}};
    uint64_t volumeSum = 10253;
    EXPECT_EQ(volumeSum, calculator.VolumeSum(tickersT));
}

TEST(MetricsCounter, ReturnCorrectVolumeSummIfTickerQTM)
{
    metrics::MetricsCalculator calculator;
    uint64_t volumeSum = s_QTMTikers[0].volume+ s_QTMTikers[1].volume;
    EXPECT_EQ(volumeSum, calculator.VolumeSum(s_QTMTikers));
}

TEST(MetricsCounter, SubAskBid_Return0_04IfTickerTypeT)
{
    metrics::MetricsCalculator calculator;
    std::vector<double> askSubBid = {0.04};
    const std::vector<row::Quote> tickersT = {{15051420, 47.47, 10, 47.51, 14, 10253}};
    const double absError = 0.001;
    EXPECT_NEAR(askSubBid[0], calculator.AskSubBid(tickersT)[0], absError);
}

TEST(MetricsCounter, SubAskBid_ReturnCorrectResultsIfTickerTypeQTM)
{
    metrics::MetricsCalculator calculator;
    std::vector<double> askSubBid = {0.84, 0.05};
    const double absError = 0.001;
    EXPECT_NEAR(askSubBid[0], calculator.AskSubBid(s_qtmTikersWithDifferentBid)[0], absError);
    EXPECT_NEAR(askSubBid[1], calculator.AskSubBid(s_qtmTikersWithDifferentBid)[1], absError);
}

TEST(MetricsCounter, MinOfSubAskAndBid_Return0_05IfTickerTypeQTM)
{
    metrics::MetricsCalculator calculator;
    double min = 0.05;
    const double absError = 0.001;
    EXPECT_NEAR(min, calculator.GetMin(calculator.AskSubBid(s_qtmTikersWithDifferentBid)), absError);
}

TEST(MetricsCounter, MaxOfSubAskAndBid_Return0_84IfTickerTypeQTM)
{
    metrics::MetricsCalculator calculator;
    double max = 0.84;
    const double absError = 0.001;
    EXPECT_NEAR(max, calculator.GetMax(calculator.AskSubBid(s_qtmTikersWithDifferentBid)), absError);
}

TEST(MetricsCounter, MaxOfSubAskAndBid_ThrowIfDataIsEmpty)
{
    metrics::MetricsCalculator calculator;
    EXPECT_THROW(calculator.GetMax({}), std::exception);
}

TEST(MetricsCounter, MinOfSubAskAndBid_ThrowIfDataIsEmpty)
{
    metrics::MetricsCalculator calculator;
    EXPECT_THROW(calculator.GetMin({}), std::exception);
}

TEST(MetricsCounter, RatioOfAmountsReturnCorrectResultForOneQuote)
{
    row::Quote qtmTikers = {15051420, 16.21, 137, 17.05, 13, 13};
    metrics::MetricsCalculator calculator;
    double result = 16.977;
    const double absError = 0.001;
    EXPECT_NEAR(result, calculator.GetRatio({qtmTikers}), absError);
}

TEST(MetricsCounter, RatioOfAmountsReturnCorrectResultForTwoQuote)
{
    metrics::MetricsCalculator calculator;
    double correctRatioForqtmTicker = 16.984;
    const double absError = 0.0001;
    EXPECT_NEAR(correctRatioForqtmTicker, calculator.GetRatio(s_qtmTikersWithDifferentBid), absError);
}

TEST(CSVParser, FormedCorrectOutputString_SingleQTMTicker)
{
    std::string outputData = "QTM, 0.840000, 0.840000, 13, 16.977201";
    std::vector<row::Quote>qtmTiker = {{15051420, 16.21, 137, 17.05, 13, 13}};
    EXPECT_NE(std::string::npos, utils::FormedOutputData("QTM", qtmTiker).find(outputData));
}

TEST(CSVParser, FormedCorrectOutputString_TwoQTMTicker)
{
    std::string outputData = "QTM, 0.840000, 0.050000, 54354, 16.984056";
    EXPECT_NE(std::string::npos, utils::FormedOutputData("QTM", s_qtmTikersWithDifferentBid).find(outputData));
}

TEST(CSVParser, SetFormedDataIntoStream)
{
    std::stringstream out, in;
    parser::CSVParser parser(in);
    const std::string outString = "T, 0.040000, 0.040000, 10253, 47.486668";
    const std::map<std::string, std::vector<row::Quote>> tickerMap = {{"T", {{15051420, 47.47, 10, 47.51, 14, 10253}}}};
    parser.Write(tickerMap, out);
    EXPECT_NE(std::string::npos, out.str().find(outString));
}

TEST(CSVParser, AddLFToTheEndOfTheString)
{
    std::string outputData = "QTM, 0.840000, 0.050000, 54354, 16.984056\n";
    EXPECT_EQ(outputData, utils::FormedOutputData("QTM", s_qtmTikersWithDifferentBid));
}

TEST(CSVParser, SetFormedDataWithTwoTickerTypeIntoStream)
{
    std::stringstream out, in;
    parser::CSVParser parser(in);
    const std::string outString = "QTM, 0.840000, 0.050000, 54354, 16.984056\n"
                                  "T, 0.040000, 0.040000, 10253, 47.486668\n";
    const std::map<std::string, std::vector<row::Quote>> tickerMap = {{"T", {{15051420, 47.47, 10, 47.51, 14, 10253}}},
                                                                      {"QTM", s_qtmTikersWithDifferentBid}};
    parser.Write(tickerMap, out);
    EXPECT_EQ(outString, out.str());
}

TEST(CSVParser, NoThrowIfDataIsEmpty)
{
    std::stringstream in;
    parser::CSVParser parser(in);
    std::string out;
    const std::map<std::string, std::vector<row::Quote>> tickerMap = {};
    EXPECT_NO_THROW(parser.CalculateMetrics(tickerMap, out));
}

TEST(CSVParser, CalculatedDataWithTwoTickerType)
{
    std::stringstream in;
    parser::CSVParser parser(in);
    std::string out;
    const std::string outString = "QTM, 0.840000, 0.050000, 54354, 16.984056\n"
                                  "T, 0.040000, 0.040000, 10253, 47.486668\n";
    const std::map<std::string, std::vector<row::Quote>> tickerMap = {{"T", {{15051420, 47.47, 10, 47.51, 14, 10253}}},
                                                                      {"QTM", s_qtmTikersWithDifferentBid}};
    parser.CalculateMetrics(tickerMap, out);
    EXPECT_EQ(outString, out);
}
