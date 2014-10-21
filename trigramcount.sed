## Command to use this script on:
## sed -nf trigramcount.sed fileNOR.txt | sort | uniq -c | sort -nr | sed -r 's/[ 	]*([0-9]+) (.*)/\2 \1/g' > file.trigrama

## Label 'b'.
:b

## Copy line to 'hold space'.
h

## Get first bigram.
s/\(...\).*/\1/

## If last substitution succeed, continue to label 'a'.
ta

## Here last substitution failed: It means that line has less than four
## characters to extract a bigram, so read next line.
b

## Label 'a'
:a

## Print.
p

## Copy 'hold space' into 'pattern space'.
g

## Delete first character.
s/^.//

## Goto label 'b' to repeat loop.
tb
