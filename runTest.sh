printf "Making testlex\n"
make testlex
printf "\n\n"

printf "TEST1\n"
./testlex test_stuff/test1
printf "\n\n"

printf "TEST2\n"
./testlex test_stuff/test2
printf "\n\n"

printf "TEST3\n"
./testlex test_stuff/test3
printf "\n\n"

printf "TEST4\n"
./testlex test_stuff/test4
printf "\n\n"

printf "TEST5\n"
./testlex test_stuff/test5
printf "\n\n"

printf "TEST6\n"
./testlex test_stuff/test6
printf "\n\n"

printf "TEST7\n"
./testlex test_stuff/test7
printf "\n\n"


printf "TEST_PUNCT\n"
./testlex test_stuff/punct_test
printf "\n\n"

make clean
