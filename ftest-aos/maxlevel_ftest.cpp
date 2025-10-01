#include "common/binaryio.hpp"
#include "imgaos/imgeaos.hpp"

#include "gtest/gtest.h"
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

TEST(MaxLevelImageTest, ImageTest8to16) {
  std::string const inputImagePath  = "../../in/deer-small.ppm";
  std::string const outputImagePath = "../../out/maxlevel_test8_16AOS.ppm";
  int constexpr new_max_level       = 1000;

  std::ifstream inputFile(inputImagePath, std::ios::binary);

  int const result = maxlevel(inputFile, new_max_level, outputImagePath);
  ASSERT_EQ(result, 0);
  inputFile.close();

  std::string const archivoProfe = "../../expected/maxlevel/deer-small-1000.ppm";
  std::ifstream archivo(
      archivoProfe, std::ios::binary | std::ios::ate);  // Abrir en binario y posicionarse al final
  if (!archivo) { std::cerr << "No se pudo abrir el archivo.\n"; }

  std::streamsize const tamano = archivo.tellg();  // Obtener la posición final del archivo
  archivo.close();

  int n = 0;
  std::ifstream solucion(archivoProfe, std::ios::binary);
  std::ifstream compress(outputImagePath, std::ios::binary);

  for (int i = 0; i < tamano; i++) {
    int const valor_profe    = static_cast<int>(read_binary<uint8_t>(solucion));
    int const valor_compress = static_cast<int>(read_binary<uint8_t>(compress));
    if (-5 > valor_profe - valor_compress || valor_profe - valor_compress > 5) {
      // std::cout << "byte: " << i << ", profe: " << valor_profe << ", resize: " << valor_resize <<
      // "\n";
      n++;
    }
  }
  solucion.close();
  compress.close();
  ASSERT_EQ(n, 0);
}

TEST(MaxLevelImageTest, ImageTest8to8) {
  std::string const inputImagePath  = "../../in/deer-small.ppm";
  std::string const outputImagePath = "../../out/maxlevel_test8_8AOS.ppm";
  int constexpr new_max_level       = 100;

  std::ifstream inputFile(inputImagePath, std::ios::binary);

  int const result = maxlevel(inputFile, new_max_level, outputImagePath);
  inputFile.close();
  ASSERT_EQ(result, 0);

  std::string const archivoProfe = "../../expected/maxlevel/deer-small-100.ppm";
  std::ifstream archivo(
      archivoProfe, std::ios::binary | std::ios::ate);  // Abrir en binario y posicionarse al final
  if (!archivo) { std::cerr << "No se pudo abrir el archivo.\n"; }

  std::streamsize const tamano = archivo.tellg();  // Obtener la posición final del archivo
  archivo.close();

  int n = 0;
  std::ifstream solucion(archivoProfe, std::ios::binary);
  std::ifstream compress(outputImagePath, std::ios::binary);

  for (int i = 0; i < tamano; i++) {
    int const valor_profe    = static_cast<int>(read_binary<uint8_t>(solucion));
    int const valor_compress = static_cast<int>(read_binary<uint8_t>(compress));
    if (-5 > valor_profe - valor_compress || valor_profe - valor_compress > 5) {
      // std::cout << "byte: " << i << ", profe: " << valor_profe << ", resize: " << valor_resize <<
      // "\n";
      n++;
    }
  }
  solucion.close();
  compress.close();
  ASSERT_EQ(n, 0);
}

TEST(MaxLevelImageTest, ImageTest16to8) {
  std::string const inputImagePath  = "../../expected/maxlevel/deer-small-65535.ppm";
  std::string const outputImagePath = "../../out/maxlevel_test16_8AOS.ppm";
  int constexpr new_max_level       = 100;

  std::ifstream inputFile(inputImagePath, std::ios::binary);

  int const result = maxlevel(inputFile, new_max_level, outputImagePath);
  inputFile.close();
  ASSERT_EQ(result, 0);

  std::string const archivoProfe = "../../expected/maxlevel/deer-small-100.ppm";
  std::ifstream archivo(
      archivoProfe, std::ios::binary | std::ios::ate);  // Abrir en binario y posicionarse al final
  if (!archivo) { std::cerr << "No se pudo abrir el archivo.\n"; }

  std::streamsize const tamano = archivo.tellg();  // Obtener la posición final del archivo
  archivo.close();

  int n = 0;
  std::ifstream solucion(archivoProfe, std::ios::binary);
  std::ifstream compress(outputImagePath, std::ios::binary);

  for (int i = 0; i < tamano; i++) {
    int const valor_profe    = static_cast<int>(read_binary<uint8_t>(solucion));
    int const valor_compress = static_cast<int>(read_binary<uint8_t>(compress));
    if (-5 > valor_profe - valor_compress || valor_profe - valor_compress > 5) {
      // std::cout << "byte: " << i << ", profe: " << valor_profe << ", resize: " << valor_resize <<
      // "\n";
      n++;
    }
  }
  solucion.close();
  compress.close();
  ASSERT_EQ(n, 0);
}

TEST(MaxLevelImageTest, ImageTest16to16) {
  std::string const inputImagePath  = "../../expected/maxlevel/deer-small-65535.ppm";
  std::string const outputImagePath = "../../out/maxlevel_test16_16AOS.ppm";
  int constexpr new_max_level       = 1000;

  std::ifstream inputFile(inputImagePath, std::ios::binary);

  int const result = maxlevel(inputFile, new_max_level, outputImagePath);
  inputFile.close();
  ASSERT_EQ(result, 0);

  std::string const archivoProfe = "../../expected/maxlevel/deer-small-1000.ppm";
  std::ifstream archivo(
      archivoProfe, std::ios::binary | std::ios::ate);  // Abrir en binario y posicionarse al final
  if (!archivo) { std::cerr << "No se pudo abrir el archivo.\n"; }

  std::streamsize const tamano = archivo.tellg();  // Obtener la posición final del archivo
  archivo.close();

  int n = 0;
  std::ifstream solucion(archivoProfe, std::ios::binary);
  std::ifstream compress(outputImagePath, std::ios::binary);

  for (int i = 0; i < tamano; i++) {
    int const valor_profe    = static_cast<int>(read_binary<uint8_t>(solucion));
    int const valor_compress = static_cast<int>(read_binary<uint8_t>(compress));
    if (-5 > valor_profe - valor_compress || valor_profe - valor_compress > 5) {
      // std::cout << "byte: " << i << ", profe: " << valor_profe << ", resize: " << valor_resize <<
      // "\n";
      n++;
    }
  }
  solucion.close();
  compress.close();
  ASSERT_EQ(n, 0);
}

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
