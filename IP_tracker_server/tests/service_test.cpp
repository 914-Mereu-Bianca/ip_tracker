#include <gtest/gtest.h>
#include "../router_communication/src/router.cpp"
#include "../server/src/admin.cpp"
#include "../server/src/server.cpp"
#include "../server/src/server_controller.cpp"

class FakeClient {
public:
    FakeClient(std::shared_ptr<grpc::Channel> channel) : _stub(data::IPService::NewStub(channel)) {}

    bool Authenticate(const std::string& username, const std::string& password) {
        data::Credentials request;
        request.set_username(username);
        request.set_password(password);

        data::OperationResponse response;
        grpc::ClientContext context;
        grpc::Status status = _stub->Authenticate(&context, request, &response);

        if (status.ok()) {
            return response.success();
        } else {
            return false;
        }   
    }

    data::OperationResponse ChangeCredentials(const std::string& username, const std::string& password, const std::string& current_password, bool reset) {
        data::Credentials request;
        request.set_username(username);
        request.set_password(password);
        request.set_old_password(current_password);
        request.set_reset(reset);

        data::OperationResponse response;
        grpc::ClientContext context;

        grpc::Status status = _stub->ChangeCredentials(&context, request, &response);

        if (status.ok()) {
        std::cout << "RPC send successfully: " << response.message() << std::endl;
        return response;
        } else {
        std::cout << "RPC failed: " << status.error_message() << std::endl;
        return response;
        }
    }

    data::OperationResponse ChangeEmail(const std::string& email, const std::string& password) {
        data::Email request;
        request.set_email(email);
        std::cout<<password<<std::endl;
        request.set_password(password);

        data::OperationResponse response;
        grpc::ClientContext context;

        grpc::Status status = _stub->ChangeEmail(&context, request, &response);

        if (status.ok()) {
        std::cout << "RPC send successfully: " << response.message() << std::endl;
        return response;
        } else {
        std::cout << "RPC failed: " << status.error_message() << std::endl;
        return response;
        }
    }

    data::OperationResponse ManageDevice(const std::string& operation, const std::string& name, const std::string &mac) {
        data::Request request;
        request.set_request(operation);
        request.set_name(name);
        request.set_mac(mac);
        data::OperationResponse response;
        grpc::ClientContext context;

        grpc::Status status = _stub->ManageDevice(&context, request, &response);

        if (status.ok()) {
        std::cout << "RPC send successfully: " << response.message() << std::endl;
        return response;
        } else {
        std::cout << "RPC failed: " << status.error_message() << std::endl;
        return response;
        }
    }


private:
    std::unique_ptr<data::IPService::Stub> _stub;
};


class ServiceTest : public ::testing::Test {
protected:
    Admin admin;
    MainService test_server;
    std::thread server_thread;

    ServiceTest() : admin("../../utils/credentials.txt"), test_server("0.0.0.0", 50052, admin) {}

    void SetUp() override {
        server_thread = std::thread([this]() {
            test_server.runServer();
        });
    }

    void TearDown() override {
        test_server.shutdown();
        server_thread.join();
    }
};


TEST_F(ServiceTest, AuthenticationTest) {
    FakeClient fake_client(grpc::CreateChannel("localhost:50052", grpc::InsecureChannelCredentials()));
    EXPECT_FALSE(fake_client.Authenticate("us", "password"));
    EXPECT_TRUE(fake_client.Authenticate("admin", "admin"));
}

TEST_F(ServiceTest, ChangeCredentialsTest) {
    FakeClient fake_client(grpc::CreateChannel("localhost:50052", grpc::InsecureChannelCredentials()));
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
    auto resp = fake_client.ChangeCredentials("", "", "admin", 0);
    EXPECT_EQ(resp.message(), "New password cannot be empty!");
}

TEST_F(ServiceTest, ChangeEmailTest) {
    FakeClient fake_client(grpc::CreateChannel("localhost:50052", grpc::InsecureChannelCredentials()));
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
    auto resp = fake_client.ChangeEmail("", "admin");
    EXPECT_EQ(resp.message(), "Wrong email format!");
}

TEST_F(ServiceTest, ManageDeviceTest) {
    FakeClient fake_client(grpc::CreateChannel("localhost:50052", grpc::InsecureChannelCredentials()));
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
}