#include "test-boost.hpp"

#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>

#include <string>
#include <iostream>

BoostTest::BoostTest (){
	std::cout << "Hello world! I am process "<< _communicator.rank() << " of " << _communicator.size()-1 << std::endl;
}

void BoostTest::PassMessageToNext(std::string message){

	int rank = getCommunicatorRank();
	int nextRank = (rank+1)%_communicator.size();

	_communicator.send(nextRank,0,message);

}

std::string BoostTest::RecieveMessageFromPrevious(){
	int rank = getCommunicatorRank();
	int prevRank = rank-1;
	if ( prevRank == -1 )
		prevRank = _communicator.size() - 1;

	std::string message;

	_communicator.recv(prevRank,0,message);

	return message;

}

std::string BoostTest::Pack(std::string data[]){

}

int BoostTest::getCommunicatorRank(){
	return _communicator.rank();
}
