#ifndef BOOST_TEST_
#define BOOST_TEST_

#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>

#include <string>
#include <vector>


namespace mpi = boost::mpi;

class BoostTest{
public:

	typedef std::string			Payload;
	typedef std::vector<std::string>	VectorPayload;


	BoostTest ();

/* PTP Communication */
	void PassMessageToNext(std::string message);
	
	std::string RecieveMessageFromPrevious();

/* Non-Blocking Communication */
	std::string SendRecvMessages(int dest, int src, std::string sendMessage);

/* Scatter Communication */
	void ScatterMessage(VectorPayload *payload_send, VectorPayload *payload_recv);

/* Gather Communication */
	
/* Misc Methods */

	std::string Pack(std::string data[]);

	int getRank();

	int getPrevRank();
	
	int getNextRank();	

	int getWorldSize();
private:

	mpi::environment _environment;
	mpi::communicator _communicator;

};

#include "test-boost.inl"
#endif
