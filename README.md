# Tarea-Fil-sofos-comelones
# Tarea: Filósofos Comelones 🍝

## Descripción
Implementación del problema clásico de los filósofos comensales utilizando hilos en C. Este programa simula 5 filósofos que alternan entre pensar y comer, compartiendo tenedores entre ellos.

## 🎯 Objetivo
Demostrar la solución al problema de sincronización y exclusión mutua usando mutex y variables de condición para evitar interbloqueos (deadlocks).

## ⚙️ Características
- 5 filósofos representados como hilos
- Estados: 🧠 Pensando, 🍽️ Hambriento, 🍝 Comiendo
- Uso de mutex para secciones críticas
- Variables de condición para sincronización
- Prevención de interbloqueos

## 🏃‍♂️ Compilación y Ejecución

### Compilar:
```bash
gcc -o filosofos Filósofos.c -lpthread
