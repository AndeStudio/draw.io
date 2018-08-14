#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

int main(int argc, char *argv[]){
	char buffer[20],//缓冲区，用于存放从文件读取的数据
		*src = argv[1],//原始文件
		*dst = argv[2],//目标文件
		*key = argv[3];//密钥

	if(src==NULL || dst==NULL || key==NULL){//检查参数
		printf("usage: xor src dst key\n");
		exit(0);
	}

	int readCount,//每次从文件中读取的字节数
		i,//循环次数
		keyLen = strlen(key);//密钥的长度

	FILE *fpSrc = fopen(src, "rb"),//原始文件与目标文件指针,以二进制方式读取/写入文件
		*fpDst = fopen(dst, "wb");

	if(fpSrc==NULL){
		printf("[%s] error\n", src);
		exit(0);
	}
	if(fpDst==NULL){
		printf("[%s] error \n", dst);
		exit(0);
	}

	//从文件中读取keyLen长度的数据，保存到buffer，直到文件结束
	while( (readCount=fread(buffer, 1, keyLen, fpSrc)) > 0 ){
		for(i=0; i<readCount; i++){
			buffer[i] ^= key[i];//对buffer中的数据逐字节进行异或运算
		}
		fwrite(buffer, 1, readCount, fpDst);//将buffer中的数据写入文件
	}

	fclose(fpSrc);
	fclose(fpDst);
	printf("success");
	return 1;
}
