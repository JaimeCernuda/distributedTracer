#include <mpi.h>
#include <chrono>
#include <thread>
#include "Tracer.h"

void deepFunction() {
    TRACE_FUNC();
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
}

void nestedFunction() {
    TRACE_FUNC();
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate work
    deepFunction();
}

void parallelFunction(int id) {
    TRACE_FUNC();
    std::this_thread::sleep_for(std::chrono::milliseconds(200 * id)); // Simulate work
}

void someFunction() {
    TRACE_FUNC();
    nestedFunction();
    for (int i = 0; i < 3; ++i) {
        parallelFunction(i);
    }
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    static int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    INIT_TRACE_MANAGER();

    someFunction();
    if (rank == 0) {
        nestedFunction();
    }

    MPI_Finalize();
    return 0;
}
