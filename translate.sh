#!/bin/bash

#Decription:	将64字节对齐的文本转换为32字节对齐的文本
#Author:	zxy
#Email:		1004958034@qq.com
#Version:	1.0
#History:	first draft
#Date:		2018/09/06

if [ $# != 2 ]
then
	echo "usage:$0 inFileName outFileName"
	exit 0
fi

rm -rf $2

while read line
do
	if [ -z $line ]
	then
		echo "" >> $2
	else
		echo ${line:0:64} >> $2
		echo ${line:64:128} >> $2
	fi
done < $1
