#include "../router_communication/src/router_controller.cpp"
#include <gtest/gtest.h>

class RouterTest : public ::testing::Test {
protected:
    RouterController router_controller;
    RouterTest() {}

    void SetUp() override {
        
    }

    void TearDown() override {
    }
    
};


