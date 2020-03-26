# RSA-CSOCKET

Encrypt the data sending between csocket with RSA-256.

## Getting Started

Firstly, generate dynamic library by following command:
```
make install
```
then, build executable binary file:

```
make
```

Also, you could use [Docker](https://www.docker.com) to build environment automatically:
```
docker build -t my-rsa-csocket .
docker run --rm -i -t my-rsa-csocket
```
