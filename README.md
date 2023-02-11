# numberRepresentation
This program converts any number with a base from 2 to 34 in a decimal number

operation: read the input stream for outputting the decimal value of numbers
represented in different bases. The representation has the following format:

dndn-1...d0#base

Where:

  #             signal that just after this, there is a sequence of decimal
                digits ('0'..'9') representing the base (always in decimal)
                of the starting digit sequence (dndn-1...d0 )

  base          a sequence of decimal digits ('0'..'9') representing the base
                The base must be any value from 2 up to 36


  dndn-1..d0    A sequence of character digits, in each one dx must
                represent a valid digit for the base. For bases greater than
                10 (up or lower case) letter are used, in alphabetic order,
                'A' (or 'a') represents digit value 10;
                'B' (or 'b') represents digit value 11;
                 .
                 .
                'Z' (or 'z') represents digit value 34;
