CC=gcc
CFLAGS=-Wall -g
O_DIR=../build


_OBJ = main.o term.o
OBJ = $(patsubst %,$(O_DIR)/%,$(_OBJ))


auto: $(OBJ)
	$(CC) $(CFLAGS) -o $(O_DIR)/auto

# convert all .c to .o in build dir
$(O_DIR)/%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $(O_DIR)/$@ $<

clean:
	rm $(O_DIR)/*.o $(O_DIR)/auto
