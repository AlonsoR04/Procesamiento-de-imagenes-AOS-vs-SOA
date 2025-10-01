#include "imgsoa/imgesoa.hpp"

#include <cstdint>
#include <cstddef>
#include <utility>
#include <gtest/gtest.h>
#include <vector>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)


// Color 8 a clave 32
TEST(Color8AClave32Test, ConvertRGBTo32Bits) {
  // Valores de entrada
  PixelData<uint8_t> pixels;
  pixels.r = {255, 128, 20};
  pixels.g = {128, 64, 40};
  pixels.b = {64, 32, 8};
  uint32_t constexpr resultado_esperado1 = (static_cast<uint32_t>(255) << 16 |
                                            static_cast<uint32_t>(128) << 8 |
                                            static_cast<uint32_t>(64));
  uint32_t constexpr resultado_esperado2 = (static_cast<uint32_t>(128) << 16 |
                                            static_cast<uint32_t>(64) << 8 |
                                            static_cast<uint32_t>(32));
  uint32_t constexpr resultado_esperado3 = (static_cast<uint32_t>(20) << 16 |
                                            static_cast<uint32_t>(40) << 8 |
                                            static_cast<uint32_t>(8));
  // Ejecución y comprobación
  EXPECT_EQ(color8_a_clave32(pixels, 0), resultado_esperado1);
  EXPECT_EQ(color8_a_clave32(pixels, 1), resultado_esperado2);
  EXPECT_EQ(color8_a_clave32(pixels, 2), resultado_esperado3);
}

// Color 16 a clave 64
TEST(Color16AClave64Test, ConvertRGBTo64Bits) {
  // Valores de entrada
  PixelData<uint16_t> pixels;
  pixels.r = {255, 128, 20};
  pixels.g = {128, 64, 40};
  pixels.b = {64, 32, 8};
  uint64_t constexpr resultado_esperado1 = (static_cast<uint64_t>(255) << 32 |
                                            static_cast<uint64_t>(128) << 16 |
                                            static_cast<uint64_t>(64));
  uint64_t constexpr resultado_esperado2 = (static_cast<uint64_t>(128) << 32 |
                                            static_cast<uint64_t>(64) << 16 |
                                            static_cast<uint64_t>(32));
  uint64_t constexpr resultado_esperado3 = (static_cast<uint64_t>(20) << 32 |
                                            static_cast<uint64_t>(40) << 16 |
                                            static_cast<uint64_t>(8));
  // Ejecución y comprobación
  EXPECT_EQ(color16_a_clave64(pixels, 0), resultado_esperado1);
  EXPECT_EQ(color16_a_clave64(pixels, 1), resultado_esperado2);
  EXPECT_EQ(color16_a_clave64(pixels, 2), resultado_esperado3);
}

// Ordenar vector de claves 32
TEST(OrdenarColores32Test, OrderColors32) {
  // Valores de entrada
  std::vector<std::pair<uint32_t, int>> colores = {
    {0xFF0000, 5},
    {0x00FF00, 3},
    {0x0000FF, 3},
    {0xFFFFFF, 5},
    {0x000000, 1}
  };
  // Ejecución
  ordenar_colores32(colores);
  // Comprobación
  std::vector<std::pair<uint32_t, int>> const esperado = {
    {0xFFFFFF, 5},
    {0xFF0000, 5},
    {0x00FF00, 3},
    {0x0000FF, 3},
    {0x000000, 1}
  };
  EXPECT_EQ(colores, esperado);
}

// Ordernar vector vacío
TEST(OrdenarColores32Test, OrderEmptyColors32) {
  // Valor de entrada
  std::vector<std::pair<uint32_t, int>> colores;
  // Ejecución
  ordenar_colores32(colores);
  // Comprobación
  EXPECT_TRUE(colores.empty());
}

