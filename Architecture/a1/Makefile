# Standard flags for compiling C programs.
CC = gcc
CFLAGS	= -std=c99 -o -Werror -Wextra -Wall

all:
	# Compile the program.
	$(CC) $(CFLAGS) a1.c -o a1

	# Run the program using the test.in file, and redirect to a file named standard_output.out
	./a1 < test.in > output.out

clean:
	# Remove the executable / output file.
	rm a1 output.out
