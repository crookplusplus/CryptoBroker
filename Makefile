#Authored by: Chris Rook

#UPDATING CHECKLIST
#Add object file name to objs var
#Make file set method structure ONE PER FILE

# CXX Make variable for compiler
CXX=g++
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show the necessary warning files
# -g3         include information for symbolic debugger e.g. gdb 
CXXFLAGS=-std=c++11 -Wall -g3 -c 

# object files
OBJS = main.o consumer.o log.o producer.o shared.o

# Program name
PROGRAM = cryptoexc

# The program depends upon its object files
$(PROGRAM) : $(OBJS)
	$(CXX) -o $(PROGRAM) $(OBJS) -pthread

#structure for object file creation

consumer.o : consumer.cpp consumer.h
	$(CXX) $(CXXFLAGS) consumer.cpp

shared.o : shared.cpp shared.h
	$(CXX) $(CXXFLAGS) shared.cpp

log.o : log.cpp log.h
	$(CXX) $(CXXFLAGS) log.cpp

producer.o : producer.cpp producer.h
	$(CXX) $(CXXFLAGS) producer.cpp

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp


# Once things work, people frequently delete their object files.
# If you use "make clean", this will do it for you.
# As we use gnuemacs which leaves auto save files termintating
# with ~, we will delete those as well.
clean :
	rm -f *.o *~ $(PROGRAM)