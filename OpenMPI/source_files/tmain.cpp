#include <iostream>
#include <cstring>
#include <vector>

#include "/home/alexander/GitRepos/MyRepos.d/Flamingo/dataframe/transporter/source_files/transporter.hpp"

void TestTBCast2(); //Uknown data_size
void TestTBCast();
void TestBCast();
void TestScatter();

int main(){
	
//	TestBCast();

//	TestTBCast();

	TestTBCast2();

//	TestScatter();

	return 0;
}

void TestTBCast2(){
	Transporter obj;
	ProcessInfo objInfo = obj.GetProcessInfo();
	std::vector<char> send_data;
	char *recv_data;
	int element_count = 5;
	int source = 0;

	if(objInfo.world_rank == source){
		for(int i = 0; i < element_count; i++){
			send_data.push_back('X');
		}

		for(int i =0; i < send_data.size(); i++){
			std::cout << "send_data["<<i<<"]= " << send_data[i] << std::endl;
		}
	}

	obj.Broadcast<std::vector<char>::iterator>(
			send_data.begin(),
			send_data.end(),
			recv_data,
			source
			);
	std::cout << "Process " << objInfo.world_rank << " recieved: ";
	for(int i = 0 ; i < element_count; i++){
		std::cout << recv_data[i];
	}
	std::cout << std::endl;


}

void TestTBCast(){
	Transporter obj;
	ProcessInfo objInfo = obj.GetProcessInfo();
	std::vector<char> send_data;
	char *recv_data;
	int element_count = 5;
	int source = 0;

	if(objInfo.world_rank == source){
		send_data.push_back('H');
		send_data.push_back('E');
		send_data.push_back('L');
		send_data.push_back('L');
		send_data.push_back('O');
	}	
		obj.Broadcast<std::vector<char>::iterator>(
				send_data.begin(),
				send_data.end(),
				element_count,
				recv_data,
				source
				);
	
	std::cout << "Process " << objInfo.world_rank << " recieved: ";
	for(int i = 0 ; i < element_count; i++){
		std::cout << recv_data[i];
	}
	std::cout << std::endl;


}



void TestBCast(){
	Transporter obj;
	ProcessInfo objInfo = obj.GetProcessInfo();

	char *send_data;
	char *recv_data;
	int element_count = 3;
	int source = 0;

	if(objInfo.world_rank == source){
		send_data = "msg";
		std::cout << "Send data prepared: ";
		for(int i = 0; i < element_count; i++){
			std::cout << send_data[i];
		}
		std::cout << std::endl;
	}

	obj.Broadcast(
			send_data,
			recv_data,
			element_count,
			source
		     );
		
	std::cout << "Process " << objInfo.world_rank << " recieved: ";
for(int i = 0 ; i < element_count; i++){
		std::cout << recv_data[i];
	}
	std::cout << std::endl;

	
}

void TestScatter(){
	Transporter obj;
	ProcessInfo objInfo = obj.GetProcessInfo();

	std::vector<std::string> send_data;
	char *recv_data;
	int source = 0;

	if(objInfo.world_rank == source){
//		std::cout << obj.GetSummary() << std::endl;
		for(int i = 0; i < objInfo.world_size; i++){
				std::string data;
				for(int j = 0; j < i; j++){
					data.append(std::to_string(i));
				}
				send_data.push_back(data);
		}
		//send_data.push_back("0");
		//send_data.push_back("1");
		//send_data.push_back("22");
//		send_data.push_back("333");
//		send_data.push_back("4444");

		for(int i =0; i <send_data.size(); i++){
			for(int j =0; j < send_data.data()[i].size(); j++){
			//	std::cout << "Data2[" << i << "][" << j <<  "] = " << send_data.data()[i][j] << std::endl; 
			}
		}
	}	
	obj.Scatter(
			&send_data,
			recv_data,
			source
		   );


			
	std::cout << "Process " << objInfo.world_rank << " recieved: ";
for(int i = 0 ; i < objInfo.world_rank; i++){
		std::cout << recv_data[i];
	}
	std::cout << std::endl;

}


