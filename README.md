# Ajedrez Engine

Motor de ajedrez multi-lenguaje, en desarrollo.

## Estructura
- `engine-cpp/` — motor en C++ (bitboards, generación de movimientos, búsqueda, protocolo UCI)
- `gui-java/` — interfaz gráfica en Java *(próximamente)*
- `analysis-py/` — scripts de testing y análisis de partidas en Python *(próximamente)*

## Estado actual
- ✅ Representación del tablero con bitboards
- ✅ Función de impresión del tablero
- ✅ Generación de movimientos
- 🔲 Búsqueda (minimax + alpha-beta)
- 🔲 Protocolo UCI
- 🔲 GUI en Java
- 🔲 Análisis de partidas en Python

## Cómo compilar el motor
Abre `engine-cpp/ChessEngine/ChessEngine.slnx` en Visual Studio y compila (Ctrl+F7).
