
#include "imgesoa.hpp"

#include "common/binaryio.hpp"
#include "common/info.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename T>
PixelData<T> save_pixels(std::ifstream & archivo, Imagen const & foto) {
  /* Función que recibe un archivo .ppm y devuelve un structure of arrays (SOA) con
  la información de los píxeles */
  // Calculamos el número total de píxeles

  if (!archivo.is_open()) { throw std::runtime_error("El archivo no está abierto."); }
  std::size_t const n =
      static_cast<std::size_t>(foto.altura) * static_cast<std::size_t>(foto.anchura);

  // Creamos la estructura de los pixeles y añadimos a la estrucura
  PixelData<T> pixeles;
  pixeles.r.reserve(n);
  pixeles.g.reserve(n);
  pixeles.b.reserve(n);
  for (std::size_t i = 0; i < n; i++) {
    // Leemos los valores de los píxeles en un bucle
    pixeles.r.push_back(read_binary<T>(archivo));
    pixeles.g.push_back(read_binary<T>(archivo));
    pixeles.b.push_back(read_binary<T>(archivo));
  }
  // Devolvemos los datos de los píxeles
  return pixeles;
}

template <typename T>
void crear_imagen(Imagen const & foto, struct PixelData<T> const & pixeles,
                  std::string const & nombre) {
  /* Función que crea un archivo .ppm con la implementación SOA */
  // Comprobamos la intensidad de la imagen
  std::ofstream archivoSalida(nombre, std::ios::binary);
  if (foto.maxIntensidad < 0 || foto.maxIntensidad > MAX_LEVEL_LIMIT) {
    std::cerr << "Valor de intensidad máxima inválido en la creación de imagen: "
              << foto.maxIntensidad;
  }
  // Comprobamos que el archivo este abierto
  if (!archivoSalida.is_open()) {
    throw std::runtime_error("Error al abrir el archivo para escritura: " + nombre);
  }
  // Escribimos la cabecera en el archivo de salida
  archivoSalida << foto.formato << "\n"
                << std::to_string(foto.anchura) << " " << std::to_string(foto.altura) << "\n"
                << std::to_string(foto.maxIntensidad) << "\n";
  // Iteramos en la estructura de vectores de los píxeles para escribir en el archivo

  int const num_pixels = foto.altura * foto.anchura;

  for (std::size_t i = 0; i < static_cast<std::size_t>(num_pixels); ++i) {
    write_binary(archivoSalida, pixeles.r[i]);
    write_binary(archivoSalida, pixeles.g[i]);
    write_binary(archivoSalida, pixeles.b[i]);
  }

  archivoSalida.close();
}

void escalar_pixel_16_8(Imagen const & foto, int const new_max_level,
                        PixelData<uint16_t> const & pixeles_origen,
                        PixelData<uint8_t> & pixeles_destino) {
  // Calculamos el factor para reescalar el color de los pixeles
  double const factor = static_cast<double>(new_max_level) / foto.maxIntensidad;
  // Escalamos el tamaño del vector de origen ya que cambia de dato
  pixeles_destino.r.resize(pixeles_origen.r.size());
  pixeles_destino.g.resize(pixeles_origen.g.size());
  pixeles_destino.b.resize(pixeles_origen.b.size());

  // Calculamos los pixeles
  int const cantidad_pixeles = foto.altura * foto.anchura;

  if (static_cast<size_t>(cantidad_pixeles) != pixeles_origen.r.size()) {
    throw std::runtime_error("El numero de pixel es incorrecto");
  }

  // Recorremos cada vector de componentes para reescalarlos teniendo en cuenta los limites.
  for (size_t i = 0; i < static_cast<size_t>(cantidad_pixeles); ++i) {
    pixeles_destino.r[i] = std::clamp(static_cast<uint8_t>(pixeles_origen.r[i] * factor),
                                      static_cast<uint8_t>(0), static_cast<uint8_t>(new_max_level));
    pixeles_destino.g[i] = std::clamp(static_cast<uint8_t>(pixeles_origen.g[i] * factor),
                                      static_cast<uint8_t>(0), static_cast<uint8_t>(new_max_level));
    pixeles_destino.b[i] = std::clamp(static_cast<uint8_t>(pixeles_origen.b[i] * factor),
                                      static_cast<uint8_t>(0), static_cast<uint8_t>(new_max_level));
  }
}

