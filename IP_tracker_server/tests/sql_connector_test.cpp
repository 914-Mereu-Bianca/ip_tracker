#include "../database/src/sql_connector.cpp"
#include <gtest/gtest.h>

class SqlConnectorTest : public ::testing::Test {
protected:
    SqlConnector sql_connector;
    SqlConnectorTest() {}

    void SetUp() override {
        
    }

    void TearDown() override {
    }
    
};

