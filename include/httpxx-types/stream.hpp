#pragma once

namespace httpxx_types {

class ReadableStream {

public:
  virtual ~ReadableStream() {}

  virtual int read(unsigned char *buffer, int max_len) = 0;
};

class SeekableStream {

public:
  virtual ~SeekableStream(){};

  virtual void seek() const = 0;
  virtual size_t tell() const = 0;
  virtual size_t size() const = 0;
};

class WritableStream {

public:
  virtual ~WritableStream(){};
  virtual int write(unsigned char *buffer, int len) = 0;
};

} // namespace httpxx_types