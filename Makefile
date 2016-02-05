PROGRAM = hdr
CXXFLAGS=-I/usr/local/include `pkg-config --cflags opencv`
LDFLAGS=-L/usr/local/lib -lm `pkg-config --libs opencv`
OBJECTS=hdr.o

.SUFFIXES: .cpp .o

$(PROGRAM): $(OBJECTS)
	$(CXX)  $^  -o $(PROGRAM) $(LDFLAGS) 

.c.o:
	$(CXX) -c $(CXXFLAGS) $<

.PHONY:clean
clean:
	rm -f hdr *.o
