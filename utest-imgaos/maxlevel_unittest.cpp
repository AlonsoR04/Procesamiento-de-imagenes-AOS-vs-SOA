
#include "common/info.hpp"
#include "imgaos/imgeaos.hpp"
#include "gtest/gtest.h"
#include <vector>
#include <cstdint>

// Test para escalar de 16 a 8 bits
TEST(EscalarTest, Escalar_16_to_8) {
  // Datos de entrada
  constexpr int ALTURA = 100; // Nueva intensidad máxima
  constexpr int ANCHURA = 100;
  constexpr int NEW_INTENSITY = 255; // Nueva intensidad máxima
  constexpr int OLD_INTENSITY = 3000; // Intensidad original

  // Crear un vector de píxeles de 16 bits (uint16_t)
  std::vector<Pixel<uint16_t>> const pixeles16 = {
    {.r = 1000, .g = 1500, .b = 2000},
    {.r = 500,  .g = 750,  .b = 1000},
    {.r = 2000, .g = 2500, .b = 2550}
  };

  // Crear el vector de píxeles de 8 bits (uint8_t) donde guardaremos el resultado
  std::vector<Pixel<uint8_t>> pixeles8;

  // Información de la imagen (simulando los valores de una imagen)
  Imagen foto;
  foto.formato = "P6";
  foto.altura = ALTURA;
  foto.anchura = ANCHURA;
  foto.maxIntensidad = OLD_INTENSITY;

  // Llamar a la función que estamos testeando
  escalar_pixel_16_to_8(pixeles8, pixeles16, NEW_INTENSITY, foto);

  // Verificar que los valores de los píxeles en pixeles8 sean los esperados
  EXPECT_EQ(pixeles8[0].r, static_cast<uint8_t>(85));  // 1000 * (255 / 3000)
  EXPECT_EQ(pixeles8[0].g, static_cast<uint8_t>(127));  // 1500 * (255 / 3000)
  EXPECT_EQ(pixeles8[0].b, static_cast<uint8_t>(170)); // 2000 * (255 / 3000)

  EXPECT_EQ(pixeles8[1].r, static_cast<uint8_t>(42));  // 500 * (255 / 3000)
  EXPECT_EQ(pixeles8[1].g, static_cast<uint8_t>(63));  // 750 * (255 / 3000)
  EXPECT_EQ(pixeles8[1].b, static_cast<uint8_t>(85));  // 1000 * (255 / 3000)

  EXPECT_EQ(pixeles8[2].r, static_cast<uint8_t>(170));  // 2000 * (255 / 3000)
  EXPECT_EQ(pixeles8[2].g, static_cast<uint8_t>(212)); // 2500 * (255 / 3000)
  EXPECT_EQ(pixeles8[2].b, static_cast<uint8_t>(216)); // 2550 * (255 / 3000)
}

