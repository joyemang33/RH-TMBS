g++ main.cpp -o main -O2
g++ validator.cpp -o val -O2
g++ test.cpp -o test -O2
./test ../datasets/ method1 > result1.txt
./test ../datasets/ method3 > result3.txt
./test ../datasets/ method4 > result4.txt
