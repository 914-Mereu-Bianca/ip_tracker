// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: auth.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_auth_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_auth_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4023000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4023001 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_auth_2eproto

PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_auth_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable
    descriptor_table_auth_2eproto;
class AuthRequest;
struct AuthRequestDefaultTypeInternal;
extern AuthRequestDefaultTypeInternal _AuthRequest_default_instance_;
class AuthResponse;
struct AuthResponseDefaultTypeInternal;
extern AuthResponseDefaultTypeInternal _AuthResponse_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template <>
::AuthRequest* Arena::CreateMaybeMessage<::AuthRequest>(Arena*);
template <>
::AuthResponse* Arena::CreateMaybeMessage<::AuthResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE


// ===================================================================


// -------------------------------------------------------------------

class AuthRequest final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:AuthRequest) */ {
 public:
  inline AuthRequest() : AuthRequest(nullptr) {}
  ~AuthRequest() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR AuthRequest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  AuthRequest(const AuthRequest& from);
  AuthRequest(AuthRequest&& from) noexcept
    : AuthRequest() {
    *this = ::std::move(from);
  }

  inline AuthRequest& operator=(const AuthRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline AuthRequest& operator=(AuthRequest&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const AuthRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const AuthRequest* internal_default_instance() {
    return reinterpret_cast<const AuthRequest*>(
               &_AuthRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(AuthRequest& a, AuthRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(AuthRequest* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(AuthRequest* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  AuthRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<AuthRequest>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const AuthRequest& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const AuthRequest& from) {
    AuthRequest::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(AuthRequest* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "AuthRequest";
  }
  protected:
  explicit AuthRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kUsernameFieldNumber = 1,
    kPasswordFieldNumber = 2,
  };
  // string username = 1;
  void clear_username() ;
  const std::string& username() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_username(Arg_&& arg, Args_... args);
  std::string* mutable_username();
  PROTOBUF_NODISCARD std::string* release_username();
  void set_allocated_username(std::string* ptr);

  private:
  const std::string& _internal_username() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_username(
      const std::string& value);
  std::string* _internal_mutable_username();

  public:
  // string password = 2;
  void clear_password() ;
  const std::string& password() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_password(Arg_&& arg, Args_... args);
  std::string* mutable_password();
  PROTOBUF_NODISCARD std::string* release_password();
  void set_allocated_password(std::string* ptr);

  private:
  const std::string& _internal_password() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_password(
      const std::string& value);
  std::string* _internal_mutable_password();

  public:
  // @@protoc_insertion_point(class_scope:AuthRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr username_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr password_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_auth_2eproto;
};// -------------------------------------------------------------------

class AuthResponse final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:AuthResponse) */ {
 public:
  inline AuthResponse() : AuthResponse(nullptr) {}
  ~AuthResponse() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR AuthResponse(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  AuthResponse(const AuthResponse& from);
  AuthResponse(AuthResponse&& from) noexcept
    : AuthResponse() {
    *this = ::std::move(from);
  }

  inline AuthResponse& operator=(const AuthResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline AuthResponse& operator=(AuthResponse&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const AuthResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const AuthResponse* internal_default_instance() {
    return reinterpret_cast<const AuthResponse*>(
               &_AuthResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(AuthResponse& a, AuthResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(AuthResponse* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(AuthResponse* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  AuthResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<AuthResponse>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const AuthResponse& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const AuthResponse& from) {
    AuthResponse::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(AuthResponse* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "AuthResponse";
  }
  protected:
  explicit AuthResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMessageFieldNumber = 2,
    kSuccessFieldNumber = 1,
  };
  // string message = 2;
  void clear_message() ;
  const std::string& message() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_message(Arg_&& arg, Args_... args);
  std::string* mutable_message();
  PROTOBUF_NODISCARD std::string* release_message();
  void set_allocated_message(std::string* ptr);

  private:
  const std::string& _internal_message() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_message(
      const std::string& value);
  std::string* _internal_mutable_message();

  public:
  // bool success = 1;
  void clear_success() ;
  bool success() const;
  void set_success(bool value);

  private:
  bool _internal_success() const;
  void _internal_set_success(bool value);

  public:
  // @@protoc_insertion_point(class_scope:AuthResponse)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr message_;
    bool success_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_auth_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// AuthRequest

// string username = 1;
inline void AuthRequest::clear_username() {
  _impl_.username_.ClearToEmpty();
}
inline const std::string& AuthRequest::username() const {
  // @@protoc_insertion_point(field_get:AuthRequest.username)
  return _internal_username();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void AuthRequest::set_username(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.username_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:AuthRequest.username)
}
inline std::string* AuthRequest::mutable_username() {
  std::string* _s = _internal_mutable_username();
  // @@protoc_insertion_point(field_mutable:AuthRequest.username)
  return _s;
}
inline const std::string& AuthRequest::_internal_username() const {
  return _impl_.username_.Get();
}
inline void AuthRequest::_internal_set_username(const std::string& value) {
  ;


  _impl_.username_.Set(value, GetArenaForAllocation());
}
inline std::string* AuthRequest::_internal_mutable_username() {
  ;
  return _impl_.username_.Mutable( GetArenaForAllocation());
}
inline std::string* AuthRequest::release_username() {
  // @@protoc_insertion_point(field_release:AuthRequest.username)
  return _impl_.username_.Release();
}
inline void AuthRequest::set_allocated_username(std::string* value) {
  _impl_.username_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.username_.IsDefault()) {
          _impl_.username_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:AuthRequest.username)
}

// string password = 2;
inline void AuthRequest::clear_password() {
  _impl_.password_.ClearToEmpty();
}
inline const std::string& AuthRequest::password() const {
  // @@protoc_insertion_point(field_get:AuthRequest.password)
  return _internal_password();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void AuthRequest::set_password(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.password_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:AuthRequest.password)
}
inline std::string* AuthRequest::mutable_password() {
  std::string* _s = _internal_mutable_password();
  // @@protoc_insertion_point(field_mutable:AuthRequest.password)
  return _s;
}
inline const std::string& AuthRequest::_internal_password() const {
  return _impl_.password_.Get();
}
inline void AuthRequest::_internal_set_password(const std::string& value) {
  ;


  _impl_.password_.Set(value, GetArenaForAllocation());
}
inline std::string* AuthRequest::_internal_mutable_password() {
  ;
  return _impl_.password_.Mutable( GetArenaForAllocation());
}
inline std::string* AuthRequest::release_password() {
  // @@protoc_insertion_point(field_release:AuthRequest.password)
  return _impl_.password_.Release();
}
inline void AuthRequest::set_allocated_password(std::string* value) {
  _impl_.password_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.password_.IsDefault()) {
          _impl_.password_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:AuthRequest.password)
}

// -------------------------------------------------------------------

// AuthResponse

// bool success = 1;
inline void AuthResponse::clear_success() {
  _impl_.success_ = false;
}
inline bool AuthResponse::success() const {
  // @@protoc_insertion_point(field_get:AuthResponse.success)
  return _internal_success();
}
inline void AuthResponse::set_success(bool value) {
  _internal_set_success(value);
  // @@protoc_insertion_point(field_set:AuthResponse.success)
}
inline bool AuthResponse::_internal_success() const {
  return _impl_.success_;
}
inline void AuthResponse::_internal_set_success(bool value) {
  ;
  _impl_.success_ = value;
}

// string message = 2;
inline void AuthResponse::clear_message() {
  _impl_.message_.ClearToEmpty();
}
inline const std::string& AuthResponse::message() const {
  // @@protoc_insertion_point(field_get:AuthResponse.message)
  return _internal_message();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void AuthResponse::set_message(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.message_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:AuthResponse.message)
}
inline std::string* AuthResponse::mutable_message() {
  std::string* _s = _internal_mutable_message();
  // @@protoc_insertion_point(field_mutable:AuthResponse.message)
  return _s;
}
inline const std::string& AuthResponse::_internal_message() const {
  return _impl_.message_.Get();
}
inline void AuthResponse::_internal_set_message(const std::string& value) {
  ;


  _impl_.message_.Set(value, GetArenaForAllocation());
}
inline std::string* AuthResponse::_internal_mutable_message() {
  ;
  return _impl_.message_.Mutable( GetArenaForAllocation());
}
inline std::string* AuthResponse::release_message() {
  // @@protoc_insertion_point(field_release:AuthResponse.message)
  return _impl_.message_.Release();
}
inline void AuthResponse::set_allocated_message(std::string* value) {
  _impl_.message_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.message_.IsDefault()) {
          _impl_.message_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:AuthResponse.message)
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_auth_2eproto_2epb_2eh
