#---------------------------------#
#             Grupo 3             #
#    Marcos Germano,  nº 69721    #
#    Rafael Baltazar, nº 70116    #
#---------------------------------#

## NORMALIZE THE CORPORA
cat pt/pt.txt | sed -r 's/(.*)/\L\1/g' | sed -r 's/[<>]//g' | sed -r 's/^(.*)$/<<\1>/g' | sed -r 's/([^ ])([().:,;/%-+"“”])/\1 \2/g' | sed -r 's/([().:,;/%-+"“”])([^ ])/\1 \2/g' | sed -r 's/([().:,;/%-+"“”]) ([>])$/\1\2/g' > pt/ptNOR.txt;
cat en/en.txt | sed -r 's/(.*)/\L\1/g' | sed -r 's/[<>]//g' | sed -r 's/^(.*)$/<<\1>/g' | sed -r 's/([^ ])([().:,;/%-+"“”])/\1 \2/g' | sed -r 's/([().:,;/%-+"“”])([^ ])/\1 \2/g' | sed -r 's/([().:,;/%-+"“”]) ([>])$/\1\2/g' > en/enNOR.txt;
cat fr/fr.txt | sed -r 's/(.*)/\L\1/g' | sed -r 's/[<>]//g' | sed -r 's/^(.*)$/<<\1>/g' | sed -r 's/([^ ])([().:,;/%-+"“”])/\1 \2/g' | sed -r 's/([().:,;/%-+"“”])([^ ])/\1 \2/g' | sed -r 's/([().:,;/%-+"“”]) ([>])$/\1\2/g' > fr/frNOR.txt;
cat de/de.txt | sed -r 's/(.*)/\L\1/g' | sed -r 's/[<>]//g' | sed -r 's/^(.*)$/<<\1>/g' | sed -r 's/([^ ])([().:,;/%-+"“”])/\1 \2/g' | sed -r 's/([().:,;/%-+"“”])([^ ])/\1 \2/g' | sed -r 's/([().:,;/%-+"“”]) ([>])$/\1\2/g' > de/deNOR.txt;
cat it/it.txt | sed -r 's/(.*)/\L\1/g' | sed -r 's/[<>]//g' | sed -r 's/^(.*)$/<<\1>/g' | sed -r 's/([^ ])([().:,;/%-+"“”])/\1 \2/g' | sed -r 's/([().:,;/%-+"“”])([^ ])/\1 \2/g' | sed -r 's/([().:,;/%-+"“”]) ([>])$/\1\2/g' > it/itNOR.txt;

## COUNT BIGRAMS AND TRIGRAMS
sed -nf bigramcount.sed pt/ptNOR.txt | sort | uniq -c | sort -nr | sed -r 's/[ 	]*([0-9]+) (.*)/\2\t\1/g' > pt/pt.bigrama;
sed -nf bigramcount.sed en/enNOR.txt | sort | uniq -c | sort -nr | sed -r 's/[ 	]*([0-9]+) (.*)/\2\t\1/g' > en/en.bigrama;
sed -nf bigramcount.sed fr/frNOR.txt | sort | uniq -c | sort -nr | sed -r 's/[ 	]*([0-9]+) (.*)/\2\t\1/g' > fr/fr.bigrama;
sed -nf bigramcount.sed de/deNOR.txt | sort | uniq -c | sort -nr | sed -r 's/[ 	]*([0-9]+) (.*)/\2\t\1/g' > de/de.bigrama;
sed -nf bigramcount.sed it/itNOR.txt | sort | uniq -c | sort -nr | sed -r 's/[ 	]*([0-9]+) (.*)/\2\t\1/g' > it/it.bigrama;
sed -nf trigramcount.sed pt/ptNOR.txt | sort | uniq -c | sort -nr | sed -r 's/[ 	]*([0-9]+) (.*)/\2\t\1/g' > pt/pt.trigrama;
sed -nf trigramcount.sed en/enNOR.txt | sort | uniq -c | sort -nr | sed -r 's/[ 	]*([0-9]+) (.*)/\2\t\1/g' > en/en.trigrama;
sed -nf trigramcount.sed fr/frNOR.txt | sort | uniq -c | sort -nr | sed -r 's/[ 	]*([0-9]+) (.*)/\2\t\1/g' > fr/fr.trigrama;
sed -nf trigramcount.sed de/deNOR.txt | sort | uniq -c | sort -nr | sed -r 's/[ 	]*([0-9]+) (.*)/\2\t\1/g' > de/de.trigrama;
sed -nf trigramcount.sed it/itNOR.txt | sort | uniq -c | sort -nr | sed -r 's/[ 	]*([0-9]+) (.*)/\2\t\1/g' > it/it.trigrama;

## COMPILE THE PROGRAM (with and without smoothing)
g++ -o predictor predictor.cpp;
g++ -o predictor_laplace predictor_laplace.cpp;

## TEST (with and without smoothing)
rm Resultado.txt;
touch Resultado.txt;

echo "TESTE 1 c/ alisamento" >> Resultado.txt;
echo "the score for yesterday's soccer match was 2-1 , in favor of liverpool's team ." | ./predictor_laplace >> Resultado.txt;

echo "TESTE 2 c/ alisamento" >> Resultado.txt;
echo "ich möchte dich zum abendessen einladen ." | ./predictor_laplace >> Resultado.txt;

echo "TESTE 3 c/ alisamento" >> Resultado.txt;
echo "ontem , o tribunal decidiu culpá-lo por ter assassinado toda a sua família ." | ./predictor_laplace >> Resultado.txt;

echo "TESTE 1" >> Resultado.txt;
echo "the score for yesterday's soccer match was 2-1 , in favor of liverpool's team." | ./predictor >> Resultado.txt;

echo "TESTE 2" >> Resultado.txt;
echo "ich möchte dich zum abendessen einladen ." | ./predictor >> Resultado.txt;

echo "TESTE 3" >> Resultado.txt;
echo "ontem , o tribunal decidiu culpá-lo por ter assassinado toda a sua família ." | ./predictor >> Resultado.txt;
