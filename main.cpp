#include <mpi.h>
#include <chrono>
#include <thread>
#include "Tracer.h"

void deepFunction(int rank) {
    TRACE_FUNC(rank);
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
}

void nestedFunction(int rank) {
    TRACE_FUNC(rank);
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate work
    deepFunction(rank);
}

void parallelFunction(int rank, int id) {
    TRACE_FUNC(rank);
    std::this_thread::sleep_for(std::chrono::milliseconds(200 * id)); // Simulate work
}

void someFunction(int rank) {
    TRACE_FUNC(rank);
    nestedFunction(rank);
    for (int i = 0; i < 3; ++i) {
        parallelFunction(rank, i);
    }
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    INIT_TRACE();

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    someFunction(rank);
    if (rank == 0) {
        nestedFunction(rank);
    }

    MPI_Finalize();
    return 0;
}
