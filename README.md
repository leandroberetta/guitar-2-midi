# Guitar2MIDI

**Trabajo Final de Grado**  
Carrera de Ingeniería Electrónica  
Universidad de Palermo

## ¿Qué es Guitar2MIDI?

**Guitar2MIDI** es un proyecto de conversión de señal de guitarra eléctrica a mensajes MIDI USB en tiempo real, desarrollado como Trabajo Final de Grado de la carrera de Ingeniería Electrónica.

El sistema está basado en un microcontrolador STM32F407 Discovery. Toma la señal analógica de una guitarra eléctrica, realiza análisis de frecuencia para detectar la nota fundamental, y envía los correspondientes mensajes MIDI "Note On" y "Note Off" a la computadora, permitiendo que la guitarra sea utilizada como controlador MIDI para sintetizadores, DAWs y otros dispositivos compatibles.

## Características principales

- Procesamiento de señal en tiempo real (detección de frecuencia fundamental).
- Envío de mensajes MIDI estándar por USB (clase MIDI compliant).
- Compatible con software musical en Windows, macOS y Linux.

## Autor

Leandro Beretta  
Trabajo Final de Grado - Ingeniería Electrónica  
Universidad de Palermo

## Licencia

### Código fuente propio

El código desarrollado específicamente para este proyecto se distribuye bajo la licencia [MIT](LICENSE).

### Dependencias y archivos generados por STM32CubeIDE

Este proyecto incluye archivos fuente y librerías generadas por STM32CubeIDE y STM32CubeMX, así como controladores HAL, CMSIS y middleware oficial de STMicroelectronics (archivos en `Drivers/`, `Middlewares/`, etc.).

- **STM32Cube HAL y middleware:**  
  Distribuidos bajo la licencia BSD-3-Clause.  
  Para más detalles, ver los encabezados de cada archivo y la documentación oficial de STMicroelectronics.
  
**Al utilizar o redistribuir este proyecto, se mantienen los avisos de licencia originales de STMicroelectronics y de los autores de las librerías externas.**
