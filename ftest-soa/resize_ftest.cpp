#include "common/binaryio.hpp"
#include "imgsoa/imgesoa.hpp"

#include "gtest/gtest.h"
#include <cmath>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

TEST(ResizeImageTest, Resize) {
  std::string const inputImagePath  = "../../in/deer-large.ppm";
  std::string const outputImagePath = "../../out/resize_testSOA.ppm";
  std::ifstream inputFile(inputImagePath, std::ios::binary);

  int const result = resize(inputFile, outputImagePath, 1000, 1000);
  inputFile.close();
  ASSERT_EQ(result, 0);

  std::string const archivoProfe = "../../expected/resize/deer-large-1000.ppm";
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

TEST(ResizeImageTest, Resize2) {
  std::string const inputImagePath  = "../../in/deer-large.ppm";
  std::string const outputImagePath = "../../out/resize_testSOA.ppm";
  std::ifstream inputFile(inputImagePath, std::ios::binary);

  int const result = resize(inputFile, outputImagePath, 100, 100);
  inputFile.close();
  ASSERT_EQ(result, 0);

  std::string const archivoProfe = "../../expected/resize/deer-large-100.ppm";
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
