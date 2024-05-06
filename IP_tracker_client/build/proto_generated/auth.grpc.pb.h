// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: auth.proto
#ifndef GRPC_auth_2eproto__INCLUDED
#define GRPC_auth_2eproto__INCLUDED

#include "auth.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

class AuthService final {
 public:
  static constexpr char const* service_full_name() {
    return "AuthService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status Authenticate(::grpc::ClientContext* context, const ::AuthRequest& request, ::AuthResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::AuthResponse>> AsyncAuthenticate(::grpc::ClientContext* context, const ::AuthRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::AuthResponse>>(AsyncAuthenticateRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::AuthResponse>> PrepareAsyncAuthenticate(::grpc::ClientContext* context, const ::AuthRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::AuthResponse>>(PrepareAsyncAuthenticateRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void Authenticate(::grpc::ClientContext* context, const ::AuthRequest* request, ::AuthResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void Authenticate(::grpc::ClientContext* context, const ::AuthRequest* request, ::AuthResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::AuthResponse>* AsyncAuthenticateRaw(::grpc::ClientContext* context, const ::AuthRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::AuthResponse>* PrepareAsyncAuthenticateRaw(::grpc::ClientContext* context, const ::AuthRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status Authenticate(::grpc::ClientContext* context, const ::AuthRequest& request, ::AuthResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::AuthResponse>> AsyncAuthenticate(::grpc::ClientContext* context, const ::AuthRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::AuthResponse>>(AsyncAuthenticateRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::AuthResponse>> PrepareAsyncAuthenticate(::grpc::ClientContext* context, const ::AuthRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::AuthResponse>>(PrepareAsyncAuthenticateRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void Authenticate(::grpc::ClientContext* context, const ::AuthRequest* request, ::AuthResponse* response, std::function<void(::grpc::Status)>) override;
      void Authenticate(::grpc::ClientContext* context, const ::AuthRequest* request, ::AuthResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::AuthResponse>* AsyncAuthenticateRaw(::grpc::ClientContext* context, const ::AuthRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::AuthResponse>* PrepareAsyncAuthenticateRaw(::grpc::ClientContext* context, const ::AuthRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Authenticate_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status Authenticate(::grpc::ServerContext* context, const ::AuthRequest* request, ::AuthResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_Authenticate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_Authenticate() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Authenticate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Authenticate(::grpc::ServerContext* /*context*/, const ::AuthRequest* /*request*/, ::AuthResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAuthenticate(::grpc::ServerContext* context, ::AuthRequest* request, ::grpc::ServerAsyncResponseWriter< ::AuthResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Authenticate<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_Authenticate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_Authenticate() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::AuthRequest, ::AuthResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::AuthRequest* request, ::AuthResponse* response) { return this->Authenticate(context, request, response); }));}
    void SetMessageAllocatorFor_Authenticate(
        ::grpc::MessageAllocator< ::AuthRequest, ::AuthResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::AuthRequest, ::AuthResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_Authenticate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Authenticate(::grpc::ServerContext* /*context*/, const ::AuthRequest* /*request*/, ::AuthResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* Authenticate(
      ::grpc::CallbackServerContext* /*context*/, const ::AuthRequest* /*request*/, ::AuthResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_Authenticate<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_Authenticate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_Authenticate() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Authenticate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Authenticate(::grpc::ServerContext* /*context*/, const ::AuthRequest* /*request*/, ::AuthResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Authenticate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_Authenticate() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Authenticate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Authenticate(::grpc::ServerContext* /*context*/, const ::AuthRequest* /*request*/, ::AuthResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAuthenticate(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_Authenticate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_Authenticate() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->Authenticate(context, request, response); }));
    }
    ~WithRawCallbackMethod_Authenticate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Authenticate(::grpc::ServerContext* /*context*/, const ::AuthRequest* /*request*/, ::AuthResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* Authenticate(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Authenticate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_Authenticate() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::AuthRequest, ::AuthResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::AuthRequest, ::AuthResponse>* streamer) {
                       return this->StreamedAuthenticate(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_Authenticate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Authenticate(::grpc::ServerContext* /*context*/, const ::AuthRequest* /*request*/, ::AuthResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedAuthenticate(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::AuthRequest,::AuthResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_Authenticate<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_Authenticate<Service > StreamedService;
};


#endif  // GRPC_auth_2eproto__INCLUDED
