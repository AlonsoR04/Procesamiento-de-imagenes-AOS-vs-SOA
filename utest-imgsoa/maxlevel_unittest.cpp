#include "common/info.hpp"
#include "imgsoa/imgesoa.hpp"
#include "gtest/gtest.h"
#include <vector>
#include <cstdint>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

// Test para escalar de 16 a 8 bits
TEST(EscalarTest, Escalar_16_to_8SOA) {
  // Datos de entrada
  constexpr int ALTURA = 2; // Nueva intensidad máxima
  constexpr int ANCHURA = 2;
  constexpr int NEW_INTENSITY = 255; // Nueva intensidad máxima
  constexpr int OLD_INTENSITY = 3000; // Intensidad original

  // Crear una instancia de PixelData con tipo int
  PixelData<uint16_t> pixeles16;

  // Rellenar los vectores con datos (valores de color para cada píxel)
  pixeles16.r = {1000, 1500, 2000, 1000}; // Colores rojos
  pixeles16.g = {500, 750, 1000, 500};  // Colores verdes
  pixeles16.b = {2000, 2500, 2550, 2000};  // Colores azules


  // Crear el vector de píxeles de 8 bits (uint8_t) donde guardaremos el resultado
  PixelData<uint8_t> pixeles8;
  // Información de la imagen (simulando los valores de una imagen)
  Imagen foto;
  foto.formato = "P6";
  foto.altura = ALTURA;
  foto.anchura = ANCHURA;
  foto.maxIntensidad = OLD_INTENSITY;

  // Llamar a la función que estamos testeando
  escalar_pixel_16_8(foto, NEW_INTENSITY, pixeles16, pixeles8);

  // Verificar que los valores de los píxeles en pixeles8 sean los esperados
  EXPECT_EQ(pixeles8.r[0], static_cast<uint8_t>(85));  // 1000 * (255 / 3000)
  EXPECT_EQ(pixeles8.g[0], static_cast<uint8_t>(42));  // 500 * (255 / 3000)
  EXPECT_EQ(pixeles8.b[0], static_cast<uint8_t>(170)); // 2000 * (255 / 3000)

  EXPECT_EQ(pixeles8.r[1], static_cast<uint8_t>(127));  // 1500 * (255 / 3000)
  EXPECT_EQ(pixeles8.g[1], static_cast<uint8_t>(63));  // 750 * (255 / 3000)
  EXPECT_EQ(pixeles8.b[1], static_cast<uint8_t>(212));  // 2500 * (255 / 3000)

  EXPECT_EQ(pixeles8.r[2], static_cast<uint8_t>(170));  // 2000 * (255 / 3000)
  EXPECT_EQ(pixeles8.g[2], static_cast<uint8_t>(85)); // 1000 * (255 / 3000)
  EXPECT_EQ(pixeles8.b[2], static_cast<uint8_t>(216)); // 2550 * (255 / 3000)

  EXPECT_EQ(pixeles8.r[3], static_cast<uint8_t>(85));  // 1000 * (255 / 3000)
  EXPECT_EQ(pixeles8.g[3], static_cast<uint8_t>(42));  // 500 * (255 / 3000)
  EXPECT_EQ(pixeles8.b[3], static_cast<uint8_t>(170)); // 2000 * (255 / 3000)
}

