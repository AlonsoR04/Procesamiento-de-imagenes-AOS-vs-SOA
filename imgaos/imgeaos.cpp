#include "imgeaos.hpp"
#include "common/binaryio.hpp"
#include "common/info.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

/* #########################################################
FUNCIONES PARA LECTURA Y ESCRITURA DATOS
############################################################ */

// Funcion para leer del archivo 6 bytes y escribirlos en una estructura Pixel
std::vector<Pixel<uint16_t>> save_pixels16(std::ifstream & archivo, Imagen const & foto) {
  int const n = foto.altura * foto.anchura;
  std::vector<Pixel<uint16_t>> pixeles(static_cast<std::vector<Pixel<uint16_t>>::size_type>(n));
  for (auto & pixel : pixeles) {
    pixel.r = read_binary<uint16_t>(archivo);
    pixel.g = read_binary<uint16_t>(archivo);
    pixel.b = read_binary<uint16_t>(archivo);
  }
  return pixeles;
}

// Funcion para leer del archivo 3 bytes y escribirlos en una estructura Pixel
std::vector<Pixel<uint8_t>> save_pixels8(std::ifstream & archivo, Imagen const & foto) {
  int const n = foto.altura * foto.anchura;
  std::vector<Pixel<uint8_t>> pixeles(static_cast<std::vector<Pixel<uint8_t>>::size_type>(n));
  for (auto & pixel : pixeles) {
    pixel.r = read_binary<uint8_t>(archivo);
    pixel.g = read_binary<uint8_t>(archivo);
    pixel.b = read_binary<uint8_t>(archivo);
  }
  return pixeles;
}

// Funcion que con una estructura AOS y el vector de pixeles crea la imagen de salida
template <typename T>
void crear_imagen(Imagen const & foto, std::vector<Pixel<T>> const & pixeles,
                  std::string const & nombre) {
  std::ofstream archivoSalida(nombre, std::ios::binary);

  if (!archivoSalida.is_open()) {
    throw std::runtime_error("Error al abrir el archivo para escritura: " + nombre);
  }

  archivoSalida << foto.formato << "\n"
                << foto.anchura << " " << foto.altura << "\n"
                << foto.maxIntensidad << "\n";

  for (auto const & pixel : pixeles) {
    write_binary(archivoSalida, pixel.r);
    write_binary(archivoSalida, pixel.g);
    write_binary(archivoSalida, pixel.b);
  }
  archivoSalida.close();
}

/* #########################################################
FUNCIONES PARA MAXLEVEL
############################################################ */

// Estas 4 funciones escalar_pixel hacen la operacion matemática necesaria para maxlevel

void escalar_pixel_8_to_8(std::vector<Pixel<uint8_t>> & pixeles, int new_max_level,
                          Imagen const & foto) {
  // Calculamos el factor para reescalar el color de los pixeles
  double const factor = static_cast<double>(new_max_level) / foto.maxIntensidad;

  for (auto & pixel : pixeles) {
    pixel.r = std::clamp(static_cast<uint8_t>(pixel.r * factor), static_cast<uint8_t>(0),
                         static_cast<uint8_t>(new_max_level));
    pixel.g = std::clamp(static_cast<uint8_t>(pixel.g * factor), static_cast<uint8_t>(0),
                         static_cast<uint8_t>(new_max_level));
    pixel.b = std::clamp(static_cast<uint8_t>(pixel.b * factor), static_cast<uint8_t>(0),
                         static_cast<uint8_t>(new_max_level));
  }
}

void escalar_pixel_16_to_8(std::vector<Pixel<uint8_t>> & pixeles,
                           std::vector<Pixel<uint16_t>> const & pixeles_origen, int new_max_level,
                           Imagen const & foto) {
  // Calculamos el factor para reescalar el color de los pixeles
  double const factor = static_cast<double>(new_max_level) / foto.maxIntensidad;
  // Escalamos el tamaño del vector de origen ya que cambia de dato
  pixeles.resize(pixeles_origen.size());
  // Recorremos cada vector de componentes para reescalarlos teniendo en cuenta los limites.
  for (size_t i = 0; i < pixeles_origen.size(); i++) {
    pixeles[i].r = std::clamp(static_cast<uint8_t>(pixeles_origen[i].r * factor),
                              static_cast<uint8_t>(0), static_cast<uint8_t>(new_max_level));
    pixeles[i].g = std::clamp(static_cast<uint8_t>(pixeles_origen[i].g * factor),
                              static_cast<uint8_t>(0), static_cast<uint8_t>(new_max_level));
    pixeles[i].b = std::clamp(static_cast<uint8_t>(pixeles_origen[i].b * factor),
                              static_cast<uint8_t>(0), static_cast<uint8_t>(new_max_level));
  }
}

