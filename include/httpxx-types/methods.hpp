#pragma once
#include <ostream>

namespace httpxx_types {

enum class Method {
  Get,
  Post,
  Put,
  Patch,
  Option,
  Head,
  Delete,
};

const char *method_name(Method method);

std::ostream &operator<<(std::ostream &os, Method m);
}