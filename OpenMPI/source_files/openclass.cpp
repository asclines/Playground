#include "openclass.hpp"

#include <mpi.h>
#include <stdio.h>
#include <string>

/**************************************************************************
 * 	Public Method Definitions
 **************************************************************************/

Open::Open(){
	MPI_Init(NULL,NULL);
	
	MPI_Comm_size(MPI_COMM_WORLD, &process_info_.world_size);
	
	
	MPI_Comm_rank(MPI_COMM_WORLD, &process_info_.world_rank);
	
	char name[MPI_MAX_PROCESSOR_NAME];
	int name_length;
	MPI_Get_processor_name(name,&name_length);
	process_info_.name = name;

	
	

}


Open::~Open(){
	MPI_Finalize();

}

ProcessInfo Open::GetProcessInfo(){
	return process_info_;
}

std::string Open::GetSummary(){
	std::string summary = "Process Info: ";

	summary.append("\n\tProcess Name: ");
	summary.append(process_info_.name);

	summary.append("\n\tWorld Rank: ");
	summary.append(std::to_string(process_info_.world_rank));
	
	summary.append("\n\tWorld Size: ");
	summary.append(std::to_string(process_info_.world_size));

	return summary;
}



std::string Open::ScatterChar(
		char *send_data,
		int element_count, //Elements per processor
		int root
		){

	char *recv_buffer = (char *) malloc(sizeof(char) * element_count);

	MPI_Scatter(
			send_data,
			element_count,
			MPI_CHAR,
			recv_buffer,
			element_count,
			MPI_CHAR,
			root,
			MPI_COMM_WORLD
		   );
		
	std::string recv;
	for(int i=0; i < element_count; i++){
		recv.push_back(recv_buffer[i]);
	}

	return recv;

}

std::string Open::BCastChar(
		char *send_data,
		int element_count,
		int root){

	char *recv_buffer;
	if(process_info_.world_rank == root){
		recv_buffer = send_data;
	} else {
		recv_buffer = (char *)malloc(sizeof(char) * element_count);
	}

	
	MPI_Bcast(
			recv_buffer,
			element_count,
			MPI_CHAR,
			root,
			MPI_COMM_WORLD
		 );

	std::string recv;
	for(int i=0; i < element_count; i++){
		recv.push_back(recv_buffer[i]);
	}
	return recv;

}

/**************************************************************************
 * 	Private Method Definitions
 **************************************************************************/

void Open::SetProcessInfo(ProcessInfo process_info){
	process_info_ = process_info;
}
