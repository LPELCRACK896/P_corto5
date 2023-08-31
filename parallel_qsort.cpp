#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <omp.h> 



#define MAX_ELEMENTOS 100

using namespace std;
using namespace std::chrono;


/* 
Esta sección no es paralelizable por las limitante de los arcihvos.
 */
void write_csv(int *arr, int size, const string& filename) {
  ofstream file(filename);
  if(!file.is_open()) {
    cerr << "Error al abrir el archivo " << filename << endl;
    exit(1);
  }

  for(int i = 0; i < size; i++) {
    file << arr[i];
    if(i < size - 1) {
      file << ",";
    }
  }
  file << "\n";
  file.close();
}
/* 
Esta sección no es paralelizable por las limitante de los arcihvos.
 */
void read_csv(int *arr, int size, const string& filename) {
  ifstream file(filename);
  if(!file.is_open()) {
    cerr << "Error al abrir el archivo " << filename << endl;
    exit(1);
  }

  string temp;
  for(int i = 0; i < size; i++) {
    if(!getline(file, temp, ',')) {
      cerr << "Error al leer el archivo" << endl;
      exit(1);
    }
    arr[i] = stoi(temp);
  }
  file.close();
}

void par_qsort(int *data, int lo, int hi) {
  if(lo > hi) return;
  int l = lo;
  int h = hi;
  int p = data[(hi + lo) / 2];

  while(l <= h) {
    while((data[l] - p) < 0) l++;
    while((data[h] - p) > 0) h--;
    if(l <= h) {
      int tmp = data[l];
      data[l] = data[h];
      data[h] = tmp;
      l++; h--;
    }
  }
  /* 
     Se paraleliza considerando el divide and conquer. SIendo las secciones las ramificaciones que llama la respectiva iteracion. 
   */
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      par_qsort(data, lo, h);
    }
    #pragma omp section
    {
      par_qsort(data, l, hi);
    }
  }
}

int main (int argc, char *argv[]) {

  if (argc != 2) {
    printf("Usage: qSort cantidad_de_numeros\n");
    exit(1);
  }

  int cant_numeros_aleatorios = atoi(argv[1]);
  int randon_nums[cant_numeros_aleatorios];

  auto start = high_resolution_clock::now();

  for (int j=0; j<cant_numeros_aleatorios; j++)
    randon_nums[j] = rand()%(MAX_ELEMENTOS)+1;

  write_csv(randon_nums, cant_numeros_aleatorios, "random_numbers.csv");

  int read_random_nums[cant_numeros_aleatorios]; 

  read_csv(read_random_nums, cant_numeros_aleatorios, "random_numbers.csv");

  par_qsort(read_random_nums, 0, cant_numeros_aleatorios-1);

  write_csv(read_random_nums, cant_numeros_aleatorios, "sorted_numbers.csv");

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);

  cout << "Tiempo de ejecucion: " << duration.count() << " ms" << endl;

  return 0;
}