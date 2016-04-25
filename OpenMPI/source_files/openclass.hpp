#ifndef OPEN_CLASS_H
#define OPEN_CLASS_H

#include <string>

struct ProcessInfo{
	int world_size;
	int world_rank;
	std::string name;
};



class Open{
	public:
		//Constructors/Destructors
		Open();
		~Open();

		//Methods - Utils
		ProcessInfo GetProcessInfo();
		std::string GetSummary(); //For debugging use

		//Methods - MPI Operations
		std::string ScatterChar(
				char *send_data,
				int element_count, //Number of elements per processor
				int root
				); //Send same number of char elements from root process to all others

		std::string BCastChar(
				char *send_data,
				int element_count,
				int root
				); 
		

	private:

		//Methods
		void SetProcessInfo(ProcessInfo process_info);

		//Data members
		ProcessInfo process_info_;


};

#endif