void escalar_pixel_8_8(Imagen const & foto, int const new_max_level,
                       PixelData<uint8_t> & pixeles_origen) {
  // Calculamos el factor para reescalar el color de los pixeles
  double const factor = static_cast<double>(new_max_level) / foto.maxIntensidad;
  // Calculamos los pixeles
  int const cantidad_pixeles = foto.altura * foto.anchura;

  if (static_cast<size_t>(cantidad_pixeles) != pixeles_origen.r.size()) {
    throw std::runtime_error("El numero de pixel es incorrecto");
  }

  // Recorremos cada vector de componentes para reescalarlos teniendo en cuenta los limites.
  for (size_t i = 0; i < static_cast<size_t>(cantidad_pixeles); ++i) {
    pixeles_origen.r[i] = std::clamp(static_cast<uint8_t>(pixeles_origen.r[i] * factor),
                                     static_cast<uint8_t>(0), static_cast<uint8_t>(new_max_level));
    pixeles_origen.g[i] = std::clamp(static_cast<uint8_t>(pixeles_origen.g[i] * factor),
                                     static_cast<uint8_t>(0), static_cast<uint8_t>(new_max_level));
    pixeles_origen.b[i] = std::clamp(static_cast<uint8_t>(pixeles_origen.b[i] * factor),
                                     static_cast<uint8_t>(0), static_cast<uint8_t>(new_max_level));
  }
}

void escalar_pixel_8_16(Imagen const & foto, int const new_max_level,
                        PixelData<uint8_t> const & pixeles_origen,
                        PixelData<uint16_t> & pixeles_destino) {
  // Calculamos el factor para reescalar el color de los pixeles
  double const factor = static_cast<double>(new_max_level) / foto.maxIntensidad;
  // Escalamos el tamaño del vector de origen ya que cambia de dato
  pixeles_destino.r.resize(pixeles_origen.r.size());
  pixeles_destino.g.resize(pixeles_origen.g.size());
  pixeles_destino.b.resize(pixeles_origen.b.size());

  // Calculamos los pixeles
  int const cantidad_pixeles = foto.altura * foto.anchura;

  if (static_cast<size_t>(cantidad_pixeles) != pixeles_origen.r.size()) {
    throw std::runtime_error("El numero de pixel es incorrecto");
  }

  // Recorremos cada vector de componentes para reescalarlos teniendo en cuenta los limites.
  for (size_t i = 0; i < static_cast<size_t>(cantidad_pixeles); ++i) {
    pixeles_destino.r[i] =
        std::clamp(static_cast<uint16_t>(pixeles_origen.r[i] * factor), static_cast<uint16_t>(0),
                   static_cast<uint16_t>(new_max_level));
    pixeles_destino.g[i] =
        std::clamp(static_cast<uint16_t>(pixeles_origen.g[i] * factor), static_cast<uint16_t>(0),
                   static_cast<uint16_t>(new_max_level));
    pixeles_destino.b[i] =
        std::clamp(static_cast<uint16_t>(pixeles_origen.b[i] * factor), static_cast<uint16_t>(0),
                   static_cast<uint16_t>(new_max_level));
  }
}

void escalar_pixel_16_16(Imagen const & foto, int const new_max_level,
                         PixelData<uint16_t> & pixeles_origen) {
  // Calculamos el factor para reescalar el color de los pixeles
  double const factor = static_cast<double>(new_max_level) / foto.maxIntensidad;
  // Calculamos los pixeles
  int const cantidad_pixeles = foto.altura * foto.anchura;

  if (static_cast<size_t>(cantidad_pixeles) != pixeles_origen.r.size()) {
    throw std::runtime_error("El numero de pixel es incorrecto");
  }

  // Recorremos cada vector de componentes para reescalarlos teniendo en cuenta los limites.
  for (size_t i = 0; i < static_cast<size_t>(cantidad_pixeles); ++i) {
    pixeles_origen.r[i] =
        std::clamp(static_cast<uint16_t>(pixeles_origen.r[i] * factor), static_cast<uint16_t>(0),
                   static_cast<uint16_t>(new_max_level));
    pixeles_origen.g[i] =
        std::clamp(static_cast<uint16_t>(pixeles_origen.g[i] * factor), static_cast<uint16_t>(0),
                   static_cast<uint16_t>(new_max_level));
    pixeles_origen.b[i] =
        std::clamp(static_cast<uint16_t>(pixeles_origen.b[i] * factor), static_cast<uint16_t>(0),
                   static_cast<uint16_t>(new_max_level));
  }
}

