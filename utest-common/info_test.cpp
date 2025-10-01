#include "gtest/gtest.h"
#include "common/info.hpp"

#include <stdexcept>
#include <fstream>
#include <cstdio>
#include <string>
#include <iostream>

// Test para un archivo existente
TEST(SaveInfoTest, ValidPPMFormat) {
    // Ruta al archivo PPM
    const std::string file_name = "../../in/deer-large.ppm";
    // Abrimos el archivo existente
    std::ifstream input(file_name, std::ios::binary);
    ASSERT_TRUE(input.is_open()) << "No se pudo abrir el archivo: " << file_name;
    // Ejecutamos la función
    Imagen const img = save_info(input);
    // Resultados esperados
    EXPECT_EQ(img.formato, "P6");
    EXPECT_EQ(img.anchura, 8000);
    EXPECT_EQ(img.altura, 6000);
    EXPECT_EQ(img.maxIntensidad, 255);
    // Cerramos el archivo
    input.close();
}
// Test para manejar formato incorrecto de PPM
TEST(SaveInfoTest, InvalidPPMFormat) {
    std::string const file_name = "temp_invalid.ppm";
    std::ofstream tempFile(file_name);
    tempFile << "P5\n800 600\n255\n"; // Formato incorrecto
    tempFile.close();
    std::ifstream input(file_name);
    // Resultado esperado
    EXPECT_THROW(save_info(input), std::runtime_error);
    // Limpiar el archivo temporal
    int const error_remove = std::remove(file_name.c_str());
    ASSERT_FALSE(error_remove) << "Error al eliminar el archivo temporal: " << file_name;
}

// Test para manejar un archivo con un valor máximo de intensidad demasiado alto
TEST(SaveInfoTest, MaxIntensityTooHigh) {
    // Creacion del archivo temporal
    std::string const file_name = "temp_high_max_intensity.ppm";
    std::ofstream tempFile(file_name);
    tempFile << "P6\n800 600\n65536\n";
    tempFile.close();
    std::ifstream input(file_name);
    // Resultado esperado
    EXPECT_THROW(save_info(input), std::runtime_error);
    // Limpiar el archivo temporal
    int const error_remove = std::remove(file_name.c_str());
    ASSERT_FALSE(error_remove) << "Error al eliminar el archivo temporal: " << file_name;
}