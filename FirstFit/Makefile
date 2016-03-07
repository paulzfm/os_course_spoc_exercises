CXX		= gcc
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:%.c=%.o)
CFLAGS  =
LFLAGS  =
TARGET  = ff

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *~ $(TARGET)
