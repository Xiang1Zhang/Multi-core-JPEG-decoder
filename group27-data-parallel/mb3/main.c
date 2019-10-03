#include <comik.h>
#include <global_memmap.h>
#include <5kk03-utils.h>
#include <hw_dma.h>

#include "structures.h"
#include "actors.h"

//volatile unsigned int *DMA_mem = (unsigned int*) mb3_dmamem0_BASEADDR;
volatile unsigned int *output_mem = (unsigned int*) shared_pt_REMOTEADDR;
volatile unsigned int *shared_mem = (unsigned int*) (shared_pt_REMOTEADDR + 4*1024*1024);
volatile unsigned char *remote_buffer = (unsigned int*) (shared_pt_REMOTEADDR + 4*1024*1024 + 512*1024);

int division(int y_size){
	int i = y_size/10;
	if(i*10<y_size){
		i++;
	}

	return i;
}

TIME t1, t2;
VldHeader header;

SubHeader2 sh2;
FValue fv[10];
SubHeader1 sh1;
PBlock pbout[10];
FBlock fbout;
ColorBuffer cbout;
//int start_row = 0;
//int start_dmem = 0;
//int burst_size = 0;


int main (void)
{
    //DMA dma = {0, mb3_dma0_BASEADDR};
	// Sync with the monitor.
	mk_mon_sync();
	// Enable stack checking.
	start_stack_check();
 
  
  t1 = hw_tifu_systimer_get(); 

	// Paint it our 'group' color so we can identify it.
	for ( int i = 471859 ; i < 629145;i++ ){
		output_mem[i] = 0xFFFFFF00;
	}

    
	// Start decoding the JPEG.
    init_header_vld ( &header, shared_mem, output_mem);
	int coef =division(header.my_size);
    //start_row = 4*coef;
    //start_dmem = start_row*1024;
  mk_mon_debug_info(header.x_size);
  mk_mon_debug_info(header.y_size);
    
    while(1)
    {
        if(header.my_size < 3) {
            break;
        }

        header_vld ( &header, &header, &(fv[0]), &sh1, &sh2  );
        
		if(header.MCU_row > 4*coef && header.MCU_row <= 7*coef ){
        	for ( int i = 0; i < 10 ; i++ )
        	{
            	iqzz( &(fv[i]), &fbout);
            	idct( &fbout, &(pbout[i]));
        	}
        	
        	cc( &sh1, &(pbout[0]), &cbout);
		    raster( &sh2, &cbout );
		}

        if ( header.MCU_row == 8*coef || sh2.leftover == 0){
             break;
        }
    }


  t2 = hw_tifu_systimer_get();
  TIME diff = t2-t1;
  mk_mon_debug_info((int)((LO_64(diff)/120000)));
  
	// Signal the monitor we are done.
	mk_mon_debug_tile_finished();
	return 0;
}
