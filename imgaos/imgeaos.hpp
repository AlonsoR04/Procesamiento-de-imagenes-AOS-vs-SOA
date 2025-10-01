#ifndef IMGEAOS_H
#define IMGEAOS_H

#include "common/info.hpp"
#include "common/binaryio.hpp"

#include <cstdint>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>

template <typename T>
struct Pixel {
  T r, g, b;
};

/*FUNCIONES PARA LEER Y ESCRIBIR*/

std::vector<Pixel<uint8_t>> save_pixels8(std::ifstream & archivo, Imagen const & foto);
std::vector<Pixel<uint16_t>> save_pixels16(std::ifstream & archivo, Imagen const & foto);
template <typename T>
void crear_imagen(Imagen const & foto, std::vector<Pixel<T>> const & pixeles,
                  std::string const & nombre);

/*FUNCION MAXLEVEL*/

int maxlevel(std::ifstream & archivo_i, int new_max_level, std::string const & nombre_salida);

void escalar_pixel_8_to_8(std::vector<Pixel<uint8_t>> & pixeles, int new_max_level,
                          Imagen const & foto);

void escalar_pixel_16_to_8(std::vector<Pixel<uint8_t>> & pixeles,
                           std::vector<Pixel<uint16_t>> const & pixeles_origen, int new_max_level,
                           Imagen const & foto);

void escalar_pixel_8_to_16(std::vector<Pixel<uint16_t>> & pixeles,
                           std::vector<Pixel<uint8_t>> const & pixeles_origen, int new_max_level,
                           Imagen const & foto);

void escalar_pixel_16_to_16(std::vector<Pixel<uint16_t>> & pixeles, int new_max_level,
                            Imagen const & foto);

template <typename T>
void escalar_color_mismos_bytes(std::vector<Pixel<T>> & pixeles, Imagen const & foto,
  int new_max_level,std::string const & nombre);

// Plantilla para escalar píxeles con distinto tamaño de bytes
template <typename T, typename U>
void escalar_color_distintos_bytes(std::vector<Pixel<T>> & pixeles, std::vector<Pixel<U>> const & pixeles_origen,
                                   Imagen const & foto,
                                   int new_max_level, std::string const & nombre);

/* FUNCION RESIZE */

template <typename T>
Pixel<T> interpolate(Pixel<T> const & c1, Pixel<T> const & c2, float t) {
  Pixel<T> result{};
  result.r = static_cast<T>(std::trunc(static_cast<float>(c1.r) +
                                       t * (static_cast<float>(c2.r) - static_cast<float>(c1.r))));
  result.g = static_cast<T>(std::trunc(static_cast<float>(c1.g) +
                                       t * (static_cast<float>(c2.g) - static_cast<float>(c1.g))));
  result.b = static_cast<T>(std::trunc(static_cast<float>(c1.b) +
                                       t * (static_cast<float>(c2.b) - static_cast<float>(c1.b))));

  return result;
}


int resize(std::ifstream & archivo_i, std::string const & archivo_o,
           int  new_width, int  new_heigth);
template <typename T>

std::vector<Pixel<T>> resize_template(std::vector<Pixel<T>> pixeles_originales, Imagen const & foto,
                                      Imagen const & foto2);

/* FUNCION CUTFREQ */

// Constantes de desplazamiento de bits
int constexpr mascara = 0xFFF;
int constexpr desplazamiento1 = 32;
int constexpr desplazamiento2 = 16;
int constexpr desplazamiento3 = 8;

