#!/bin/bash

function repairExtrasfun() {
	ROOT=$(pwd)
	unameOut="$(uname -s)"
	echo "Reparando las librerias..."
	# Compila aabbTree
	cd $ROOT/extras/aabbTree > /dev/null
	case "${unameOut}" in
		Linux*)
			echo "Recompilando aabbTree para Linux"
			make -f LinMakefile clean > /dev/null
			make -f LinMakefile > /dev/null
			cp ./bin/libaabbtree.so $ROOT/lib/linux > /dev/null
		;;
		MINGW*)
			echo "Recompilando aabbTree para Windows"
			make -f WinMakefile clean > /dev/null
			make -f WinMakefile > /dev/null
			cp ./bin/libaabbtree.dll $ROOT/lib/mingw64 > /dev/null
		;;
		*) echo "UNKNOWN:${unameOut}";;
	esac
	# Compila ter-terrain
	cd $ROOT/extras/ter-terrain > /dev/null
	case "${unameOut}" in
		Linux*)
			echo "Recompilando ter-terrain para Linux"
			make -f LinMakefile clean > /dev/null
			make -f LinMakefile > /dev/null
			cp ./bin/libterterrain.so $ROOT/lib/linux > /dev/null
		;;
		MINGW*)
			echo "Recompilando ter-terrain para Windows"
			make -f WinMakefile clean > /dev/null
			make -f WinMakefile > /dev/null
			cp ./bin/libterterrain.dll $ROOT/lib/mingw64 > /dev/null
		;;
		*) echo "UNKNOWN: ${unameOut}";;
	esac
	echo "Finalizado"
}

function cleanfun() {
	unameOut="$(uname -s)"
	case "${unameOut}" in
		Linux*)
			echo "Limpiando el proyecto en Linux"
			make -f LinMakefile clean
		;;
		MINGW*)
			echo "Limpiando el proyecto en Windows"
			make -f WinMakefile clean
		;;
		*) echo "UNKNOWN: ${unameOut}";;
	esac
}

function makefun() {
	unameOut="$(uname -s)"
	case "${unameOut}" in
		Linux*)
			echo "Compilando el proyecto para Linux"
			make -f LinMakefile -j$1
		;;
		MINGW*)
			echo "Compilando el proyecto para Windows"
			make -f WinMakefile -j$1
		;;
		*) echo "UNKNOWN: ${unameOut}";;
	esac
}

function execfun() {
	unameOut="$(uname -s)"
	case "${unameOut}" in
		Linux*)
			echo "Ejecutando el proyecto para Linux"
			export LD_LIBRARY_PATH=./lib/linux:$LD_LIBRARY_PATH
			./bin/ThrivingColony
		;;
		MINGW*)
			echo "Ejecutando el proyecto para Windows"
			export PATH=./lib/mingw64:$PATH
			./bin/ThrivingColony.exe
		;;
		*) echo "UNKNOWN: ${unameOut}";;
	esac
}

case "$1" in
	clean)
		cleanfun
	;;
	make)
		makefun $2
	;;
	makeclean)
		cleanfun
		makefun $2
	;;
	repair)
		repairExtrasfun
	;;
	exec)
		execfun
	;;
	*) echo "Comando desconocido: ${unameOut}";;
esac