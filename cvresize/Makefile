PC=\
	opencv4

CXXFLAGS=\
	-std=c++11\
	-Wall\
	-Ofast\
	-Iinclude\
	-DDISABLE_RUST_SUPPORT\
	`pkg-config --cflags $(PC)`

LDFLAGS=\
	`pkg-config --libs $(PC)`

CPP=\
	$(shell ls src/cvresize/*.cpp)
O=$(CPP:%.cpp=%.o)

BIN=resize

$(BIN): $(O) 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(BIN)
	find . -name '*.o' -delete