void escalar_pixel_8_to_16(std::vector<Pixel<uint16_t>> & pixeles,
                           std::vector<Pixel<uint8_t>> const & pixeles_origen, int new_max_level,
                           Imagen const & foto) {
  // Calculamos el factor para reescalar el color de los pixeles
  double const factor = static_cast<double>(new_max_level) / foto.maxIntensidad;
  // Escalamos el tamaño del vector de origen ya que cambia de dato
  pixeles.resize(pixeles_origen.size());
  // Recorremos cada vector de componentes para reescalarlos teniendo en cuenta los limites.
  for (size_t i = 0; i < pixeles_origen.size(); ++i) {
    pixeles[i].r = std::clamp(static_cast<uint16_t>(pixeles_origen[i].r * factor),
                              static_cast<uint16_t>(0), static_cast<uint16_t>(new_max_level));
    pixeles[i].g = std::clamp(static_cast<uint16_t>(pixeles_origen[i].g * factor),
                              static_cast<uint16_t>(0), static_cast<uint16_t>(new_max_level));
    pixeles[i].b = std::clamp(static_cast<uint16_t>(pixeles_origen[i].b * factor),
                              static_cast<uint16_t>(0), static_cast<uint16_t>(new_max_level));
  }
}

void escalar_pixel_16_to_16(std::vector<Pixel<uint16_t>> & pixeles, int new_max_level,
                            Imagen const & foto) {
  // Calculamos el factor para reescalar el color de los pixeles
  double const factor = static_cast<double>(new_max_level) / foto.maxIntensidad;
  // Recorremos cada vector de componentes para reescalarlos teniendo en cuenta los limites.
  for (auto & pixel : pixeles) {
    pixel.r = std::clamp(static_cast<uint16_t>(static_cast<int>(pixel.r * factor)),
                         static_cast<uint16_t>(0), static_cast<uint16_t>(new_max_level));
    pixel.g = std::clamp(static_cast<uint16_t>(static_cast<int>(pixel.g * factor)),
                         static_cast<uint16_t>(0), static_cast<uint16_t>(new_max_level));
    pixel.b = std::clamp(static_cast<uint16_t>(static_cast<int>(pixel.b * factor)),
                         static_cast<uint16_t>(0), static_cast<uint16_t>(new_max_level));
  }
}

int maxlevel(std::ifstream & archivo_i, int new_max_level, std::string const & nombre) {
  Imagen const foto = save_info(archivo_i);

  if (new_max_level <= MAX_255INTENSITY_LIMIT) {  // Nueva intensidad no supera 255
    if (foto.maxIntensidad > MAX_255INTENSITY_LIMIT) { // La intensidad de la foto antigua es mayor  que 255
      std::vector<Pixel<uint16_t>> const pixeles16 = save_pixels16(archivo_i, foto);
      std::vector<Pixel<uint8_t>> pixeles8;
      escalar_color_distintos_bytes(pixeles8, pixeles16, foto, new_max_level, nombre);
    } else {  // Vieja intensidad <= 255
      std::vector<Pixel<uint8_t>> pixeles8 = save_pixels8(archivo_i, foto);
      escalar_color_mismos_bytes(pixeles8, foto, new_max_level, nombre);
    }
  } else {
    if (foto.maxIntensidad <= MAX_255INTENSITY_LIMIT) { // La intensidad nueva es mayor 255
      std::vector<Pixel<uint8_t>> const pixeles8 = save_pixels8(archivo_i, foto);
      std::vector<Pixel<uint16_t>> pixeles16;
      escalar_color_distintos_bytes(pixeles16, pixeles8, foto, new_max_level, nombre);
    } else {  // Vieja intensidad > 255
      std::vector<Pixel<uint16_t>> pixeles16 = save_pixels16(archivo_i, foto);
      escalar_color_mismos_bytes(pixeles16, foto, new_max_level, nombre);
    }
  }
  return 0;
}

