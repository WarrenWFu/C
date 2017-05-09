#!/bin/sh
#应该注意enca在转换的时候可能存在修改文件的风险，转换前最好做备份
#将用gb编码的文件改成utf-8编码，将windows行结束标志 /r/n改成UNIX的/n
if [[ -z $1 ]];then
	echo "myutf8conv will convert all the files in ./ and subfolders from various formats to utf-8"
    echo "FORMAT:myutf8conv FILENAME"
    echo "FILENAME added by postfix .rep is the file to restore the result of myutf8conv"
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

#NUM=`wc -l "$1" | awk '{print $1}'`
NUM=0

#man enca中语言如果用全称大写开头的系统不认，还是用以下的简称，或者尝试小写全称
LANGUAGES=(zh cs bg et hr hu lt lv pl ru sk sl uk)

while read i
do
#dos2unix始终会打错误输出，暂时通过返回处理20160413
	dos2unix $i 2>/dev/null
	if [[ $? -ne 0 ]];then
		echo "dos2unix $i failed" >>./${1}.rep
	fi

#ascii文件和utf-8文件不用重新编码
	if [[ ! -z `file "$i" | grep -E "ASCII|UTF-8"` ]];then
		continue
	fi
	for j in ${LANGUAGES[@]}
	do
		enca -L "$j" -x utf-8 "$i" 2>>./${1}.rep
		if [[ $? -eq 0 ]];then
			if [[ "$j" != "zh" ]];then
				echo "<------------------------------$i fixed by $j------------------------------>" >>./${1}.rep
			fi
			break
		fi
        #到最后一个还是没能重新编码则记录文件
		if [[ "$j" == "uk" ]];then
			echo "<------------------------------$i can't be reencoded------------------------------>" >>./${1}.rep
		fi
	done

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

