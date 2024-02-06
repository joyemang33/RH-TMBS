g++ main.cpp -o main -O2
g++ validator.cpp -o val -O2
g++ test.cpp -o test -O2
./test ../datasets/ > result.txt
