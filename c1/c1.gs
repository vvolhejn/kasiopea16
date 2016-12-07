n/{' '/ {~}%}% # parse input, creating an array of numbers for each line
-1%~ # reverse, dump onto stack
~1+:t;  # take the number of tests out of the single-element array
[]:a;
{t 1-:t}{   # for each test
  ;       # discard length information
  [[\.;]] # no idea why this works - put data about one test into single array
  a + :a; # add to array of tests
}while
10 16?:I; # infinity
a-1%{ # for each test
  ~   # dump array
  0\2$,,{;I}%++ # append and prepend dummy knights
  :k;
  :h;  # heads
  0:c; # cost
  {     # for each head
    h)    # add current head to stack
    \:h;  # save new heads
    {. k -1 =>1\-} # while current knight is taller
    {
      k)\:k;\    # add the knight to the stack
    }while
    ;c+:c; # remove head from stack, add best knight to cost
    h     # add heads to stack for evaluation
  }do
  c I<c 0~ if
  p
}%
;