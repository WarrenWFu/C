#!/bin/expect
#使用expect可以很方便的实现交互，这个命令广泛用于系统的维护过程中
#这两句用于接收命令行参数
#set user [lindex $argv 0]
#set passwd [lindex $argv 1]
spawn su -
expect ":"
send "123123\n"
interact

##!/bin/bash
#用这句可以达到自动修改密码的目的,但是有的命令并不能起作用，效果有限
#(echo "123123"; sleep 1; echo "tf6cyh6n"; sleep 1; echo "tf6cyh6n")|passwd


