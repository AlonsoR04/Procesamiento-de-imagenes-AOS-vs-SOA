#include "imgsoa/imgesoa.hpp"
#include "common/binaryio.hpp"

#include "gtest/gtest.h"
#include <ios>
#include <fstream>
#include <cstdint>
#include <vector>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

TEST(TestsTablaColores, TestTablaColores8) {
  PixelData<uint8_t> const pixeles = {
    .r={100, 100, 50, 255, 50},
    .g={150,150,50, 255, 50},
    .b={200,200,50, 155, 50}};

  auto result        = tabla_colores(static_cast<int>(pixeles.r.size()), pixeles);
  auto tabla_colores = result.first;
  const int n              = result.second;

  EXPECT_EQ(n, 3);

  ASSERT_EQ(tabla_colores.r[0], 50);
  ASSERT_EQ(tabla_colores.r[1], 100);
  ASSERT_EQ(tabla_colores.r[2], 255);

  ASSERT_EQ(tabla_colores.g[0], 50);
  ASSERT_EQ(tabla_colores.g[1], 150);
  ASSERT_EQ(tabla_colores.g[2], 255);

  ASSERT_EQ(tabla_colores.b[0], 50);
  ASSERT_EQ(tabla_colores.b[1], 200);
  ASSERT_EQ(tabla_colores.b[2], 155);
}

TEST(TestsTablaColores, TestTablaColores16) {
  PixelData<uint16_t> const pixeles = {
    .r={1000, 1000, 500, 2550, 500},
    .g={1500,1500,500, 2550, 500},
    .b={2000,2000,500, 1550, 500}};

  auto result        = tabla_colores(static_cast<int>(pixeles.r.size()), pixeles);
  auto tabla_colores = result.first;
  const int n              = result.second;

  EXPECT_EQ(n, 3);
  ASSERT_EQ(tabla_colores.r[0], 500);
  ASSERT_EQ(tabla_colores.r[1], 1000);
  ASSERT_EQ(tabla_colores.r[2], 2550);

  ASSERT_EQ(tabla_colores.g[0], 500);
  ASSERT_EQ(tabla_colores.g[1], 1500);
  ASSERT_EQ(tabla_colores.g[2], 2550);

  ASSERT_EQ(tabla_colores.b[0], 500);
  ASSERT_EQ(tabla_colores.b[1], 2000);
  ASSERT_EQ(tabla_colores.b[2], 1550);
}

TEST(TestEscribirIndices, TestEscribirIndices8) {
  PixelData<uint8_t> const pixeles = {
    .r={100, 100, 50, 255, 50},
    .g={150, 150, 50, 255, 50},
    .b={200, 200, 50, 255, 50}};

  auto result        = tabla_colores(static_cast<int>(pixeles.r.size()), pixeles);
  auto tabla_colores = result.first;
  std::ofstream salida("../../out/escribir_indices_test.txt", std::ios::binary);
  Pixeles_y_tabla<uint8_t> pixelesYTabla = {.pixeles=pixeles, .tabla_colores=tabla_colores};
  escribir_indices<uint8_t, uint8_t>(salida, pixelesYTabla);
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
