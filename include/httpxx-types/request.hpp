#pragma once
#include <httpxx-types/header.hpp>
#include <httpxx-types/methods.hpp>
#include <httpxx-types/stream.hpp>
#include <httpxx-types/url.hpp>

namespace httpxx_types {

namespace internal {
class RequestPrivate;
}

class Request {

public:
  Request();
  Request(const Request &other);
  Request(Request &&other);
  Request &operator=(const Request &req);
  Request &operator=(Request &&req);
  ~Request();

  URL url() const;
  Request &set_url(const URL &url);

  Method method() const;
  Request &set_method(const Method method);

  ReadableStream *body() const;
  Request &set_body(ReadableStream *stream);
  Request &set_body(std::unique_ptr<ReadableStream> &&stream);

  Header &header();
  void set_header(const Header &header);

  template <typename T> Request &set(const std::string &name, const T &t) {
    std::string v = std::to_string(t);
    header().insert(name, v);
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &, const Request &);

private:
  std::unique_ptr<internal::RequestPrivate> d;
};

} // namespace httpxx_types