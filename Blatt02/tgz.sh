#!/bin/sh

if [ $# -ne 2 ]; then
	echo "Usage: ./tgz.sh DEST_FILE SOURCE_DIR"
	exit 1
fi

if [ -e $1 ]; then
	echo "Archive already exists: $1"
	exit 1
fi

if [ ! -d $2 ]; then
	echo "Source directory not found: $2"
	exit 1
fi

if [ ! -r $2 ]; then
	echo "Missing read permission: $2"
	exit 1
fi

exit $(tar -zcf $1 $2)
