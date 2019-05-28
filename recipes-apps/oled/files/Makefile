all: oled

oled: oled.o
	$(CC) -o oled oled.o $(LDFLAGS)

oled.o: oled.c
	$(CC) $(CFLAGS) -c oled.c

clean:
	rm -f *.o
