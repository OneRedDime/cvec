CC=gcc
CFLAGS=-Wall -Werror

LIB_SRC=cvec.c
LIB=libcvec.so

TEST_SRC=test.c
TEST=test

all: $(LIB) $(TEST)

$(LIB): $(LIB_SRC)
	$(CC) $(CFLAGS) -c -shared -o $@ $^ -I.

$(TEST): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $@ $^ -L. -I. -lcvec

clean:
	rm -f $(LIB) $(TEST)
