#! /bin/bash

# TO TEST
# shell_loops.sh a b 'c d' e
# shell_loops.sh *
# shell_loops getopt.c bin2Hex.cpp a.out somefile.txt

# save the command line arguments
CMD_ARGS="$*"

#-----------------------------------------------------------------
# simple 
echo "---- for with a list ----"
for i in 1 2 3
do
    echo $i
done


#-----------------------------------------------------------------
# for using $*
echo
echo '---- for using $* ----'

echo Number of arguments passed is $#

for arg in $*
do
    echo $arg
done



#-----------------------------------------------------------------
# for using $@
echo
echo '---- for using $@ ----'

echo Number of arguments passed is $#

for arg in "$@"
do
    echo $arg
done



#-----------------------------------------------------------------
# for without a list
echo
echo '---- for without a list ----'

echo Number of arguments passed is $#

for arg 
do
    echo $arg
done



#-----------------------------------------------------------------
# while
echo
echo 
echo '---- while: execute when cmd returns zero ----'
echo 'note: zero means true for shell'
i=1
while [ "$i" -le 5 ]
do
    echo $i
    i=$((i+1))
done

#-----------------------------------------------------------------
# while
echo
echo 
echo '---- while: print command line args one per line -----'
while [ "$#" -ne 0 ]
do
    echo "$1"
    shift
done


#-----------------------------------------------------------------
# until
echo
echo 
echo '---- until: execute when cmd returns non-zero ----'

until [ -s ~/tmp/data.txt ]
do
    echo "waiting for ~/tmp/data.txt to have non-zero length"
    sleep 1
done
file_size=`ls -hl ~/tmp/data.txt | awk '{print $5}'`
echo "~/tmp/data.txt has size $file_size bytes"



#-----------------------------------------------------------------
# break
echo
echo 
echo '---- Breaking out of a loop -----'
echo "Now entering infinite loop. Type quit to exit out of it"

while true
do
    read cmd
    if [ "$cmd" = quit ]
    then 
        break
    else
        echo "You entered:$cmd"
    fi
done


#-----------------------------------------------------------------
# continue
echo
echo 
echo '---- Skipping the remaining commands in a loop ----'
for file in $CMD_ARGS
do
    if [ ! -e "$file" ]
    then
        echo "$file not found!"
        continue
    fi
    file_size=`ls -hl $file | awk '{print $5}'`
    echo "$file has size $file_size bytes"
done



#-----------------------------------------------------------------
# one liner for
echo
echo 
echo '---- Typing a loop on one line ----'
for i in 1 2 3 4; do echo $i; done




#-------------------------------------------------------------------
REPEATS=10
i=0
while [ $i -lt $REPEATS ]
do
    echo "----------LOOPING-----------"
    echo
    let "i+=1"
done
