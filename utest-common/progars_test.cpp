#include "common/progars.hpp"

#include "gtest/gtest.h"
#include <cstddef>
#include <string>
#include <vector>

/* FUNCION CONVERTIR ENTERO */

/* Test para comprobar la entrada de una cadena de texto valida (convertible a entero)*/
TEST(convertir_entero, valid_value){
  // Cadena que representa un numero entero
  EXPECT_EQ(10, convertir_entero("10"));
}

/* Test para comprobar la entrada de una cadena de texto invalida (no se puede convertir a entero) */
TEST(convertir_entero, invalid_value){
  // Cadena que no representa un entero
  EXPECT_EQ(-1, convertir_entero("hola"));
  // Cadena que representa un entero fuera de rango para la funcion std::stoi
  EXPECT_EQ(-1, convertir_entero("10000000000000000"));
}

/* FUNCION NUMERO_ARGUMENTOS_ERRONEO */

/* Test para comprobar la entrada de un numero de argumento válido*/
TEST(numero_argumentos_erroneo, valid_argc) {
  EXPECT_EQ(0, numero_argumentos_erroneo(3));
  EXPECT_EQ(0, numero_argumentos_erroneo(4));
  EXPECT_EQ(0, numero_argumentos_erroneo(5));
}

/* Test para comprobar la entrada de un numero de argumentos menor o mayor al permitido */
TEST(numero_argumentos_erroneo, invalid_argc) {
  EXPECT_EQ(-1, numero_argumentos_erroneo(2));
  EXPECT_EQ(-1, numero_argumentos_erroneo(6));
}

/* FUNCION CHECK INFO */

/* Test para comprobar una entrada válida para la operación INFO */
TEST(check_info, valid_value) {
  // Establecemos un vector de comandos
  std::vector<std::string> const argumentos = {"input.ppm", "output.ppm", "info"};
  // Calculamos el tamaño del vector
  std::size_t const tamano_argumentos = argumentos.size();
  EXPECT_EQ(0, check_info(static_cast<int>(tamano_argumentos), argumentos));
}

/* Test para comprobar una entrada invalida para la operación INFO */
TEST(check_info, invalid_value) {
  // Número de argumentos mayor a 3
  std::vector<std::string> const argumentos1 = {"input.ppm", "output.ppm", "info", "3"};
  std::size_t const tamano_argumentos1 = argumentos1.size();
  EXPECT_EQ(-1, check_info(static_cast<int>(tamano_argumentos1), argumentos1));
  // Nunca se va a dar un número de argumentos menor a 3, ya que se cubre en otra función
}

/* FUNCION CHECK MAXLEVEL */

// Test para comprobar una entrada válida para la operación MAXLEVEL
TEST(check_maxlevel, valid_value) {
  std::vector<std::string> const argumentos = {"input.ppm", "output.ppm", "maxlevel", "4"};
  std::size_t const tamano_argumentos = argumentos.size();
  EXPECT_EQ(0, check_maxlevel(static_cast<int>(tamano_argumentos), argumentos));
}

// Test para comprobar una entrada inválida para la operación MAXLEVEL
TEST(check_maxlevel, invalid_value) {
  // Número de argumentos inválido
  std::vector<std::string> const argumentos1 = {"input.ppm", "output.ppm", "maxlevel"};
  std::size_t const tamano_argumentos1 = argumentos1.size();
  EXPECT_EQ(-1, check_maxlevel(static_cast<int>(tamano_argumentos1), argumentos1));
  // Valor "maxlevel" fuera de rango ( < 0)
  std::vector<std::string> const argumentos2 = {"input.ppm", "output.ppm", "maxlevel", "-1"};
  std::size_t const tamano_argumentos2 = argumentos2.size();
  EXPECT_EQ(-1, check_maxlevel(static_cast<int>(tamano_argumentos2), argumentos2));
  // Valor "maxlevel" fuera de rango ( > 65536)
  std::vector<std::string> const argumentos3 = {"input.ppm", "output.ppm", "maxlevel", "65537"};
  std::size_t const tamano_argumentos3 = argumentos3.size();
  EXPECT_EQ(-1, check_maxlevel(static_cast<int>(tamano_argumentos3), argumentos3));
}

/* FUNCION CHECK_CUTFREQ */

