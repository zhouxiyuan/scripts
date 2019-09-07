#!/usr/local/bin/python3
#coding:UTF-8
#Decription:	将64字节对齐的文本转换为32字节对齐的文本
#Author:	zxy
#Email:		1004958034@qq.com
#Version:	1.0
#History:	first draft
#Date:		2018/09/07
import sys

if len(sys.argv) != 3:
	print("usage:%s inFileName outFileName" % sys.argv[0])
	sys.exit(1)

#open file
inFile = open(sys.argv[1], "r")
outFile = open(sys.argv[2], "w")

#read a line data
line = inFile.readline()
while line:
	#if it is a link break
	if len(line) == 1:
		outFile.write("\n")
		line = inFile.readline()
		continue
	outFile.write(line[0:64]+"\n")
	outFile.write(line[64:128]+"\n")
	line = inFile.readline()

inFile.close()
outFile.close()
