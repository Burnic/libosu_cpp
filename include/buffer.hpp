#ifndef LIBOSU_INCLUDE_BUFFER_HPP
#define LIBOSU_INCLUDE_BUFFER_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

namespace osu {
  class Buffer {
  public:
    void Write(const char* x);
    void Write(std::string x);
    void Write(std::string x, bool o);
    void Write(bool b);
    void Write(std::int8_t i);
    void Write(std::uint8_t i);
    void Write(std::int16_t i);
    void Write(std::uint16_t i);
    void Write(std::int32_t i);
    void Write(std::uint32_t i);
    void Write(std::int64_t i);
    void Write(std::uint64_t i);
    void Write(std::double_t i);
    void Write(std::float_t i);
    void Write(osu::Buffer b);

    std::string Read(std::size_t size);
    uint8_t ReadByte();
    std::string ReadOsuString();
    int16_t ReadSInt16();
    uint16_t ReadUInt16();
    int32_t ReadSInt32();
    uint32_t ReadUInt32();
    int64_t ReadSInt64();
    uint64_t ReadUInt64();
    float_t ReadFloat();
    double_t ReadDouble();
    uint64_t ReadULEB128();

    // Print self as byte array.
    void Print();

    // Write an ULEB128 compressed uint64_t
    void WriteULEB128(std::uint64_t i);
    // Allocate empty bytes to buffer.
    void allocate(std::size_t size);
    // Seek to an position in this buffer. can throw osu::POS_OUT_OF_RANGE
    void seek(std::size_t pos);
    // Convert out buffer to an string.
    std::string toString();
    // Get size of our buffer.
    std::size_t Size();
    private:
    // Data of our Buffer.
    std::vector<std::uint8_t> raw_Buffer;
    // Position of the Buffer.
    std::size_t pos = 0;
    std::size_t readpos = 0;

    // Cast everything that moves to an char array aka osu::buffer.
    template <typename T>
    osu::Buffer Cast2Char(T t) {
      osu::Buffer o;

      uint8_t a[sizeof(T)];
      memcpy(a, &t, sizeof(T));
      for (size_t i = 0; i < sizeof(T); i++) {
        if (i != 0 && !IsLittleEndian())
          a[i] >> 8 * i;

        o.Write(a[i]);
      }

      return o;
    }
    bool IsLittleEndian();
  };
}

#endif