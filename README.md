# Proyecto de Arquitectura de Computadores - Programación en C++

El objetivo principal es implementar y analizar distintas funciones de procesamiento de imágenes en **C++**, comparando dos metodologías de organización de datos: **AOS (Array of Structures)** y **SOA (Structure of Arrays)**.

---

## 📌 Descripción del Proyecto
Se han implementado una serie de funciones que permiten leer, editar y crear imágenes en formato `.ppm`.  
Posteriormente, se han comparado las implementaciones AOS y SOA en términos de **tiempo de ejecución**, **consumo de energía** y **potencia**.

Las funciones principales son:
- **BinaryIO** → Lectura y escritura binaria de imágenes.
- **Info** → Obtención de información básica de la imagen (formato, dimensiones, nivel de intensidad).
- **Maxlevel** → Escalado de la intensidad de los píxeles (8/16 bits).
- **Resize** → Redimensionado de imágenes con interpolación bilineal.
- **Cutfreq** → Eliminación de colores poco frecuentes con sustitución por colores cercanos.
- **Compress** → Compresión mediante tabla de colores y reindexado.

---

## 🛠️ Tecnologías utilizadas
- Lenguaje: **C++**
- Estándar de código: **Clang-Tidy**
- Cluster de ejecución: **Avignon (UC3M)**
- Metodología de trabajo: **Agile** + **programación por parejas**

---

## ✅ Pruebas realizadas
- **Pruebas unitarias** → Validación de flujo de código y comprobación de casos límite.  
- **Pruebas funcionales** → Comparación de salidas frente a las soluciones esperadas.

---

## 📊 Análisis de rendimiento
Se realizaron mediciones en el cluster Avignon para las funciones principales, obteniendo comparativas entre AOS y SOA en términos de:
- **Tiempo de ejecución (s)**
- **Energía consumida (J)**
- **Potencia (W)**

### Resultados destacados:
- **Maxlevel**: No hay diferencias claras entre AOS y SOA en tiempo y energía, pero AOS muestra menor potencia.  
- **Resize**: SOA consume más potencia debido a accesos dispersos en memoria.  
- **Cutfreq**: AOS es más eficiente en tiempo y energía gracias al acceso contiguo en memoria.  
- **Compress**: Similar en tiempo y energía, pero AOS presenta mayor potencia.  

---

## 📌 Conclusiones
- **AOS** es generalmente más eficiente en la mayoría de funciones (tiempo y energía).  
- **SOA** puede ser más adecuado en casos específicos, como en la función *Maxlevel*.  
- La elección de la metodología depende del tipo de operación y la forma de acceso a los datos.

---

## 👥 Autores
- Javier Rosales Lozano  
- Alonso Rios Guerra  
- Manuel Roldán Matea  
- Guillermo Sancho González  

Universidad Carlos III de Madrid - 2024/2025
