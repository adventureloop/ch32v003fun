#!/bin/sh

target=192.168.4.84

if [ -z $1 ]
then
	echo "no binary passed"
	exit
fi

binary=$1

echo pushing and flashing $1
scp ~/code/ch32v003fun/projects/${binary}/${binary}.bin ${target}:fw-bin/ && \
	ssh ${target} sudo ./minichlink -w ~/fw-bin/${binary}.bin flash -b
