#pragma once
#include <cstdlib>
#include <expected>
#include <string>
#include <iostream>

template<typename T, typename E>
class Result {
  std::expected<T, E> value;

public:
  T unwrap();
  T expected(std::string message);
  static Result<T, E> ok(T value);
  static Result<T, E> err(E err);
  bool has_value();
};

template<typename E>
class Result<void, E> {
  std::expected<void, E> value;

public:
  void unwrap();
  void expected(std::string message);
  static Result<void, E> ok();
  static Result<void, E> err(E err);
  bool has_value();
};

#define try(f) \
  { \
    auto v = f; \
    if (!v.has_value()) { \
      return v; \
    } \
  }

template<typename T, typename E>
Result<T, E> ok(T value);

template<typename T, typename E>
Result<T, E> err(E error);

template<typename E>
Result<void, E> ok();

template<typename E>
Result<void, E> err(E error);

template<typename T, typename E>
T Result<T, E>::unwrap() {
  if (!this->value.has_value()) {
    std::cout << this->value.value() << std::endl;
    exit(1);
  }
}

template<typename T, typename E>
T Result<T, E>::expected(std::string message) {
  if (!this->value.has_value()) {
    std::cout << this->value.error() << std::endl;
    exit(1);
  }
}

template<typename T, typename E>
Result<T, E> Result<T, E>::ok(T value) {
  Result<T, E> r;
  r.value = value;
  return r;
}

template<typename T, typename E>
Result<T, E> Result<T, E>::err(E err) {
  return std::unexpected(err);
}

template<typename T, typename E>
bool Result<T, E>::has_value() {
  return this->value.has_value();
}

// deal no return value

template<typename E>
void Result<void, E>::unwrap() {
  if (!this->value.has_value()) {
    exit(1);
  }
}

template<typename E>
void Result<void, E>::expected(std::string message) {
  if (!this->value.has_value()) {
    std::cout << this->value.error() << std::endl;
    exit(1);
  }
}

template<typename E>
Result<void, E> Result<void, E>::ok() {
  Result<void, E> r;
  return r;
}

template<typename E>
Result<void, E> Result<void, E>::err(E err) {
  Result<void, E> r;
  r.value = std::unexpected<E>(err);
  return r;
}

template<typename E>
bool Result<void, E>::has_value() {
  return this->value.has_value();
}

// alias

template<typename T, typename E>
Result<T, E> ok(T value) {
  return Result<T, E>::ok(value);
}

template<typename T, typename E>
Result<T, E> err(E error) {
  return Result<T, E>::err(error);
}

template<typename E>
Result<void, E> ok() {
  return Result<void, E>::ok();
}

template<typename E>
Result<void, E> err(E error) {
  return Result<void, E>::err(error);
}
