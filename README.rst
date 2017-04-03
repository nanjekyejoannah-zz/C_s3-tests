#S3 Compatibility Tests

This is a set of completely unofficial Amazon AWS S3 compatibility tests, that will hopefully be useful to people implementing software that exposes an S3-like API.

The tests use the Google C++ Testing Framework. 

You need to create your configuration file with the location of the service , and one set of credentials. Copy config.cfg.sample and edit accordingly. 

#TODo

Ensure a reasonable subset of tests implemented in [python s3_tests](https://github.com/ceph/s3-tests) is implemented.