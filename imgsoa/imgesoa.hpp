#ifndef IMGESOA_H
#define IMGESOA_H

#include "common/info.hpp"
#include "common/binaryio.hpp"

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

template <typename T>
struct PixelData {
    std::vector<T> r;
    std::vector<T> g;
    std::vector<T> b;
};

template <typename T>
PixelData<T> save_pixels(std::ifstream & archivo, Imagen const & foto);

template <typename T>
void crear_imagen(Imagen const & foto, struct PixelData<T> const & pixeles, std::string const & nombre);

template <typename T>
void crear_imagen(Imagen const & foto, struct PixelData<T> const & pixeles,
                  std::string const & nombre);

/* FUNCIÓN MAXLEVEL */

void escalar_pixel_16_8(Imagen const & foto,int new_max_level, PixelData<uint16_t> const & pixeles_origen,
  PixelData<uint8_t> & pixeles_destino);

void escalar_pixel_8_8(Imagen const & foto,int new_max_level, PixelData<uint8_t> & pixeles_origen);

void escalar_pixel_8_16(Imagen const & foto,int new_max_level, PixelData<uint8_t> const & pixeles_origen,
                        PixelData<uint16_t> & pixeles_destino);
void escalar_pixel_16_16(Imagen const & foto,int new_max_level, PixelData<uint16_t> & pixeles_origen);

int maxlevel(std::ifstream & archivo, int new_max_level,
  std::string const & nombre_salida);

/* FUNCIÓN RESIZE */

template <typename T>
void interpolate(PixelData<T> const & data, size_t idx1, size_t idx2, float t, T & r_out, T & g_out, T & b_out);

template <typename T>
PixelData<T> resize_template(PixelData<T> pixeles_originales, Imagen const & foto,
                             Imagen const & foto2);

int resize(std::ifstream & archivo_i, std::string const & archivo_o, int const new_width, int const new_height);

/* FUNCIÓN CUTFREQ */

// Constantes de desplazamiento de bits
int constexpr mascara = 0xFFF;
int constexpr desplazamiento1 = 32;
int constexpr desplazamiento2 = 16;
int constexpr desplazamiento3 = 8;

// Funciones de conversión de Pixel de 3/6bytes a entero de 32/64bits y viceversa
uint32_t color8_a_clave32(PixelData<uint8_t> const & pixeles, size_t index);
uint64_t color16_a_clave64(PixelData<uint16_t> const & pixeles, size_t index);


// Funciones de creación de vectores de pares <Pixel, frecuencia>
std::vector<std::pair<uint32_t, int>> vector_colores8(PixelData<uint8_t> const & pixeles);
std::vector<std::pair<uint64_t, int>> vector_colores16(PixelData<uint16_t> const & pixeles);

// Función de ordenación del vector de frecuencias
void ordenar_colores32(std::vector<std::pair<uint32_t, int>>& colores);
void ordenar_colores64(std::vector<std::pair<uint64_t, int>>& colores);

// Estructura de sets para almacenar colores frecuentes y colores a eliminar
template <typename T>
struct ColoresDivididos {
    std::unordered_set<T> frecuentes;
    std::unordered_set<T> eliminar;
};

// Funciones para rellenar la estructura anterior en función de un vector de pares <uint32/64_t, frecuencia>
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

// Estructura SOA para almacenar las conversiones de entero a color
template <typename T, typename U>
struct ColoresSOA {
    std::vector<U> claves;      // Array para las claves uint32_t
    std::vector<T> r_values;     // Array para los componentes R
    std::vector<T> g_values;     // Array para los componentes G
    std::vector<T> b_values;     // Array para los componentes B
};

// Funciones para la búsqueda de sustitutos
uint32_t buscar_color_sustituto32(uint32_t const & color_pixel, ColoresSOA <uint8_t, uint32_t> const & colores_frecuentes_cache);
uint64_t buscar_color_sustituto64(uint64_t const & color_pixel, ColoresSOA <uint16_t, uint64_t> const & colores_frecuentes_cache);

// Funciones para cambiar los colores como claves del diccionario de sustitutos
void calcular_colores_sustitutos8(PixelData<uint8_t> & pixeles,
                                  ColoresDivididos<uint32_t> const & colores_divididos);
void calcular_colores_sustitutos16(PixelData<uint16_t> & pixeles,
                                   ColoresDivididos<uint64_t> const & colores_divididos);

// Función Cutfreq
int cutfreq(std::ifstream & input_file, std::string const & output_file, int const n);

/* FUNCIÓN COMPRESS */

/* Estrucura creada para que no de el error: 2 adjacent parameters of
 * similar type are easily swapped by mistake en la funcion escribir indices*/
template <typename T>
struct Pixeles_y_tabla {PixelData<T> pixeles;
                        PixelData<T> tabla_colores;};

template <typename T>
std::pair<PixelData<T>, int> tabla_colores(int size, PixelData<T> const &pixeles);

// Funcion para escribir los pixeles como indice de la tabla de color
// Para el template: T es en funcion de el valor maximo de intensidad
// y U el tipo de dato para escribir el indice
template <typename T, typename U>
void escribir_indices(std::ofstream & archivoSalida, Pixeles_y_tabla<T> &pixelesYTabla) {
  PixelData<T> const & pixeles       = pixelesYTabla.pixeles;
  PixelData<T> const & tabla_colores = pixelesYTabla.tabla_colores;
  U n                                = 0;
  // Escribe todos los pixeles de la imagen como indices, n es el indice en la tabla de color
  for (size_t i = 0; i < pixeles.r.size(); i++) {
    n = 0;
    for (size_t j = 0; j < tabla_colores.r.size(); j++) {
      if (pixeles.r[i] == tabla_colores.r[j] && pixeles.g[i] == tabla_colores.g[j] &&
          pixeles.b[i] == tabla_colores.b[j]) {
        write_binary(archivoSalida, n);
        break;
      }
      n++;
    }
  }
}

template <typename T>
void compress_template(int size, std::ofstream & archivoSalida, PixelData<T> &pixeles);

int compress(std::ifstream & archivo_i, std::string const & archivo_o);

#endif
