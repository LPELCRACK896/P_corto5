#include <omp.h>
#include <iostream>

int main() {
    int maxThreads = omp_get_max_threads();
    std::cout << "Max threads: " << maxThreads << std::endl;
    return 0;
}