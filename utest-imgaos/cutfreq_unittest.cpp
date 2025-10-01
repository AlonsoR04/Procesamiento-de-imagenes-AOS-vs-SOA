
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

#include "imgaos/imgeaos.hpp"

#include <cstdint>
#include <gtest/gtest.h>
#include <utility>
#include <vector>

// Color 8 a clave 32
TEST(Color8AClave32Test, ConvertRGBTo32Bits) {
  // Valores de entrada
  Pixel<uint8_t> constexpr rojo_pixel{.r = 255, .g = 0, .b = 0};
  Pixel<uint8_t> constexpr verde_pixel{.r = 0, .g = 255, .b = 0};
  Pixel<uint8_t> constexpr azul_pixel{.r = 0, .g = 0, .b = 255};
  Pixel<uint8_t> constexpr blanco_pixel{.r = 0, .g = 0, .b = 0};
  Pixel<uint8_t> constexpr negro_pixel{.r = 255, .g = 255, .b = 255};
  // Resultato esperado
  uint32_t constexpr rojo_clave   = 0xFF0000;
  uint32_t constexpr verde_clave  = 0x00FF00;
  uint32_t constexpr azul_clave   = 0x0000FF;
  uint32_t constexpr blanco_clave = 0x000000;
  uint32_t constexpr negro_clave  = 0xFFFFFF;
  // Ejecución y comprobación
  EXPECT_EQ(color8_a_clave32(rojo_pixel), rojo_clave);
  EXPECT_EQ(color8_a_clave32(verde_pixel), verde_clave);
  EXPECT_EQ(color8_a_clave32(azul_pixel), azul_clave);
  EXPECT_EQ(color8_a_clave32(blanco_pixel), blanco_clave);
  EXPECT_EQ(color8_a_clave32(negro_pixel), negro_clave);
}

// Clave 32 a color 8
TEST(Clave32AColor8Test, Convert32BitsToRGB) {
  // Valores de entrada
  uint32_t constexpr rojo_clave   = 0xFF0000;
  uint32_t constexpr verde_clave  = 0x00FF00;
  uint32_t constexpr azul_clave   = 0x0000FF;
  uint32_t constexpr blanco_clave = 0x000000;
  uint32_t constexpr negro_clave  = 0xFFFFFF;
  // Resultado esperado
  Pixel<uint8_t> constexpr rojo_pixel   = {.r = 255, .g = 0, .b = 0};
  Pixel<uint8_t> constexpr verde_pixel  = {.r = 0, .g = 255, .b = 0};
  Pixel<uint8_t> constexpr azul_pixel   = {.r = 0, .g = 0, .b = 255};
  Pixel<uint8_t> constexpr blanco_pixel = {.r = 0, .g = 0, .b = 0};
  Pixel<uint8_t> constexpr negro_pixel  = {.r = 255, .g = 255, .b = 255};
  // Ejecución
  auto resultado_rojo   = clave32_a_color8(rojo_clave);
  auto resultado_verde  = clave32_a_color8(verde_clave);
  auto resultado_azul   = clave32_a_color8(azul_clave);
  auto resultado_blanco = clave32_a_color8(blanco_clave);
  auto resultado_negro  = clave32_a_color8(negro_clave);
  // Resultado
  EXPECT_EQ(resultado_rojo.r, rojo_pixel.r);
  EXPECT_EQ(resultado_rojo.g, rojo_pixel.b);
  EXPECT_EQ(resultado_rojo.b, rojo_pixel.b);
  EXPECT_EQ(resultado_verde.r, verde_pixel.r);
  EXPECT_EQ(resultado_verde.g, verde_pixel.g);
  EXPECT_EQ(resultado_verde.b, verde_pixel.b);
  EXPECT_EQ(resultado_azul.r, azul_pixel.r);
  EXPECT_EQ(resultado_azul.g, azul_pixel.g);
  EXPECT_EQ(resultado_azul.b, azul_pixel.b);
  EXPECT_EQ(resultado_blanco.r, blanco_pixel.r);
  EXPECT_EQ(resultado_blanco.g, blanco_pixel.g);
  EXPECT_EQ(resultado_blanco.b, blanco_pixel.b);
  EXPECT_EQ(resultado_negro.r, negro_pixel.r);
  EXPECT_EQ(resultado_negro.g, negro_pixel.g);
  EXPECT_EQ(resultado_negro.b, negro_pixel.b);
}

