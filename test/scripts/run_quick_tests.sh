#!/bin/sh

run_test() {
	printf "%-68s" "$1 $2 $3"
	$1 --size $2 --blocksize $3 >& /dev/null
	if [ $? -eq 0 ]; then
		printf "%10s\n" "[pass]"
	else 
		printf "%10s\n" "[failed]"
	fi;
}

echo -e "\nRUNNING TESTS ...";

for t in $*; do

run_test ./$t  65536  16

done

echo -e "... TESTS COMPLETE.";