int maxlevel(std::ifstream & archivo, int new_max_level, std::string const & nombre_salida) {
  Imagen const foto = save_info(archivo);
  // Caso en el que la nueva intensidad sea 255 o menor
  if (new_max_level <= MAX_255INTENSITY_LIMIT) {
    // La intensidad de la foto antigua es mayor  que 255
    if (foto.maxIntensidad > MAX_255INTENSITY_LIMIT) {
      PixelData<uint16_t> const pixeles16 = save_pixels<uint16_t>(archivo, foto);
      PixelData<uint8_t> pixeles8;
      escalar_pixel_16_8(foto, new_max_level, pixeles16, pixeles8);
      foto.maxIntensidad = new_max_level;
      crear_imagen(foto, pixeles8, nombre_salida);

    } else if (foto.maxIntensidad <= MAX_255INTENSITY_LIMIT) {
      PixelData<uint8_t> pixeles8 = save_pixels<uint8_t>(archivo, foto);
      escalar_pixel_8_8(foto, new_max_level, pixeles8);
      foto.maxIntensidad = new_max_level;
      crear_imagen(foto, pixeles8, nombre_salida);
      // La intensidad nueva es mayor 255
    }

  } else {
    if (foto.maxIntensidad <= MAX_255INTENSITY_LIMIT) {
      PixelData<uint8_t> const pixeles8 = save_pixels<uint8_t>(archivo, foto);
      PixelData<uint16_t> pixeles16;
      escalar_pixel_8_16(foto, new_max_level, pixeles8, pixeles16);
      foto.maxIntensidad = new_max_level;
      crear_imagen(foto, pixeles16, nombre_salida);
    } else {
      PixelData<uint16_t> pixeles16 = save_pixels<uint16_t>(archivo, foto);
      escalar_pixel_16_16(foto, new_max_level, pixeles16);
      foto.maxIntensidad = new_max_level;
      crear_imagen(foto, pixeles16, nombre_salida);
    }
  }
  return 0;
}

/* #########################################################
FUNCIONES PARA RESIZE
############################################################ */

// Función para la interpolación de colores
template <typename T>
void interpolate(PixelData<T> const & data, size_t idx1, size_t idx2, float t, T & r_out, T & g_out,
                 T & b_out) { // Aplicamos para cada color, la interpolacion con el color del pixel 2
  r_out = static_cast<T>(std::trunc(static_cast<float>(data.r[idx1]) +
                         t * (static_cast<float>(data.r[idx2]) - static_cast<float>(data.r[idx1]))));
  g_out = static_cast<T>(std::trunc(static_cast<float>(data.g[idx1]) +
                         t * (static_cast<float>(data.g[idx2]) - static_cast<float>(data.g[idx1]))));
  b_out = static_cast<T>(std::trunc(static_cast<float>(data.b[idx1]) +
                         t * (static_cast<float>(data.b[idx2]) - static_cast<float>(data.b[idx1]))));
}

// Funcion compatible para uint_8 y uint_16
template <typename T>
PixelData<T> resize_template(PixelData<T> pixeles_originales, Imagen const & foto,
                             Imagen const & foto2) {
  PixelData<T> resultPixels; // Definimos la estructura de arrays
  resultPixels.r.resize(static_cast<size_t>(foto2.anchura) * static_cast<size_t>(foto2.altura)); // Aumentamos el tamaño del vector para cada componente
  resultPixels.g.resize(static_cast<size_t>(foto2.anchura) * static_cast<size_t>(foto2.altura));
  resultPixels.b.resize(static_cast<size_t>(foto2.anchura) * static_cast<size_t>(foto2.altura));

  for (int i = 0; i < foto2.altura; i++) { // Recorremos cada pixel de la imagen y realizamos las operaciones para el reescalado de tamaño
    float const origY = static_cast<float>(i * (foto.altura-1)) / static_cast<float>(foto2.altura-1);
    int const yl = static_cast<int>(std::floor(origY));
    int const yh = static_cast<int>(std::ceil(origY));
    for (int j = 0; j < foto2.anchura; j++) {
      float const origX = static_cast<float>(j * (foto.anchura-1)) / static_cast<float>(foto2.anchura-1);
      int const xl = static_cast<int>(std::floor(origX));
      int const xh = static_cast<int>(std::ceil(origX));

      size_t const pixel1 = static_cast<size_t>(yl) * static_cast<size_t>(foto.anchura) + static_cast<size_t>(xl);
      size_t const pixel2 = static_cast<size_t>(yl) * static_cast<size_t>(foto.anchura) + static_cast<size_t>(xh);
      size_t const pixel3 = static_cast<size_t>(yh) * static_cast<size_t>(foto.anchura) + static_cast<size_t>(xl);
      size_t const pixel4 = static_cast<size_t>(yh) * static_cast<size_t>(foto.anchura) + static_cast<size_t>(xh);

      T r1 = 0, g1 = 0, b1 = 0, r2 = 0, g2 = 0, b2 = 0;
      float const fh = origX - static_cast<float>(xl);
      interpolate<T>(pixeles_originales, pixel1, pixel2, fh, r1, g1, b1);
      interpolate<T>(pixeles_originales, pixel3, pixel4, fh, r2, g2, b2);

      size_t const idxOut =
          static_cast<size_t>(i) * static_cast<size_t>(foto2.anchura) + static_cast<size_t>(j);
      float const fv = origY - static_cast<float>(yl);
      resultPixels.r[idxOut] = static_cast<T>(std::trunc(
          static_cast<float>(r1) + fv * (static_cast<float>(r2) - static_cast<float>(r1))));
      resultPixels.g[idxOut] = static_cast<T>(std::trunc(
          static_cast<float>(g1) + fv * (static_cast<float>(g2) - static_cast<float>(g1))));
      resultPixels.b[idxOut] = static_cast<T>(std::trunc(
          static_cast<float>(b1) + fv * (static_cast<float>(b2) - static_cast<float>(b1))));
    }
  }
  return resultPixels;
}

