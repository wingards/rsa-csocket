FROM ubuntu:latest
MAINTAINER wing

COPY . .

ARG ENV

RUN apt-get update
RUN apt-get -y install build-essential
RUN make install
RUN make
RUN chmod +x entry.sh
CMD /bin/bash ./entry.sh
