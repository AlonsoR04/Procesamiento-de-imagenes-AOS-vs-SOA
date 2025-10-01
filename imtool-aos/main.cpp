#include "../common/progars.hpp"
#include "../common/info.hpp"
#include "../imgaos/imgeaos.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
  const std::vector<std::string> args(argv + 1, argv + argc); // Almacenamos argumentos en un vector

  if (validar_argumentos(argc - 1, args) == -1) { // Comprobamos si los argumentos de entrada son válidos
    return -1;
  }

  std::ifstream archivoEntrada(args[0], std::ios::binary); // Abrimos el archivo

  if (!archivoEntrada.is_open()){ // Comprobamos si se abre el archivo
    std::cerr << "No se pudo abrir el archivo.";
    return -1;
  }

  // Dependiendo de la operacion ejecutamos la operacion seleccionada
  if (args[2] == "info") {
    info(archivoEntrada);
  }
  if (args[2] == "maxlevel") {
    maxlevel(archivoEntrada, std::stoi(args[3]), args[1]);
  }
  if (args[2] == "cutfreq") {
    cutfreq(archivoEntrada, args[1], std::stoi(args[3]));
  }
  if (args[2] == "resize") {
    resize(archivoEntrada,args[1],std::stoi(args[3]),std::stoi(args[4]));
  }
  if (args[2] == "compress") {
    compress(archivoEntrada, args[1]);
  }
  return 0;
}