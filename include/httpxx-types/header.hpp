#pragma once
#include <map>
#include <string>

namespace httpxx_types {

enum Method {
  Get,
  Post,
  Put,
  Patch,
  Option,
  Head,
  Delete,
};

const char *method_name(Method method);

struct CaseInsensitiveCompare {
  bool operator()(const std::string &a, const std::string &b) const noexcept;
};

using Header = std::map<std::string, std::string, CaseInsensitiveCompare>;

} // namespace httpxx_types