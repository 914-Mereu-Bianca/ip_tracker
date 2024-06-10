#include <gtest/gtest.h>
#include "../src/client.cpp"

class FakeServer : public data::IPService::Service {
public:
    FakeServer() {}

    void runServer() {
        grpc::ServerBuilder builder;
        builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
        builder.RegisterService(this);
        server = builder.BuildAndStart();
        std::cout << "Server listening " << std::endl;
        server->Wait();
    }

    void shutdown() {
        server->Shutdown();
    }

private: 

    grpc::Status Authenticate(grpc::ServerContext *context, const data::Credentials* request, data::OperationResponse* response) {
        std::cout<<request->username()<< " "<<request->password()<<std::endl;
        if (request->username() == "user" && request->password() == "password") {
            response->set_success(true);
            response->set_message("Authentication successful");
        } else {
            response->set_success(false);
            response->set_message("Authentication failed");
        }
        return grpc::Status::OK;
    }

private:
    std::unique_ptr<grpc::Server> server;
};


TEST(ClientAuthenticationTest, Test) {
    
    FakeServer fake_server;
    std::thread thread = std::thread([&fake_server]() {
        fake_server.runServer();
    });

    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    MainClient client(channel);

    EXPECT_FALSE(client.Authenticate("usr", "password"));
    EXPECT_TRUE(client.Authenticate("user", "password"));

    fake_server.shutdown();
    thread.join();
    
}