// Test para escalar de 16 a 16 bits
TEST(EscalarTest, Escalar_16_to_16SOA) {
  // Datos de entrada
  constexpr int ALTURA = 2; // Nueva intensidad máxima
  constexpr int ANCHURA = 2;
  constexpr int NEW_INTENSITY = 1000; // Nueva intensidad máxima
  constexpr int OLD_INTENSITY = 3000; // Intensidad original

  // Crear una instancia de PixelData con tipo int
  PixelData<uint16_t> pixeles16;

  // Rellenar los vectores con datos (valores de color para cada píxel)
  pixeles16.r = {1000, 1500, 2000, 1000}; // Colores rojos
  pixeles16.g = {500, 750, 1000, 500};  // Colores verdes
  pixeles16.b = {2000, 2500, 2550, 2000};  // Colores azules

  // Información de la imagen (simulando los valores de una imagen)
  Imagen foto;
  foto.formato = "P6";
  foto.altura = ALTURA;
  foto.anchura = ANCHURA;
  foto.maxIntensidad = OLD_INTENSITY;

  // Llamar a la función que estamos testeando
  escalar_pixel_16_16(foto,NEW_INTENSITY,pixeles16);

  // Verificar que los valores de los píxeles en pixeles8 sean los esperados
  EXPECT_EQ(pixeles16.r[0], static_cast<uint16_t>(333));  // 1000 * (1000 / 3000)
  EXPECT_EQ(pixeles16.g[0], static_cast<uint16_t>(166));  // 500 * (1000 / 3000)
  EXPECT_EQ(pixeles16.b[0], static_cast<uint16_t>(666)); // 2000 * (1000 / 3000)

  EXPECT_EQ(pixeles16.r[1], static_cast<uint16_t>(500));  // 1500 * (1000 / 3000)
  EXPECT_EQ(pixeles16.g[1], static_cast<uint16_t>(250));  // 750 * (1000 / 3000)
  EXPECT_EQ(pixeles16.b[1], static_cast<uint16_t>(833));  // 2500 * (1000 / 3000)

  EXPECT_EQ(pixeles16.r[2], static_cast<uint16_t>(666));  // 2000 * (1000 / 3000)
  EXPECT_EQ(pixeles16.g[2], static_cast<uint16_t>(333)); // 1000 * (1000 / 3000)
  EXPECT_EQ(pixeles16.b[2], static_cast<uint16_t>(850)); // 2550 * (1000 / 3000)

  EXPECT_EQ(pixeles16.r[3], static_cast<uint16_t>(333));  // 1000 * (1000 / 3000)
  EXPECT_EQ(pixeles16.g[3], static_cast<uint16_t>(166));  // 500 * (1000 / 3000)
  EXPECT_EQ(pixeles16.b[3], static_cast<uint16_t>(666)); // 2000 * (1000 / 3000)
}

// Test para escalar de 8 a 16 bits
TEST(EscalarTest, Escalar_8_to_16SOA) {
  // Datos de entrada
  constexpr int ALTURA = 2; // Nueva intensidad máxima
  constexpr int ANCHURA = 2;
  constexpr int NEW_INTENSITY = 1000; // Nueva intensidad máxima
  constexpr int OLD_INTENSITY = 255; // Intensidad original

  // Crear una instancia de PixelData con tipo int
  PixelData<uint8_t> pixeles8;

  // Rellenar los vectores con datos (valores de color para cada píxel)

  pixeles8.r = {100, 150, 200, 100}; // Colores rojos
  pixeles8.g = {50, 75, 100, 50};  // Colores verdes
  pixeles8.b = {200, 250, 255, 200};  // Colores azules

  PixelData<uint16_t> pixeles16;
  // Información de la imagen (simulando los valores de una imagen)
  Imagen foto;
  foto.formato = "P6";
  foto.altura = ALTURA;
  foto.anchura = ANCHURA;
  foto.maxIntensidad = OLD_INTENSITY;

  // Llamar a la función que estamos testeando
  escalar_pixel_8_16(foto,NEW_INTENSITY,pixeles8,pixeles16);

  // Verificar que los valores de los píxeles en pixeles16 sean los esperados
  EXPECT_EQ(pixeles16.r[0], static_cast<uint16_t>(392));  // 100 * (1000 / 255)
  EXPECT_EQ(pixeles16.g[0], static_cast<uint16_t>(196));  // 50 * (1000 / 255)
  EXPECT_EQ(pixeles16.b[0], static_cast<uint16_t>(784)); // 200 * (1000 / 255)

  EXPECT_EQ(pixeles16.r[1], static_cast<uint16_t>(588));  // 150 * (1000 / 255)
  EXPECT_EQ(pixeles16.g[1], static_cast<uint16_t>(294));  // 75 * (1000 / 255)
  EXPECT_EQ(pixeles16.b[1], static_cast<uint16_t>(980));  // 250 * (1000 / 255)

  EXPECT_EQ(pixeles16.r[2], static_cast<uint16_t>(784));  // 200 * (1000 / 255)
  EXPECT_EQ(pixeles16.g[2], static_cast<uint16_t>(392)); // 100 * (1000 / 255)
  EXPECT_EQ(pixeles16.b[2], static_cast<uint16_t>(1000)); // 255 * (1000 / 255)

  EXPECT_EQ(pixeles16.r[3], static_cast<uint16_t>(392));  // 100 * (1000 / 255)
  EXPECT_EQ(pixeles16.g[3], static_cast<uint16_t>(196));  // 50 * (1000 / 255)
  EXPECT_EQ(pixeles16.b[3], static_cast<uint16_t>(784)); // 200 * (1000 / 255)
}

