#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "sys/time.h"
#include "string.h"

#define PAGE_SIZE 4*1024

int main(int argc, char * argv[])
{

	char file_name[100];
	char *buf;
	FILE *fp;
	unsigned long loop_size = 1;
	int i = 0;
	unsigned long req_size = 1 * 1024;
	unsigned long long file_size = 0;
	struct timeval tv0, tv1;
	struct timezone tz0, tz1;
	double time;

	int ret;

	if(argc != 4){
		printf("Command format: %s file_name req_size(KB) file_size\n", argv[0]);
		exit(0);
	}

	strcpy(file_name, argv[1]);
	fp = fopen(file_name, "w");
	if(fp == NULL){
		printf("Error: cannot open %s\n", file_name);
		exit(1);
	}

	req_size = atoi(argv[2]) * 1024;
	file_size = (unsigned long long) atoi(argv[3]) * PAGE_SIZE;
	buf = (char *) malloc(sizeof(char) * req_size);

	loop_size = ( file_size + req_size ) / req_size - 1;
	
	ret = gettimeofday(&tv0, &tz0);
	if(ret)
		printf("Fail to get time!\n");
	
	for(i = 0; i < loop_size; i++){
		fseek(fp, req_size*i, SEEK_SET);
		fwrite(buf, req_size, 1, fp);		
	}

	ret = gettimeofday(&tv1, &tz1);
        if(ret)
                printf("Fail to get time!\n");
	
	time = ((tv1.tv_sec - tv0.tv_sec) * 1000000 + tv1.tv_usec - tv0.tv_usec) * 1.0 / 1000000;
	printf("Running time : %f s, I/O write throughput : %f MB/s\n", time, file_size * 1.0 / (time * 1024 * 1024));
	free(buf);
	fclose(fp);

	return 0;
}
