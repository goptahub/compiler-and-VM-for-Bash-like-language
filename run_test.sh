#!/bin/bash

TEST_DIR=test_sh

for test in $TEST_DIR/{while,if,test,math,nested}*.sh
do
name="${test%???}"

./sh_parser $test "$name".basm &> /dev/null
if (( $? != 0 ));then
echo "[-] $name: sh_parser failed"
continue
fi

./bvmc -ae "$name".basm |& sed '1d' > "$name".out
if (( $? != 0 ));then
echo "[-] $name: bvmc failed"
continue
fi


diff "$name".out "$name".ans &> /dev/null
if (( $? != 0 ));then
echo "[-] $name: diff failed"
continue
fi

#rm -f "$name".basm "$name".out

done &> result
