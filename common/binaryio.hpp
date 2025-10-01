#ifndef BINARYIO_H
#define BINARYIO_H
#include <cstdint>
#include <iostream>
#include <string>
#include <variant>
#include <fstream>

// Funcion para leer todos los archivos .cpp y devolverlo en variables de 8 o 16 bits
template <typename T>
T read_binary(std::istream & input) {
  T value;
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  input.read(reinterpret_cast<char *>(&value), sizeof(value));
  return value;
}

// Funcion para escribir todos los datos en los archivos
template <typename T>
inline void write_binary(std::ofstream & output, T const & value) {
  constexpr uint8_t mask  = 0xff;
  constexpr uint8_t shift = 8;
  if constexpr (std::is_same_v<T, std::uint8_t>) {
    // Si T es uint8_t escribe el valor
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    output.write(reinterpret_cast<char const *>(&value), sizeof(value));
  } else if constexpr (std::is_same_v<T, std::uint16_t>) {
    // Si T es uint16_t, divide en bytes y escribe ambos
    auto low_byte  = static_cast<uint8_t>(value & mask);
    auto high_byte = static_cast<uint8_t>((value >> shift) & mask);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    output.write(reinterpret_cast<char const *>(&low_byte), sizeof(low_byte));
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    output.write(reinterpret_cast<char const *>(&high_byte), sizeof(high_byte));
  } else if constexpr (std::is_same_v<T, std::uint32_t>) {
    // Si T es uint32_t (para la funcion compress), divide en 4 bytes y los escribe en little-endian
    auto low_byte      = static_cast<uint8_t>(value & mask);
    auto low_mid_byte  = static_cast<uint8_t>((value >> shift) & mask);
    auto high_mid_byte = static_cast<uint8_t>((value >> (shift * 2)) & mask);
    auto high_byte     = static_cast<uint8_t>((value >> (shift * 3)) & mask);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    output.write(reinterpret_cast<char const *>(&low_byte), sizeof(low_byte));
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    output.write(reinterpret_cast<char const *>(&low_mid_byte), sizeof(low_mid_byte));
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    output.write(reinterpret_cast<char const *>(&high_mid_byte), sizeof(high_mid_byte));
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    output.write(reinterpret_cast<char const *>(&high_byte), sizeof(high_byte));
  }
}

#endif
