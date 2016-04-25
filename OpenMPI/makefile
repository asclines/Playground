#Compiler macros
CC=mpic++
FLAGS=-std=c++11

#Includes
IN_MPI=-I /usr/include/openmpi

#Locations
LIB=-L /usr/lib/x86_64-linux-gnu


#Directories
SRC=source_files
T_SRC=/home/alexander/GitRepos/MyRepos.d/Flamingo/dataframe/transporter/source_files
OUT=out

#Objects
O_OPENCLASS=$(OUT)/openclass.o
O_T=$(OUT)/transporter.o

#Files
F_OPENCLASS=$(SRC)/openclass.*
F_T=$(T_SRC)/transporter.*


program: $(SRC)/main.cpp $(O_OPENCLASS)
	$(CC) $(O_OPENCLASS) $(SRC)/main.cpp -o $(OUT)/program-openclass $(IN_MPI)

transporter: $(SRC)/tmain.cpp $(O_T)
	$(CC) $(FLAGS) $(O_T) $(SRC)/tmain.cpp -o $(OUT)/program-transporter $(IN_MPI)

$(O_OPENCLASS): $(F_OPENCLASS)
	$(CC) $(IN_MPI) -c $(SRC)/openclass.cpp $(FLAGS) -o $@

$(O_T): $(F_T)
	$(CC) $(FLAGS) $(IN_MPI) -c $(T_SRC)/transporter.cpp -o $@
