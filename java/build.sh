#!/bin/bash

if [ "$1" == "clean" ]; then
	rm -rf ./target
	exit 0
fi

if [ ! -d "./target" ]; then
	mkdir ./target
fi

javac -d ./target -cp . Programm.java

if [ "$1" == "run" ]; then
	cd ./target
	java Programm
fi

