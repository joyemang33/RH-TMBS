g++ main.cpp -o main -O2
g++ validator.cpp -o val -O2
g++ testVar.cpp -o testVar -O2
./testVar ../datasets/ method1 100 > result1.txt
./testVar ../datasets/ method2 100 > result2.txt
# ./testVar ../datasets/ method3 100 > result3.txt
# ./testVar ../datasets/ method4 100 > result4.txt
