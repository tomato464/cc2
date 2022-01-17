#bin.sh

Assert(){
	INPUT="$1"
	EXPECT="$2"

	./cc2 --input "$INPUT" > test.s
	gcc test.s -o test
	./test
	ACTUAL="$?"

	if [ "$ACTUAL" = "$EXPECT"  ]
	then
		echo "$INPUT => $ACTUAL"
	else
		echo "input : $INPUT"
		echo "expect : $EXPECT"
		echo "actual : $ACTUAL"
		exit 1
	fi
}

make

echo "test begin"

Assert "62" "62"
Assert "4+5-2" "7"
Assert "30 + 12 +2 - 10" "34"
Assert "10 + 5 * 5" "35"

Assert "20 * 4 / 4 + (3 + 5) * 2" "36"
Assert "(3 + 5) / 2" "4"

echo "-------------------"
echo "---test all pass---"
echo "-------------------"
