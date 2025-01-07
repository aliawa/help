# Info
----------------------------------------------------------------------
echo $SHELL                     # what is my shell
$SHELL --version                # what is my shell version


# Variables 
  pattern here means globbing pattern
${#var}                         # strlen(var)

${string:pos}                   # Extracts substring starting at pos.(pos starts at 0)
${string:pos:length}            # Extracts length characters starting at pos.

${string#pattern}               # Deletes shortest match of glob pattern from front
${string##pattern}              # Deletes longest match of pattern from front
${string%pattern}               # Deletes shortest match of pattern from back
${string%%pattern}              # Deletes longest match of pattern from back

${string/pattern/replace}       # Search and replace first occurance
${string//pattern/replace}      # Search and replace all occurance
${string/#pattern/replacement}  # Search and replace front part (anchor at front)
${string/%pattern/replacement}  # Search and replace back part

${VAR?"err-msg"}                # If VAR not defined display err-msg and exit
: ${VAR?}                       # err-msg is optional, using ":" command.

${VAR-default}, ${VAR:-default} # If VAR not set at all or it is set but is NULL, use default
${VAR=default}, ${VAR:=default} # If VAR not set/is NULL, set it to default
${VAR:-}                        # if VAR not set use empty string. this avoids 'VAR' is unset error from bash in [ -z "${VAR:-}" ]



--> see man zshexpn

# Regular expressions
----------------------------------------------------------------------

## match a hexadecimal number
`
[[ ! "$START_ADDR" =~ ^[0]?[xX]?[0-9A-Fa-f][0-9A-Fa-f]*$ ]]
`

## Use of capture groups
```
langRegex='(..)_(..)'
if [[ $LANG =~ $langRegex ]]
then
    echo "Your country code (ISO 3166-1-alpha-2) is ${BASH_REMATCH[2]}."
    echo "Your language code (ISO 639-1) is ${BASH_REMATCH[1]}."
else
    echo "Your locale was not recognised"
fi
```

## NOTE: dont enclose regex in quotes
```
*Wrong*     if [[ "$A" =~ "^dp.*" ]]; then  echo "yes"; fi
*Correct*   if [[ "$A" =~ ^dp.* ]]; then  echo "yes"; fi
```

## Check if string contains only numbers
`$VAR =~ ^[0-9]+$`
## Check if string contains only alphabets and numbers
`$VAR =~ ^[[:alnum:]]+$`



# Passing args to commands
----------------------------------------------------------------------

## read input by lines
ls -F | while read i; do ...; done

##  First arg of command is variable
git ls-files --others --exclude-standard | while read -r i; do cp --parents $i ~/tmp; done

## using xagrs with any argument
git ls-files --others --exclude-standard | xargs -I{} cp --parents {} ~/tmp

##  read formated string
str="ali awais street 95050 ca usa"
read _ last _ zip _ _ <<< "$str"
echo "$last, $zip"

A="State:abc"
IFS=:; read state val <<< $A






# ANSI Escape Sequences for text format and color
## Bold
echo -e "\033[1mThis is a BOLD line\033[0m"
## Underline
echo -e "\033[4mThis is a underlined line.\033[0m"

tput bold; echo "bold text"   # print bold
tput sgr0; echo "normal text" # reset to normal

## All escape sequences
http://ascii-table.com/ansi-escape-sequences-vt-100.php

## readable format
bold_on=`tput bold` 
bold_off=`tput sgr0`
hl_on=`tput smso`       # Highlight (reverse video)
hl_off=`tput rmso`      # Highlight (reverse video)
ul_on=`tput smul`       # Underline
ul_off=`tput rmul`      # Underline off
echo "this is ${bold_on}bold${bold_off} but this isn't"


# here-is document
cat << End-Of-Msg
This is line 1 of the messge
This is line 2 of the message
End-Of-Msg

## here-is document with parameter substitution turned off
cat << 'End-Of-Msg'
This is line 1: My dir is $HOME
This is line 2: cd $PTOP
End-Of-Msg


# Terminal Flow control
Ctrl-S - Stop Sending (Freeze terminal)
Ctrl-Q - Resume Sending (Unfreeze terminal)



# job control
Ctrl-z              pause job
fg %1               resume job number 1
bg %1               resume job number 1 in the background
disown %2           keep the background job running even when the shell exits
kill %2             kill job 2
kill -9 %1



# Redirect
## Redirect stdout and stderr
cmd > file.txt 2>&1
cmd &> file.txt

## Redirect only stderr
exec 2>errors.txt


## Action if command successful
cd blah && echo "success" || echo "fail"

[ -z $A ] && echo "zero" || echo "non-zero"


# see all bash defines
bash -v


# map "jk" in vi mode
$if mode=vi

    set keymap vi-command
    "jk": vi-insertion-mode

    set keymap vi-insert
    "jk": vi-movement-mode

$endif 



# history

## Previous commands complete
!:p        # show previous command but don't execute it
!!         # last command
!<word>    # last command begining with keyword. e.g !mv
!?<word>?  # last command containing keyword. e.g !?search?
!n         # command at history number n
!-n        # n number of commands before


## extract arguments from last command
!:0                   # previous command
!^, !:2, !:3, ... !$  # first, second, third ... last argument
!*                    # all arguments, synonym !:*
!:-                   # everything except the last argument


## extract arguments from earlier command
!-2:1, !-2:2 ...      # first, second ... from command before last

## resuse second argument of the command containiing keyword
ls !<keyword>:2

## execute last command with "ls" replaced by "cat"
^ls^cat^
!119:s/1.1/2.2/     # history nr 119, replace 1.1 with 2.2

## Word modifiers
h   # Remove a trailing file name component, leaving only the head.
t   # Remove all leading file name components, leaving the tail.
r   # Remove a trailing suffix of the form .xxx, leaving the basename.
e   # Remove all but the trailing suffix. 


## tips
search and replace in command line.
!#:1:s/txt/json

cut the last (Ctrl-W) word and paste it (Ctrl-Y)
Ctrl-W Ctrl-Y



# Detect, if script is running in background
  $$ = PID of current process
case $(ps -o stat= -p $$) in
    *+*) echo "Running in foreground" ;;
      *) echo "Running in background" ;;
esac



# mkdir -p examples
mkdir -p /home/john/Downloads/web
mkdir -p Downloads/{active-torrents,finished-torrents,web}
mkdir -p johnbokma.com/{branches,tags,trunk/{cgi-bin,htdocs,scripts}}



# read from file line by line
input="/path/to/txt/file"
while IFS= read -r var; do
    echo "$var"
done < "$input"


# Get user input
read -p "Continue? " -n 1 -r
echo
if [[ $REPLY =~ [Yy]$ ]];then
    <execute dangerous action>
fi

echo "Type Y to run zsh: \c"
read line
[ "$line" = Y ] && exec $HOME/bin/zsh -l



# functions

## sequence  <start> <step> <end>
for p in $(seq 10 1 19); do
done

## random number in the range 0 - 32767 
number=$RANDOM
echo "Random number less than 50: $((number % 50))"

## arithmetic expansion with let
let "end = start + num"
let "n += 3"




# Bracket expansion (Brace expansion)
mv foo-baz.txt foo-quux.txt
mv foo-{baz,quux}.txt

mv foo.txt foo-baz.txt
mv foo{,-baz}.txt

mv file.name !#:1.bak
cp process.log !#:1.old
!#:1 expands to the word with index 1

Cartesian product
$ echo {A,B}{C,D}
AC AD BC BD

echo file1.{cpp,c,h,hxx}   # produces : file1.cpp file1.c file1.h file1.hxx

## combination of brace expansion and globs
echo {/home/*,/root}/.*profile

## output: 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19
echo {0,1}{0..9}

touch {a..f}{1..5}
a1 a2 a3 a4 a5 b1 b2 b3 b4 b5 c1 c2 c3 c4 c5 e1 e2 e3 e4 e5 f1 f2 f3 f4 f5


Shell expansion
https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_03_04.html




# Builtin variables
```
$-  Flags passed to script. example [[ $- = *i* ]]
$!  PID of last background job
$_  Final argument of previous command
$?  Exit status of function,command,script
$$  PID of script, used to create unique temp files
$*  All the arguments
$@  All the script args, same as $* but considers quoted args as one
$#  Number of args
```

# Color
https://misc.flogisoft.com/bash/tip_colors_and_formatting

for i in {0..255}; do
    printf "\x1b[38;5;${i}mcolour${i}\x1b[0m\n"
done


## escape can be written as
\e[             # not recognized by zsh
\x1b[
\033[


# Command line args

## while
while [[ "$#" > 0 ]]; do
    case $1 in
        -b) BACKUP="1";shift;;
        -c) CHECK="1";shift;;
        -*) usage;exit;;
        *) break;;
    esac
done


## if
if [ "$#" -ne 1 ]; then
    echo "Usage: number digit"
    exit 1
fi

## case

case "$1"
in
    0) echo zero;;
    1) echo one;;
    3) echo three;;
    *) echo "Bad argument";;
esac

### patterns in case
with "shopt -s extglob"
	?() - zero or one occurrences of pattern
	*() - zero or more occurrences of pattern
	+() - one or more occurrences of pattern
	@() - one occurrence of pattern
	!() - anything except the pattern



## getopts
while getopts vkm:l:w:h option
do
    case "$option"
        in
        m) MAND_OPTS=$OPTARG;;
        k) KDEV=TRUE;;
        l) LANPCAP=$OPTARG;;
        w) WANPCAP=$OPTARG;;
        v) USEVALGRIND=TRUE;;
        h) usage; exit;;
       \?) echo -en "\nUsage:"; usage; exit 1;;

    esac
done

## Manual parsing (zsh)
local usage=(
        "optparsing_demo [-h|--help]"
        "optparsing_demo [-v|--verbose] [-f|--filename=<file>] [<message...>]"
        )
opterr() { echo >&2 "optparsing_demo: Unknown option '$1'" }

while (( $# )); do
    case $1 in
      --)                 shift; positional+=("${@[@]}"); break  ;;
      -h|--help)          printf "%s\n" $usage && return         ;;
      -v|--verbose)       flag_verbose=true                      ;;
      -f|--filename)      shift; filename=$1                     ;;
      -f=*|--filename=*)  filename="${1#*=}"                     ;;
      -*)                 opterr $1 && return 2                  ;;
      *)                  positional+=("${@[@]}"); break         ;;
    esac
    shift
  done



# the last argument should be the directory
if [ "$OPTIND" -gt "$#" ]
then
    echo
    echo "Missing directory!"
    usage
    exit 2
fi

# get the last argument now
shift $((OPTIND - 1))
DHOME=$1

# getopt
args=$(getopt -l st,cb: ac:fh $*)
if [ $? != 0 ]
then
    help
    exit 2
fi
set -- $args

for i; do
    case "$i" in
        -a) abort;exit;;
        -f) FETCH_MAIN=1;shift;;
        -h) help; exit;;
        -c) COMMIT_ID=$(eval echo "$2");
            shift 2;;
        --cb) COMMIT_BUGID=$(eval echo "$2");
              shift 2;;
        --st) status;exit;;
        --) shift; break;;
    esac
done



# Other
## upper case
tr '[:lower:]' '[:upper:]' <<< $VAR
echo {var^^}        # only for bash
echo {var,,}        # only for bash
echo {var:u}        # only for zsh

## length of string
${#VAR}



# Arrays
    myarray=(1 2 "three" 4 "five")      # create an arrray, Note: no comma
    myarray=($(ls backport_data*))      # create from command output
    myarray+=("six")                    # append new element to array

    # Associative array
    arr2=([HDD]=Samsung [Monitor]=Dell [Keyboard]=A4Tech)
    arr1[fruit]=Mango

    echo ${#myarray[*]}                 # number of elements in array
    echo ${#myarray[@]}                 # number of elements in array

    echo ${myarray[1]}                  # retrieve first element, indices start at 1 not 0
    echo ${myarray[-1]}                 # retrieve last element
    echo ${myarray[$i]}                 # $i contains index of element to retrieve
    echo ${myarray[@]}                  # retrieve ALL elements
    echo ${myarray[*]}                  # retrieve ALL elements

                                        # copy a file into an array
    array1=( `cat "$filename" | tr '\n' ' '`) 
    array2=( "${array1[@]}" )           # copy one array to another


    unset myarray[2]                    # delete 3rd element
    unset myarray                       # delete entire array

    for f in ${myarray[@]}; do          # loop over array elements
      echo "$f"
    done

    for i in ${!myarray[@]}; do         # loop over array indices, when both indices and elements are needed.
        echo "$i:$myarray[$i]"
    done

    declare -A arr1                     # declare associative array. (may need #!/bin/zsh as first line)
    typeset -A arr1                     # same as above

    declare -a arr1                     # optionally declare an array
    local -a arr2

    cp ${~tpath[$opt]} $LOCAL_DIR       # Zsh, perform globbing on array variable



# Conditional Expressions
    man test


# Loops
    #bash/zsh
    for x in {1..10}; do echo $RANDOM; done

    # zsh
    for ((i=1;i<=10;i++)); do echo $RANDOM; done


# Tricks
    
The following will print an error message for all entries that are not existing in the filesystem, and return a nonzero value.
echo -n $PATH | xargs -d: stat -c %n
To simply check whether all elements are paths and get a return code, you can also use test:
echo -n $PATH | xargs -d: -n1 test -d

# OS specific actions in bashrc
case "$OSTYPE" in
     darwin*)
            echo "macos" ;;
      linux*)
            echo "linux" ;;
      cygwin) ;; # Windows
        bsd*) ;; # BSD
           *) ;; # Unknown
esac


# ---------------------------------------
# symbols
# ---------------------------------------

$# : number of arguments passed to the command
$* : All the arguments passed to the program

Example
echo $# arguments passed
echo they are :$*:


$? : Exit status of the last command
$1 - $9: Arguments 1 to 9 passed to the program

${10}: Argument number 10 passed to the program

[ expr ] : return 0 if expr is true and 1 if it is not
$ [ "$x1" = 5 ]
$ echo $?
0



# Types of shell

if [ "$PS1" ]; then
    # We are in interactive shell
fi

if shopt -q login_shell; then
    # We are in login shell
fi


# Configuration

When loging in through ssh, .bashrc is not sourced. You must put this in .bash_profile
if [ -f ~/.bashrc ]; then
  . ~/.bashrc
fi




# bash completion

## procedure
create file _replay_data.sh
source _replay_data.sh; PATH=$PATH:.

## complete
-W <words>
complete -W 'hello none what' replay_data.py 
replay_data.py <tab>
hello none what

-f             same as "-A file", create completion options from files in current directory
-d             same as "-A directory", create completion options from sub-directories in current directory
-X <pattern>   Remove all matching pattern from completions generated by preceding options
-X <!pattern>  Remove all not matching pattern from completions generated by preceding options
complete -f -X '!*.txt' sample_command


-F <function>  Call provided function that returns the completions in COMPREPLY array.
               Inside the function:
               $1               name of command
               $2               word being completed
               $3               preceding word
               ${COMP_WORDS[@]} All words entered so far
               $#COMP_CWORD     Index of current word in COMP_WORDS array

-o <option>    special instructions for readline library
complete -F _UseGetOpt-2 -o filenames ./UseGetOpt-2.sh




A technique to export env in bash programatically
--------------------------------------------------
eval "$(/opt/homebrew/bin/brew shellenv)"



Readline Editing
----------------------------------------------------------------------
C-a Move to the start of the line.
C-e Move to the end of the line.
M-f Move forward a word.
M-b Move backward a word.
C-l Clear the screen, reprinting the current line at the top.

C-k Kill the text from the current cursor position to the end of the line.
M-d Kill from the cursor to the end of the current word, or if between words, to the end of the next word.
C-w Kill from the cursor to the previous whitespace. 
C-y Yank the most recently killed text back into the buffer at the cursor.

ctrl u      delete to begining of line
ctrl k      delete to end of line
ctrl p      backwards in history, same as up-arrow
ctrl n      forward in history, same as down-arrow

C-xC-e  edit-and-execute-command 
    Invoke editor defined by $EDITOR on the current command line, and execute the result as shell commands.
    Emacs mode: C-xC-e
    In vi mode: ESC+v

C-r    reverse-search-history incremental backward search in history
C-s    forward-search-history incremental forward search in history
C-o    operate-and-get-next 
       Accept the current line for execution and fetch the next line relative to the current line from 
       the history for editing.  Any argument is ignored. 

C-d    delete under cursor
C-_    undo last delete
option b    back one word
option f    forward one word


Zsh word splitting and globbing upon parameter expansion
----------------------------------------------------------------------
echo $=file   perform word splitting
echo $~file   perform globbing
echo $=~file  perform both


ZSH
---------------------------------------------------------------------
quote everything in the string
print -r -- ${(q)string}
${(z)line}      split line into array
${(Q)word}      unquote word


Zsh Arrays
----------------------------------------------------------------------
print $#array           length of array
array[2]=()             delete second element in array

print ${array[(r)s*]}   first element that matches the pattern
print ${array[(R)s*]}   last element that matches the pattern
print ${array[(i)v*]}   index of first match
print ${array[(I)v*]}   index of last match
print ${(k)assoc}       print all keys of associative array
print ${(v)assoc}       print all values of associative array
print -l "${(@kv)assoc}"    print one per line


Zsh switch case
----------------------------------------------------------------------
case 0 in
    ([0-9]) print digit ;;
    ([a-zA-Z]) print letter ;;
    ([^0-9a-zA-Z]) print neither ;;
esac
