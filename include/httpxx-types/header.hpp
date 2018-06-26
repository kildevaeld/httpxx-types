#pragma once
#include <map>
#include <string>

namespace httpxx_types {

struct CaseInsensitiveCompare {
  bool operator()(const std::string &a, const std::string &b) const noexcept;
};

using Header = std::map<std::string, std::string, CaseInsensitiveCompare>;

} // namespace httpxx_types