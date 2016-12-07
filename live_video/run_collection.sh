#!/bin/bash
# collcect rtt text files from users

user_ip=$1
server_ip=$2
v_ip1=$3
v_ip2=$4


declare -a dests=($user_ip $v_ip1 $v_ip2)
 
mkdir -p "$user_ip" #mkdir if not exist

printf "\n============== Collecting results ==============\n"


for dest in "${dests[@]}"; do
  scp ucr_video@${dest}:rtt.txt ./$1/${dest}.txt

  cat ./$1/${dest}.txt    # latency for each connection in one group
  printf "\n"
done

# awk '{ sum += $1 } END { print sum }' $1/*   # sum of latency in one groups
