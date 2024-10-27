/*
  Copyright (C) 2003-2024 GraphicsMagick Group

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  Bitstream benchmarks and tests.
  Written by Bob Friesenhahn, September 2003

*/

#include <magick/studio.h>
#include <magick/image.h> /* For MaxValueGivenBits() */
#include <magick/bit_stream.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ( int argc, char *argv[])
{
  const char
    *mode;

  register unsigned int
    rep,
    x;

  register unsigned char
    *bytes;

  unsigned int
    result=0;

  unsigned int
    quantum;

  FILE
    *file;

  if (argc < 2)
    {
      (void) printf("usage: %s read/write/test args\n", argv[0]);
      exit(1);
    }

  mode = argv[1];

  file=fopen("/dev/null","wb+");
  if (!file)
    {
      (void) printf("Failed to open file\n");
      exit(1);
    }

  if (strcmp(mode,"read") == 0)
    {
      BitStreamReadHandle
        read_stream;

      unsigned int
        bits;

      unsigned int
        reps;

      if (argc != 4)
        {
          (void) printf("usage: %s read repetitions bits\n", argv[0]);
          exit(1);
        }

      reps = atoi(argv[2]);
      if ((reps == 0) || (reps > INT_MAX))
        {
          (void) printf("Unreasonable reps %u!\n", reps);
          exit(1);
        }
      bits = atoi(argv[3]);
      if ((bits == 0) || (bits > 32))
        {
          (void) printf("Unreasonable bits %u!\n", bits);
          exit(1);
        }

      bytes=(unsigned char *)malloc((size_t) reps*2);
      if (!bytes)
        {
          (void) printf("Failed to allocate %lu bytes\n", (unsigned long) reps*2);
          exit(1);
        }
      for (rep=0; rep < reps*2; rep++)
        bytes[rep]=(unsigned char) rep;

      for (rep=reps; rep > 0; rep--)
        {
          MagickBitStreamInitializeRead(&read_stream,bytes);
          for (x=reps; x > 0; x--)
            {
              quantum=MagickBitStreamMSBRead(&read_stream,bits);
              result += quantum;
            }
        }

      free(bytes);
    }
  else if (strcmp(mode,"write") == 0)
    {
      BitStreamWriteHandle
        write_stream;

      unsigned int
        bits;

      unsigned int
        reps;

      if (argc != 4)
        {
          (void) printf("usage: %s write repetitions bits\n", argv[0]);
          exit(1);
        }

      reps = atoi(argv[2]);
      if ((reps == 0) || (reps > INT_MAX))
        {
          (void) printf("Unreasonable reps %u!\n", reps);
          exit(1);
        }
      bits = atoi(argv[3]);
      if ((bits == 0) || (bits > 32))
        {
          (void) printf("Unreasonable bits %u!\n", bits);
          exit(1);
        }

      bytes=(unsigned char *)calloc(reps,2);
      if (!bytes)
        {
          (void) printf("Failed to allocate %lu bytes\n", (unsigned long) reps*2);
          exit(1);
        }
      (void) memset(bytes,0,(size_t) reps*2);

      for (rep=reps; rep > 0; rep--)
        {
          MagickBitStreamInitializeWrite(&write_stream,bytes);
          for (x=reps; x > 0; x--)
            {
              MagickBitStreamMSBWrite(&write_stream,bits,x);
              result += bytes[x];
            }
        }

      free(bytes);
    }
  else if (strcmp(mode,"test") == 0)
    {
      BitStreamWriteHandle
        write_stream;

      BitStreamReadHandle
        read_stream;

      size_t
        allocated_bytes;

      unsigned long
        max_quantum_value;

      unsigned int
        bits,
        max_bits,
        read_quantum,
        write_quantum;

      if (argc != 3)
        {
          (void) printf("usage: %s test max_bits\n", argv[0]);
          exit(1);
        }

      max_bits = atoi(argv[2]);
      if ((max_bits == 0) || (max_bits > 32))
        {
          (void) printf("Unreasonable max_bits %u!\n", max_bits);
          exit(1);
        }

      for (bits=1 ; bits <= max_bits; bits++)
        {
          max_quantum_value=MaxValueGivenBits(bits);

          allocated_bytes=max_quantum_value;
          if (bits > 7)
            allocated_bytes *= 2;
          if (bits > 15)
            allocated_bytes *= 2;

          bytes=(unsigned char *)malloc(allocated_bytes);
          if (!bytes)
            {
              (void) printf("Failed to allocate %lu bytes\n",(unsigned long) allocated_bytes);
              exit(1);
            }
          else
            {
              (void) printf("Bits %02u, Allocated %lu bytes\n",bits, (unsigned long) allocated_bytes);
            }
          (void) memset(bytes,0xff,allocated_bytes);

          MagickBitStreamInitializeWrite(&write_stream,bytes);
          MagickBitStreamInitializeRead(&read_stream,bytes);

          for (write_quantum=0; write_quantum < max_quantum_value; write_quantum++)
            {
              MagickBitStreamMSBWrite(&write_stream,bits,write_quantum);
              read_quantum=MagickBitStreamMSBRead(&read_stream,bits);
              if (read_quantum != write_quantum)
                {
                  (void) printf("mismatch: bits=%u write_quantum=%u read_quantum=%u\n",
                         bits,write_quantum,read_quantum);
                }
            }

          free(bytes);
        }
    }

  (void) fprintf(file,"result=%u\n",result);
  (void) fclose(file);

  return 0;
}
