
# Minishell

Bienvenido a **Minishell**, un proyecto de creación de una shell mínima basada en Unix. Este proyecto fue desarrollado como parte del plan de estudios de la escuela 42 para proporcionar una comprensión más profunda de cómo funcionan las shells y para mejorar las habilidades en programación en C.

## Tabla de contenidos

- [Descripción](#descripción)
- [Características](#características)
- [Compilación e Instalación](#compilación-e-instalación)
- [Uso](#uso)
- [Builtins Implementados](#builtins-implementados)
- [Funciones Específicas](#funciones-específicas)
- [Detalles Técnicos](#detalles-técnicos)
- [Autores](#autores)

## Descripción

**Minishell** es una réplica simple de la shell de Unix, diseñada para ejecutar comandos básicos, redirecciones de entrada/salida, tuberías y algunas características de control de flujo. Es una buena oportunidad para entender los fundamentos de la creación de procesos, gestión de señales, redirección de archivos y la ejecución de comandos en sistemas Unix.

## Características

- Manejo de comandos simples y combinaciones con pipes (`|`).
- Implementación de redirecciones de entrada (`<`), salida (`>`) y salida de append (`>>`).
- Ejecución de comandos del sistema.
- Implementación de algunos **builtins** esenciales.
- Gestión de señales como `Ctrl+C`, `Ctrl+D` y `Ctrl+\`.
- Soporte básico para variables de entorno.
- Manejo de comillas simples y dobles en los argumentos.
- Heredoc (`<<`) para entrada múltiple desde el terminal.

## Compilación e Instalación

1. **Clona el repositorio**:
   ```bash
   git clone https://github.com/samuelhm/Minishell.git
   cd Minishell
   ```

2. **Compila el proyecto** usando el siguiente comando:
   ```bash
   make
   ```

3. **Ejecuta el shell**:
   ```bash
   ./minishell
   ```

## Uso

Cuando ejecutes el shell, verás un prompt donde podrás escribir comandos como lo harías en una shell de Unix. Por ejemplo:

```shell
minishell$ echo "Hello, World!"
Hello, World!

minishell$ ls -l | grep Minishell
```

## Builtins Implementados

Estos son los builtins que se han implementado en **Minishell**:

- `echo` con la opción `-n`.
- `cd` para cambiar de directorio.
- `pwd` para mostrar el directorio actual.
- `export` para gestionar variables de entorno.
- `unset` para eliminar variables de entorno.
- `env` para mostrar las variables de entorno.
- `exit` para salir de la shell.

## Funciones Específicas

**Minishell** utiliza varias funciones y estructuras para organizar y gestionar los diferentes aspectos de la shell. Algunas de las funciones clave incluyen:

- `process_line`: Procesa y organiza los comandos, maneja la ejecución y el flujo de control.
- `handle_redirection`: Maneja las redirecciones de entrada y salida.
- `execute_command`: Se encarga de ejecutar un comando simple o encadenado con pipes.
- `set_signals`: Configura las señales para el shell.
- `split_input`: Convierte la línea de entrada en un array de cadenas separadas por espacios y otros signos.

## Detalles Técnicos

El proyecto fue desarrollado utilizando el lenguaje C estándar y hace uso de las bibliotecas y funciones básicas de Unix para la manipulación de procesos, la gestión de archivos y la manipulación de señales. Se tuvieron en cuenta los siguientes puntos clave:

- **Redirección de Entrada/Salida**: Uso de `dup2()` para redirigir descriptores de archivo.
- **Manejo de Pipes**: Creación y uso de pipes para la comunicación entre procesos.
- **Gestión de Procesos**: Uso de `fork()`, `execve()` y `waitpid()`.
- **Señales**: Manejo de señales de interrupción como `SIGINT`, `SIGQUIT`, etc.
- **Expansión de Variables**: Soporte básico para la expansión de variables del entorno utilizando el símbolo `$`.

## Autores

- **Samuel H. M.** - [GitHub](https://github.com/samuelhm)
- **Lin Yao** - [GitHub](https://github.com/hazeliny)