// Ordenar vector de claves 64
TEST(OrdenarColores64Test, OrderColor64) {
  // Valores de entrada
  std::vector<std::pair<uint64_t, int>> colores = {
    {0xFF0000, 5},
    {0x00FF00, 3},
    {0x0000FF, 3},
    {0xFFFFFF, 5},
    {0x000000, 1}
  };
  // Ejecución
  ordenar_colores64(colores);
  // Comprobación
  std::vector<std::pair<uint64_t, int>> const esperado = {
    {0xFFFFFF, 5},
    {0xFF0000, 5},
    {0x00FF00, 3},
    {0x0000FF, 3},
    {0x000000, 1}
  };
  EXPECT_EQ(colores, esperado);
}

// Ordenar vector vacío
TEST(OrdenarColores32Test, ManejaListaVacia) {
  // Valor de entrada
  std::vector<std::pair<uint32_t, int>> colores;
  // Ejecución
  ordenar_colores32(colores);
  // Comprobación
  EXPECT_TRUE(colores.empty());
}

// Obtener frecuencia de colores 8

TEST(VectorColores8Test, CalculateFrequencies32) {
  // Valor de entrada
  PixelData<uint8_t> const pixeles = {
    .r={255, 0, 0, 255, 255},
    .g={0, 255, 0, 255, 255},
    .b={0, 0, 255, 0, 0}
  };
  // Ejecución
  auto resultado = vector_colores8(pixeles);
  // Comprobación
  std::vector<std::pair<uint32_t, int>> esperado = {
    {0xFFFF00, 2},
    {0xFF0000, 1},
    {0x00FF00, 1},
    {0x0000FF, 1},
  };
  EXPECT_EQ(resultado.size(), esperado.size());
  for (size_t i = 0; i < resultado.size(); i++) {
    EXPECT_EQ(resultado[i].first, esperado[i].first);
    EXPECT_EQ(resultado[i].second, esperado[i].second);
  }
}

// Obtener frecuencia de colores 16

TEST(VectorColores16Test, CalculateFrequencies63) {
  // Valor de entrada
  PixelData<uint16_t> const pixeles = {
    .r={255, 0, 0, 0, 0},
    .g={0, 255, 0, 0, 0},
    .b={0, 0, 255, 0, 0}
  };
  // Ejecución
  auto resultado = vector_colores16(pixeles);
  // Comprobación
  std::vector<std::pair<uint64_t, int>> esperado = {
    {0x0000000000, 2},
    {0xFF00000000, 1},
    {0x0000FF0000, 1},
    {0x00000000FF, 1},
  };
  EXPECT_EQ(resultado.size(), esperado.size());
  for (size_t i = 0; i < resultado.size(); i++) {
    EXPECT_EQ(resultado[i].first, esperado[i].first);
    EXPECT_EQ(resultado[i].second, esperado[i].second);
  }
}

// Dividir entre claves 32 frecuentes y no frecuentes

TEST(DividirColores32Test, DivideColors32) {
  // Datos de entrada
  std::vector<std::pair<uint32_t, int>> const colores = {
    {0xFF0000, 10}, // Rojo
    {0x00FF00, 8},  // Verde
    {0x0000FF, 6},  // Azul
    {0xFFFFFF, 4},  // Negro
    {0x000000, 2}   // Blanco
  };
  int constexpr n = 2;
  ColoresDivididos<uint32_t> resultado;
  // Ejecución
  dividir_colores(colores, n, resultado);
  // Comprobación
  EXPECT_EQ(resultado.frecuentes.size(), 3);
  EXPECT_EQ(resultado.eliminar.size(), 2);
}

// Dividir entre claves 64 frecuentes y no frecuentes

TEST(DividirColores64Test, DivideColors64) {
  // Datos de entrada
  std::vector<std::pair<uint64_t, int>> const colores = {
    {0xFF00000000000000, 10}, // Color 1
    {0x00FF000000000000, 8},  // Color 2
    {0x0000FF0000000000, 6},  // Color 3
    {0xFFFFFF0000000000, 4},  // Color 4
    {0x000000FF00000000, 2}   // Color 5
  };
  int constexpr n = 2;
  ColoresDivididos<uint64_t> resultado;
  // Ejecución
  dividir_colores(colores, n, resultado);
  // Comprobación
  EXPECT_EQ(resultado.frecuentes.size(), 3); // Debe haber 3 colores frecuentes
  EXPECT_EQ(resultado.eliminar.size(), 2);   // Debe haber 2 colores a eliminar
}

