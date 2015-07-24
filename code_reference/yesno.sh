#!/bin/bash

yesno()
{
    while true; do
        read -p "${1} (y/n) " -n1 response ; echo
        case "$response" in
            [yY]) return 0 ;;
            [nN]) return 1 ;;
            *) echo "try again" ;;
        esac
    done
    # should never get here
    exit 42
}



if yesno "Shall I install $PACKAGENAME ?"
then
    echo "yum install $PACKAGENAME"
else
    echo "installation of $PACKAGENAME skipped"
fi