// Test para escalar de 16 a 16 bits
TEST(EscalarTest2, Escalar_16_to_16) {
  // Datos de entrada
  constexpr int ALTURA = 100; // Nueva intensidad máxima
  constexpr int ANCHURA = 100;
  constexpr int NEW_INTENSITY = 2000; // Nueva intensidad máxima
  constexpr int OLD_INTENSITY = 3000; // Intensidad original

  // Crear un vector de píxeles de 16 bits (uint16_t)
  std::vector<Pixel<uint16_t>> pixeles16 = {
    // NOLINTNEXTLINE(clang-tidy:magic_number
    {.r = 1000, .g = 1500, .b = 2000},
    // NOLINTNEXTLINE(clang-tidy:magic_number
    { .r = 500,  .g = 750, .b = 1000},
    // NOLINTNEXTLINE(clang-tidy:magic_number
    {.r = 2000, .g = 2500, .b = 2550}
  };
  // Información de la imagen (simulando los valores de una imagen)
  Imagen foto;
  foto.formato = "P6";
  foto.altura = ALTURA;
  foto.anchura = ANCHURA;
  foto.maxIntensidad = OLD_INTENSITY;
  // Llamar a la función que estamos testeando
  escalar_pixel_16_to_16(pixeles16, NEW_INTENSITY, foto);
  // Verificar que los valores de los píxeles en pixeles8 sean los esperados
  EXPECT_EQ(pixeles16[0].r, static_cast<uint16_t>(666));  // 1000 * (2000 / 3000)
  EXPECT_EQ(pixeles16[0].g, static_cast<uint16_t>(1000));  // 1500 * (2000 / 3000)
  EXPECT_EQ(pixeles16[0].b, static_cast<uint16_t>(1333)); // 2000 * (2000 / 3000)

  EXPECT_EQ(pixeles16[1].r, static_cast<uint16_t>(333));  // 500 * (2000 / 3000)
  EXPECT_EQ(pixeles16[1].g, static_cast<uint16_t>(500));  // 750 * (2000 / 3000)
  EXPECT_EQ(pixeles16[1].b, static_cast<uint16_t>(666));  // 1000 * (2000 / 3000)

  EXPECT_EQ(pixeles16[2].r, static_cast<uint16_t>(1333));  // 2000 * (2000 / 3000)
  EXPECT_EQ(pixeles16[2].g, static_cast<uint16_t>(1666)); // 2500 * (2000 / 3000)
  EXPECT_EQ(pixeles16[2].b, static_cast<uint16_t>(1700)); // 2550 * (2000 / 3000)
}

// Test para escalar de 16 a 8 bits
TEST(EscalarTest3, Escalar_8_to_8) {
  // Datos de entrada
  constexpr int ALTURA = 100; // Nueva intensidad máxima
  constexpr int ANCHURA = 100;
  constexpr int NEW_INTENSITY = 100; // Nueva intensidad máxima
  constexpr int OLD_INTENSITY = 255; // Intensidad original
  // Crear un vector de píxeles de 16 bits (uint16_t)
  std::vector<Pixel<uint8_t>> pixeles8 = {
    // NOLINTNEXTLINE(clang-tidy:magic_number
    {.r = 100, .g = 150, .b = 200},
    // NOLINTNEXTLINE(clang-tidy:magic_number
    {.r = 50,  .g = 75,  .b = 100},
    // NOLINTNEXTLINE(clang-tidy:magic_number
    {.r = 200, .g = 250, .b = 255}
  };
  // Información de la imagen (simulando los valores de una imagen)
  Imagen foto;
  foto.formato = "P6";
  foto.altura = ALTURA;
  foto.anchura = ANCHURA;
  foto.maxIntensidad = OLD_INTENSITY;

  // Llamar a la función que estamos testeando
  escalar_pixel_8_to_8(pixeles8, NEW_INTENSITY, foto);
  // Verificar que los valores de los píxeles en pixeles8 sean los esperados
  EXPECT_EQ(pixeles8[0].r, static_cast<uint8_t>(39));  // 100 * (100 / 255)
  EXPECT_EQ(pixeles8[0].g, static_cast<uint8_t>(58));  // 50 * (100 / 255)
  EXPECT_EQ(pixeles8[0].b, static_cast<uint8_t>(78)); // 200 * (100/ 255)

  EXPECT_EQ(pixeles8[1].r, static_cast<uint8_t>(19));  // 150 * (100 / 255)
  EXPECT_EQ(pixeles8[1].g, static_cast<uint8_t>(29));  // 75 * (100 / 255)
  EXPECT_EQ(pixeles8[1].b, static_cast<uint8_t>(39));  // 250 * (100 / 255)

  EXPECT_EQ(pixeles8[2].r, static_cast<uint8_t>(78));  // 200 * (100 / 255)
  EXPECT_EQ(pixeles8[2].g, static_cast<uint8_t>(98)); // 100 * (100 / 255)
  EXPECT_EQ(pixeles8[2].b, static_cast<uint8_t>(100)); // 255 * (100 / 255)
}







