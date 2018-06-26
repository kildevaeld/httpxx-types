#pragma once
#include <map>
#include <string>

namespace httptypes {

struct CaseInsensitiveCompare {
  bool operator()(const std::string &a, const std::string &b) const noexcept;
};

using Header = std::map<std::string, std::string, CaseInsensitiveCompare>;

} // namespace httptypes