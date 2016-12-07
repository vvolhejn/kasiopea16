requires the input to be rid of lines with numbers; must end with newline
>>>>>>>>>>
,[
  read line
  ----------[++++++++++>>>>>>>>>>,----------]
  <<<<<<<<<<  back to the beginning
  >>+         set the condition cell to true so that the loop is performed
  [[-] do
    <<[<<<<<<<<<<]>>>>>>>>>> go to beginning
    [for each input character
      [->+>>+<<<]>[-<+>]
      >>>>+>
      [-]++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ compare with 65 to check if the character is a letter (65=A)
      >>[-]+<<<<<<
      <[-]+
      [ a loop that compares two numbers by decreasing them while both are nonzero
        [-]>[-]++ prepare condition
        >-[<->>]>[<]         sub 1 if a gt 0
        >>-[<<<<->>>>>]>[<]  sub 1 if b gt 0
        <<<<<
        <+>[<->[-]]< negate condition; if it is not 0 then one of the numbers must be 0
      ]
      >> if this cell is nonzero the character is a letter
      <+>[<->[-]]+< make a negation
      [>-<[-]]>     if nonletter do this (now unused; used to print the character)
      [[-]          otherwise rotate
        <<<
        find out if the character is A
        [->+>+<<]>[-<+>]>
        -----------------------------------------------------------------
        <+>[<->[-]]<
        [-<++++++++++++++++++++++++++>] if then A add 26
        <- rotate by one
        >>>
      ]
      >>>>>>> go to next character of line
    ]
    <<<<<<<<<<[->+>+<<]>[-<+>]> check if the last character is R by copying it and subtracting 82 (ASCII code of R)
    ----------------------------------------------------------------------------------
  ] while the last character is not R
  <<[<<<<<<<<<<]>>>>>>>>>>[.>>>>>>>>>>]++++++++++.[-]>>>>>>>>>> print the line when done
,] stop when the file ends (must end with a newline)