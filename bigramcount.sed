#---------------------------------#
#             Grupo 3             #
#    Marcos Germano,  nº 69721    #
#    Rafael Baltazar, nº 70116    #
#---------------------------------#

## Command to use this script on:
## sed -nf ../bigramcount.sed fileNOR.txt | sort | uniq -c | sort -nr | sed -r 's/[ 	]*([0-9]+) (.*)/\2\t\1/g' > file.bigrama

## Label 'b'.
:b

## Copy line to 'hold space'.
h

## Get the first bigram.
s/\(..\).*/\1/

## If the last substitution succeeded, continue to label 'a'.
ta

## Here the last substitution failed. 
## It means that the line has less than four
## characters to extract a bigram, so read the next line.
b

## Label 'a'
:a

## Print.
p

## Copy 'hold space' into 'pattern space'.
g

## Delete first character, because it is not going to be read in the next loop.
s/^.//

## Goto label 'b' to repeat loop.
tb
