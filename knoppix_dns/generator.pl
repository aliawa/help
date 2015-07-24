#!/usr/bin/perl
#
# Program to do the obvious
#

$a = 'Hello world';
print "$a\n";           # Print a message

$file='file.txt';
open(INFO, ">$file");   # Open for output

for ($i = 2101; $i < 2401; ++$i)     # Start with $i = 1
                                # Do it while $i < 10
                                # Increment $i before repeating
{
    $_=$i;
    @chars = split(//);
    print INFO "$chars[3].$chars[2].$chars[1].$chars[0]";
    print INFO '    60 IN NAPTR 100 10 "u" "E2U+SIP" "!^.*$!sip:';
    print INFO $_;
    print INFO '@ewn-enum-1.seiri.com:6081!".';
    print INFO "\n";
}

close(INFO);

