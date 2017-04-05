**S3 Compatibility Tests**

This is a set of completely unofficial Amazon AWS S3 compatibility tests, that will hopefully be useful to people implementing software that exposes an S3-like API.

The tests use the Google C++ Testing Framework. 

**Compile and run the tests:**

::
	cmake CMakeLists.txt
	make
	./runTests

**TODo**

Make assertions for specific error code , error reason and error status parameters in the tests.

Ensure a reasonable subset of tests implemented in [python s3_tests](https://github.com/ceph/s3-tests) is implemented.