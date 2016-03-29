#include "test-boost.hpp"

#include <string>
#include <vector>

//Foward declarations

void PtpCommunication();//Point-to-point communication

void NbCommunication(); //Non-blocking communication

void ScatterCommunication(); // Scatter Communication

int main(){

//	NbCommunication();

	ScatterCommunication();

	return 0;
}



void PtpCommunication(){
	BoostTest obj;
	
	int rank = obj.getRank();

	std::string sentMessage = "Hello from ";
	obj.PassMessageToNext(sentMessage);

	std::string message = obj.RecieveMessageFromPrevious();

	std::cout << "Message Recieved : '" << message << "'" << std::endl;
}

void NbCommunication(){

	BoostTest obj;

	int rank = obj.getRank();
	int prevRank = obj.getPrevRank();
	int nextRank = obj.getNextRank();

	std::string sendMessage = "Hello from ";
	sendMessage.append(std::to_string(rank));

	std::string recvMessage = obj.SendRecvMessages(nextRank,prevRank,sendMessage);

	std::cout << "Message Recieved : '" << recvMessage << "'" << std::endl;


}	


void ScatterCommunication(){

	BoostTest obj;

	int rank = obj.getRank();
	
	BoostTest::VectorPayload payload_send;
	payload_send.resize(obj.getWorldSize());

	
	for ( int i = 0; i < obj.getWorldSize(); i++ ){
		std::string str = "Hello ";
		str.append(std::to_string(i));
		str.append(" from ");
		str.append(std::to_string(rank));
		payload_send[i] = str;		
	}
	
	BoostTest::VectorPayload payload_recv;
        obj.ScatterMessage(&payload_send,&payload_recv);
	
	std::cout << "Process[" << rank << "] Recieved " << payload_recv.size() << " messages. " << std::endl;
	for ( int i = 0; i < payload_recv.size(); i++){
		std::cout << "Process[" << rank << "] recieved message: '" << payload_recv[i] << std::endl;
	}

}
