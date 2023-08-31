# Corto 5 

## Descripcion

Leer  datos  de  números  desde  un  archivo  csv  y  clasificarlos.  Escribir  la  lista  ordenada  de  números a un segundo archivo.  Paralelizar mediante OpenMP usando parallel for, sections,  tasks, modificación de scope de variables, políticas de planificación y medición de tiempos

## Ejemplos 

Los siguientes son archivos de referencia, provistos por el catedrático. 

- `example_q_sort.c`
- `example_fileHandler.c`

## Uso

### Programa secuencial

#### Compilacion
```
g++ sequential_qsort.cpp -o sequential_qsort
```


#### Ejecucion
```
.\sequential_qsort.exe
```

### Programa paralelo

#### Compilacion
```
g++ -fopenmp -std=c++11 parallel_qsort.cpp -o parallel_qsort
```
#### Ejecucion

Para generar y ordenar 1000 numeros. 
```
.\parallel_qsort.exe 1000
```

### Extra

```
g++ -fopenmp pc_info.cpp -o pc_info
```

```
.\pc_info.exe
```
## Anexos
### Compilación programa paralelo
#### Base
```
g++ -fopenmp .c -o output
```

#### Generico
```
g++ -fopenmp <nombre_archivo_c_con_extension> -o <nombre_output>
```
#### Ejemplo
Para un archivo hello.c
```
g++ -fopenmp hello.c -o hello
```