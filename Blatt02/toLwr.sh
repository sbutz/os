#!/bin/sh

debug=0
if [ $1 = '-d' ]; then
	debug=1
	shift;
fi

if [ $# -eq 0 ]; then
	echo "Usage: ./toLwr.sh [-d] [...file]"
fi

while [ $# -ge 1 ]; do
	name=$(echo $1 | tr '[:upper:]' '[:lower:]')

	if [ -f $1 ]; then
		echo "$1 -> $name"
		if [ $debug -eq 0 ]; then
			$(mv $1 $name)
		fi
	else
		echo "File not found: $1"
	fi

	shift 1
done
