#include <httpxx-types/methods.hpp>

namespace httptypes {

const char *method_name(Method method) {
  switch (method) {
  case Method::Post:
    return "POST";
  case Method::Get:
    return "GET";
  case Method::Put:
    return "PUT";
  case Method::Patch:
    return "PATCH";
  case Method::Option:
    return "OPTION";
  case Method::Delete:
    return "DELETE";
  case Method::Head:
    return "HEAD";
  }
}

std::ostream &operator<<(std::ostream &os, Method m) {
  os << method_name(m);
  return os;
}

} // namespace httptypes