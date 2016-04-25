#include <mpi.h>
#include <stdio.h>



void HelloWorld(){
	MPI_Init(NULL,NULL);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_length;
	MPI_Get_processor_name(processor_name, &name_length);

	std::cout << "Hello world from processor " << processor_name << " rank " << world_rank << " out of " << world_size << " processors." << std::endl;

	MPI_Finalize();

}