// Función principal que declara los tipos de dato dependiendo de si la intensidad es <255 o >255
int resize(std::ifstream & archivo_i, std::string const & archivo_o, int const new_width,
           int const new_height) {
  Imagen const foto = save_info(archivo_i);

  Imagen const foto2 = {.formato       = foto.formato,
                        .altura        = new_height,
                        .anchura       = new_width,
                        .maxIntensidad = foto.maxIntensidad};

  if (foto.maxIntensidad <= MAX_255INTENSITY_LIMIT) {
    PixelData<uint8_t> const pixeles       = save_pixels<uint8_t>(archivo_i, foto); // Leemos la imagen
    PixelData<uint8_t> const resultPixeles = resize_template(pixeles, foto, foto2); // Ejecutamos la propia funcion resize
    crear_imagen(foto2, resultPixeles, archivo_o); // Creamos la imagen escalada

  } else {
    PixelData<uint16_t> const pixeles       = save_pixels<uint16_t>(archivo_i, foto); // Leemos la imagen
    PixelData<uint16_t> const resultPixeles = resize_template(pixeles, foto, foto2); // Ejecutamos la propia funcion resize
    crear_imagen(foto2, resultPixeles, archivo_o); // Creamos la imagen escalada
  }
  return 0;
}

/* #########################################################################
FUNCIÓN CUTFREQ
############################################################################ */

// Conversión de colores a enteros

uint32_t color8_a_clave32(PixelData<uint8_t> const & pixels, size_t index) {
  // Convierte un pixel de 3bytes en entero de 32 bits
  return (static_cast<uint32_t>(pixels.r[index]) << desplazamiento2 |
          static_cast<uint32_t>(pixels.g[index]) << desplazamiento3 |
          static_cast<uint32_t>(pixels.b[index]));
}

uint64_t color16_a_clave64(PixelData<uint16_t> const & pixels, size_t index) {
  // Convierte un pixel de 6bytes en entero de 64 bits
  return (static_cast<uint64_t>(pixels.r[index]) << desplazamiento1 |
          static_cast<uint64_t>(pixels.g[index]) << desplazamiento2 |
          static_cast<uint64_t>(pixels.b[index]));
}

// Función de ordenación del vector de frecuencias

void ordenar_colores32(std::vector<std::pair<uint32_t, int>>& colores) {
  std::sort(colores.begin(), colores.end(), [](auto &left, auto &right) {
    if (left.second != right.second) {
      return left.second > right.second;
    } else {
      // A igualdad de frecuencias, almacenamos las componentes
      auto const r1 = static_cast<uint8_t>((left.first >> desplazamiento2) & mascara);
      auto const g1 = static_cast<uint8_t>((left.first >> desplazamiento3) & mascara);
      auto const b1 = static_cast<uint8_t>(left.first & mascara);
      auto const r2 = static_cast<uint8_t>((right.first >> desplazamiento2) & mascara);
      auto const g2 = static_cast<uint8_t>((right.first >> desplazamiento3) & mascara);
      auto const b2 = static_cast<uint8_t>(right.first & mascara);
      return (r1 != r2) ? r1 > r2 :
              (g1 != g2) ? g1 > g2 :
              b1 > b2;
    }
  });
}

