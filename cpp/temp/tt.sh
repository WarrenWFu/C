#! /usr/bin/expect -f 
spawn scp $1 $2
expect "*password:" 
send "upp2016\r"
expect eof