// Color 16 a clave 64
TEST(Color16AClave64Test, ConvertRGBTo64Bits) {
  // Valores de entrada
  Pixel<uint16_t> constexpr rojo_pixel{.r = 255, .g = 0, .b = 0};
  Pixel<uint16_t> constexpr verde_pixel{.r = 0, .g = 255, .b = 0};
  Pixel<uint16_t> constexpr azul_pixel{.r = 0, .g = 0, .b = 255};
  Pixel<uint16_t> constexpr blanco_pixel{.r = 0, .g = 0, .b = 0};
  Pixel<uint16_t> constexpr negro_pixel{.r = 255, .g = 255, .b = 255};
  // Resultados esperados
  uint64_t constexpr rojo_clave   = 0x000000FF00000000;
  uint64_t constexpr verde_clave  = 0x0000000000FF0000;
  uint64_t constexpr azul_clave   = 0x00000000000000FF;
  uint64_t constexpr blanco_clave = 0x0000000000000000;
  uint64_t constexpr negro_clave  = 0x000000FF00FF00FF;
  // Ejecución y comprobación
  EXPECT_EQ(color16_a_clave64(rojo_pixel), rojo_clave);
  EXPECT_EQ(color16_a_clave64(verde_pixel), verde_clave);
  EXPECT_EQ(color16_a_clave64(azul_pixel), azul_clave);
  EXPECT_EQ(color16_a_clave64(blanco_pixel), blanco_clave);
  EXPECT_EQ(color16_a_clave64(negro_pixel), negro_clave);
}

// Clave 64 a color 16
TEST(Clave64AColor16Test, Convert64BitsToRGB) {
  // Valores de entrada
  uint64_t constexpr rojo_clave   = 0x000000FF00000000;
  uint64_t constexpr verde_clave  = 0x0000000000FF0000;
  uint64_t constexpr azul_clave   = 0x00000000000000FF;
  uint64_t constexpr blanco_clave = 0x0000000000000000;
  uint64_t constexpr negro_clave  = 0x000000FF00FF00FF;
  // Resultado esperado
  Pixel<uint16_t> constexpr rojo_pixel   = {.r = 255, .g = 0, .b = 0};
  Pixel<uint16_t> constexpr verde_pixel  = {.r = 0, .g = 255, .b = 0};
  Pixel<uint16_t> constexpr azul_pixel   = {.r = 0, .g = 0, .b = 255};
  Pixel<uint16_t> constexpr blanco_pixel = {.r = 0, .g = 0, .b = 0};
  Pixel<uint16_t> constexpr negro_pixel  = {.r = 255, .g = 255, .b = 255};
  // Ejecución
  auto resultado_rojo   = clave64_a_color16(rojo_clave);
  auto resultado_verde  = clave64_a_color16(verde_clave);
  auto resultado_azul   = clave64_a_color16(azul_clave);
  auto resultado_blanco = clave64_a_color16(blanco_clave);
  auto resultado_negro  = clave64_a_color16(negro_clave);
  // Comprobación
  EXPECT_EQ(resultado_rojo.r, rojo_pixel.r);
  EXPECT_EQ(resultado_rojo.g, rojo_pixel.g);
  EXPECT_EQ(resultado_rojo.b, rojo_pixel.b);
  EXPECT_EQ(resultado_verde.r, verde_pixel.r);
  EXPECT_EQ(resultado_verde.g, verde_pixel.g);
  EXPECT_EQ(resultado_verde.b, verde_pixel.b);
  EXPECT_EQ(resultado_azul.r, azul_pixel.r);
  EXPECT_EQ(resultado_azul.g, azul_pixel.g);
  EXPECT_EQ(resultado_azul.b, azul_pixel.b);
  EXPECT_EQ(resultado_blanco.r, blanco_pixel.r);
  EXPECT_EQ(resultado_blanco.g, blanco_pixel.g);
  EXPECT_EQ(resultado_blanco.b, blanco_pixel.b);
  EXPECT_EQ(resultado_negro.r, negro_pixel.r);
  EXPECT_EQ(resultado_negro.g, negro_pixel.g);
  EXPECT_EQ(resultado_negro.b, negro_pixel.b);
}