void ordenar_colores64(std::vector<std::pair<uint64_t, int>>& colores) {
  std::sort(colores.begin(), colores.end(), [](auto &left, auto &right) {
    if (left.second != right.second) {
      return left.second > right.second;
    } else {
      // A igualdad de frecuencias, comparamos las componentes
      auto const r1 = static_cast<uint16_t>((left.first >> desplazamiento1) & mascara);
      auto const g1 = static_cast<uint16_t>((left.first >> desplazamiento2) & mascara);
      auto const b1 = static_cast<uint16_t>(left.first & mascara);
      auto const r2 = static_cast<uint16_t>((right.first >> desplazamiento1) & mascara);
      auto const g2 = static_cast<uint16_t>((right.first >> desplazamiento2) & mascara);
      auto const b2 = static_cast<uint16_t>(right.first & mascara);
      return (r1 != r2) ? r1 > r2 :
              (g1 != g2) ? g1 > g2 :
              b1 > b2;
    }
  });
}

// Vectores de colores

std::vector<std::pair<uint32_t, int>> vector_colores8(PixelData<uint8_t> const & pixeles) {
  // Almacenamos en un diccionario los colores con sus frecuencias
  std::unordered_map<uint32_t, int> diccionario;
  for (size_t i = 0; i < pixeles.r.size(); i++) {
    uint32_t const color = color8_a_clave32(pixeles, i);
    diccionario[color]++;
  }
  // Creamos un vector de pares y lo ordenamos
  std::vector<std::pair<uint32_t, int>> colores(diccionario.begin(), diccionario.end());
  ordenar_colores32(colores);
  return colores;
}

std::vector<std::pair<uint64_t, int>> vector_colores16(PixelData<uint16_t> const & pixeles) {
  // Almacenamos en un diccionario los colores con sus frecuencias
  std::unordered_map<uint64_t, int> diccionario;
  for (size_t i = 0; i < pixeles.r.size(); i++) {
    uint64_t const color = color16_a_clave64(pixeles, i);
    diccionario[color]++;
  }
  // Creamos un vector de pares y lo ordenamos
  std::vector<std::pair<uint64_t, int>> colores(diccionario.begin(), diccionario.end());
  ordenar_colores64(colores);
  return colores;
}



// Busqueda de colores sustitutos

uint32_t buscar_color_sustituto32(uint32_t const & color_pixel, ColoresSOA<uint8_t, uint32_t> const & colores_frecuentes_cache) {
  // Extraemos las componentes rgb directamente de la clave original
  auto color_original_r = static_cast<uint8_t>((color_pixel >> desplazamiento2) & mascara);
  auto color_original_g = static_cast<uint8_t>((color_pixel >> desplazamiento3) & mascara);
  auto color_original_b = static_cast<uint8_t>(color_pixel & mascara);
  // Variables de comparación
  uint32_t color_mas_cercano = color_pixel;
  int distancia_minima = std::numeric_limits<int>::max();
  // Iteramos sobre los colores frecuentes
  for (size_t i = 0; i < colores_frecuentes_cache.claves.size(); ++i) {
    // Extraemos las componentes rgb directamente
    int const dr = color_original_r - colores_frecuentes_cache.r_values[i];
    int const dg = color_original_g - colores_frecuentes_cache.g_values[i];
    int const db = color_original_b - colores_frecuentes_cache.b_values[i];
    // Calculamos distancia euclidea
    int const distancia_calculada = dr * dr + dg * dg + db * db;
    // Si se encuentra un mejor valor actualizamos al color más cercano
    if (distancia_minima > distancia_calculada) {
      distancia_minima = distancia_calculada;
      color_mas_cercano = colores_frecuentes_cache.claves[i];
    }
  }
  return color_mas_cercano;
}