// Plantilla para escalar píxeles con el mismo tamaño de bytes
template <typename T>
void escalar_color_mismos_bytes(std::vector<Pixel<T>> & pixeles, Imagen const & foto,
                                int new_max_level, std::string const & nombre) {
  // Comparamos el tipo de dato que entra y actualizamos
  if constexpr (std::is_same_v<T, uint8_t>) {
    // Caso para escalar 8 a 8 bits
    escalar_pixel_8_to_8(pixeles, new_max_level, foto);
  } else if constexpr (std::is_same_v<T, uint16_t>) {
    // Caso para escalar 16 a 16 bits
    escalar_pixel_16_to_16(pixeles, new_max_level, foto);
  }
  // Actualizar la intensidad máxima y crear la imagen
  foto.maxIntensidad = new_max_level;
  crear_imagen(foto, pixeles, nombre);
}

// Plantilla para escalar píxeles con distinto tamaño de bytes
template <typename T, typename U>
void escalar_color_distintos_bytes(std::vector<Pixel<T>> & pixeles,
                                   std::vector<Pixel<U>> const & pixeles_origen,
                                   Imagen const & foto, int new_max_level,
                                   std::string const & nombre) {
  // Comparamos el tipo de dato de destino que entra y actualizamos
  if constexpr (std::is_same_v<T, uint8_t>) {
    // Caso para escalar 16 a 8 bits
    escalar_pixel_16_to_8(pixeles, pixeles_origen, new_max_level, foto);
  } else if constexpr (std::is_same_v<T, uint16_t>) {
    // Caso para escalar 8 a 16 bits
    escalar_pixel_8_to_16(pixeles, pixeles_origen, new_max_level, foto);
  }
  // Actualizar la intensidad máxima y crear la imagen
  foto.maxIntensidad = new_max_level;
  crear_imagen(foto, pixeles, nombre);
}

/* #########################################################
FUNCIONES PARA RESIZE
############################################################ */

// Template creado para no repetir codigo en la funcion resize para operar en 8 o 16 bits
template <typename T>
std::vector<Pixel<T>> resize_template(std::vector<Pixel<T>> pixeles_originales, Imagen const & foto,
                                      Imagen const & foto2) {
  std::vector<Pixel<T>> pixeles(static_cast<size_t>(foto2.anchura * foto2.altura));
  for (int i = 0; i < foto2.altura; i++) { // Se itera por cada linea del la foto
    float const origY = // Se almacena posicion Y del pixel original
        (static_cast<float>(i * (foto.altura - 1)) / static_cast<float>(foto2.anchura - 1));
    int const yl = static_cast<int>(std::floor(origY));
    int const yh = static_cast<int>(std::ceil(origY));

    for (int j = 0; j < foto2.anchura; j++) { // Se itera por cada columna del la foto
      float const origX = // Se almacena posicion X del pixel original
          (static_cast<float>(j * (foto.anchura - 1)) / static_cast<float>(foto2.anchura - 1));
      int const xl = static_cast<int>(std::floor(origX));
      int const xh = static_cast<int>(std::ceil(origX));
      // Se obtienen los 4 pixeles alrededor de las posiciones del pixel original
      Pixel<T> const pixel1 =
          pixeles_originales[static_cast<size_t>(yl) * static_cast<size_t>(foto.anchura) +
                             static_cast<size_t>(xl)];
      Pixel<T> const pixel2 =
          pixeles_originales[static_cast<size_t>(yl) * static_cast<size_t>(foto.anchura) +
                             static_cast<size_t>(xh)];
      Pixel<T> const pixel3 =
          pixeles_originales[static_cast<size_t>(yh) * static_cast<size_t>(foto.anchura) +
                             static_cast<size_t>(xl)];
      Pixel<T> const pixel4 =
          pixeles_originales[static_cast<size_t>(yh) * static_cast<size_t>(foto.anchura) +
                             static_cast<size_t>(xh)];
      // Función interplar definida en el archivo de cabezera
      Pixel const c1 = interpolate<T>(pixel1, pixel2, origX - static_cast<float>(xl));
      Pixel const c2 = interpolate<T>(pixel3, pixel4, origX - static_cast<float>(xl));

      pixeles[static_cast<size_t>(i * foto2.anchura) + static_cast<size_t>(j)] =
          (interpolate<T>(c1, c2, origY - static_cast<float>(yl)));
    }
  }
  return pixeles;
}

