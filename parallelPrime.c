#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int number, prime;

    int count = 0;
    int n = 10000;
    float start_time, end_time;
    
    if (rank == 0) {
    	start_time = MPI_Wtime();
    }

    if (rank == 0) {
        for (int number = 2; number < n; number++) {
            MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        }
        number = -1;
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&prime, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (prime != -1) {
            printf("\nProcess %d received %d ", rank, prime);


            while (1) {
                MPI_Recv(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                if (number == -1) {
                    if (rank + 1 < size) {
                        MPI_Send(&number, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                    }
                    break;
                }
                
                if (number % prime != 0) {
                    if (rank + 1 < size) {
                        MPI_Send(&number, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                    }
                }
            }
        } else {
            if (rank + 1 < size) {
                MPI_Send(&prime, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            }
        }
    }    
    if (rank == 0){
    	end_time = MPI_Wtime();    
    	printf("\nelapsed time is: %f seconds\n",end_time-start_time);
    }

    MPI_Finalize();

    return 0;
}
