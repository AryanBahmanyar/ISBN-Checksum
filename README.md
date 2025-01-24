# isbn-checksum
A command-line program that validates an ISBN (International Standard Book Number) based on its check digit (last digit), or calculates and prints the check digit if it's omitted. An ISBN is a unique 10-digit or 13-digit number that is assigned to each publication, including separate editions of the same book, for identifying them in databases. ISBN-13 is the newer standard and always starts with the digits 978. The last digit in both ISBN-10 and ISBN-13 is the check digit which validates the ISBN based on a formula utilizing the other digits.

## Calculating ISBN-10 check digit
For a number with digits $x_{i}$, the general formula is:  
$A = 10x_{1} + 9x_{2} + 8x_{3} + 7x_{4} + 6x_{5} + 5x_{6} + 4x_{7} + 3x_{8} + 2x_{9}$

The check digit is then:  
$(11 - (A \mod 11)) \mod 11$

The check digit in ISBN-10 is always between 0 and 10. For a single digit, use that digit as the check digit, and for 10, use X.

## Calculating ISBN-13 check digit
For a number with digits $x_{i}$, the general formula is:  
$A = x_{1} + x_{3} + x_{5} + x_{7} + x_{9} + x_{11}$  
$B = (x_{2} + x_{4} + x_{6} + x_{8} + x_{10} + x_{12}) \times 3$

The check digit is then:  
$(10 - (A + B) \mod 10) \mod 10$

The check digit in ISBN-13 is always between 0 and 9.
