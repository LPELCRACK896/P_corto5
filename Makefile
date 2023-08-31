# Variables
CXX = g++
CXXFLAGS = -std=c++11
OPENMP_FLAGS = -fopenmp
SEQ_OUT = sequential_qsort.exe
PAR_OUT = parallel_qsort.exe
PC_INFO_OUT = pc_info.exe
NUM_ALEATORIOS = 100000


# Tarea por defecto
all: seq par pc_info

# Compilación y ejecución del programa secuencial
seq: sequential_qsort.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(SEQ_OUT)
	@echo "Ejecutando $(SEQ_OUT) 5 veces..."
	@$(SEQ_OUT) $(NUM_ALEATORIOS) > res_seq.txt
	@for /l %%x in (1, 1, 4) do $(SEQ_OUT) $(NUM_ALEATORIOS) >> res_seq.txt

# Compilación y ejecución del programa paralelo
par: parallel_qsort.cpp
	$(CXX) $(CXXFLAGS) $(OPENMP_FLAGS) $^ -o $(PAR_OUT)
	$(PAR_OUT) $(NUM_ALEATORIOS) > res_par.txt
	@for /l %%x in (1, 1, 4) do $(PAR_OUT) $(NUM_ALEATORIOS) >> res_par.txt

# Compilación y ejecución del programa para obtener información de la PC
pc_info: pc_info.cpp
	$(CXX) $(CXXFLAGS) $(OPENMP_FLAGS) $^ -o $(PC_INFO_OUT)

# Tarea para probar políticas de planificación de OpenMP
test: parallel_qsort.cpp
	$(CXX) $(CXXFLAGS) $(OPENMP_FLAGS) $^ -o $(PAR_OUT)
	(set OMP_SCHEDULE=static,64 && $(PAR_OUT) $(NUM_ALEATORIOS) > res_par.txt)
	@for /l %%x in (1, 1, 4) do (set OMP_SCHEDULE=static,64 && $(PAR_OUT) $(NUM_ALEATORIOS) >> res_par.txt)

# Limpia los archivos compilados
clean:
	del /F /Q $(SEQ_OUT) $(PAR_OUT) $(PC_INFO_OUT)

.PHONY: all seq par pc_info test clean
