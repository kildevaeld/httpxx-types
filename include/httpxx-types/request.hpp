#pragma once
#include <httpxx-types/header.hpp>
#include <httpxx-types/methods.hpp>
#include <httpxx-types/url.hpp>
#include <streams++/streams.hpp>

namespace httptypes {

enum class Version { Nine, OneOne, Two };

std::ostream &operator<<(std::ostream &, Version);

namespace internal {
class RequestPrivate;
}

class Request {

public:
  Request(Method method = Method::Get, const URL &url = URL());
  Request(const URL &url);

  Request(const Request &other) = delete;
  Request(Request &&other);
  Request &operator=(const Request &req) = delete;
  Request &operator=(Request &&req);
  ~Request();

  URL &url();
  Request &set_url(const URL &url);

  Method method() const;
  Request &set_method(const Method method);

  streams::ReadableStream *body() const;
  Request &set_body(streams::ReadableStream *stream);
  Request &set_body(std::unique_ptr<streams::ReadableStream> &&stream);

  Header &header();
  void set_header(const Header &header);

  template <typename T> Request &set(const std::string &name, const T &t) {
    std::string v = std::to_string(t);
    header().insert(name, v);
    return *this;
  }

  void write(streams::WritableStream &stream);

  friend std::ostream &operator<<(std::ostream &, const Request &);

private:
  std::unique_ptr<internal::RequestPrivate> d;
};

} // namespace httptypes