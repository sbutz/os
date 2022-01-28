#!/bin/sh

IN=personal
OUT=personal.sort

head -2 $IN > $OUT
tail -n +3 $IN | sort >> $OUT
