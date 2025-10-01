
#include "imgaos/imgeaos.hpp"
#include "common/binaryio.hpp"

#include "gtest/gtest.h"
#include <algorithm>
#include <ios>
#include <fstream>
#include <cstddef>
#include <cstdint>
#include <vector>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

TEST(TestsOrdenarPixeles, TestOrdenarPixeles8) {
  Pixel<uint8_t> constexpr pixel1{.r=100, .g=150, .b=200};
  Pixel<uint8_t> constexpr pixel2{.r=150, .g=100, .b=200};
  Pixel<uint8_t> constexpr pixel3{.r=100, .g=100, .b=250};

  std::vector<Pixel<uint8_t>> pixeles = {pixel1, pixel2, pixel3};

  std::sort(pixeles.begin(), pixeles.end(), ordenar_pixeles<uint8_t>);

  std::vector<Pixel<uint8_t>> pixeles_ordenados = {pixel3, pixel1, pixel2};

  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(pixeles[i].r, pixeles_ordenados[i].r);
    ASSERT_EQ(pixeles[i].g, pixeles_ordenados[i].g);
    ASSERT_EQ(pixeles[i].b, pixeles_ordenados[i].b);
  }
}

TEST(TestsOrdenarPixeles, TestOrdenarPixeles16) {
  Pixel<uint16_t> constexpr pixel1{.r=1000, .g=1500, .b=2000};
  Pixel<uint16_t> constexpr pixel2{.r=1500, .g=1000, .b=2000};
  Pixel<uint16_t> constexpr pixel3{.r=1000, .g=1000, .b=2500};

  std::vector<Pixel<uint16_t>> pixeles = {pixel1, pixel2, pixel3};

  std::sort(pixeles.begin(), pixeles.end(), ordenar_pixeles<uint16_t>);

  std::vector<Pixel<uint16_t>> pixeles_ordenados = {pixel3, pixel1, pixel2};

  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(pixeles[i].r, pixeles_ordenados[i].r);
    ASSERT_EQ(pixeles[i].g, pixeles_ordenados[i].g);
    ASSERT_EQ(pixeles[i].b, pixeles_ordenados[i].b);
  }
}

TEST(TestsTablaColores, TestTablaColores8) {
  std::vector<Pixel<uint8_t>> const pixeles = {
    {.r=100, .g=150, .b=200},
    {.r=100, .g=150, .b=200},
    { .r=50,  .g=50,  .b=50},
    {.r=255, .g=255, .b=255},
    { .r=50,  .g=50,  .b=50}
  };

  auto result        = tabla_colores(static_cast<int>(pixeles.size()), pixeles);
  auto tabla_colores = result.first;
  const int n              = result.second;

  EXPECT_EQ(n, 3);
  ASSERT_EQ(tabla_colores[0].r, 50);
  ASSERT_EQ(tabla_colores[0].g, 50);
  ASSERT_EQ(tabla_colores[0].b, 50);

  ASSERT_EQ(tabla_colores[1].r, 100);
  ASSERT_EQ(tabla_colores[1].g, 150);
  ASSERT_EQ(tabla_colores[1].b, 200);

  ASSERT_EQ(tabla_colores[2].r, 255);
  ASSERT_EQ(tabla_colores[2].g, 255);
  ASSERT_EQ(tabla_colores[2].b, 255);
}

TEST(TestsTablaColores, TestTablaColores16) {
  std::vector<Pixel<uint16_t>> const pixeles = {
    {.r=1000, .g=1500, .b=2000},
    {.r=1000, .g=1500, .b=2000},
    { .r=500,  .g=500,  .b=500},
    {.r=2550, .g=2550, .b=2550},
    { .r=500,  .g=500,  .b=500}
  };

  auto result        = tabla_colores(static_cast<int>(pixeles.size()), pixeles);
  auto tabla_colores = result.first;
  const int n              = result.second;

  EXPECT_EQ(n, 3);
  ASSERT_EQ(tabla_colores[0].r, 500);
  ASSERT_EQ(tabla_colores[0].g, 500);
  ASSERT_EQ(tabla_colores[0].b, 500);

  ASSERT_EQ(tabla_colores[1].r, 1000);
  ASSERT_EQ(tabla_colores[1].g, 1500);
  ASSERT_EQ(tabla_colores[1].b, 2000);

  ASSERT_EQ(tabla_colores[2].r, 2550);
  ASSERT_EQ(tabla_colores[2].g, 2550);
  ASSERT_EQ(tabla_colores[2].b, 2550);
}

TEST(TestEscribirIndices, TestEscribirIndices8) {
  std::vector<Pixel<uint8_t>> const pixeles = {
    {.r=100, .g=150, .b=200},
    {.r=100, .g=150, .b=200},
    { .r=50,  .g=50,  .b=50},
    {.r=255, .g=255, .b=255},
    { .r=50,  .g=50,  .b=50}
  };
  auto result        = tabla_colores(static_cast<int>(pixeles.size()), pixeles);
  auto tabla_colores = result.first;
  std::ofstream salida("../../out/escribirindices.txt", std::ios::binary);
  Pixeles_y_tabla<uint8_t> pixelesYTabla = {.pixeles=pixeles, .tabla_colores=tabla_colores};
  escribir_indices<uint8_t, uint8_t>(salida, static_cast<int>(pixeles.size()), pixelesYTabla);
  salida.close();
  std::ifstream archivo("../../out/escribirindices.txt", std::ios::binary);
  ASSERT_EQ(read_binary<uint8_t>(archivo), static_cast<uint8_t>(1));
  ASSERT_EQ(read_binary<uint8_t>(archivo), static_cast<uint8_t>(1));
  ASSERT_EQ(read_binary<uint8_t>(archivo), static_cast<uint8_t>(0));
  ASSERT_EQ(read_binary<uint8_t>(archivo), static_cast<uint8_t>(2));
  ASSERT_EQ(read_binary<uint8_t>(archivo), static_cast<uint8_t>(0));
  archivo.close();
}

TEST(TestEscribirIndices, TestEscribirIndices16) {
  std::vector<Pixel<uint16_t>> const pixeles = {
    {.r=1000, .g=1500, .b=2000},
    {.r=1000, .g=1500, .b=2000},
    { .r=500,  .g=500,  .b=500},
    {.r=2550, .g=2550, .b=2550},
    { .r=500,  .g=500,  .b=500}
  };
  auto result        = tabla_colores(static_cast<int>(pixeles.size()), pixeles);
  auto tabla_colores = result.first;
  std::ofstream salida("../../out/escribir_indices_test.txt", std::ios::binary);
  Pixeles_y_tabla<uint16_t> pixelesYTabla = {.pixeles=pixeles, .tabla_colores=tabla_colores};
  escribir_indices<uint16_t, uint8_t>(salida, static_cast<int>(pixeles.size()), pixelesYTabla);
  salida.close();
  std::ifstream archivo("../../out/escribir_indices_test.txt", std::ios::binary);
  ASSERT_EQ(read_binary<uint8_t>(archivo), static_cast<uint8_t>(1));
  ASSERT_EQ(read_binary<uint8_t>(archivo), static_cast<uint8_t>(1));
  ASSERT_EQ(read_binary<uint8_t>(archivo), static_cast<uint8_t>(0));
  ASSERT_EQ(read_binary<uint8_t>(archivo), static_cast<uint8_t>(2));
  ASSERT_EQ(read_binary<uint8_t>(archivo), static_cast<uint8_t>(0));
  archivo.close();
}

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