// Test para escalar de 8 a 8 bits
TEST(EscalarTest, Escalar_8_to_8SOA) {
  // Datos de entrada
  constexpr int ALTURA = 2; // Nueva intensidad máxima
  constexpr int ANCHURA = 2;
  constexpr int NEW_INTENSITY = 100; // Nueva intensidad máxima
  constexpr int OLD_INTENSITY = 255; // Intensidad original

  // Crear una instancia de PixelData con tipo int
  PixelData<uint8_t> pixeles8;
  // Rellenar los vectores con datos (valores de color para cada píxel)
  pixeles8.r = {100, 150, 200, 100}; // Colores rojos
  pixeles8.g = {50, 75, 100, 50};  // Colores verdes
  pixeles8.b = {200, 250, 255, 200};  // Colores azules

  // Información de la imagen (simulando los valores de una imagen)
  Imagen foto;
  foto.formato = "P6";
  foto.altura = ALTURA;
  foto.anchura = ANCHURA;
  foto.maxIntensidad = OLD_INTENSITY;

  // Llamar a la función que estamos testeando
  escalar_pixel_8_8(foto,NEW_INTENSITY,pixeles8);

  // Verificar que los valores de los píxeles en pixeles8 sean los esperados
  EXPECT_EQ(pixeles8.r[0], static_cast<uint8_t>(39));  // 100 * (100 / 255)
  EXPECT_EQ(pixeles8.g[0], static_cast<uint8_t>(19));  // 50 * (100 / 255)
  EXPECT_EQ(pixeles8.b[0], static_cast<uint8_t>(78)); // 200 * (100 / 255)

  EXPECT_EQ(pixeles8.r[1], static_cast<uint8_t>(58));  // 150 * (100 / 255)
  EXPECT_EQ(pixeles8.g[1], static_cast<uint8_t>(29));  // 75 * (100 / 255)
  EXPECT_EQ(pixeles8.b[1], static_cast<uint8_t>(98));  // 250 * (100 / 255)

  EXPECT_EQ(pixeles8.r[2], static_cast<uint8_t>(78));  // 200 * (100 / 255)
  EXPECT_EQ(pixeles8.g[2], static_cast<uint8_t>(39)); // 100 * (100 / 255)
  EXPECT_EQ(pixeles8.b[2], static_cast<uint8_t>(100)); // 255 * (100 / 255)

  EXPECT_EQ(pixeles8.r[3], static_cast<uint8_t>(39));  // 100 * (100 / 255)
  EXPECT_EQ(pixeles8.g[3], static_cast<uint8_t>(19));  // 50 * (100 / 255)
  EXPECT_EQ(pixeles8.b[3], static_cast<uint8_t>(78)); // 200 * (100 / 255)
}


// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
