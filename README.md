# RSA-CSOCKET

Encrypt the data sending between csocket with RSA-256.

## Getting Started

Firstly, generate dynamic library by following command:
```
make install
```
Then, build executable binary file:

```
make
```
Finally, execute the server and client individually (and please do not change the order due to the csocket issue) by:
```
./server
./client
```

Also, there's another option that you could use [Docker](https://www.docker.com) to build environment and activate the program automatically for testing the program whether or not it work well:
```
docker build -t my-rsa-csocket .
docker run --rm -i -t my-rsa-csocket
```