int resize(std::ifstream & archivo_i, std::string const & archivo_o, int const new_width,
           int const new_heigth) {
  // Almacena la informacion de la imagen y la nueva imagen a crear
  Imagen const foto  = save_info(archivo_i);
  Imagen const foto2 = {.formato       = foto.formato,
                        .altura        = new_heigth,
                        .anchura       = new_width,
                        .maxIntensidad = foto.maxIntensidad};
  if (foto.maxIntensidad <= MAX_255INTENSITY_LIMIT) {
    std::vector<Pixel<uint8_t>> const pixeles_originales = save_pixels8(archivo_i, foto);
    std::vector<Pixel<uint8_t>> const pixeles =
        resize_template<uint8_t>(pixeles_originales, foto, foto2);
    crear_imagen(foto2, pixeles, archivo_o);
  } else {
    std::vector<Pixel<uint16_t>> const pixeles_originales = save_pixels16(archivo_i, foto);
    std::vector<Pixel<uint16_t>> const pixeles =
        resize_template<uint16_t>(pixeles_originales, foto, foto2);
    crear_imagen(foto2, pixeles, archivo_o);
  }
  return 0;
}

/* ###########################################################
FUNCIONES PARA CUTFREQ
############################################################## */

// Funciones de conversión de Pixel a clave y viceversa

uint32_t color8_a_clave32(Pixel<uint8_t> const & pixel) {
  // Dado un pixel de 3 bytes devuelve un entero de 16 bits rgb
  return (static_cast<uint32_t>(pixel.r) << desplazamiento2) |
         (static_cast<uint32_t>(pixel.g) << desplazamiento3) | static_cast<uint32_t>(pixel.b);
}

uint64_t color16_a_clave64(Pixel<uint16_t> const & pixel) {
  // Dado un pixel de 6 bytes devuelve un entero de 32 bits rgb
  return (static_cast<uint64_t>(pixel.r) << desplazamiento1) |
         (static_cast<uint64_t>(pixel.g) << desplazamiento2) | static_cast<uint64_t>(pixel.b);
}

Pixel<uint8_t> clave32_a_color8(uint32_t const & clave) {
  // Dado un entero de 16 bits rgb devuelve un pixel de 3 bytes
  return Pixel<uint8_t>{.r = static_cast<uint8_t>((clave >> desplazamiento2) & mascara),
                        .g = static_cast<uint8_t>((clave >> desplazamiento3) & mascara),
                        .b = static_cast<uint8_t>((clave) &mascara)};
}

Pixel<uint16_t> clave64_a_color16(uint64_t const & clave) {
  // Dado un entero de 32 bits rgb devuelve un pixel de 6 bytes
  return Pixel<uint16_t>{.r = static_cast<uint16_t>(clave >> desplazamiento1),
                         .g = static_cast<uint16_t>(clave >> desplazamiento2),
                         .b = static_cast<uint16_t>(clave)};
}

// Creación de vectores de colores y frecuencias

std::vector<std::pair<uint32_t, int>> vector_colores8(std::vector<Pixel<uint8_t>> const & pixeles) {
  // Devuelve un vector de enteros de 32 bits rgb con sus correspondientes frecuencias
  std::unordered_map<uint32_t, int> frecuencia;
  // Almacenamos en un diccionario los colores con el número de veces que aparece
  for (auto const & pixel : pixeles) { frecuencia[color8_a_clave32(pixel)]++; }
  return {frecuencia.begin(), frecuencia.end()};
}

std::vector<std::pair<uint64_t, int>>
    vector_colores16(std::vector<Pixel<uint16_t>> const & pixeles) {
  // Devuelve un vector de enteros de 64 bits rgb con sus correspondientes frecuencias
  std::unordered_map<uint64_t, int> frecuencia;
  // Almacenamos en un diccionario los colores con el número de veces que aparece
  for (auto const & pixel : pixeles) { frecuencia[color16_a_clave64(pixel)]++; }
  return {frecuencia.begin(), frecuencia.end()};
}

