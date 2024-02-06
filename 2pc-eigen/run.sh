g++ validator.cpp -o val -O2
g++ test.cpp -o test -O2
./test eigensign > result1.txt
./test greedy_signed_degree > result2.txt
