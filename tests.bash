#!/bin/bash
echo "Tests Bash"
cd src
echo "----------------------------"
# $? = 0 se compilou bem
# $? = 2 otherwise
make 

if [ $? -eq 0 ] ; then
  echo "COMPILATION SUCCESSFUL"
  echo "Test 1 [dir]:"
  (./simpledu ../TestDir || echo $?) | sort -k2 > testeT_simpledu1.txt
  (du ../TestDir || echo $?) | sort -k2 > testeT_du1.txt
  diff -q testeT_simpledu1.txt testeT_du1.txt > /dev/null 2>&1 && echo OK || echo FAILED
  echo
  echo "Test 2 [-l dir]:"
  (./simpledu ../TestDir -l || echo $?) | sort -k2 > testeT_simpledu2.txt
  (du ../TestDir -l || echo $?) | sort -k2 > testeT_du2.txt
  diff -q testeT_simpledu2.txt testeT_du2.txt > /dev/null 2>&1 && echo OK || echo FAILED
  echo
  echo "Test 3 [-l dir -b]:"
  (./simpledu ../TestDir -l -b || echo $?) | sort -k2 > testeT_simpledu3.txt
  (du ../TestDir -l -b || echo $?) | sort -k2 > testeT_du3.txt
  diff -q testeT_simpledu3.txt testeT_du3.txt > /dev/null 2>&1 && echo OK || echo FAILED
  echo
  echo "Test 4 [-l dir -b -S]:"
  (./simpledu ../TestDir -l -b -S || echo $?) | sort -k2 > testeT_simpledu4.txt
  (du ../TestDir -l -b -S || echo $?) | sort -k2 > testeT_du4.txt
  diff -q testeT_simpledu4.txt testeT_du4.txt > /dev/null 2>&1 && echo OK || echo FAILED
  echo
  echo "Test 5 [-l dir -b -S --max-depth=2]:"
  (./simpledu ../TestDir -l -b -S --max-depth=2 || echo $?) | sort -k2 > testeT_simpledu5.txt
  (du ../TestDir -l -b -S --max-depth=2 || echo $?) | sort -k2 > testeT_du5.txt
  diff -q testeT_simpledu5.txt testeT_du5.txt > /dev/null 2>&1 && echo OK || echo FAILED
  echo
  echo "Test 6 [-l dir -B 1]:"
  (./simpledu ../TestDir -l -B 1 || echo $?) | sort -k2 > testeT_simpledu6.txt
  (du ../TestDir -l -B 1 || echo $?) | sort -k2 > testeT_du6.txt
  diff -q testeT_simpledu6.txt testeT_du6.txt > /dev/null 2>&1 && echo OK || echo FAILED
  echo
  echo "Test 7 [-l dir -a]:"
  (./simpledu ../TestDir -l -a || echo $?) | sort -k2 > testeT_simpledu7.txt
  (du ../TestDir -l -a || echo $?) | sort -k2 > testeT_du7.txt
  diff -q testeT_simpledu7.txt testeT_du7.txt > /dev/null 2>&1 && echo OK || echo FAILED
  echo
  echo "Test 8 [-l dir -a -L]:"
  (./simpledu ../TestDir -l -a -L || echo $?) | sort -k2 > testeT_simpledu8.txt
  (du ../TestDir -l -a -L || echo $?) | sort -k2 > testeT_du8.txt
  diff -q testeT_simpledu8.txt testeT_du8.txt > /dev/null 2>&1 && echo OK || echo FAILED
  echo
  echo "Test 9 [-l dir -a -B 1000 -b]:"
  (./simpledu ../TestDir -l -a -B 1000 -b || echo $?) | sort -k2 > testeT_simpledu9.txt
  (du ../TestDir -l -a -B 1000 -b || echo $?) | sort -k2 > testeT_du9.txt
  diff -q testeT_simpledu9.txt testeT_du9.txt > /dev/null 2>&1 && echo OK || echo FAILED
  echo
  echo "Test 10 [-l dir -b -a -B 1000]:"
  (./simpledu ../TestDir -l -b -a -B 1000 || echo $?) | sort -k2 > testeT_simpledu10.txt
  (du ../TestDir -l -b -a -B 1000 || echo $?) | sort -k2 > testeT_du10.txt
  diff -q testeT_simpledu10.txt testeT_du10.txt > /dev/null 2>&1 && echo OK || echo FAILED
  echo
  echo "Test 11 [-l dir -a -B 1000] (similar to TEST 6):"
  (./simpledu ../TestDir -l -a -B 1000 || echo $?) | sort -k2 > testeT_simpledu11.txt
  (du ../TestDir -l -a -B 1000 || echo $?) | sort -k2 > testeT_du11.txt
  diff -q testeT_simpledu11.txt testeT_du11.txt > /dev/null 2>&1 && echo OK || echo FAILED
  echo
  echo "Test 12 [-l dir -a -B 1024 -b]:"
  (./simpledu ../TestDir -l -a -B 1024 -b || echo $?) | sort -k2 > testeT_simpledu12.txt
  (du ../TestDir -l -a -B 1024 -b || echo $?) | sort -k2 > testeT_du12.txt
  diff -q testeT_simpledu12.txt testeT_du12.txt > /dev/null 2>&1 && echo OK || echo FAILED
  echo
  echo "Test 13 [-l dir -b -a -B 1024]:"
  (./simpledu ../TestDir -l -b -a -B 1024 || echo $?) | sort -k2 > testeT_simpledu13.txt
  (du ../TestDir -l -a -b -B 1024 || echo $?) | sort -k2 > testeT_du13.txt
  diff -q testeT_simpledu13.txt testeT_du13.txt > /dev/null 2>&1 && echo OK || echo FAILED
  
  make clean
else
  echo "COMPILATION ERROR";
fi



# Flags Possiveis:
# -a  --all               - mostra também files
# -b  --bytes             - apresenta nº de bytes em vez de blocos 
# -B  --block-size=SIZE   - define o tamanho dos blocos
# -l  --count-links       - contabiliza multiplas vezes o mesmo ficheiro
# -L  --dereference       - segue links simbolicos
# -S  --separate-dirs     - não inclui o tamanho dos subdirs
# --max-depth=N           - limita a informação exibida a N (0,1, …) níveis de profundidade de diretórios.