#pragma once

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
}