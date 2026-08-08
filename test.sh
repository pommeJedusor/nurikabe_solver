#!/bin/bash

make re

TMP_DIR=$(mktemp -d)

for FILE in solutions/*;
do
	FILENAME=$(basename $FILE)
	./nurikabe_solver maps/$FILENAME > $TMP_DIR/$FILENAME
	echo "${FILENAME}"
	diff solutions/$FILENAME $TMP_DIR/$FILENAME
done

rm $TMP_DIR -rf
