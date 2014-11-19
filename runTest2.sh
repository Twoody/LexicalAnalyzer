
# testall.sh : unit testing for kestrel compiler
#   author: members of the Venture group

# run this from the main project directory or it won't work very well!

TESTDIR="test_stuff/progs/"
TESTLEX="./testlex"
TESTPARSE="testparse"

# lexical tests
#   compares output of ./testlex < progs/*.k
#   to the expected output in progs/%.lex
#   if differences are found, says so and leaves behind progs/%.ldiff
printf "Making testlex\n"
make testlex
printf "\n\n"

echo "LEXICAL"
for l in $TESTDIR*.lex
do
  f=${l/%.lex/.k}
  o=${l/%.lex/.ltest}
  d=${l/%.lex/.ldiff}
  echo -n "$f."
  $TESTLEX < $f > $o
  echo -n "."
  diff -U 0 $o $l > $d
  c=$(grep -v ^@ $d | wc -l)
  rm $o
  if [ $c -eq 0 ]; then
    echo .good!
    rm $d
  else
    echo ".bad! $c differences"
  fi
done

make clean
# parser tests
#  compares output of ./testparse < test/*.k
#  to the expected output in test/%.par
echo
echo "PARSER"
echo "nothing to test yet!"
exit
      
