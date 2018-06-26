#include <httpxx-types/request.hpp>
#include <sstream>
static bool iequals(const std::string &a, const std::string &b) {
  unsigned int sz = a.size();
  if (b.size() != sz)
    return false;
  for (unsigned int i = 0; i < sz; ++i)
    if (std::tolower(a[i]) != std::tolower(b[i]))
      return false;
  return true;
}

static const char *const kCRLF = "\r\n";

namespace httpxx_types {

namespace internal {
class RequestPrivate {
public:
  URL url;
  Method method;
  Header header;
  std::unique_ptr<ReadableStream> body;
};
} // namespace internal

Request::Request() : d(new internal::RequestPrivate()) {}
Request::Request(const Request &other) : d(new internal::RequestPrivate()) {
  d->url = other.url();
  d->method = other.method();
}
Request::Request(Request &&other) {}
Request &Request::operator=(const Request &req) {
  if (this != &req) {
    d->url = req.d->url;
    d->method = req.d->method;
  }
  return *this;
}
Request &Request::operator=(Request &&req) {
  if (this != &req) {
    this->d.swap(req.d);
  }
  return *this;
}

Request::~Request() {}

URL Request::url() const { return d->url; }
Request &Request::set_url(const URL &url) {
  d->url = url;
  return *this;
}

Method Request::method() const { return d->method; }
Request &Request::set_method(const Method method) {
  d->method = method;
  return *this;
}

Header &Request::header() { return d->header; }
void Request::set_header(const Header &header) { d->header = header; }

ReadableStream *Request::body() const { return d->body.get(); }
Request &Request::set_body(ReadableStream *stream) { d->body.reset(stream); }
Request &Request::set_body(std::unique_ptr<ReadableStream> &&stream) {
  d->body = std::move(stream);
}

std::ostream &operator<<(std::ostream &s, const Request &r) {
  s << method_name(r.d->method) << " " << r.d->url.path() << " HTTP/1.1"
    << kCRLF;

  bool has_host, has_cl = false;

  for (const auto &h : r.d->header) {
    if (iequals(h.first, "content-length"))
      has_cl = true;
    else if (iequals(h.first, "host"))
      has_host = true;
    s << h.first << ": " << h.second << kCRLF;
  }

  if (!has_host && r.d->url.host().size() > 0) {
    s << "Host: " << r.d->url.host() << kCRLF;
  }

  auto m = r.d->method;

  bool has_body = d->body != nullptr;

  if (has_body) {
    auto seekable = dynamic_cast<SeekableStream *>(d->body);
    if (seekable && !has_cl) {
      s << "Content-Length: " << seekable->size() << kCRLF;
    } else {
    }
  }

  /*if ((r.d->body.size() > 0 &&
     (m == Method::Post || m == Method::Put || m == Method::Patch)) &&
    !has_cl) {
  s << "Content-Length: " << r.d->body.size() << kCRLF;
}

s << kCRLF;

if (r.d->body.size() > 0) {
  if (m == Method::Post || m == Method::Put || m == Method::Patch) {
    s << r.d->body;
  }
}*/

  return s;
}

} // namespace httpxx_types