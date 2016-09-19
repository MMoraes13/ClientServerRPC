#!/bin/sh
a=0
while [ $a -lt 10 ]
do
START_TIME=`echo $(($(date +%s%N)/1000000))`
./client 192.168.136.128 4000
END_TIME=`echo $(($(date +%s%N)/1000000))`
ELAPSED_TIME=$(($END_TIME - $START_TIME))
echo $ELAPSED_TIME
if [ $a -eq 10 ]
then
  break
fi
a=`expr $a + 1`
done