// Ordenar vector de claves 32
TEST(OrdenarColores32Test, OrderPixels32) {
  // Valor de entrada
  Pixel<uint8_t> constexpr pixel1{.r = 100, .g = 150, .b = 200};
  Pixel<uint8_t> constexpr pixel2{.r = 50, .g = 100, .b = 150};
  Pixel<uint8_t> constexpr pixel3{.r = 200, .g = 250, .b = 100};
  Pixel<uint8_t> constexpr pixel4                     = {.r = 100, .g = 150, .b = 200};
  std::vector<std::pair<uint32_t, int>> colores_32bit = {
    {color8_a_clave32(pixel1), 5},
    {color8_a_clave32(pixel2), 3},
    {color8_a_clave32(pixel3), 5},
    {color8_a_clave32(pixel4), 7},
  };
  // Ejecución
  ordenar_colores32(colores_32bit);
  // Comprobación
  EXPECT_EQ(colores_32bit[0].second, 7);
  EXPECT_EQ(colores_32bit[1].second, 5);
  EXPECT_EQ(colores_32bit[1].first, color8_a_clave32(pixel1));
  EXPECT_EQ(colores_32bit[2].first, color8_a_clave32(pixel3));
  EXPECT_EQ(colores_32bit[2].second, 5);
  EXPECT_EQ(colores_32bit[3].second, 3);
}

// Ordenar vector de claves 64
TEST(OrdenarColores64Test, OrderPixels64) {
  // Valor de entrada
  Pixel<uint16_t> constexpr pixel1{.r = 100, .g = 150, .b = 200};
  Pixel<uint16_t> constexpr pixel2{.r = 50, .g = 100, .b = 150};
  Pixel<uint16_t> constexpr pixel3{.r = 200, .g = 250, .b = 100};
  Pixel<uint16_t> constexpr pixel4                    = {.r = 100, .g = 150, .b = 200};
  std::vector<std::pair<uint64_t, int>> colores_64bit = {
    {color16_a_clave64(pixel1), 5},
    {color16_a_clave64(pixel2), 3},
    {color16_a_clave64(pixel3), 5},
    {color16_a_clave64(pixel4), 7},
  };
  // Ejecución
  auto colores_ordenados = ordenar_colores64(colores_64bit);
  // Comprobación
  EXPECT_EQ(colores_ordenados[0].second, 7);
  EXPECT_EQ(colores_ordenados[1].second, 5);
  EXPECT_EQ(colores_ordenados[1].first, color16_a_clave64(pixel1));
  EXPECT_EQ(colores_ordenados[2].first, color16_a_clave64(pixel3));
  EXPECT_EQ(colores_ordenados[2].second, 5);
  EXPECT_EQ(colores_ordenados[3].second, 3);
}

// Obtener frecuencia de colores 8
TEST(VectorColores8Test, MapFrequenceColor8) {
  // Valor de entrada
  std::vector<Pixel<uint8_t>> const pixeles = {
    {.r = 255,   .g = 0,   .b = 0}, // Color rojo
    {  .r = 0, .g = 255,   .b = 0}, // Color verde
    {  .r = 0,   .g = 0, .b = 255}, // Color azul
    {.r = 255,   .g = 0,   .b = 0}, // Color rojo
    {  .r = 0, .g = 255,   .b = 0}, // Color verde
  };
  // Ejecución
  auto resultado = vector_colores8(pixeles);
  // Comprobación
  ASSERT_EQ(resultado.size(), 3);
  for (auto const & par : resultado) {
    if (par.first == color8_a_clave32({.r = 255, .g = 0, .b = 0})) {
      ASSERT_EQ(par.second, 2);  // El color rojo debe aparecer 2 veces
    } else if (par.first == color8_a_clave32({.r = 0, .g = 255, .b = 0})) {
      ASSERT_EQ(par.second, 2);  // El color verde debe aparecer 2 veces
    } else if (par.first == color8_a_clave32({.r = 0, .g = 0, .b = 255})) {
      ASSERT_EQ(par.second, 1);  // El color azul debe aparecer 1 vez
    }
  }
}

