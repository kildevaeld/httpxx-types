#pragma once
#include <ostream>

namespace httptypes {

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