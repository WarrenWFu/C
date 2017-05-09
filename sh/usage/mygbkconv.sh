#!/bin/sh
#应该注意enca在转换的时候可能存在修改文件的风险，转换前最好做备份
#将用gb编码的文件改成utf-8编码，将windows行结束标志 /r/n改成UNIX的/n
if [[ -z $1 ]];then
	echo "mygbkconv will convert all the C/C++ source files in ./ and subfolders from utf-8 to gbk"
    echo "FORMAT:mygbkconv FILENAME"
    echo "FILENAME added by postfix .rep is the file to restore the result of mygbkconv"
	exit 1
fi

if [[ ! -z `ls | grep -w -E "$1|${1}\.rep"` ]];then
	echo "$1 exists,change another"
	exit 1
fi

#只是针对C和C++源文件进行转码，如有需要自行修改下列文件后缀
find . -type f -name "*.[ch]" > $1
find . -type f -name "*.[ch]pp" >> $1
find . -type f -name "*.[ch]xx" >> $1

NUM=0

while read i
do
#ascii文件和utf-8文件不用重新编码
	if [[ ! -z `file "$i" | grep -E "ASCII|ISO-8859"` ]];then
		continue
	fi

    enca -L zh -x gbk "$i" 2>>./${1}.rep
    if [[ $? -ne 0 ]];then
        echo "<------------------------------$i can't be reencoded------------------------------>" >>./${1}.rep
    fi

	(( NUM=NUM + 1))
	echo $NUM 
done < $1

rm -f "$1"
if [[ -z `ls | grep -w "${1}\.rep"` ]];then
    echo "All files reencoded with no error"
    exit
fi
if [[ `du ${1}.rep | awk '{print $1}'` -eq 0 ]];then
	rm -f ${1}.rep
	echo "All files reencoded with no error"
else
	echo "Check the ${1}.rep file"
fi

