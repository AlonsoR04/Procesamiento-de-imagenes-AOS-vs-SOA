#include "progars.hpp"

#include "info.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int convertir_entero(std::string const & string) {
  /* Funcion que a partir de una cadena de caracteres lo convierte a entero */
  try {
    // Intentamos convertir la cadena a entero y si podemos devolvemos el entero
    int const num = std::stoi(string);
    return num;
  } catch (std::invalid_argument const &) {
    // Excepcion en caso de que la cadena no represente un entero y por tanto no se pueda convertir
    std::cerr << "Error (convertir_entero): Argumento inválido\n";
    return -1;
  } catch (std::out_of_range const &) {
    // Excepcion en caso de que el entero que representa la cadena sea muy grande
    std::cerr << "Error (convertir_entero): Valor fuera de rango\n";
    return -1;
  }
}

int numero_argumentos_erroneo(int const n_param) {
  /* Funcion que comprueba el numero de argumentos valido */
  if (n_param < MIN_NUM_ARGUMENTS || n_param > MAX_NUM_ARGUMENTS) {
    // Excepcion en caso de que no pertenezca al rango [3,5]
    std::cerr << "Error (numero_argumentos_erroneo): Número de argumentos introducidos erróneo:\t"
              << n_param << "\n";
    return -1;
  }
  return 0;
}

int check_info(int const n_param, std::vector<std::string> const & args) {
  /* Funcion que comprueba el formato valido para info*/
  int const n_param_extra = n_param - 3;
  if (n_param != 3) {
    std::cerr << "Error (check_info): Número de argumentos extra inválido para:\t" << args[2]
              << "\t" << n_param_extra << "\n";
    return -1;
  }
  return 0;
}

int check_maxlevel(int const n_param, std::vector<std::string> const & args) {
  /* Funcion que comprueba el formato valido para maxlevel*/
  int const n_param_extra = n_param - 3;
  if (n_param != 4) {
    std::cerr << "Error (check_maxlevel): Número de argumentos extra inválido:\t" << n_param_extra
              << "\n";
    return -1;
  }
  int const maxlevel = convertir_entero(args[3]);
  if (maxlevel < 0 || maxlevel > MAX_LEVEL_LIMIT) {
    std::cerr << "Error (check_maxlevel): Valor fuera de rango para:\t" << args[2] << "\t"
              << maxlevel << "\n";
    return -1;
  }
  return 0;
}

int check_cutfreq(int const n_param, std::vector<std::string> const & args) {
  /* Funcion que comprueba el formato valido para cutfreq */
  int const n_param_extra = n_param - 3;
  if (n_param != 4) {
    std::cerr << "Error (check_cutfreq): Número de argumentos extra inválido:\t" << n_param_extra
              << "\n";
    return -1;
  }
  int const cutfreq_value = convertir_entero(args[3]);
  if (cutfreq_value < 0) {
    std::cerr << "Error (check_cutfreq): Valor fuera de rango para:\t" << args[2] << "\t"
              << cutfreq_value << "\n";
    return -1;
  }
  return 0;
}

int check_resize(int const n_param, std::vector<std::string> const & args) {
  /* Funcion que comprueba el formato valido para resize */
  int const n_param_extra = n_param - 3;
  if (n_param != MAX_NUM_ARGUMENTS) {
    std::cerr << "Error (check_resize): Número de argumentos extra inválido:\t" << n_param_extra
              << "\n";
    return -1;
  }
  int const new_width  = convertir_entero(args[3]);
  int const new_height = convertir_entero(args[4]);
  if (new_width <= 0) {
    std::cerr << "Error (check_resize): Valor ancho fuera de rango para:\t" << args[2] << "\t"
              << new_width << "\n";
    return -1;
  }
  if (new_height <= 0) {
    std::cerr << "Error (check_resize): Valor alto fuera de rango para:\t" << args[2] << "\t"
              << new_height << "\n";
    return -1;
  }
  return 0;
}

int check_compress(int const n_param, std::vector<std::string> const & args) {
  /* Funcion que comprueba el formato valido para compress */
  if (n_param != 3) {
    std::cerr << "Error: Invalid extra arguments for compress:\t" << args[4] << "\n";
    return -1;
  }
  return 0;
}

int check_op(int const n_param, std::vector<std::string> const & args) {
  /* Funcion que comprueba el formato valido para la operacion */
  if (args[2] == "info") { return check_info(n_param, args); }
  if (args[2] == "maxlevel") { return check_maxlevel(n_param, args); }
  if (args[2] == "cutfreq") { return check_cutfreq(n_param, args); }
  if (args[2] == "resize") { return check_resize(n_param, args); }
  if (args[2] == "compress") { return check_compress(n_param, args); }
  std::cerr << "Error (check_op): Operación inválida:\t" << args[2] << "\n";
  return -1;
}

int validar_argumentos(int const argc, std::vector<std::string> const & args) {
  /* Función principal que valida los parámetros */
  // Comprobamos que contiene el número de argumentos correcto (intervalo [3,5]).
  if (numero_argumentos_erroneo(argc) == -1) { return -1; }
  // Comprobamos que el segundo argumento sea una op valida y a su vez comprobamos si los parametros
  // de la operacion son validos
  if (check_op(argc, args) == -1) { return -1; }
  return 0;
}