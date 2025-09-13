#include "App.h"
#include "./sw/stopwatch.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE (12000 * 8000)
#define STAGES (4)

unsigned char * Data[STAGES + 1];

void Exit_with_error(void)
{
  perror(NULL);
  exit(EXIT_FAILURE);
}

void Load_data(void)
{
  FILE * File = fopen("Input.bin", "rb");
  if (File == NULL)
    Exit_with_error();

  if (fread(Data[0], 1, DATA_SIZE, File) != DATA_SIZE)
    Exit_with_error();

  if (fclose(File) != 0)
    Exit_with_error();
}

void Store_data(const char * Filename, int Stage, unsigned int Size)
{
  FILE * File = fopen(Filename, "wb");
  if (File == NULL)
    Exit_with_error();

  if (fwrite(Data[Stage], 1, Size, File) != Size)
    Exit_with_error();

  if (fclose(File) != 0)
    Exit_with_error();
}

int main()
{
  stopwatch time_total;
  stopwatch time_scale;
  stopwatch time_filter;
  stopwatch time_differ;
  stopwatch time_compress;
  for (int i = 0; i <= STAGES; i++)
  {
    // We could strictly allocate less memory for some of these buffers, but
    // that is irrelevant here.
    Data[i] = (unsigned char*)malloc(DATA_SIZE);
    if (Data[i] == NULL)
      Exit_with_error();
  }
  Load_data();
  
  time_scale.start();
  Scale(Data[0], Data[1]);
  time_scale.stop();

  time_filter.start();
  Filter(Data[1], Data[2]);
  time_filter.stop();

  time_differ.start();
  Differentiate(Data[2], Data[3]);
  time_differ.stop();

  time_compress.start();
  int Size = Compress(Data[3], Data[4]);
  time_compress.stop();

  Store_data("Output.bin", 4, Size);
  printf("Total latency of scale is: %.6f ns.\n", time_scale.latency());
  printf("Total latency of filter is: %.6f ns.\n", time_filter.latency());
  printf("Total latency of differentiate is: %.6f ns.\n", time_differ.latency());
  printf("Total latency of compress is: %.6f ns.\n\n", time_compress.latency());

  printf("Average latency of scale per loop iteration is: %.6f ns.\n", time_scale.avg_latency());
  printf("Average latency of filter per loop iteration is: %.6f ns.\n", time_filter.avg_latency());
  printf("Average latency of differentiate per loop iteration is: %.6f ns.\n", time_differ.avg_latency());
  printf("Average latency of compress per loop iteration is: %.6f ns.\n", time_compress.avg_latency());

  for (int i = 0; i <= STAGES; i++)
    free(Data[i]);

  puts("Application completed successfully.");

  return EXIT_SUCCESS;
}


