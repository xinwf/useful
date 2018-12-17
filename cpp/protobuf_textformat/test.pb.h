// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test.proto

#ifndef PROTOBUF_test_2eproto__INCLUDED
#define PROTOBUF_test_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_test_2eproto();
void protobuf_AssignDesc_test_2eproto();
void protobuf_ShutdownFile_test_2eproto();

class student;
class classes;

// ===================================================================

class student : public ::google::protobuf::Message {
 public:
  student();
  virtual ~student();

  student(const student& from);

  inline student& operator=(const student& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const student& default_instance();

  void Swap(student* other);

  // implements Message ----------------------------------------------

  student* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const student& from);
  void MergeFrom(const student& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // required int32 age = 2;
  inline bool has_age() const;
  inline void clear_age();
  static const int kAgeFieldNumber = 2;
  inline ::google::protobuf::int32 age() const;
  inline void set_age(::google::protobuf::int32 value);

  // optional string addr = 3;
  inline bool has_addr() const;
  inline void clear_addr();
  static const int kAddrFieldNumber = 3;
  inline const ::std::string& addr() const;
  inline void set_addr(const ::std::string& value);
  inline void set_addr(const char* value);
  inline void set_addr(const char* value, size_t size);
  inline ::std::string* mutable_addr();
  inline ::std::string* release_addr();
  inline void set_allocated_addr(::std::string* addr);

  // @@protoc_insertion_point(class_scope:student)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_age();
  inline void clear_has_age();
  inline void set_has_addr();
  inline void clear_has_addr();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::std::string* addr_;
  ::google::protobuf::int32 age_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_test_2eproto();
  friend void protobuf_AssignDesc_test_2eproto();
  friend void protobuf_ShutdownFile_test_2eproto();

  void InitAsDefaultInstance();
  static student* default_instance_;
};
// -------------------------------------------------------------------

class classes : public ::google::protobuf::Message {
 public:
  classes();
  virtual ~classes();

  classes(const classes& from);

  inline classes& operator=(const classes& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const classes& default_instance();

  void Swap(classes* other);

  // implements Message ----------------------------------------------

  classes* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const classes& from);
  void MergeFrom(const classes& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // repeated .student member = 2;
  inline int member_size() const;
  inline void clear_member();
  static const int kMemberFieldNumber = 2;
  inline const ::student& member(int index) const;
  inline ::student* mutable_member(int index);
  inline ::student* add_member();
  inline const ::google::protobuf::RepeatedPtrField< ::student >&
      member() const;
  inline ::google::protobuf::RepeatedPtrField< ::student >*
      mutable_member();

  // @@protoc_insertion_point(class_scope:classes)
 private:
  inline void set_has_name();
  inline void clear_has_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::google::protobuf::RepeatedPtrField< ::student > member_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_test_2eproto();
  friend void protobuf_AssignDesc_test_2eproto();
  friend void protobuf_ShutdownFile_test_2eproto();

  void InitAsDefaultInstance();
  static classes* default_instance_;
};
// ===================================================================


// ===================================================================

// student

// required string name = 1;
inline bool student::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void student::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void student::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void student::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& student::name() const {
  return *name_;
}
inline void student::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void student::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void student::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* student::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* student::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void student::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required int32 age = 2;
inline bool student::has_age() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void student::set_has_age() {
  _has_bits_[0] |= 0x00000002u;
}
inline void student::clear_has_age() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void student::clear_age() {
  age_ = 0;
  clear_has_age();
}
inline ::google::protobuf::int32 student::age() const {
  return age_;
}
inline void student::set_age(::google::protobuf::int32 value) {
  set_has_age();
  age_ = value;
}

// optional string addr = 3;
inline bool student::has_addr() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void student::set_has_addr() {
  _has_bits_[0] |= 0x00000004u;
}
inline void student::clear_has_addr() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void student::clear_addr() {
  if (addr_ != &::google::protobuf::internal::kEmptyString) {
    addr_->clear();
  }
  clear_has_addr();
}
inline const ::std::string& student::addr() const {
  return *addr_;
}
inline void student::set_addr(const ::std::string& value) {
  set_has_addr();
  if (addr_ == &::google::protobuf::internal::kEmptyString) {
    addr_ = new ::std::string;
  }
  addr_->assign(value);
}
inline void student::set_addr(const char* value) {
  set_has_addr();
  if (addr_ == &::google::protobuf::internal::kEmptyString) {
    addr_ = new ::std::string;
  }
  addr_->assign(value);
}
inline void student::set_addr(const char* value, size_t size) {
  set_has_addr();
  if (addr_ == &::google::protobuf::internal::kEmptyString) {
    addr_ = new ::std::string;
  }
  addr_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* student::mutable_addr() {
  set_has_addr();
  if (addr_ == &::google::protobuf::internal::kEmptyString) {
    addr_ = new ::std::string;
  }
  return addr_;
}
inline ::std::string* student::release_addr() {
  clear_has_addr();
  if (addr_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = addr_;
    addr_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void student::set_allocated_addr(::std::string* addr) {
  if (addr_ != &::google::protobuf::internal::kEmptyString) {
    delete addr_;
  }
  if (addr) {
    set_has_addr();
    addr_ = addr;
  } else {
    clear_has_addr();
    addr_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// classes

// required string name = 1;
inline bool classes::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void classes::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void classes::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void classes::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& classes::name() const {
  return *name_;
}
inline void classes::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void classes::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void classes::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* classes::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* classes::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void classes::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// repeated .student member = 2;
inline int classes::member_size() const {
  return member_.size();
}
inline void classes::clear_member() {
  member_.Clear();
}
inline const ::student& classes::member(int index) const {
  return member_.Get(index);
}
inline ::student* classes::mutable_member(int index) {
  return member_.Mutable(index);
}
inline ::student* classes::add_member() {
  return member_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::student >&
classes::member() const {
  return member_;
}
inline ::google::protobuf::RepeatedPtrField< ::student >*
classes::mutable_member() {
  return &member_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_test_2eproto__INCLUDED
