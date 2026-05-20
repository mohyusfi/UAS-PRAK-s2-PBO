
CXX = g++

CXXFLAGS = -Wall -std=c++20

TARGET = laundry_app

SRC = src/main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o ./build/$(TARGET)

run: $(TARGET)
	./build/$(TARGET)

clean:
	rm -f $(TARGET)
