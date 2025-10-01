#include "common/binaryio.hpp"
#include "imgaos/imgeaos.hpp"

#include "gtest/gtest.h"
#include <cmath>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

TEST(CompressImageTest, Compress) {
  std::string const inputImagePath  = "../../in/lake-small.ppm";
  std::string const outputImagePath = "../../out/compress_testAOS.cppm";
  std::ifstream inputFile(inputImagePath, std::ios::binary);

  int const result = compress(inputFile, outputImagePath);
  inputFile.close();
  ASSERT_EQ(result, 0);

  std::string const archivoProfe = "../../expected/compress/lake-small.cppm";
  std::ifstream archivo(
      archivoProfe, std::ios::binary | std::ios::ate);  // Abrir en binario y posicionarse al final
  if (!archivo) { std::cerr << "No se pudo abrir el archivo.\n"; }

  std::streamsize const tamano = archivo.tellg();  // Obtener  el tamaño en bytes del archivo
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

TEST(CompressImageTest, Compress2) {
  std::string const inputImagePath  = "../../in/deer-small.ppm";
  std::string const outputImagePath = "../../out/compress_testAOS2.cppm";
  std::ifstream inputFile(inputImagePath, std::ios::binary);

  int const result = compress(inputFile, outputImagePath);
  inputFile.close();
  ASSERT_EQ(result, 0);

  std::string const archivoProfe = "../../expected/compress/deer-small.cppm";
  std::ifstream archivo(
      archivoProfe, std::ios::binary | std::ios::ate);  // Abrir en binario y posicionarse al final
  if (!archivo) { std::cerr << "No se pudo abrir el archivo.\n"; }

  std::streamsize const tamano = archivo.tellg();  // Obtener el tamaño en bytes del archivo
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