uint64_t buscar_color_sustituto64(uint64_t const & color_pixel, ColoresSOA<uint16_t, uint64_t> const & colores_frecuentes_cache) {
  // Extraemos las componentes rgb directamente de la clave orignal
  auto color_original_r = static_cast<uint16_t>((color_pixel >> desplazamiento2) & mascara);
  auto color_original_g = static_cast<uint16_t>((color_pixel >> desplazamiento3) & mascara);
  auto color_original_b = static_cast<uint16_t>(color_pixel & mascara);
  // Variables de comparación
  uint64_t color_mas_cercano = color_pixel;
  int distancia_minima = std::numeric_limits<int>::max();
  // Iteramos sobre los colores frecuentes
  for (size_t i = 0; i < colores_frecuentes_cache.claves.size(); ++i) {
    // Extraemos las componentes rgb directamente
    int const dr = color_original_r - colores_frecuentes_cache.r_values[i];
    int const dg = color_original_g - colores_frecuentes_cache.g_values[i];
    int const db = color_original_b - colores_frecuentes_cache.b_values[i];
    // Calculamos distancia euclidea
    int const distancia_calculada = dr * dr + dg * dg + db * db;
    // Si se encuentra un mejor valor actualizamos al color más cercano
    if (distancia_minima > distancia_calculada) {
      distancia_minima = distancia_calculada;
      color_mas_cercano = colores_frecuentes_cache.claves[i];
    }
  }
  return color_mas_cercano;
}

// Calcular colores sustitutos

void calcular_colores_sustitutos8(PixelData<uint8_t> & pixeles,
                                  ColoresDivididos<uint32_t> const & colores_divididos) {
  // Creamos una "cache" de sustituciones y colores frecuentes usando ColoresSOA
  ColoresSOA<uint8_t, uint32_t> cache;  // Para almacenar colores de sustitución ya calculados
  ColoresSOA<uint8_t, uint32_t> colores_frecuentes_cache;  // Para almacenar los colores frecuentes
  for (const auto& color_frecuente : colores_divididos.frecuentes) { // Llenamos colores_frecuentes_cache con claves y valores RGB de colores frecuentes
    auto color_r = static_cast<uint8_t>((color_frecuente >> desplazamiento2) & mascara);
    auto color_g = static_cast<uint8_t>((color_frecuente >> desplazamiento3) & mascara);
    auto color_b = static_cast<uint8_t>(color_frecuente & mascara);
    colores_frecuentes_cache.claves.push_back(color_frecuente);
    colores_frecuentes_cache.r_values.push_back(color_r);
    colores_frecuentes_cache.g_values.push_back(color_g);
    colores_frecuentes_cache.b_values.push_back(color_b);
  }
  for (size_t i = 0; i < pixeles.r.size(); i++) {
    uint32_t const clave = color8_a_clave32(pixeles, i); // Recorremos cada píxel en la imagen y procesamos los colores que deben ser sustituidos
    if (colores_divididos.eliminar.find(clave) != colores_divididos.eliminar.end()) { // Si el color debe ser eliminado, buscamos un color de sustitución
      auto it = std::find(cache.claves.begin(), cache.claves.end(), clave);
      if (it == cache.claves.end()) { // Si no existe en el cache, calcular el sustituto y almacenarlo en cache
        uint32_t const sustituto_clave = buscar_color_sustituto32(clave, colores_frecuentes_cache);
        // Extraemos las componentes rgb directamente
        auto color_sustituyente_r = static_cast<uint8_t>((sustituto_clave >> desplazamiento2) & mascara);
        auto color_sustituyente_g = static_cast<uint8_t>((sustituto_clave >> desplazamiento3) & mascara);
        auto color_sustituyente_b = static_cast<uint8_t>(sustituto_clave & mascara);
        cache.claves.push_back(clave); // Almacenamos en cache
        cache.r_values.push_back(color_sustituyente_r);
        cache.g_values.push_back(color_sustituyente_g);
        cache.b_values.push_back(color_sustituyente_b);
        pixeles.r[i] = color_sustituyente_r; // Usamos el color de sustitución recién calculado
        pixeles.g[i] = color_sustituyente_g;
        pixeles.b[i] = color_sustituyente_b;
      } else { // Si ya está en cache, usamos el color de sustitución almacenado
        auto idx = static_cast<size_t>(std::distance(cache.claves.begin(), it));
        pixeles.r[i] = cache.r_values[idx];
        pixeles.g[i] = cache.g_values[idx];
        pixeles.b[i] = cache.b_values[idx];
      }
    }
  }
}

