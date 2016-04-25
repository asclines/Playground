#!/bin/bash

echo "Starting"
NP=5 #Number of process for mpirun 

echo Making program
make transporter

getopts ":n:" opt;
	if [ "$opt" == n ] ; then
		NP=$OPTARG
	fi

	
echo "Running with $NP processes"
mpirun -n $NP out/program-transporter


	
		


echo Done
