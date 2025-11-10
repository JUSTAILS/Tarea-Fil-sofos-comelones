# Filósofos Comelones - Solución con Variables de Condición

## Descripción
Implementación del problema de sincronización "Los Filósofos Comelones" utilizando **variables de condición** y un **árbitro centralizado**. Esta solución es más elegante y eficiente que las basadas únicamente en mutexes.

## Características de la Implementación

### 🎯 Solución Implementada: **Arbitraje Central con Variables de Condición**
- Un único mutex global protege el estado de todos los filósofos
- Variables de condición individuales para cada filósofo
- Función `test()` que decide cuándo un filósofo puede comer

### Estados del Filósofo
- **THINKING (0)**: Pensando 🧠
- **HUNGRY (1)**: Tiene hambre 🍽️  
- **EATING (2)**: Comiendo 🍝

## Mecanismos de Sincronización

### 1. Prevención de Race Conditions
- **Mutex global**: Garantiza acceso exclusivo al array de estados
- **Operaciones atómicas**: Cambios de estado protegidos por el mutex

### 2. Prevención de Deadlock
- **Test centralizado**: La función `test()` verifica ambos vecinos
- **Exclusión mutua garantizada**: Solo un filósofo come por vez en cada "tripleta"
- **Notificación dirigida**: `pthread_cond_signal()` solo al filósofo afectado

### 3. Prevención de Starvation
- **Notificaciones en cadena**: Al liberar tenedores, se notifica a ambos vecinos
- **Justicia en la espera**: Variables de condición garantizan orden FIFO
- **Oportunidad equitativa**: Todos los filósofos son notificados cuando corresponde

## Compilación y Ejecución

```bash
# Compilar
make

# Ejecutar
./filosofos_comelones

# Limpiar
make clean












