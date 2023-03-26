#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# TEST 1
echo -e "${NC}Test 1:"
output1=$(./tail testfile)
output2=$(tail testfile)
if [ "$output1" = "$output2" ]; then
  echo -e "${GREEN}Success: OK"
else
  echo -e "${RED}Error: TEST FAILED"
fi

# TEST 2
echo -e "${NC}Test 2:"
output1=$(./tail -n 1 testfile)
output2=$(tail -1 testfile)
if [ "$output1" = "$output2" ]; then
  echo -e "${GREEN}Success: OK"
else
  echo -e "${RED}Error: TEST FAILED"
fi

# TEST 3
echo -e "${NC}Test 3:"
output1=$(./tail -n 0 testfile 2>/dev/null)
output2=$(tail -0 testfile)
if [ "$output1" = "$output2" ]; then
  echo -e "${GREEN}Success: OK"
else
  echo -e "${RED}Error: TEST FAILED"
fi

# TEST 4
echo -e "${NC}Test 4:"
output1=$(./tail <testfile 2>/dev/null)
output2=$(tail <testfile)
if [ "$output1" = "$output2" ]; then
  echo -e "${GREEN}Success: OK"
else
  echo -e "${RED}Error: TEST FAILED"
fi

# TEST NEGATIVE NUMBER
echo -e "${NC}Test negative number:"
./tail -n -2 testfile 2>/dev/null
if [ "$?" == 1 ]; then
  echo -e "${GREEN}Success: OK"
else
  echo -e "${RED}Error: TEST FAILED"
fi

# TEST FILE DOES NOT EXIST
echo -e "${NC}Test file does not exist:"
./tail kadaoaskdas 2>/dev/null
if [ "$?" == 1 ]; then
  echo -e "${GREEN}Success: OK"
else
  echo -e "${RED}Error: TEST FAILED"
fi

# TEST WRONG ARGS
echo -e "${NC}Test wrong arguments:"
./tail -n 2>/dev/null
if [ "$?" == 1 ]; then
  echo -e "${GREEN}Success: OK"
else
  echo -e "${RED}Error: TEST FAILED"
fi


