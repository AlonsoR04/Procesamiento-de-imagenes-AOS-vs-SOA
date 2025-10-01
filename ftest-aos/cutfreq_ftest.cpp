#include "imgaos/imgeaos.hpp"

#include "gtest/gtest.h"
#include <cmath>
#include <fstream>
#include <ios>
#include <string>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

// Para los test funcionales de la funcion cutfreq no hemos comprobado que sean
// similares a los outputs esperados por lo mencionado en la memoria
TEST(Cutfreqtest, Cutfreq162) {
  std::string const inputImagePath  = "../../in/lake-large.ppm";
  std::string const outputImagePath = "../../out/cutfreq_162kAOS.ppm";
  int constexpr colors              = 162000;

  std::ifstream inputFile(inputImagePath, std::ios::binary);

  // Realiza la operación de escalado de imagen
  int const result = cutfreq(inputFile, outputImagePath, colors);

  // Cierra el archivo de entrada
  inputFile.close();

  // Verifica que la operación no devuelva un error
  ASSERT_EQ(result, 0);
}

TEST(Cutfreqtest, Cutfreq100) {
  std::string const inputImagePath  = "../../in/lake-large.ppm";
  std::string const outputImagePath = "../../out/cutfreq_100kAOS.ppm";
  int constexpr colors              = 100000;

  std::ifstream inputFile(inputImagePath, std::ios::binary);

  // Realiza la operación de escalado de imagen
  int const result = cutfreq(inputFile, outputImagePath, colors);

  // Cierra el archivo de entrada
  inputFile.close();

  // Verifica que la operación no devuelva un error
  ASSERT_EQ(result, 0);
}

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)