
# ChavezNet - Sistema de Recomendación de Películas

Proyecto del curso de Programación III, realizado por Sergio Sebastian Lezama Orihuela, Felix Alberto Martinez Olivos, Milton Joel Cordova Navarro, y Angel Toshio Tribeño Hurtado.

## Descripción del Proyecto

ChavezNet implementa un sistema de recomendación de películas utilizando un Árbol Binario de Búsqueda (ABS). Los usuarios pueden registrar sus gustos y obtener recomendaciones basadas en las películas que les gustan.
Para entender mejor como funciona este proyecto, en el siguiente enlace se encuentra un video de explicación: [link del video](https://drive.google.com/drive/folders/1f76zPKyri5rW8kaNTuNWbinLzZG710iv?usp=sharing)

## Características

- **Inserción de películas** en el árbol binario de búsqueda.
- **Búsqueda** de películas por título, sinopsis y tags.
- **Recomendación** de películas basadas en los gustos del cliente.
- **Serialización** de los likes de los clientes en un archivo y carga de los mismos desde un archivo.
- **Patrón de diseño Factory Method** para la creación de clientes.
- **Patrón de diseño Singleton** para la creación de la instancia del árbol binario de búsqueda.
- **Uso de programación concurrente** para la eficiencia de la lectura de datos.
- **Uso de programación Genérica** para la implementación del árbol.

## Requisitos

- C++17 o superior
- Compilador compatible con C++17 (g++, clang++, etc.)
- CMake para la gestión de la compilación

## Instalación

1. Clona este repositorio:
   ```sh
   git clone https://github.com/SergioSLO/ChavezNet.git
   ```
2. Navega al directorio del proyecto:
   ```sh
   cd ChavezNet
   ```
3. Compila el proyecto:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

## Uso

1. Ejecuta el programa.
2. El programa permite agregar likes de películas a los clientes y generar recomendaciones basadas en esos gustos.

## Archivos

- `main.cpp`: Contiene la función principal del programa.
- `include/`: Contiene los archivos de encabezado para las clases `Cliente`, `Pelicula`, `Arbol`, y las fábricas.
   - `Cliente.h`: Definición de la clase `Cliente`.
   - `Pelicula.h`: Definición de la clase `Pelicula`.
   - `Arbol.h`: Definición de la clase `Arbol`.
   - `ClienteFactory.h`: Definición de la interfaz de la fábrica de clientes.
   - `ClienteConcreteFactory.h`: Implementación concreta de la fábrica de clientes.
- `src/`: Contiene las implementaciones de las clases.
   - `Cliente.cpp`: Implementación de la clase `Cliente`.
   - `Pelicula.cpp`: Implementación de la clase `Pelicula`.
   - `Arbol.cpp`: Implementación de la clase `Arbol`.
   - `ClienteConcreteFactory.cpp`: Implementación de la fábrica concreta de clientes.
- `data/`: Directorio donde se guardan los datos serializados de los likes de los clientes.
   - `RawData.csv`: Archivo CSV con datos de películas.
   - `RawData_fixed.csv`: Archivo CSV con datos de películas corregidos.
- `CMakeLists.txt`: Archivo de configuración para la compilación con CMake.
- `README.md`: Este archivo de documentación.

## Referencias Bibliográficas

1. **Design Patterns: Elements of Reusable Object-Oriented Software** - Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides
   - Esta referencia cubre los patrones de diseño que se han utilizado en este proyecto, como Factory Method y Singleton.

2. **The C++ Programming Language** - Bjarne Stroustrup
   - Un recurso esencial para comprender las características avanzadas de C++ utilizadas en este proyecto.

3. **Effective Modern C++** - Scott Meyers
   - Este libro proporciona una guía sobre las mejores prácticas y técnicas modernas en C++11 y C++14, muchas de las cuales son relevantes para este proyecto.

4. **Introduction to Algorithms** - Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein
   - Un recurso fundamental para comprender los algoritmos y estructuras de datos, como el árbol binario de búsqueda (ABS), utilizado en este proyecto.

## Licencia

Este proyecto está licenciado bajo la Licencia MIT. Para más detalles, consulta el archivo LICENSE.
