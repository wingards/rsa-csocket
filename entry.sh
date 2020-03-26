#!/bin/bash

./server &
sleep 1
./client 0.0.0.0

#if [ $1 = "server" ]; then
#	./server
#else
#	./client 0.0.0.0
#fi
