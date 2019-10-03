#include <comik.h>
#include <global_memmap.h>
#include <5kk03-utils.h>
#include <fifo.h>
#include <memmap.h>
#include <hw_dma.h>

#include "fifo_structures.h"
#include "structures.h"
#include "actors.h"

volatile unsigned int *output_mem = (unsigned int*) shared_pt_REMOTEADDR;
volatile unsigned int *shared_mem = (unsigned int*) (shared_pt_REMOTEADDR + 4*1024*1024);
volatile unsigned char *remote_buffer = (unsigned int*) (shared_pt_REMOTEADDR + 4*1024*1024 + 512*1024);

From3_to_4 local;
From1_to_4 local_from1;
ColorBuffer cbout;
PBlock pbout[10];

int main (void)
{
	// Enable stack checking.
	start_stack_check();

    int dma_num = 1;
    hw_declare_dmas(1);
	hw_dma_add(1, (int*) mb4_dma0_BASEADDR);
 
	FCB *fcb_from3 = fifo_add(
		MB4_FIFO_WC_c3,
		MB4_FIFO_RC_c3,
		MB4_FIFO_RWC_c3,
		MB4_FIFO_RRC_c3,
		MB4_FIFO_BUFFER_c3,
		MB4_FIFO_RBUFFER_c3,
		2,
		sizeof(From3_to_4),
		1,1,
	    0,
		1,
		0,
		0);

	FCB *fcb_from1 = fifo_add(
		MB4_FIFO_WC_c1,
		MB4_FIFO_RC_c1,
		MB4_FIFO_RWC_c1,
		MB4_FIFO_RRC_c1,
		MB4_FIFO_BUFFER_c1,
		MB4_FIFO_RBUFFER_c1,
		3,
		sizeof(From1_to_4),
		1,1,
	    dma_num,
		1,
		0,
		0);

	// Sync with the monitor.
	mk_mon_sync();

  TIME t1, t2;
  t1 = hw_tifu_systimer_get(); 

    // Paint it our 'group' color so we can identify it.
	for ( int i = 629145; i < 786432; i++ ){
		output_mem[i] = 0xFFFFFF00;
	}

	fifo_set_consumption_token_rate(fcb_from3, 1);
	fifo_set_consumption_token_rate(fcb_from1, 1);
    local.sh2.leftover = 3;
    local_from1.sh2.leftover = -1;

    while(1)
    {
        if ( local.sh2.leftover >= 3 ){
		    while(!fifo_check_data(fcb_from3));
            volatile From3_to_4 *sp_from3 = fifo_claim_data(fcb_from3);
		    fifo_pull(fcb_from3);
            local = *sp_from3;
		    fifo_release_space(fcb_from3);

            for ( int i = 0; i < 10 ; i++ )
            {
                FBlock fbout;
                iqzz( &(local.fv[i]), &fbout);
                idct( &fbout, &(pbout[i]));
            }
            cc( &local.sh1, &(pbout[0]), &cbout);
            raster( &local.sh2, &cbout );
        }

        if(fifo_check_data(fcb_from1))  {
            volatile From1_to_4 *sp_from1 = fifo_claim_data(fcb_from1);
		    fifo_pull(fcb_from1);
            local_from1 = *sp_from1;
		    fifo_release_space(fcb_from1);
            cc( &local_from1.sh1, &(local_from1.pbout[0]), &cbout);
            raster( &local_from1.sh2, &cbout );
        }

        if ( local_from1.sh2.leftover == 0 || local_from1.sh2.leftover == 1 || local_from1.sh2.leftover == 2){
            break;
        }

    }

  
  t2 = hw_tifu_systimer_get();
  TIME diff = t2-t1;
  mk_mon_debug_info((int)(LO_64(diff)/120000));
  
	// Signal the monitor we are done.
	mk_mon_debug_tile_finished();
	return 0; 
}
