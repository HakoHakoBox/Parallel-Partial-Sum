#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); //world_rank is incermenting
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size); //world_size is 10
	int token = 0;
	int final_token = 0;
	const int n = 1000;
	int a[n];

	if (world_rank == 0){
	for (int i = 0; i<n; i++){
		a[i] = i+1;
		}
	}
	MPI_Bcast(a, n, MPI_INT,0,MPI_COMM_WORLD);
	int test1 = world_rank * n/world_size;
	int test2 = (world_rank +1)*n/world_size;
	for (int i = test1; i<test2; i++){
		token += a[i];
	}	
	
	MPI_Reduce(&token, &final_token, 1, MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	printf("The token from processor %d is %d\n", world_rank, token);
	if (world_rank ==0){
	printf("The final_token is %d\n", final_token);
	}


	

	
	MPI_Finalize();		
}
	



