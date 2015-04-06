CC = g++
CFLAGS = -Wall -lpthread

TARGET = router
TARGET2 = source

all: $(TARGET) $(TARGET2)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) $(TARGET).cpp -o $(TARGET)

$(TARGET2): $(TARGET2).cpp
	$(CC) $(CFLAGS) $(TARGET2).cpp -o $(TARGET2)

clean:
	$(RM) $(TARGET) 
