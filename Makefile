CC = gcc
CFLAGS = -std=c99

tst: memfile.h tst_data.h
	$(CC) -o tst $(CFLAGS) main.c memfile.c tst_data.c

.PHONY: clean
clean:
	rm tst
