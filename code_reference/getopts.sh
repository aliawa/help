#!/bin/bash

usage() {
    echo "   $(basename $0) [-m] [-t <value>] username"
    echo 
}



#
# getopts will populate OPTIND and OPTARG
# OPTIND: index of next argument to be processed
# OPTARG: argument of the processed option, if any
# option character followed by ":" will have an argument
# if option string starts with ":" no errors are reported
#
while getopts mt: option
do
    case "$option" in
        m) echo "m is present";;
        t) echo "t is $OPTARG";;
        *) usage; exit;;
    esac
done


#
# OPTIND will now contain the index of first non option
# parameter
#
if [ "$OPTIND" -gt "$#" ]; then
    echo "Missing user name!"
    usage
    exit 2
fi

#
# Shifting parameter by OPTIND-1 will cause $1 to
# contain the first non option parameter.
#
shift $((OPTIND-1))
echo "Username: $1"





