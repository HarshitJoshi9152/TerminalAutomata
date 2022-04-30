CC=gcc
CFLAGS=-Wall -g -O3 -fshort-enums
O_DIR=../build


SRC = main.c term.c draw.c
_OBJ = $(SRC:.c=.o)
OBJ = $(patsubst %,$(O_DIR)/%,$(_OBJ))


auto: $(OBJ)
	$(CC) $(CFLAGS) -o $(O_DIR)/auto $(OBJ)

# convert all .c to .o in build dir
$(O_DIR)/%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(O_DIR)/*.o $(O_DIR)/auto
