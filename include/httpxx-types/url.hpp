#pragma once
#include <iostream>
#include <map>
#include <sstream>
#include <string>
namespace httpxx_types {

static std::string url_encode(const std::string &in) {
  std::string out;
  char hex[] = "0123456789abcdef";
  for (auto c : in) {
    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ||
        ('0' <= c && c <= '9')) {
      out.push_back(c);
      // putchar(c);
    } else {
      // putchar('%');
      out.push_back('%');
      out.push_back(hex[c >> 4]);
      out.push_back(hex[c & 15]);
      // putchar(hex[c >> 4]);
      // putchar(hex[c & 15]);
    }
  }
  return out;
}

class Query {

public:
  Query() {}
  Query(const std::string &str) {
    std::stringstream ss(str);
    std::string s;

    while (getline(ss, s, '&')) {

      auto idx = s.find('=');
      if (idx == std::string::npos) {
        set(s, true);
      } else {
        auto k = s.substr(0, idx);
        auto v = s.substr(idx + 1);
        std::cout << k << " "
                  << " " << v << std::endl;
        m_query[k] = v;
      }
    }
  }

  template <class T> void set(const std::string &key, const T &v) {
    m_query.insert(key, std::to_string(v));
  }

  void set(const std::string &key, bool ok) {
    m_query[key] = ok ? std::string("true") : std::string("false");
  }

  void set(const std::string &key, const char *str) {
    m_query[key] = std::string(str);
  }

  std::string str() const {
    std::stringstream s;
    int i = 0;
    auto size = m_query.size();
    for (auto &kv : m_query) {
      s << url_encode(kv.first) << "=" << url_encode(kv.second);
      if (i < size - 1) {
        s << "&";
      }
      i++;
    }
    return s.str();
  }

private:
  std::map<std::string, std::string> m_query;
};

class URL {

public:
  URL(const std::string &url);
  URL(const char *);
  URL();
  ~URL();

  bool parse(const std::string &url);

  int port() const;
  void set_port(int port);

  std::string host() const;
  void set_host(const std::string &host);

  std::string path() const;
  void set_path(const std::string &path);

  std::string full_path() const;

  std::string protocol() const;
  void set_protocol(const std::string &protocol);

  Query &query();
  void set_query(const Query &query);

  std::string fragment() const;
  void set_fragment(const std::string &fragment);

  bool valid() const;

  std::string str() const;

  friend std::ostream &operator<<(std::ostream &os, const URL &dt);

private:
  std::string m_host;
  int m_port;
  std::string m_path;
  std::string m_protocol;
  // std::string m_query;
  Query m_query;
  std::string m_fragment;
  bool m_valid = false;
};
} // namespace httpxx_types
