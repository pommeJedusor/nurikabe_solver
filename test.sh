#!/bin/bash

normal_check(){
    FILE=$1
    FILENAME=$(basename $FILE)
    echo "${FILENAME}"
    if [ "$CHECK_FOR_MEMORY_LEAKS" = true ] ; then
	    valgrind -q --error-exitcode=1 --exit-on-first-error=yes --leak-check=yes ./nurikabe_solver maps/$FILENAME > $TMP_DIR/$FILENAME
    else
	    ./nurikabe_solver maps/$FILENAME > $TMP_DIR/$FILENAME
    fi
    diff solutions/$FILENAME $TMP_DIR/$FILENAME
}

error_check(){
    FILE=$1
    FILENAME=$(basename $FILE)
    echo "${FILENAME}"
    if [ "$CHECK_FOR_MEMORY_LEAKS" = true ] ; then
	    valgrind -q --error-exitcode=1 --exit-on-first-error=yes --leak-check=yes ./nurikabe_solver maps/$FILENAME 1> $TMP_DIR/$FILENAME 2> $TMP_DIR/$(FILENAME)_err
    else
	    ./nurikabe_solver maps/$FILENAME  1> $TMP_DIR/$FILENAME 2> "$TMP_DIR/${FILENAME}_err"
    fi
    echo -n "" | diff - $TMP_DIR/$FILENAME
    echo "map invalid or failed to solve map" | diff - "$TMP_DIR/${FILENAME}_err"
}

#CHECK_FOR_MEMORY_LEAKS=true
CHECK_FOR_MEMORY_LEAKS=false

make re

TMP_DIR=$(mktemp -d)

for FILE in solutions/*;
do
	normal_check $FILE
done

echo "<-- error checks -->"
error_check maps/map100
error_check maps/map101
error_check maps/map102
error_check maps/map103

rm $TMP_DIR -rf