// Ordenar colores

std::vector<std::pair<uint32_t, int>>
    ordenar_colores32(std::vector<std::pair<uint32_t, int>> & colores) {
  std::ranges::sort(colores.begin(), colores.end(),
                    [](std::pair<uint32_t, int> const & a, std::pair<uint32_t, int> const & b) {
                      if (a.second == b.second) {
                        // A igualdad de frecuencias, comparamos las componentes
                        Pixel<uint8_t> const colorA = clave32_a_color8(a.first);
                        Pixel<uint8_t> const colorB = clave32_a_color8(b.first);
                        return (colorA.b != colorB.b)   ? (colorA.b > colorB.b)
                               : (colorA.g != colorB.g) ? (colorA.g > colorB.g)
                                                        : colorA.r > colorB.r;
                      }
                      return a.second > b.second;
                    });
  return colores;
}

std::vector<std::pair<uint64_t, int>>
    ordenar_colores64(std::vector<std::pair<uint64_t, int>> & colores) {
  std::ranges::sort(colores.begin(), colores.end(),
                    [](std::pair<uint64_t, int> const & a, std::pair<uint64_t, int> const & b) {
                      if (a.second == b.second) {
                        // A igualdad de frecuencias, comparamos las componentes
                        Pixel<uint16_t> const colorA = clave64_a_color16(a.first);
                        Pixel<uint16_t> const colorB = clave64_a_color16(b.first);
                        return (colorA.b != colorB.b)   ? (colorA.b > colorB.b)
                               : (colorA.g != colorB.g) ? (colorA.g > colorB.g)
                                                        : colorA.r > colorB.r;
                      }
                      return a.second > b.second;
                    });
  return colores;
}

// División de colores

// Busqueda de colores sustitutos

uint32_t buscar_color_sustituto32(
    uint32_t const & color_pixel,
    std::vector<std::pair<uint32_t, Pixel<uint8_t>>> const & colores_frecuentes_cache) {
  // Dado un vector de colores frecuentes, busca el color más cercano a un color dado
  Pixel<uint8_t> const color_original = clave32_a_color8(color_pixel);
  uint32_t color_mas_cercano          = color_pixel;
  // Calculamos la distancia euclídea entre todos los colores frecuentes
  int distancia_minima = std::numeric_limits<int>::max();
  for (auto const & [color_frecuente, color_frecuente_pixel] : colores_frecuentes_cache) {
    int const dr                  = color_original.r - color_frecuente_pixel.r;
    int const dg                  = color_original.g - color_frecuente_pixel.g;
    int const db                  = color_original.b - color_frecuente_pixel.b;
    int const distancia_calculada = dr * dr + dg * dg + db * db;
    // Comprobamos si la distancia es menor que la mínima
    if (distancia_calculada < distancia_minima) {
      // Almacenamos el color
      distancia_minima  = distancia_calculada;
      color_mas_cercano = color_frecuente;
    }
  }
  // Devolvemos el color final
  return color_mas_cercano;
}

uint64_t buscar_color_sustituto64(
    uint64_t const & color_pixel,
    std::vector<std::pair<uint64_t, Pixel<uint16_t>>> const & colores_frecuentes_cache) {
  // Dado un vector de colores frecuentes, busca el color más cercano a un color dado
  Pixel<uint16_t> const color_original = clave64_a_color16(color_pixel);
  uint64_t color_mas_cercano           = color_pixel;
  // Calculamos la distancia euclídea entre todos los colores frecuentes
  int distancia_minima = std::numeric_limits<int>::max();
  for (auto const & [color_frecuente, color_frecuente_pixel] : colores_frecuentes_cache) {
    int const dr                  = color_original.r - color_frecuente_pixel.r;
    int const dg                  = color_original.g - color_frecuente_pixel.g;
    int const db                  = color_original.b - color_frecuente_pixel.b;
    int const distancia_calculada = dr * dr + dg * dg + db * db;
    // Comprobamos si la distancia es menor que la mínima
    if (distancia_calculada < distancia_minima) {
      // Almacenamos el color
      distancia_minima  = distancia_calculada;
      color_mas_cercano = color_frecuente;
    }
  }
  // Devolvemos el color final
  return color_mas_cercano;
}

