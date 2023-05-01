## Basics 

### quotes '"' and braces '{}' are similar
puts {Hello, World - In Braces}
puts "Hello, World - In quotes" 

### inline comments
puts Hello ;# comment

### assignment
set X "some string"
set Y 1.24
set arr(1) "apple"
set arr(2) "banana"

puts X
puts arr(1)

### sustitution
puts "The current stock value is $varName" 
puts "....\n"

### no substitution
puts {The current stock value is $varName} 
puts {....\n}

### output from a command execution
set y [ set x "def"]

### Math
expr { -3 * 4 + 5}

### string 
expr { "9" eq "9.0"}
expr { $x>0? ($x+1) : ($x-1) }

    set b "blue"
    string match {b*} $b  => true 

    regexp -- {^-[0-9]$} "-22"   => True 



## functions

### user defined functions
proc sum {arg1 arg2} {
    set x [expr {$arg1 + $arg2}];
    return $x
}

#### default values and variable number of args
proc f1 {a {b 1} {c 2}} {
    puts "$a $b $c"
}
f1 3

proc f2 {a b args} {
    puts "$a $b $args"
}
f2 1 2 3 4 5 6 7



## Control

### if then else
if {$x == 1} {
    puts "x is 1"
} elseif { $x == 2 } {
    puts "x is 2"
} else { 
    puts "x is $x"
}

### switch
switch $x {
    "$z" {
        puts "matched value of z"
    }
    ONE {
        puts "matched the string \"ONE\""
    }
    1 {
        puts "matched the number \"1\""
    }
}



## Looping

### while
set x 1
while {$x < 5} {
    puts "x is $x"
    set x [expr {$x + 1}]
}

### for
for {set i 0} {$i < 10} {incr i} {
    puts "I inside first loop: $i"
}



## list

### various ways to create a list
set lst {{item 1} {item 2} {item 3}}
set lst [split "item 1.item 2.item 3" "."]
set lst [list "item 1" "item 2" "item 3"]

### list operations
puts "[lindex $lst 2]"
puts "[llength $lst]"

### list loop
foreach j $lst {
    puts $j
}


## command line args
```
set argc [llength $argv]
for {set i 0} {$i<$argc} {incr i} {
    puts "arg $i: [lindex $argv $i]"
}
```

