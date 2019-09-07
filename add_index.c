/*
 * description: 为数据包打上序号
 * author:	zxy
 * email:	1004958034@qq.com
 * version:	1.0
 * history:	first draft
 * date:	2018/09/06
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 4096
#define PCAP_HEAD   24
#define DATA_HEAD   16
#define DEBUG

#define SWAP32(n)			\
	((((n) & 0x000000FF) << 24) |	\
	 (((n) & 0x0000FF00) << 8)  |	\
	 (((n) & 0x00FF0000) >> 8)  |	\
	 (((n) & 0xFF000000) >> 24)	\
	)

int main(int argc, char* argv[])
{
	FILE* inFile;
	FILE* outFile;
	unsigned int count    = 0;
	unsigned char* pdata  = NULL;
	unsigned int fileSize = 0;
	unsigned int curPos   = 0;
	unsigned int pktlen   = 0;
	
	if(argc != 3)
	{
		printf("program description: number the packet, the goal is sort.\n");
		printf("usage:%s inFileName outFileName\n", argv[0]);
		return -1;
	}
	pdata = (unsigned char*)malloc(BUFFER_SIZE);
	memset(pdata, 0, BUFFER_SIZE);

	inFile = fopen(argv[1], "rb");
	outFile = fopen(argv[2], "wb");
	if(inFile == NULL || outFile == NULL)
	{
		printf("error:file open failed.\n");
		return -1;
	}
	
	//get file size
	fseek(inFile, 0, SEEK_END);
	fileSize = ftell(inFile);
	rewind(inFile);
	
	//read file of pcap head
	fread(pdata, PCAP_HEAD, 1, inFile);
	fwrite(pdata, PCAP_HEAD, 1, outFile);
	curPos += PCAP_HEAD;
	
	//read per packet data
	while(curPos < fileSize)
	{
		count++;
		fread(pdata, DATA_HEAD, 1, inFile);
		memcpy(&pktlen, pdata + 8, 4);
#ifdef DEBUG
		printf("pktlen = %d\n", pktlen);
#endif
		fwrite(pdata, DATA_HEAD, 1, outFile);
		curPos += DATA_HEAD;
		
		fread(pdata, pktlen, 1, inFile);
		memset(pdata + pktlen - 4, 0, 4);
		*((unsigned int*)(pdata + pktlen - 4)) = SWAP32(count);
		fwrite(pdata, pktlen, 1, outFile);
		curPos += pktlen;
	}
	free(pdata);
	pdata = NULL;
	fclose(inFile);
	fclose(outFile);
	return 0;
}