// Calcular colores sustitutos para los píxeles

void calcular_colores_sustitutos8(std::vector<Pixel<uint8_t>> & pixeles,
                                  ColoresDivididos<uint32_t> const & colores_divididos) {
  // Almacenamos los colores sustitutos en un diccionario para no repetir cálculos
  std::unordered_map<uint32_t, Pixel<uint8_t>> cache;
  // Convertimos los colores frecuentes en un vector de pares para optimizar la búsqueda
  std::vector<std::pair<uint32_t, Pixel<uint8_t>>> colores_frecuentes_cache;
  colores_frecuentes_cache.reserve(colores_divididos.frecuentes.size());
  // Añadimos a caché las conversiones de los frecuentes, así nos ahorramos búsqueda
  for (auto & color_frecuente : colores_divididos.frecuentes) {
    colores_frecuentes_cache.emplace_back(color_frecuente, clave32_a_color8(color_frecuente));
  }
  // Para cada pixel de la imagen, buscamos su sustituto
  for (auto & pixel : pixeles) {
    uint32_t const clave = color8_a_clave32(pixel);
    // Si es un color a eliminar, buscamos su sustituto
    if (colores_divididos.eliminar.find(clave) != colores_divididos.eliminar.end()) {
      // Buscamos la conversión en el diccionario de caché; si no esta, añadimos la clave
      if (cache.find(clave) == cache.end()) {
        cache[clave] = clave32_a_color8(buscar_color_sustituto32(clave, colores_frecuentes_cache));
      }
      // Sustituimos el pixel por su conversión
      pixel = cache[clave];
    }
  }
}

void calcular_colores_sustitutos16(std::vector<Pixel<uint16_t>> & pixeles,
                                   ColoresDivididos<uint64_t> const & colores_divididos) {
  // Almacenamos los colores sustitutos en un diccionario para no repetir cálculos
  std::unordered_map<uint64_t, Pixel<uint16_t>> cache;
  // Convertimos los colores frecuentes en un vector de pares para optimizar la búsqueda
  std::vector<std::pair<uint64_t, Pixel<uint16_t>>> colores_frecuentes_cache;
  colores_frecuentes_cache.reserve(colores_divididos.frecuentes.size());
  // Añadimos a caché las conversiones de los frecuentes, así nos ahorramos búsqueda
  for (auto & color_frecuente : colores_divididos.frecuentes) {
    colores_frecuentes_cache.emplace_back(color_frecuente, clave64_a_color16(color_frecuente));
  }
  // Para cada pixel de la imagen, buscamos su sustituto
  for (auto & pixel : pixeles) {
    uint64_t const clave = color16_a_clave64(pixel);
    // Si es un color a eliminar, buscamos su sustituto
    if (colores_divididos.eliminar.find(clave) != colores_divididos.eliminar.end()) {
      // Buscamos la conversión en el diccionario de caché; si no esta, añadimos la clave
      if (cache.find(clave) == cache.end()) {
        cache[clave] = clave64_a_color16(buscar_color_sustituto64(clave, colores_frecuentes_cache));
      }
      // Sustituimos el pixel por su conversión
      pixel = cache[clave];
    }
  }
}

// Función CUTFREQ

int cutfreq(std::ifstream & input_file, std::string const & output_file, int const n) {
  // Guardamos la información de la imagen
  Imagen const foto = save_info(input_file);
  if (foto.maxIntensidad <= MAX_255INTENSITY_LIMIT) {
    // Procesamiento de imagen de 8 bits
    std::vector<Pixel<uint8_t>> pixeles                           = save_pixels8(input_file, foto);
    std::vector<std::pair<uint32_t, int>> colores                 = vector_colores8(pixeles);
    std::vector<std::pair<uint32_t, int>> const colores_ordenados = ordenar_colores32(colores);
    // Dividimos los colores según su frecuencia
    ColoresDivididos<uint32_t> colores_divididos;
    dividir_colores(colores_ordenados, n, colores_divididos);
    // Sustituimos los colores que hay que eliminar
    calcular_colores_sustitutos8(pixeles, colores_divididos);
    // Creamos la nueva imagen
    crear_imagen(foto, pixeles, output_file);
  } else {
    // Procesamiento de imagen de 16 bits
    std::vector<Pixel<uint16_t>> pixeles                          = save_pixels16(input_file, foto);
    std::vector<std::pair<uint64_t, int>> colores                 = vector_colores16(pixeles);
    std::vector<std::pair<uint64_t, int>> const colores_ordenados = ordenar_colores64(colores);
    // Dividimos los colores según su frecuencia
    ColoresDivididos<uint64_t> colores_divididos;
    dividir_colores(colores_ordenados, n, colores_divididos);
    // Sustituimos los colores que hay que eliminar
    calcular_colores_sustitutos16(pixeles, colores_divididos);
    // Creamos la nueva imagen
    crear_imagen(foto, pixeles, output_file);
  }
  return 0;
}

