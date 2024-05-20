#include <gtest/gtest.h>
#include "../src/server.cpp"
#include "../src/router_communication/router.cpp"
#include "../src/router_communication/request_handler.cpp"
#include "../src/mail_communication/send_mail.cpp"
#include "../src/data_parser.cpp"

class FakeClient {
public:
    FakeClient(std::shared_ptr<grpc::Channel> channel) : _stub(data::IPService::NewStub(channel)) {}

    bool Authenticate(const std::string& username, const std::string& password) {
        data::AuthRequest request;
        request.set_username(username);
        request.set_password(password);

        data::AuthResponse response;
        grpc::ClientContext context;
        grpc::Status status = _stub->Authenticate(&context, request, &response);

        if (status.ok()) {
            return response.success();
        } else {
            return false;
        }   
    }

private:
    std::unique_ptr<data::IPService::Stub> _stub;
};


TEST(ServerAuthenticationTest, Test) {
    MainService test_server("0.0.0.0", 50052); 
    std::thread thread = std::thread([&test_server]() {
        test_server.runServer();
    });

    FakeClient fake_client(grpc::CreateChannel("localhost:50052", grpc::InsecureChannelCredentials()));
    EXPECT_FALSE(fake_client.Authenticate("us", "password"));
    EXPECT_TRUE(fake_client.Authenticate("user", "password"));
    
    test_server.shutdown();
    
    thread.join();
    
}