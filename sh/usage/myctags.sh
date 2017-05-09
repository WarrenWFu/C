#!/bin/bash
#应该注意enca在转换的时候可能存在修改文件的风险，转换前最好做备份
#将用gb编码的文件改成utf-8编码，将windows行结束标志 /r/n改成UNIX的/n
#将下面两个if注释掉，使用/tmp下面的文件作为临时存储文件比较规范
#if [[ $# -eq 0 ]];then
#	echo "usage:myctags FILENAME"
#	exit 1
#fi
#
#if [[ ! -z `ls | grep -w "$1"` ]];then
#	echo "FILENAME exists,change another"
#	exit 1
#fi

if [[ ! -z `ls /tmp | grep -w "myctags.tmp"` ]];then
    echo "/tmp/myctags.tmp already exists!"
    exit
fi 

#只是针对C和C++源文件进行转码，如有需要自行修改下列文件后缀
find . -type f -name "*.[ch]" > /tmp/myctags.tmp
find . -type f -name "*.[ch]pp" >> /tmp/myctags.tmp
find . -type f -name "*.[ch]xx" >> /tmp/myctags.tmp

#参数说明:针对c++增加原型tag增加类中变量和方法tag指定语言为c/c++,-L目标文件的列表文件
ctags --c++-kinds=+p --fields=+iaS --extra=+q --languages=c,c++ -L /tmp/myctags.tmp

rm -f /tmp/myctags.tmp
echo "Tags created"
