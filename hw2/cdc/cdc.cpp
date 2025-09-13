#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "./sw/stopwatch.h"

#define WIN_SIZE 16
#define PRIME 3
#define MODULUS 256
#define TARGET 0

uint64_t hash_func(unsigned char *input, unsigned int pos)
{
	// put your hash function implementation here
	uint64_t hash = 0;
	for(int i = 0; i < WIN_SIZE; i++) {
		uint64_t prime_pow = 1;
		for(int j = 0; j < i + 1; j++) {
			prime_pow *= static_cast<uint64_t>(PRIME);
		}
		hash += static_cast<uint64_t>(input[pos + WIN_SIZE - 1 - i]) * prime_pow;
	}
	return hash;
}

void cdc(unsigned char *buff, unsigned int buff_size)
{
	// put your cdc implementation here
	for(int i = WIN_SIZE; i<buff_size-WIN_SIZE; i++) {
		if(hash_func(buff, i) % MODULUS == TARGET) {
			printf("%d", i);
		}
	}
}

void cdc_new(unsigned char *buff, unsigned int buff_size)
{
    if (buff_size < 2u * WIN_SIZE) {return;}

    unsigned long long p_pow_w1 = 1;
    for (int k = 0; k < WIN_SIZE + 1; ++k) {
		p_pow_w1 *= PRIME;
	}

    unsigned long long h = hash_func(buff, WIN_SIZE);
    for (unsigned int i = WIN_SIZE; i < buff_size - WIN_SIZE; ++i) {
        if ((h % MODULUS) == TARGET) {
            printf("%u", i);
        }

        if (i + 1 < buff_size - WIN_SIZE) {
            unsigned char out_b = buff[i];
            unsigned char in_b  = buff[i + WIN_SIZE];
            h = h * PRIME - (unsigned long long)out_b * p_pow_w1 + (unsigned long long)in_b  * PRIME;
        }
    }
}



void test_cdc( const char* file )
{
	FILE* fp = fopen(file,"r" );
	if(fp == NULL ){
		perror("fopen error");
		return;
	}

	fseek(fp, 0, SEEK_END); // seek to end of file
	int file_size = ftell(fp); // get current file pointer
	fseek(fp, 0, SEEK_SET); // seek back to beginning of file

	unsigned char* buff = (unsigned char *)malloc((sizeof(unsigned char) * file_size ));	
	if(buff == NULL)
	{
		perror("not enough space");
		fclose(fp);
		return;
	}

	int bytes_read = fread(&buff[0],sizeof(unsigned char),file_size,fp);
	stopwatch time_cdc;
	stopwatch time_cdc_new;

	time_cdc.start();
	cdc(buff, file_size);
	time_cdc.stop();

	time_cdc_new.start();
	cdc_new(buff, file_size);
	time_cdc_new.stop();

	printf("\ncdc time: %f ns\n", time_cdc.latency());
	printf("cdc_new time: %f ns\n", time_cdc_new.latency());

    free(buff);
    return;
}

int main()
{
	test_cdc("prince.txt");
	return 0;
}