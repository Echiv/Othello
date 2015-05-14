CC=g++

TARGET = Othello

$(TARGET): AI_Mis_Can.cpp Board.cpp State.cpp Driver.cpp

	$(CC) Othello.cpp Board.cpp State.cpp Driver.cpp -o $(TARGET)

clean:

	rm -rf Othello