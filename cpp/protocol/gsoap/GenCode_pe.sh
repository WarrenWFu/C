#!/bin/sh

if [ $# -lt 1 ];then
	echo "`basename $0` wsdlfiles"
	exit 1
fi


# ---------------------------------------------
# -- 此脚本用于从wsdl生成c++框架代码(服务端)
# ---------------------------------------------

# 请修改配置
# ---------------------------------------------

# gSOAP路径
# ----------------
gSOAPDir="/mnt/winshared/it/tmp/something/gsoap-2.8"

# 服务WSDL,一般放在当前目录
# ----------------
#WSDLFile=zyccbIbsService.wsdl
WSDLFile=$@

# 不需修改
# ----------------
ImportDir=$gSOAPDir/import

# gSOAP二进制(soapcpp2/wsdl2h)路径,看情况
# ----------------
gSOAPBinDir=$gSOAPDir/bin/linux386

# 生成的框架代码放在哪里?
# ----------------
AutoGenDir=./autoGenDir

# 生成的代码及文件前缀字符, 默认为ns_
# ----------------



# 和WSDL中的definitions/targetNamespace保持一致
# ----------------
#targetNamespace="http://www.example.org/"$var"/"
# ---------------------------------------------
# 配置到此结束
# ---------------------------------------------
#echo $targetNamespace
echo 1. 初始化环境
# ---------------------------------------------
#在linux中开发不需要以下两行
#export PATH=$PATH:$gSOAPBinDir
#chmod +x $gSOAPBinDir/*  2>/dev/null
mkdir -p $AutoGenDir 2>/dev/null
for file in $WSDLFile
do
echo $file | awk '{print substr($0,0,index($0,".")-1)}' | while read var
do
varPrefix=$var
targetNamespace="http://www.cmbc.com.cn/pes/"$var"/"
echo $varPrefix = "$targetNamespace" >> typemap.dat
done
done

echo $PATH
echo 2. 编译wsdl至.h
# ---------------------------------------------
wsdl2h -f -t typemap.dat -o $AutoGenDir/serviceInternal.h $WSDLFile


echo "3. 编译.h至服务端框架代码(客户端可选, 去掉-S同时生成客户端代码)"
# ---------------------------------------------
soapcpp2 -S -L -I"$ImportDir" -d "$AutoGenDir" -j -w -x typemap.dat  $AutoGenDir/serviceInternal.h


# 清理现场, 删除一些不需要的文件
# ---------------------------------------------
rm -f typemap.dat > /dev/null
rm -f $AutoGenDir/*.nsmap > /dev/null
rm -f $AutoGenDir/serviceInternal.h > /dev/null
echo "如果上面显示(Compilation successful), 则代码已生成在 $AutoGenDir, 按回车退出"





