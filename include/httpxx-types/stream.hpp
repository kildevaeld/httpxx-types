#pragma once
#include <fstream>
#include <iostream>
#include <string>

namespace httpxx_types {

class ReadableStream {

public:
  virtual ~ReadableStream() {}
  ReadableStream() {}
  ReadableStream(const ReadableStream &) = delete;

  virtual int read(unsigned char *buffer, int max_len) = 0;
};

// template<class T>
// class IStream: public ReadableFileStream {

// public:
//   virtual ~IStream() {

//   }
//   IStream(const T ) {}

// private:
//   T *m_stream;

// }

class SeekableStream {

public:
  virtual ~SeekableStream(){};

  virtual void seek(size_t pos, std::ios::seekdir dir) = 0;
  virtual size_t tell() = 0;
  virtual size_t size() {
    auto offset = tell();
    seek(0, std::ios::end);
    auto size = tell();
    seek(offset, std::ios::beg);
    return size;
  }
};

class WritableStream {

public:
  virtual ~WritableStream(){};
  virtual int write(unsigned char *buffer, int len) = 0;
};

class ReadableFileStream : public ReadableStream, public SeekableStream {

public:
  ReadableFileStream(const std::string &path)
      : ReadableStream(), m_path(path), m_stream(path) {
    m_stream.seekg(0, std::ios::end);
    m_len = m_stream.tellg();
    m_stream.seekg(0, std::ios::beg);
  }

  virtual int read(unsigned char *buffer, int max_len) {

    if (m_offset >= m_len)
      return EOF;

    m_stream.seekg(m_offset);
    int r = max_len;
    auto e = max_len + m_offset;
    if (e > m_len) {
      r = m_len - m_offset;
    }

    m_stream.read((char *)buffer, r);

    if (!m_stream) {
      r = m_stream.gcount();
    }

    m_offset += r;

    return r;
  }

  virtual void seek(size_t pos, std::ios::seekdir dir) {
    m_stream.seekg((std::streampos)pos, dir);
    m_offset = tell();
  }

  virtual size_t tell() { return m_stream.tellg(); }

private:
  std::string m_path;
  std::fstream m_stream;
  size_t m_offset = 0;
  size_t m_len;
};

class WritableFileStream : public WritableStream {

public:
  WritableFileStream(const std::string &path, int mode = std::fstream::out)
      : m_path(path), m_stream(path, mode) {
    if (!m_stream.is_open()) {
      throw std::runtime_error("could not open file");
    }
  }

  virtual int write(unsigned char *buffer, int len) {
    m_stream.write((char *)buffer, len);
    return len;
  }

private:
  std::string m_path;
  std::fstream m_stream;
};

} // namespace httpxx_types