// Obtener frecuencia de colores 16
TEST(VectorColores16Test, MapFrequenceColor16) {
  // Valor de entrada
  std::vector<Pixel<uint16_t>> const pixeles = {
    {.r = 255,   .g = 0,   .b = 0}, // Color rojo
    {  .r = 0, .g = 255,   .b = 0}, // Color verde
    {  .r = 0,   .g = 0, .b = 255}, // Color azul
    {.r = 255,   .g = 0,   .b = 0}, // Color rojo
    {  .r = 0, .g = 255,   .b = 0}, // Color verde
  };
  // Ejecución
  auto resultado = vector_colores16(pixeles);
  // Comprobación
  ASSERT_EQ(resultado.size(), 3);
  for (auto const & par : resultado) {
    if (par.first == color8_a_clave32({.r = 255, .g = 0, .b = 0})) {
      ASSERT_EQ(par.second, 2);  // El color rojo debe aparecer 2 veces
    } else if (par.first == color8_a_clave32({.r = 0, .g = 255, .b = 0})) {
      ASSERT_EQ(par.second, 2);  // El color verde debe aparecer 2 veces
    } else if (par.first == color8_a_clave32({.r = 0, .g = 0, .b = 255})) {
      ASSERT_EQ(par.second, 1);  // El color azul debe aparecer 1 vez
    }
  }
}

// Dividir entre claves 32 frecuentes y no frecuentes
TEST(DividirColoresTest, DivideColors32) {
  // Valor de entrada
  std::vector<std::pair<uint32_t, int>> const colores = {
    {static_cast<uint32_t>(1), 5},
    {static_cast<uint32_t>(2), 3},
    {static_cast<uint32_t>(3), 1},
    {static_cast<uint32_t>(4), 8},
    {static_cast<uint32_t>(5), 2},
  };
  int constexpr n = 2;
  // Ejecución
  ColoresDivididos<uint32_t> colores_divididos;
  dividir_colores(colores, n, colores_divididos);
  // Comprobación
  ASSERT_EQ(colores_divididos.frecuentes.size(), 3);
  ASSERT_EQ(colores_divididos.eliminar.size(), 2);
}

// Dividir entre claves 64 frecuentes y no frecuentes
TEST(DividirColoresTest, DivideColors64) {
  // Valor de entrada
  std::vector<std::pair<uint64_t, int>> const colores = {
    {static_cast<uint64_t>(1), 5}, // Color 1, frecuencia 5
    {static_cast<uint64_t>(2), 3}, // Color 2, frecuencia 3
    {static_cast<uint64_t>(3), 1}, // Color 3, frecuencia 1
    {static_cast<uint64_t>(4), 8}, // Color 4, frecuencia 8
    {static_cast<uint64_t>(5), 2}, // Color 5, frecuencia 2
  };
  int constexpr n = 4;
  // Ejecución
  ColoresDivididos<uint64_t> colores_divididos;
  dividir_colores(colores, n, colores_divididos);
  // Comprobación
  ASSERT_EQ(colores_divididos.frecuentes.size(), 1);
  ASSERT_EQ(colores_divididos.eliminar.size(), 4);
}

// Buscar color sustituto de clave 32
TEST(BuscarColorSustituto32Test, ReplaceColor32) {
  // Valores de entrada
  uint32_t constexpr color_pixel                                                  = 0x12345678;
  std::vector<std::pair<uint32_t, Pixel<uint8_t>>> const colores_frecuentes_cache = {
    {0x11223344, Pixel<uint8_t>{.r = 0x11, .g = 0x22, .b = 0x33}},
    {0x55667788, Pixel<uint8_t>{.r = 0x55, .g = 0x66, .b = 0x77}},
    {0xAABBCCDD, Pixel<uint8_t>{.r = 0xAA, .g = 0xBB, .b = 0xCC}}
  };
  // Ejecución
  uint32_t const color_resultado = buscar_color_sustituto32(color_pixel, colores_frecuentes_cache);
  // Comprobación
  uint32_t constexpr color_esperado = 0x55667788;
  EXPECT_EQ(color_resultado, color_esperado);
}

