#!/usr/bin/expect
set timeout 5
spawn sshfs strt@172.168.6.66:/disk/upp/strt/ /mnt/strtdev
expect ":"
send "strt\r"

