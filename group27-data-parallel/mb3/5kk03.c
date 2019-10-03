#include <hw_dma.h>
#include <global_memmap.h>
#include "structures.h"
#include "stdarg.h"
#include "5kk03.h"

DMA dma = {0, mb3_dma0_BASEADDR};
volatile unsigned int *dma_mem = (unsigned int*) (mb3_dmamem0_BASEADDR);
volatile unsigned int dram_offset = 0;
volatile unsigned int dma_offset = 0;
volatile unsigned int read_offset = 0;
volatile unsigned int flag = 1;
volatile unsigned count = 0;
volatile int offset = 0;

  TIME t1, t2;

void my_fprintf ( FILE *stream, char *d, ... )
{
#ifdef PC
    va_list list;
    va_start ( list, d );
    vfprintf ( stream, d, list );
    va_end ( list );
#endif
}

unsigned int FGETC ( JPGFile *fp )
{
    offset = fp->vld_count - flag;

    if(offset != 0) {
        dram_offset = fp->vld_count/4;
        dma_offset = 0;

        count = 0;
        read_offset = fp->vld_count%4; 

        hw_dma_receive(&dma_mem[dma_offset], &fp->data[dram_offset], 128, &dma, NON_BLOCKING);
        while(hw_dma_status(&dma));
        dram_offset += 128;
    }

    if(offset == 0 && count%128 == 0) {
        hw_dma_receive(&dma_mem[dma_offset], &fp->data[dram_offset], 32, &dma, NON_BLOCKING);
        dram_offset += 32;
        dma_offset = (dma_offset + 32)%128;
    }

    unsigned int c = ( ( dma_mem[((count+read_offset) / 4)%128] << ( 8 * ( 3 - ( fp->vld_count % 4 ) ) ) ) >> 24 ) & 0x00ff;
    fp->vld_count++;
    count++;
    flag = fp->vld_count;
    return c;

    /*dram_offset = fp->vld_count/4;
    hw_dma_receive(&dma_mem[dma_offset], &fp->data[dram_offset], 1, &dma, BLOCKING);
    unsigned int c = ( ( dma_mem[0] << ( 8 * ( 3 - ( fp->vld_count % 4 ) ) ) ) >> 24 ) & 0x00ff;
    fp->vld_count++;
    return c;
    */
}

int FSEEK ( JPGFile *fp, int offset, int start )
{
    fp->vld_count += offset + ( start - start );    /* Just to use start... */
    return 0;
}

size_t FTELL ( JPGFile *fp )
{
    return fp->vld_count;
}
