#!/bin/bash

function repairExtras() {
	echo "Reparando las librerias..."
	ROOT=$(pwd)
	cd $ROOT/extras/aabbTree > /dev/null
	make clean > /dev/null
	make > /dev/null
	cp ./bin/libaabbtree.dll $ROOT/lib > /dev/null
	cd $ROOT/extras/ter-terrain > /dev/null
	make clean > /dev/null
	make > /dev/null
	cp ./bin/libterterrain.dll $ROOT/lib > /dev/null
	echo "Finalizado"
}

repairExtras