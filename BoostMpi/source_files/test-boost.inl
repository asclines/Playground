#include "test-boost.hpp"

#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>

#include <string>
#include <iostream>

BoostTest::BoostTest (){
	std::cout << "Hello world! I am process "<< _communicator.rank() << " of " << _communicator.size()-1 << std::endl;
}


/* PTP Communication */
void BoostTest::PassMessageToNext(std::string message){
	int nextRank = getNextRank();

	_communicator.send(nextRank,0,message);

}

std::string BoostTest::RecieveMessageFromPrevious(){

	int prevRank = getPrevRank();

	std::string message;

	_communicator.recv(prevRank,0,message);

	return message;

}


/* Non-blocking communication */
std::string BoostTest::SendRecvMessages(int dest, int src, std::string sendMessage){
	std::string recvMessage;

	mpi::request reqs[2];

	reqs[0] = _communicator.isend(dest,0,sendMessage);
	reqs[1] = _communicator.irecv(src,0,recvMessage);

	mpi::wait_all(reqs,reqs+2);

	return recvMessage;
}


/* Scatter Communication */
void BoostTest::ScatterMessage(VectorPayload *vector_payload_send, VectorPayload *vector_payload_recv){
	vector_payload_recv->resize(_communicator.size());

	for ( int i = 0; i < _communicator.size(); i++){
		Payload payload_recv;
		mpi::scatter(
			_communicator,
			*vector_payload_send,
			payload_recv,
			i
			);
		(*vector_payload_recv)[i] = payload_recv;
	}




}


/* Misc. Methods */

std::string BoostTest::Pack(std::string data[]){

}

int BoostTest::getRank(){
	return _communicator.rank();
}

int BoostTest::getPrevRank(){
	int rank = getRank();
	int prevRank = rank-1;
	if ( prevRank == -1 )
		prevRank = _communicator.size() - 1;

	return prevRank;
}

int BoostTest::getNextRank(){
	int rank = getRank();
	int nextRank = (rank+1)%_communicator.size();

	return nextRank;
}

int BoostTest::getWorldSize(){
	return _communicator.size();
}

