#include <gtest/gtest.h>
#include "../parser/src/data_parser.cpp"

class ParserTest : public ::testing::Test {
protected:
    Parser parser;
    std::string fake_response_get_all;
    std::string fake_response_blocked;
    ParserTest() {}

    void SetUp() override {
        fake_response_get_all = "";
        fake_response_blocked = "";
    }

    void TearDown() override {
    }
    
};