// Funciones de conversion de Pixel de 3/6byes a entero de 32/64bits y viceversa
uint32_t color8_a_clave32(Pixel<uint8_t> const & pixel);
uint64_t color16_a_clave64(Pixel<uint16_t> const & pixel);
Pixel<uint8_t> clave32_a_color8(uint32_t const & clave);
Pixel<uint16_t> clave64_a_color16(uint64_t const & clave);
// Funciones de creación de vectores de pares <Pixel, frecuencia>
std::vector<std::pair<uint32_t, int>> vector_colores8(std::vector<Pixel<uint8_t>> const & pixeles);
std::vector<std::pair<uint64_t, int>> vector_colores16(std::vector<Pixel<uint16_t>> const & pixeles);
// Ordenación por frecuencia y componentes
std::vector<std::pair<uint32_t, int>>ordenar_colores32(std::vector<std::pair<uint32_t, int>>& colores);
std::vector<std::pair<uint64_t, int>>ordenar_colores64(std::vector<std::pair<uint64_t, int>>& colores);
// Estructura de sets para almacenar colores frecuentes y colores a eliminar
template <typename T>
struct ColoresDivididos {
    std::unordered_set<T> frecuentes;
    std::unordered_set<T> eliminar;
};
// Función para dividir colores
template <typename T>
void dividir_colores(std::vector<std::pair<T, int>> const & colores, int const n,
                     ColoresDivididos<T> & colores_divididos) {
  // Separa en colores frecuentes y colores a eliminar de una imagen, y los guarda en un struct
  size_t const colores_frecuentes = colores.size() - static_cast<size_t>(n);
  // Recorremos el vector ordenado de colores
  for (size_t i = 0; i < colores.size(); ++i) {
    // Revisamos la posición y lo almacenamos en un lado u otro
    if (i < colores_frecuentes) {
      colores_divididos.frecuentes.insert(colores[i].first);
    } else {
      colores_divididos.eliminar.insert(colores[i].first);
    }
  }
}
// Funciones para la búsqueda de sustitutos
uint32_t buscar_color_sustituto32(uint32_t const & pixel,
                                  std::vector<std::pair<uint32_t, Pixel<uint8_t>>> const & colores_frecuentes_cache);
uint64_t buscar_color_sustituto64(uint64_t const & pixel,
                                  std::vector<std::pair<uint64_t, Pixel<uint16_t>>> const& colores_frecuentes_cache);
// Funciones de creación de diccionario de sustitutos
void calcular_colores_sustitutos8(std::vector<Pixel<uint8_t>>& pixeles,
                                  ColoresDivididos<uint32_t> const& colores_divididos);

// Funciones para cambiar los colores como claves del diccionario de sustitutos
void calcular_colores_sustitutos16(std::vector<Pixel<uint16_t>>& pixeles, ColoresDivididos<uint64_t> const& colores_divididos);
// Función CUTFREQ
int cutfreq(std::ifstream & input_file, std::string const & output_file, int const n);

/* FUNCION COMPRESS */

template <typename T>
std::pair<std::vector<Pixel<T>>, int> tabla_colores(int size, std::vector<Pixel<T>> const &pixeles);

template <typename T>
struct Pixeles_y_tabla {
    std::vector<Pixel<T>> pixeles;
    std::vector<Pixel<T>> tabla_colores;
};

// Funcion para escribir los pixeles como indice de la tabla de color
// Para el template: T es en funcion de el valor maximo de intensidad
// y U el tipo de dato para escribir el indice
template <typename T, typename U>
void escribir_indices(std::ofstream & archivoSalida, int size, Pixeles_y_tabla<T> &pixelesYTabla) {
  std::vector<Pixel<T>> const & pixeles       = pixelesYTabla.pixeles;
  std::vector<Pixel<T>> const & tabla_colores = pixelesYTabla.tabla_colores;
  U n                                         = 0;
  // Escribe todos los pixeles de la imagen como indices, n es el indice en la tabla de color
  for (size_t i = 0; i < static_cast<size_t>(size); i++) {
    n = 0;
    for (auto const & pixel : tabla_colores) {
      if (pixel.r == pixeles[i].r && pixel.g == pixeles[i].g && pixel.b == pixeles[i].b) {
        write_binary(archivoSalida, n);
        break;
      }
      n++;
    }
  }
}

template <typename T>
bool ordenar_pixeles(Pixel<T> const & p1, Pixel<T> const & p2);

template <typename T>
void compress_template(int size, std::ofstream & archivoSalida, std::vector<Pixel<T>> &pixeles);

int compress(std::ifstream & archivo_i, std::string const & archivo_o);




#endif