all: compile

compile: solution.c
	gcc -g0 -Wall -Wconversion -o solution solution.c 
	# compiler flags:
	# -g0 disable debbuging information
	# -Wall turns on most, but not all, compiler warnings
	# -Wconversion Enable implicit conversion warnings	
	# -O0 no optimization
	
	
	

clean:
	@echo "Cleaning up..."
	rm -f main.exe
	# compiler flags:
	# -f ignore non-existent files