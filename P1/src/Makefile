# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)

default: fgets quicksort_sencers quicksort_flotants quicksort_doubles quicksort_len quicksort_cmp quicksort_last

# Create all executable files
fgets: fgets.o
	gcc fgets.o -o fgets

quicksort_sencers: quicksort_sencers.o fgets.o
	gcc quicksort_sencers.o -o quicksort_sencers

quicksort_flotants: quicksort_flotants.o fgets.o
	gcc quicksort_flotants.o -o quicksort_flotants

quicksort_doubles: quicksort_doubles.o fgets.o
	gcc quicksort_doubles.o -o quicksort_doubles

quicksort_len: quicksort_len.o fgets.o
	gcc quicksort_len.o -o quicksort_len

quicksort_cmp: quicksort_cmp.o fgets.o
	gcc quicksort_cmp.o -o quicksort_cmp

quicksort_last: quicksort_last.o fgets.o
	gcc quicksort_last.o -o quicksort_last

# Creating object files
fgets.o: fgets.c
	gcc -c -Wall -Werror fgets.c

quicksort_sencers.o: quicksort_sencers.c
	gcc -c -Wall -Werror quicksort_sencers.c

quicksort_flotants.o: quicksort_flotants.c
	gcc -c -Wall -Werror quicksort_flotants.c

quicksort_doubles.o: quicksort_doubles.c
	gcc -c -Wall -Werror quicksort_doubles.c


quicksort_len.o: quicksort_len.c
	gcc -c -Wall -Werror quicksort_len.c

quicksort_cmp.o: quicksort_cmp.c
	gcc -c -Wall -Werror quicksort_cmp.c

quicksort_last.o: quicksort_last.c
	gcc -c -Wall -Werror quicksort_last.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) fgets quicksort_sencers quicksort_flotants quicksort_doubles quicksort_len quicksort_cmp quicksort_last *.o *~

