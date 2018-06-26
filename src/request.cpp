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

namespace httptypes {

std::ostream &operator<<(std::ostream &s, Version v) {
  switch (v) {
  case Version::Nine:
    s << "0.9";
    break;
  case Version::OneOne:
    s << "1.1";
    break;
  case Version::Two:
    s << "2.0";
  }
  return s;
}

namespace internal {
class RequestPrivate {
public:
  URL url;
  Method method = Method::Get;
  Header header;
  Version version = Version::OneOne;
  std::unique_ptr<streams::ReadableStream> body;
};
} // namespace internal

Request::Request(Method method, const URL &url)
    : d(new internal::RequestPrivate()) {
  d->url = url;
  d->method = method;
}

Request::Request(const URL &url) : d(new internal::RequestPrivate()) {
  d->url = url;
}

// Request::Request(const Request &other) : d(new internal::RequestPrivate()) {
//   d->url = other.url();
//   d->method = other.method();
// }
Request::Request(Request &&other) : d(std::move(other.d)) {}

// Request &Request::operator=(const Request &req) {
//   if (this != &req) {
//     d->url = req.d->url;
//     d->method = req.d->method;
//   }
//   return *this;
// }

Request &Request::operator=(Request &&req) {
  if (this != &req) {
    this->d.swap(req.d);
  }
  return *this;
}

Request::~Request() {}

URL &Request::url() { return d->url; }
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

streams::ReadableStream *Request::body() const { return d->body.get(); }
Request &Request::set_body(streams::ReadableStream *stream) {
  d->body.reset(stream);
  return *this;
}
Request &Request::set_body(std::unique_ptr<streams::ReadableStream> &&stream) {
  d->body = std::move(stream);
}

void Request::write(streams::WritableStream &stream) {
  std::stringstream s;
  s << d->method << " ";
  s << d->url.full_path();
  s << " HTTP/" << d->version << kCRLF;

  bool has_host, has_cl = false;

  for (const auto &h : d->header) {
    if (iequals(h.first, "content-length"))
      has_cl = true;
    else if (iequals(h.first, "host"))
      has_host = true;
    s << h.first << ": " << h.second << kCRLF;
  }

  if (!has_host && d->url.host().size() > 0) {
    s << "Host: " << d->url.host() << kCRLF;
  }

  auto m = d->method;

  bool has_body = d->body.operator bool() &&
                  (d->method == Method::Patch || d->method == Method::Post ||
                   d->method == Method::Put),
       chunked = false;

  if (has_body) {
    auto seekable = dynamic_cast<streams::SeekableStream *>(d->body.get());
    if (seekable && !has_cl) {
      s << "Content-Length: " << seekable->size() << kCRLF;
    } else {
      s << "Transfer-Encoding: chunked" << kCRLF;
      chunked = true;
    }
  }

  s << kCRLF;

  std::string str = s.str();

  stream.write((unsigned char *)str.data(), str.size());

  if (has_body) {
    int read = 0;
    unsigned char buffer[2048];
    while (read != EOF) {
      s.str(std::string());
      read = d->body->read(buffer, 2048);
      if (read == EOF)
        break;
      if (chunked) {
        s << std::hex << read;
        s << kCRLF;
        s.write((char *)buffer, read);
        s << kCRLF;
      } else {
        s.write((char *)buffer, read);
      }
      std::string str = s.str();
      stream.write((unsigned char *)str.data(), str.size());
    }

    if (chunked) {
      s.str(std::string());
      s << "0" << kCRLF << kCRLF;
      std::string str = s.str();
      stream.write((unsigned char *)str.data(), str.size());
    }
  }
}

std::ostream &operator<<(std::ostream &s, const Request &r) {
  s << r.d->method << " ";
  s << r.d->url.full_path();
  s << " HTTP/" << r.d->version << kCRLF;

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

  bool has_body = r.d->body.operator bool(), chunked = false;

  if (has_body) {
    auto seekable = dynamic_cast<streams::SeekableStream *>(r.d->body.get());
    if (seekable && !has_cl) {
      s << "Content-Length: " << seekable->size() << kCRLF;
    } else {
      s << "Transfer-Encoding: chunked" << kCRLF;
      chunked = true;
    }
  }

  s << kCRLF;

  if (has_body) {
    int read;
    unsigned char buffer[2048];
    while (read != EOF) {
      read = r.d->body->read(buffer, 2048);
      if (read == EOF)
        break;
      if (chunked) {
        s << std::hex << read;
        s << kCRLF;
        s.write((char *)buffer, read);
        s << kCRLF;
      } else {
        s.write((char *)buffer, read);
      }
    }

    if (chunked) {
      s << "0" << kCRLF << kCRLF;
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

} // namespace httptypes