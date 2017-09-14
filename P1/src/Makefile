# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)

default: fgets quicksort_len quicksort_cmp quicksort_last

# Create all executable files
fgets: fgets.o
	gcc fgets.o -o fgets

quicksort_len: quicksort_len.o
	gcc quicksort_len.o -o quicksort_len

quicksort_cmp: quicksort_cmp.o
	gcc quicksort_cmp.o -o quicksort_cmp

quicksort_last: quicksort_last.o
	gcc quicksort_last.o -o quicksort_last

# Creating object files
fgets.o: fgets.c
	gcc -c -Wall -Werror fgets.c

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
	$(RM) fgets quicksort_len quicksort_cmp quicksort_last *.o *~