void calcular_colores_sustitutos16(PixelData<uint16_t> & pixeles,
                                  ColoresDivididos<uint64_t> const & colores_divididos) {
  // Creamos una "cache" de sustituciones y colores frecuentes usando ColoresSOA como SOA
  ColoresSOA<uint16_t, uint64_t> cache;  // Para almacenar colores de sustitución ya calculados
  ColoresSOA<uint16_t, uint64_t> colores_frecuentes_cache;  // Para almacenar los colores frecuentes
  for (const auto& color_frecuente : colores_divididos.frecuentes) { // Llenamos colores_frecuentes_cache con claves y valores RGB de colores frecuentes
    auto color_r = static_cast<uint16_t>((color_frecuente >> desplazamiento1) & mascara);
    auto color_g = static_cast<uint16_t>((color_frecuente >> desplazamiento2) & mascara);
    auto color_b = static_cast<uint16_t>(color_frecuente & mascara);
    colores_frecuentes_cache.claves.push_back(color_frecuente);
    colores_frecuentes_cache.r_values.push_back(color_r);
    colores_frecuentes_cache.g_values.push_back(color_g);
    colores_frecuentes_cache.b_values.push_back(color_b);
  }
  for (size_t i = 0; i < pixeles.r.size(); i++) { // Recorremos cada píxel en la imagen y procesar los colores que deben ser sustituidos
    uint64_t const clave = color16_a_clave64(pixeles, i);
    if (colores_divididos.eliminar.find(clave) != colores_divididos.eliminar.end()) { // Si el color debe ser eliminado, buscamos un color de sustitución
      auto it = std::find(cache.claves.begin(), cache.claves.end(), clave);
      if (it == cache.claves.end()) { // Si no existe en el cache, calcular el sustituto y almacenarlo en cache
        uint64_t const sustituto_clave = buscar_color_sustituto64(clave, colores_frecuentes_cache);
        // Extraemos las componentes rgb directamente
        auto color_sustituyente_r = static_cast<uint16_t>((sustituto_clave >> desplazamiento1) & mascara);
        auto color_sustituyente_g = static_cast<uint16_t>((sustituto_clave >> desplazamiento2) & mascara);
        auto color_sustituyente_b = static_cast<uint16_t>(sustituto_clave & mascara);
        cache.claves.push_back(clave); // Almacenamos en cache
        cache.r_values.push_back(color_sustituyente_r);
        cache.g_values.push_back(color_sustituyente_g);
        cache.b_values.push_back(color_sustituyente_b);
        pixeles.r[i] = color_sustituyente_r; // Usamos el color de sustitución recién calculado
        pixeles.g[i] = color_sustituyente_g;
        pixeles.b[i] = color_sustituyente_b;
      } else { // Si ya está en cache, usar el color de sustitución almacenado
        auto idx = static_cast<size_t>(std::distance(cache.claves.begin(), it));
        pixeles.r[i] = cache.r_values[idx];
        pixeles.g[i] = cache.g_values[idx];
        pixeles.b[i] = cache.b_values[idx];
      }
    }
  }
}

// Función CUTFREQ

int cutfreq(std::ifstream & input_file, std::string const & output_file, int const n) {
  // Guardamos la información de la imagen
  Imagen const foto = save_info(input_file);
  // Comprobamos su intensidad
  if (foto.maxIntensidad <= MAX_255INTENSITY_LIMIT) {
    // Guardamos los pixeles y los ordenamos por colores
    PixelData<uint8_t> pixels = save_pixels<uint8_t>(input_file, foto);
    auto colores = vector_colores8(pixels);
    // Dividimos los colores en frecuentes y a eliminar
    ColoresDivididos<uint32_t> colores_divididos;
    dividir_colores(colores, n, colores_divididos);
    // Calculamos los sustitutos y creamos la imagen
    calcular_colores_sustitutos8(pixels, colores_divididos);
    crear_imagen(foto, pixels, output_file);
  } else {
    // Guardamos los pixeles y los ordenamos por colores
    PixelData<uint16_t> pixels = save_pixels<uint16_t>(input_file, foto);
    auto colores = vector_colores16(pixels);
    // Dividimos los colores en frecuentes y a eliminar
    ColoresDivididos<uint64_t> colores_divididos;
    dividir_colores(colores, n, colores_divididos);
    // Calculamos los sustitutos y creamos la imagen
    calcular_colores_sustitutos16(pixels, colores_divididos);
    crear_imagen(foto, pixels, output_file);
  }
  return 0;
}

/* #########################################################################
FUNCIÓN COMPRESS
############################################################################ */