// Test para comprobar una entrada válida para la operación CUTFREQ
TEST(check_cutfreq, valid_value) {
  std::vector<std::string> const argumentos = {"input.ppm", "output.ppm", "cutfreq", "2"};
  std::size_t const tamano_argumentos = argumentos.size();
  EXPECT_EQ(0, check_cutfreq(static_cast<int>(tamano_argumentos), argumentos));
}

// Test para comprobar una entrada inválida para la operación CUTFREQ
TEST(check_cutfreq, invalid_value) {
  // Número de argumentos inválido
  std::vector<std::string> const argumentos1 = {"input.ppm", "output.ppm", "cutfreq"};
  std::size_t const tamano_argumentos1 = argumentos1.size();
  EXPECT_EQ(-1, check_cutfreq(static_cast<int>(tamano_argumentos1), argumentos1));
  // Valor "cutfreq" fuera de rango ( < 0)
  std::vector<std::string> const argumentos2 = {"input.ppm", "output.ppm", "cutfreq", "-1"};
  std::size_t const tamano_argumentos2 = argumentos2.size();
  EXPECT_EQ(-1, check_cutfreq(static_cast<int>(tamano_argumentos2), argumentos2));
}

/* FUNCION CHECK RESIZE */

// Test para comprobar una entrada válida para la operación RESIZE
TEST(check_resize, valid_value) {
  std::vector<std::string> const argumentos = {"input.ppm", "output.ppm", "resize", "10", "20"};
  std::size_t const tamano_argumentos = argumentos.size();
  EXPECT_EQ(0, check_resize(static_cast<int>(tamano_argumentos), argumentos));
}

// Test para comprobar una entrada inválida para la operación RESIZE
TEST(check_resize, invalid_value) {
  // Número de argumentos inválido
  std::vector<std::string> const argumentos1 = {"input.ppm", "output.ppm", "resize"};
  std::size_t const tamano_argumentos1 = argumentos1.size();
  EXPECT_EQ(-1, check_resize(static_cast<int>(tamano_argumentos1), argumentos1));
  // Valor "resize width" fuera de rango ( <= 0)
  std::vector<std::string> const argumentos2 = {"input.ppm", "output.ppm", "resize", "0", "100"};
  std::size_t const tamano_argumentos2 = argumentos2.size();
  EXPECT_EQ(-1, check_resize(static_cast<int>(tamano_argumentos2), argumentos2));
  // Valor "resize height" fuera de rango ( <= 0)
  std::vector<std::string> const argumentos3 = {"input.ppm", "output.ppm", "resize", "100", "-5"};
  std::size_t const tamano_argumentos3 = argumentos3.size();
  EXPECT_EQ(-1, check_resize(static_cast<int>(tamano_argumentos3), argumentos3));
}

/* FUNCION CHECK OP */

// Test para comprobar un comando con una operación válida
TEST(check_op, valid_value) {
  std::vector<std::string> const argumentos = {"input.ppm", "output.ppm", "maxlevel", "100"};
  std::size_t const tamano_argumentos = argumentos.size();
  EXPECT_EQ(0, check_op(static_cast<int>(tamano_argumentos), argumentos));
}

// Test para comprobar un comando con una operación inválida
TEST(check_op, invalid_value) {
  std::vector<std::string> const argumentos = {"input.ppm", "output.ppm", "copy", "5"};
  std::size_t const tamano_argumentos = argumentos.size();
  EXPECT_EQ(-1, check_op(static_cast<int>(tamano_argumentos), argumentos));
}

/* FUNCION VALIDAR ARGUMENTOS */

// Test para comprobar un comando correcto
TEST(validar_argumentos, valid_value) {
  std::vector<std::string> const argumentos = {"input.ppm", "output.ppm", "info"};
  std::size_t const tamano_argumentos = argumentos.size();
  EXPECT_EQ(0, validar_argumentos(static_cast<int>(tamano_argumentos), argumentos));
}

// Test para comprobar un comando incorrecto
TEST(validar_argumentos, invalid_value) {
  // Número de argumentos inválido
  std::vector<std::string> const argumentos1 = {"input.ppm", "output.ppm"};
  std::size_t const tamano_argumentos1 = argumentos1.size();
  EXPECT_EQ(-1, validar_argumentos(static_cast<int>(tamano_argumentos1), argumentos1));
  // No hace falta hacer más tests porque ya se han cubierto anteriormente
}
