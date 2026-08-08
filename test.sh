#!/bin/bash

#CHECK_FOR_MEMORY_LEAKS=true
CHECK_FOR_MEMORY_LEAKS=false

make re

TMP_DIR=$(mktemp -d)

for FILE in solutions/*;
do
	FILENAME=$(basename $FILE)
	if [ "$CHECK_FOR_MEMORY_LEAKS" = true ] ; then
		valgrind -q --error-exitcode=1 --exit-on-first-error=yes --leak-check=yes ./nurikabe_solver maps/$FILENAME > $TMP_DIR/$FILENAME
	else
		./nurikabe_solver maps/$FILENAME > $TMP_DIR/$FILENAME
	fi
	echo "${FILENAME}"
	diff solutions/$FILENAME $TMP_DIR/$FILENAME
done

rm $TMP_DIR -rf
