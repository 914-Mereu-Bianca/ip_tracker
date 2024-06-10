#include "../mail_communication/src/send_mail.cpp"
#include <gtest/gtest.h>

class MailTest : public ::testing::Test {
protected:
    SendMail mail;
    MailTest() {}

    void SetUp() override {
        
    }

    void TearDown() override {
    }
    
};

TEST_F(MailTest, SendMailTest) {
    mail.send();
}

