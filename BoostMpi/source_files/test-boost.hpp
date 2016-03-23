#ifndef BOOST_TEST_
#define BOOST_TEST_

#include <string>
#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>


namespace mpi = boost::mpi;

class BoostTest{
public:
	BoostTest ();

	void PassMessageToNext(std::string message);
	
	std::string RecieveMessageFromPrevious();

	std::string Pack(std::string data[]);

	int getCommunicatorRank();
	

private:
	mpi::environment _environment;
	mpi::communicator _communicator;

};

#include "test-boost.inl"
#endif
