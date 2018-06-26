#include <httpxx-types/methods.hpp>

namespace httpxx_types {

const char *method_name(Method method) {
  switch (method) {
  case Post:
    return "POST";
  case Get:
    return "GET";
  case Put:
    return "PUT";
  case Patch:
    return "PATCH";
  case Option:
    return "OPTION";
  case Delete:
    return "DELETE";
  case Head:
    return "HEAD";
  }
}

} // namespace httpxx_types