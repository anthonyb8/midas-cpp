CXX=g++
CXXFLAGS=-pthread -Wall -Wno-switch -Wno-unused-function -std=c++11 -dynamiclib -fPIC
ROOT_DIR=.
BASE_SRC_DIR=${ROOT_DIR}/src
INCLUDES=-I${ROOT_DIR}/include
TARGET=libTwsSocketClient.dylib # libTwsSocketClient.so 

$(TARGET):
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BASE_SRC_DIR)/*.cpp lib/libbid.a -o$(TARGET)

clean:
	rm -f $(TARGET) *.o

