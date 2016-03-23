#Compiler macors
CC=mpic++

#Includes
IN_MPI=-I /usr/include/mpi
INBOOST=-I /usr/include/boost 


#Locations
LIB=-L /usr/lib/x86_64-linux-gnu/



#Directories
SRC=source_files
OUT=out

boost: $(BST)/*
	$(CC) $(SRC)/main.cpp -o $(OUT)/program-boost  $(INBOOST)  -lboost_mpi -lboost_serialization	
