#include <httpxx-types/request.hpp>
#include <iostream>
using namespace httptypes;

int main() {
  Request req;
  auto stream = new streams::ReadableFileStream("Makefile");
  streams::WritableFileStream output("./test_http.txt",
                                     std::fstream::out | std::fstream::trunc);

  req.set_url("http://google.com?hello&world=mand&test=1");
  req.url().query().set("rapper", "test tras");
  req.set_body(stream);
  req.set_method(Method::Post);
  // std::cout << req << std::endl;
  req.write(output);

  return 0;
}