// Buscar color sustituto de clave 32 con caché vacía
TEST(BuscarColorSustituto32Test, EmptyCacheNoReplaceColor32) {
  // Valores de entrada
  uint32_t constexpr color_pixel = 0x12345678;
  std::vector<std::pair<uint32_t, Pixel<uint8_t>>> constexpr colores_frecuentes_cache;
  // Ejecución
  uint32_t const color_resultado = buscar_color_sustituto32(color_pixel, colores_frecuentes_cache);
  // Comprobación
  EXPECT_EQ(color_resultado, color_pixel);
}

// Buscar color sustituto de clave 64
TEST(BuscarColorSustituto64Test, ReplaceColor64) {
  // Valores de entrada
  uint64_t constexpr color_pixel                                                   = 0x12345678;
  std::vector<std::pair<uint64_t, Pixel<uint16_t>>> const colores_frecuentes_cache = {
    {0x11223344, Pixel<uint16_t>{.r = 0x11, .g = 0x22, .b = 0x33}},
    {0x55667788, Pixel<uint16_t>{.r = 0x55, .g = 0x66, .b = 0x77}},
    {0xAABBCCDD, Pixel<uint16_t>{.r = 0xAA, .g = 0xBB, .b = 0xCC}}
  };
  // Ejecución
  uint64_t const color_resultado = buscar_color_sustituto64(color_pixel, colores_frecuentes_cache);
  // Comprobación
  uint64_t constexpr color_esperado = 2864434397;
  EXPECT_EQ(color_resultado, color_esperado);
}

// Buscar color sustituto de clave 64 con caché vacía
TEST(BuscarColorSustituto64Test, EmptyCacheNoReplaceColor64) {
  // Valores de entrada
  uint64_t constexpr color_pixel = 0x12345678;
  std::vector<std::pair<uint64_t, Pixel<uint16_t>>> constexpr colores_frecuentes_cache;
  // Ejecución
  uint64_t const color_resultado = buscar_color_sustituto64(color_pixel, colores_frecuentes_cache);
  // Comprobación
  EXPECT_EQ(color_resultado, color_pixel);
}

// Calcular colores sustitutos de colores 8
TEST(CalcularColoresSustitutos8Test, ChangePixels32) {
  // Valores de entrada
  std::vector<Pixel<uint8_t>> pixeles = {
    {  .r = 0,   .g = 0, .b = 255},
    {  .r = 0,   .g = 0, .b = 255},
    {  .r = 0,   .g = 0, .b = 255},
    {  .r = 0, .g = 255,   .b = 0},
    {.r = 255,   .g = 0,   .b = 0}
  };
  int constexpr n = 2;
  auto colores    = vector_colores8(pixeles);
  ordenar_colores32(colores);
  ColoresDivididos<uint32_t> colores_divididos;
  dividir_colores(colores, n, colores_divididos);
  // Ejecución
  calcular_colores_sustitutos8(pixeles, colores_divididos);
  // Comprobación
  for (auto const & pixel : pixeles) {
    EXPECT_EQ(pixel.r, 0);
    EXPECT_EQ(pixel.g, 0);
    EXPECT_EQ(pixel.b, 255);
  }
}

// Calcular colores sustitutos de colores 16
TEST(CalcularColoresSustitutos16Test, ChangePixels64) {
  // Valores de entrada
  std::vector<Pixel<uint16_t>> pixeles = {
    {.r = 255,   .g = 0, .b = 255},
    {.r = 255,   .g = 0, .b = 255},
    {  .r = 0,   .g = 0, .b = 255},
    {  .r = 0, .g = 255,   .b = 0},
    {.r = 255,   .g = 0,   .b = 0}
  };
  int constexpr n              = 3;
  auto colores                 = vector_colores16(pixeles);
  auto const colores_ordenados = ordenar_colores64(colores);
  ColoresDivididos<uint64_t> colores_divididos;
  dividir_colores(colores_ordenados, n, colores_divididos);
  // Ejecución
  calcular_colores_sustitutos16(pixeles, colores_divididos);
  // Comprobación
  for (auto const & pixel : pixeles) {
    EXPECT_EQ(pixel.r, 255);
    EXPECT_EQ(pixel.g, 0);
    EXPECT_EQ(pixel.b, 255);
  }
}

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)