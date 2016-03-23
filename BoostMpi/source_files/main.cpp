#include "test-boost.hpp"


int main(){
	BoostTest obj;

	obj.PassMessageToNext("Hello from " + obj.getCommunicatorRank());

	std::string message = obj.RecieveMessageFromPrevious();

	std::cout << "Message Recieved : '" << message << "'" << std::endl;

	return 0;
}