// Buscar color susituto de clave 32

TEST(BuscarColorSustituto32Test, ReplaceColo32) {
  // Valores de entrada
  uint32_t constexpr color_pixel = 0x112233;
  ColoresSOA<uint8_t, uint32_t> colores_frecuentes_cache;
  colores_frecuentes_cache.claves = {0xFF0000, 0x00FF00, 0x0000FF, 0x123456};
  colores_frecuentes_cache.r_values = {255, 0, 0, 18};
  colores_frecuentes_cache.g_values = {0, 255, 0, 52};
  colores_frecuentes_cache.b_values = {0, 0, 255, 86};
  // Ejecución
  uint32_t const resultado = buscar_color_sustituto32(color_pixel, colores_frecuentes_cache);
  // Comprobación
  EXPECT_EQ(resultado, 0x123456);
}

// Buscar color sustituto de clave 64

TEST(BuscarColorSustituto64Test, EncuentraColorMasCercano) {
  // Valores de entrada
  uint64_t constexpr color_pixel = 0xFF00000000000000;
  ColoresSOA<uint16_t, uint64_t> colores_frecuentes_cache;
  colores_frecuentes_cache.claves = {
    0xFF00000000000000, 0x00FF000000000000, 0x0000FF0000000000, 0x1234567890ABCDEF
  };
  colores_frecuentes_cache.r_values = {0xFF00, 0x0000, 0x0000, 0x1234};
  colores_frecuentes_cache.g_values = {0x0000, 0xFF00, 0x0000, 0x5678};
  colores_frecuentes_cache.b_values = {0x0000, 0x0000, 0xFF00, 0x90AB};
  // Ejecución
  uint64_t const resultado = buscar_color_sustituto64(color_pixel, colores_frecuentes_cache);
  // Comprobación
  EXPECT_EQ(resultado, 0xFF00000000000000);
}

// Calcular colores sustitutos de colores 8
TEST(CalcularColoresSustitutos8Test, ReplaceColors32) {
  // Valores de entrada
  PixelData<uint8_t> pixeles{
    .r={255, 128, 64},
    .g={0, 128, 64},
    .b={0, 128, 64}
  };
  auto const colores = vector_colores8(pixeles);
  ColoresDivididos<uint32_t> colores_divididos;
  int constexpr n = 2;
  dividir_colores(colores, n, colores_divididos);
  // Ejecución
  calcular_colores_sustitutos8(pixeles, colores_divididos);
  // Comprobación
  EXPECT_EQ(pixeles.r[1], 255);
  EXPECT_EQ(pixeles.g[1], 0);
  EXPECT_EQ(pixeles.b[1], 0);
  EXPECT_EQ(pixeles.r[2], 255);
  EXPECT_EQ(pixeles.g[2], 0);
  EXPECT_EQ(pixeles.b[2], 0);
}

// Calcular colores sustitutos de colores 16

TEST(CalcularColoresSustitutos16Test, ReplaceColors64) {
  // Valores de entrada
  PixelData<uint16_t> pixeles{
    .r={255, 255, 255, 0, 255},
    .g={0, 0, 0, 255, 0},
    .b={255, 255, 255, 0, 0}
  };
  auto const colores = vector_colores16(pixeles);
  ColoresDivididos<uint64_t> colores_divididos;
  int constexpr n = 2;
  dividir_colores(colores, n, colores_divididos);
  // Ejecución
  calcular_colores_sustitutos16(pixeles, colores_divididos);
  // Comprobación
  for (size_t i = 0; i < pixeles.r.size(); i++) {
    EXPECT_EQ(pixeles.r[i], 255);
    EXPECT_EQ(pixeles.g[i], 0);
    EXPECT_EQ(pixeles.b[i], 255);
  }
}

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)