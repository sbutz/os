#!/bin/sh

if [ $# -eq 0 ]; then
	echo "Usage: ./finfo.sh [...files]"
	exit 1
fi

while [ $# -ge 1 ]; do
	echo "------------------------------"

	mtime=$(stat $1 --format="%X")
	ftime=$(date -d @$mtime +'%H:%M')

	if [ -d $1 ]; then
		echo "Letzte Aenderung: $ftime $1"
	else
		echo "Ordner: $ftime $1"
	fi
	stat $1 --format="Rechte: %A"
	stat $1 --format "Groesse: %B"
	stat $1 --format="Besitzer: %U"
	stat $1 --format="Gruppe: %G"
	ftime=$(date -d @$mtime +'%b %d')
	echo "Letzte Aenderung: $ftime"

	shift
done
echo "------------------------------"
