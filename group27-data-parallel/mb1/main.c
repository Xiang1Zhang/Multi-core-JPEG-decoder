#include <comik.h>
#include <global_memmap.h>
#include <5kk03-utils.h>

#include "structures.h"
#include "actors.h"

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




int main (void)
{
	// Sync with the monitor.
	mk_mon_sync();
	// Enable stack checking.
	start_stack_check();
 
  TIME t1, t2;
  t1 = hw_tifu_systimer_get(); 

	// Paint it our 'group' color so we can identify it.
	for ( int i = 0 ; i < 235929;i++ ){
		output_mem[i] = 0xFFFFFF00;
	}

    VldHeader header;
	// Start decoding the JPEG.
    init_header_vld ( &header, shared_mem, output_mem);
	int coef =division(header.my_size);
    SubHeader2 sh2;
    while(1)
    {
        FValue fv[10];
        SubHeader1 sh1;
        header_vld ( &header, &header, &(fv[0]), &sh1, &sh2  );
        PBlock pbout[10];
		if(header.MCU_row <= 2*coef ){
        	for ( int i = 0; i < 10 ; i++ )
        	{
            	FBlock fbout;
            	iqzz( &(fv[i]), &fbout);
            	idct( &fbout, &(pbout[i]));
        	}
        	ColorBuffer cbout;
        	cc( &sh1, &(pbout[0]), &cbout);
        	raster( &sh2, &cbout );
		}

        if ( header.MCU_row > 2*coef || sh2.leftover ==0 ){
            break;
        }
    }
  
  t2 = hw_tifu_systimer_get();
  TIME diff = t2-t1;
  mk_mon_debug_info((int)((diff/50000)));
  
	// Signal the monitor we are done.
	mk_mon_debug_tile_finished();
	return 0;
}
