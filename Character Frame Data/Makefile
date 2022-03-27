CFLAGS = -Wall -g
CC = g++

character_frame_data: Main.o Character.o Linked_List.o
	$(CC) $(CFLAGS) -o character_frame_data main.o Character.o Linked_list.o

Main.o: main.cpp Character.h Linked_List.h
	$(CC) $(CFLAGS) -c main.cpp

Character.o: Character.h

Linked_List.o: Linked_List.h

clean:
	rm *.o
	rm character_frame_data