// Crear la tabla de colores
template <typename T>
std::pair<PixelData<T>, int> tabla_colores(int size, PixelData<T> const &pixeles) {
  int n = 0;
  PixelData<T> tabla_colores;
  // Recorre todos los pixeles de la imagen
  for (size_t i = 0; i < static_cast<size_t>(size); i++) {
    bool encontrado = false;
    // Busca en la tabla si ya se ha guardado ese pixel, si lo encuentra no lo guarda
    for (size_t j = 0; j < tabla_colores.r.size(); j++) {
      if (tabla_colores.r[j] == pixeles.r[i] && tabla_colores.g[j] == pixeles.g[i] &&
          tabla_colores.b[j] == pixeles.b[i]) {
        encontrado = true;
        break;
      }
    }
    // Si no esta el pixel en la tabla de colores, se guarda
    if (!encontrado) {
      size_t j = 0;
      // Busca el indice que le toca al pixel para almacenarse ordenadamente
      while (j < tabla_colores.r.size() &&
             (tabla_colores.r[j] < pixeles.r[i] ||
              (tabla_colores.r[j] == pixeles.r[i] && tabla_colores.g[j] < pixeles.g[i]) ||
              (tabla_colores.r[j] == pixeles.r[i] && tabla_colores.g[j] == pixeles.g[i] &&
               tabla_colores.b[j] < pixeles.b[i]))) {
        j++;
      }

      // Inserta en la posición encontrada
      tabla_colores.r.insert(tabla_colores.r.begin() + static_cast<long>(j), pixeles.r[i]);
      tabla_colores.g.insert(tabla_colores.g.begin() + static_cast<long>(j), pixeles.g[i]);
      tabla_colores.b.insert(tabla_colores.b.begin() + static_cast<long>(j), pixeles.b[i]);
      n++;
    }
  }
  return std::make_pair(tabla_colores, n);
}

// Funcion creada para no repetir codigo en la funcion compress para 8 u 16 biTS
template <typename T>
void compress_template(int size, std::ofstream & archivoSalida, PixelData<T> &pixeles) {
  auto result                      = tabla_colores<T>(size, pixeles);
  PixelData<T> const tabla_colores = result.first;
  int const n                      = result.second;

  archivoSalida << n << "\n";
  // Escribe todos los pixeles guardados en la tabla de color
  for (size_t i = 0; i < tabla_colores.r.size(); i++) {
    write_binary(archivoSalida, tabla_colores.r[i]);
    write_binary(archivoSalida, tabla_colores.g[i]);
    write_binary(archivoSalida, tabla_colores.b[i]);
  }
  Pixeles_y_tabla<T> pixelesYTabla{.pixeles = pixeles, .tabla_colores = tabla_colores};
  int constexpr numero8_super_magico  = 8;
  int constexpr numero16_super_magico = 16;
  int constexpr numero32_super_magico = 32;
  // Llamada a la funcion escribir pixeles en funcion del numero de pixeles en la tabla de color
  if (n < pow(2, numero8_super_magico)) {
    escribir_indices<T, uint8_t>(archivoSalida, pixelesYTabla);
  } else if (n < pow(2, numero16_super_magico)) {
    escribir_indices<T, uint16_t>(archivoSalida, pixelesYTabla);
  } else if (n < pow(2, numero32_super_magico)) {
    escribir_indices<T, uint32_t>(archivoSalida, pixelesYTabla);
  } else {
    std::cout << "Error: La imagen contiene demasiados pixeles distintos";
  }
}

int compress(std::ifstream & archivo_i, std::string const & archivo_o) {
  // Guardar los datos de la imagen y abrir el archivo de salida
  Imagen const foto = save_info(archivo_i);
  std::ofstream archivoSalida(archivo_o, std::ios::binary);

  if (!archivoSalida.is_open()) {
    throw std::runtime_error("Error al abrir el archivo para escritura: " + archivo_o);
  }
  // Se escriben en el archivo sus datos
  archivoSalida << "C6 " << foto.anchura << " " << foto.altura << " " << foto.maxIntensidad << " ";
  // Llamada a la anterior función dependiendo de el tipo de datos que se van a usar
  if (foto.maxIntensidad <= MAX_255INTENSITY_LIMIT) {
    PixelData<uint8_t> pixeles = save_pixels<uint8_t>(archivo_i, foto);
    compress_template<uint8_t>(foto.anchura * foto.altura, archivoSalida, pixeles);
  } else {
    PixelData<uint16_t> pixeles = save_pixels<uint16_t>(archivo_i, foto);
    compress_template<uint16_t>(foto.anchura * foto.altura, archivoSalida, pixeles);
  }
  archivoSalida.close();
  return 0;
}
