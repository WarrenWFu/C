#!/bin/sh
#用于将一个文件夹与一个svn文件夹同步，不要用来创建一个新的文件夹，
#最好先将svn中的文件手动拷贝到指定文件夹，这个主要用于维护 20160419
if [[ $# -ne 2 ]];then
	echo "usage:mss svnfile synfile"
	exit
fi

if [[ ! -d "$2" ]];then
	mkdir -p "$2"
fi

touch /tmp/mysvnsyn.tmp
#下面的newer的精度只能到分钟，考虑换一种方式
sleep 1m

#去掉后面跟着的/号
svnfile=`basename "$1"`
synfile=`basename "$2"`

svn update "$svnfile"

var=`find ./"$svnfile"/* -newer /tmp/mysvnsyn.tmp`

for i in $var
do
	#如果是目录则判断是否存在，不存在则创建
	if [[ -d "$i" ]];then
		direction=`echo "$i" | awk -F/ -v nd="$synfile" '{printf "./%s/",nd}{for(i=3;i<=NF;i++) {printf"%s/",$i}}'`
		if [[ ! -d $direction ]];then
			mkdir -p $direction
			echo "built $direction"
			continue
		fi
	fi
	#如果是文件，判断目录是否存在，不存在先创建目录
	direction=`dirname $i | awk -F/ -v nd="$synfile" '{printf "./%s/",nd}{for(i=3;i<=NF;i++) {printf"%s/",$i}}'`
	if [[ $direction != "./${synfile}/" ]];then
		if [[ ! -d $direction ]];then
			mkdir -p $direction
		fi
	fi
	#拷贝文件,这里应该考虑进行控制以免将修改的文件给覆盖了
	cp "$i" "$direction"
	echo "cp "$i""
	echo "to "$direction""

done

rm /tmp/mysvnsyn.tmp
