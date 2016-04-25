#include <iostream>
#include <cstring>

//#include "helloworld.cpp"
#include "openclass.hpp"

void TestBCast();
void TestScatter();

int main(){
	
	//TestScatter();
	TestBCast();

	return 0;
}

void TestBCast(){
	Open obj;
	ProcessInfo objInfo  = obj.GetProcessInfo();

	//Testing BCast
	char *send_data;
	int element_count = 3;

	if(objInfo.world_rank == 0){
		send_data = new char[element_count+1];
		send_data[element_count] = 0;
		std::string alphabet = "AABBCCDDEEFF";
		memcpy(send_data,alphabet.c_str(),element_count);



		std::cout << "Send data prepped: ";
		for(int i = 0; i < element_count; i++){
			std::cout << send_data[i];
		}
		std::cout << std::endl;
	}
		
	std::string recv_data = obj.BCastChar(
			send_data,
			element_count,
			0
			);
	std::cout << "Process " << objInfo.world_rank << " recieved: " << recv_data << std::endl;



	
}

void TestScatter(){
	Open obj;
	ProcessInfo objInfo  = obj.GetProcessInfo();

	//Testing scatter
	char *send_data;
	int element_count = 2;
	//char *recv_data = (char *)malloc(sizeof(char) * obj.GetProcessInfo().world_size);

	if(obj.GetProcessInfo().world_rank == 0){
		std::string alphabet = "AABBCCDDEEFF";

		send_data = new char[obj.GetProcessInfo().world_size+1];
		send_data[obj.GetProcessInfo().world_size] = 0;

		memcpy(send_data,alphabet.c_str(),(obj.GetProcessInfo().world_size*element_count));

		std::cout << "Send data prepped: ";
		for(int i = 0; i < obj.GetProcessInfo().world_size; i++){
			std::cout << send_data[i];
		}	
		std::cout << std::endl;
	}

	std::string recv_data = obj.ScatterChar(
			send_data,
			element_count,
			0
			);
	std::cout << "Process " << objInfo.world_rank << " recieved: " << recv_data << std::endl;

}


