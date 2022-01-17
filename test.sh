#bin.sh

Assert(){
	INPUT="$1"
	EXPECT="$2"

	ACTUAL=$(cc2 "$INPUT" > test.s && gcc test.s)

	if [ "$ACTUAL" = "$EXPECT"  ]
	then
		echo "$INPUT" => "ACTUAL"
	else
		echo "input : $INPUT"
		echo "expect : $EXPECT"
		echo "actual : $ACTUAL"
		exit 1
	fi
}

gcc cc2.c -o cc2.c

echo "test begin"



echo "-------------------"
echo "---test all pass---"
echo "-------------------"