/* #########################################################
FUNCIONES PARA COMPRESS
############################################################ */

// Funcion booleana para ordenar la tabla de color con std::sort
template <typename T>
bool ordenar_pixeles(Pixel<T> const & p1, Pixel<T> const & p2) {
  if (p1.r != p2.r) { return p1.r < p2.r; }
  if (p1.g != p2.g) { return p1.g < p2.g; }
  return p1.b < p2.b;
}

// Crear la tabla de colores
template <typename T>
std::pair<std::vector<Pixel<T>>, int> tabla_colores(int size, std::vector<Pixel<T>> const &pixeles) {
  int n = 0;
  std::vector<Pixel<T>> tabla_colores;
  // Recorre todos los pixeles de la imagen
  for (size_t i = 0; i < static_cast<size_t>(size); i++) {
    bool encontrado = false;
    // Busca en la tabla si ya se ha guardado ese pixel, si lo encuentra no lo guarda
    for (auto const & pixel : tabla_colores) {
      if (pixel.r == pixeles[i].r && pixel.g == pixeles[i].g && pixel.b == pixeles[i].b) {
        encontrado = true;
        break;
      }
    }
    // Si no esta el pixel en la tabla de colores, se guarda
    if (!encontrado) {
      tabla_colores.push_back(pixeles[i]);
      n++;
    }
  }
  // Se ordena la tbala usando la funcion anterior
  std::sort(tabla_colores.begin(), tabla_colores.end(), ordenar_pixeles<T>);

  return std::make_pair(tabla_colores, n);
}

// Funcion creada para no repetir codigo en la funcion compress para 8 u 16 bits
template <typename T>
void compress_template(int size, std::ofstream & archivoSalida, std::vector<Pixel<T>> &pixeles) {
  auto result                               = tabla_colores<T>(size, pixeles);
  std::vector<Pixel<T>> const tabla_colores = result.first;
  int const n                               = result.second;

  archivoSalida << n << "\n";
  // Escribe todos los pixeles guardados en la tabla de color
  for (auto const & pixel : tabla_colores) {
    write_binary(archivoSalida, pixel.r);
    write_binary(archivoSalida, pixel.g);
    write_binary(archivoSalida, pixel.b);
  }

  Pixeles_y_tabla<T> pixelesYTabla{.pixeles = pixeles, .tabla_colores = tabla_colores};
  int constexpr numero8_super_magico  = 8;
  int constexpr numero16_super_magico = 16;
  int constexpr numero32_super_magico = 32;
  // Llamada a la funcion escribir pixeles en funcion del numero de pixeles en la tabla de color
  if (n < pow(2, numero8_super_magico)) {
    escribir_indices<T, uint8_t>(archivoSalida, size, pixelesYTabla);
  } else if (n < pow(2, numero16_super_magico)) {
    escribir_indices<T, uint16_t>(archivoSalida, size, pixelesYTabla);
  } else if (n < pow(2, numero32_super_magico)) {
    escribir_indices<T, uint32_t>(archivoSalida, size, pixelesYTabla);
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
    std::vector<Pixel<uint8_t>> pixeles = save_pixels8(archivo_i, foto);
    compress_template<uint8_t>(foto.anchura * foto.altura, archivoSalida, pixeles);
  } else {
    std::vector<Pixel<uint16_t>> pixeles = save_pixels16(archivo_i, foto);
    compress_template<uint16_t>(foto.anchura * foto.altura, archivoSalida, pixeles);
  }
  archivoSalida.close();
  return 0;
}



