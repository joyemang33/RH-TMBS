g++ main.cpp -o main -O2
g++ validator.cpp -o val -O2
g++ test.cpp -o test -O2
# ./test ../datasets/epinions.txt 4 25 C > result1.txt
# ./test ../datasets/epinions.txt 4 25 T > result2.txt
./test ../datasets/epinions.txt 4 25 p > result3.txt
# ./test ../datasets/epinions.txt 32 25 C > result4.txt
# ./test ../datasets/epinions.txt 32 25 T > result5.txt
./test ../datasets/epinions.txt 32 25 p > result6.txt

# ./test ../datasets/wikiconflict.txt 4 25 C > result7.txt
# ./test ../datasets/wikiconflict.txt 4 25 T > result8.txt
./test ../datasets/wikiconflict.txt 4 25 p > result9.txt
# ./test ../datasets/wikiconflict.txt 32 25 C > result10.txt
# ./test ../datasets/wikiconflict.txt 32 25 T > result11.txt
./test ../datasets/wikiconflict.txt 32 25 p > result12.txt
