#include "info.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

// Cambiar a como estaba antes
Imagen save_info(std::ifstream & file_image) {
  Imagen foto;
  // Comprobar si el archivo se abrió correctamente
  if (!file_image.is_open()) { throw std::runtime_error("Error: no se pudo abrir el archivo."); }

  // Leer el formato y comprobar que este bien
  file_image >> foto.formato;
  if (foto.formato != "P6") {
    throw std::runtime_error("Formato de archivo no válido. Se esperaba 'P6'.");
  }

  // Leer dimensiones y comprobar que no sean menores a 1
  file_image >> foto.anchura >> foto.altura;
  if (foto.anchura <= 0 || foto.altura <= 0) {
    throw std::runtime_error("Dimensiones de imagen no válidas.");
  }

  // Leer el máximo nivel de intensidad y comprobar que este en el rango valido
  file_image >> foto.maxIntensidad;
  if (foto.maxIntensidad <= 0 || foto.maxIntensidad > MAX_LEVEL_LIMIT) {
    throw std::runtime_error("Valor máximo de intensidad no válido.");
  }

  // Ignorar el salto de línea que sigue al máximo nivel
  file_image.ignore(1);
  return foto;  // Devolver la estructura
}

int info(std::ifstream & fileImage) {
  /* Funcion que extrae los datos de un archivo .ppm y los imprime por pantalla */
  // Extraemos la informacion cabecera de la imagen
  Imagen const foto = save_info(fileImage);
  // Imprimimos por pantalla los resultados
  std::cout << "Image size: " << foto.anchura << "\nImage height: " << foto.altura
            << "\nMax level: " << foto.maxIntensidad;
  return 0;
}
