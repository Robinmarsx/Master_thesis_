How to compile:

step 1:

You need to install cmake, make, gcc, all boost libraries
You also need to install gecode: check here: https://www.gecode.org/download.html
choose "source packages", compile and install to /usr/local/

step 2:

create a directory called "build"
enter build and run command:
  cmake ..
run command:
  make


What you need to read:

Everything inside src/schedule folder. There is defination for:
	Operation: the nodes in graph
	Constraint: the edge in graph
	Descriptor: the graph
	Frame: the [t0, t1] for resource occupation
	Timetable: the vector that containing multiple Frames for one resource
	Rot: resource occupation table
	Engine: the abstract class defination for a schedule engine
	ResourcePredictEngine: The schedule engine that I have explained to you. you need to improve it.

The main function in src/exec/main.cpp

Don't read files in other directory, they are just dependency files, you don't need to care about them.
