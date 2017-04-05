all: s3client
URI=/home/joan/uri_install/usr/local
S3_LIB=/home/joan/aws-sdk-cpp/build/aws-cpp-sdk-s3/
CORE_LIB=/home/joan/aws-sdk-cpp/build/aws-cpp-sdk-core/
S3_INCLUDE=/home/joan/aws-sdk-cpp/aws-cpp-sdk-s3/include
CORE_INCLUDE=/home/joan/aws-sdk-cpp/aws-cpp-sdk-core/include
LDFLAGS=-L$(S3_LIB) -Wl,-rpath, -L$(CORE_LIB) -L$(URI)/lib 
CXXFLAGS=-I$(S3_INCLUDE) -I$(URI)/include -I$(CORE_INCLUDE) -g
LIBS=-laws-cpp-sdk-s3 -laws-cpp-sdk-core -lnetwork-uri
s3client: s3client.o
	$(CXX) -o s3client s3client.o $(LDFLAGS) $(LIBS)
clean:
	rm -f s3client s3client.o 
