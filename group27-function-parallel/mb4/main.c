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

SubHeader2 sh2;
ColorBuffer cbout;

int main (void)
{
	// Enable stack checking.
	start_stack_check();
 
    int dma_num = 0;

    hw_declare_dmas(1);
	hw_dma_add(1, (int*) mb4_dma0_BASEADDR);
 
	FCB *fcb_from3 = fifo_add(
		MB4_FIFO_WC_c3,
		MB4_FIFO_RC_c3,
		MB4_FIFO_RWC_c3,
		MB4_FIFO_RRC_c3,
		MB4_FIFO_BUFFER_c3,
		MB4_FIFO_RBUFFER_c3,
		4,
		sizeof(From3_to_4),
		1,1,
	    dma_num,
		1,
		0,
		0);

	FCB *fcb_from2 = fifo_add(
		MB4_FIFO_WC_c2,
		MB4_FIFO_RC_c2,
		MB4_FIFO_RWC_c2,
		MB4_FIFO_RRC_c2,
		MB4_FIFO_BUFFER_c2,
		MB4_FIFO_RBUFFER_c2,
		4,
		sizeof(From2_to_4),
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
	fifo_set_consumption_token_rate(fcb_from2, 1);

    while(1)
    {
		while(!fifo_check_data(fcb_from3));
        volatile From3_to_4 *sp_from3 = fifo_claim_data(fcb_from3);
		fifo_pull(fcb_from3);
		sh2 = sp_from3->sh2;
		fifo_release_space(fcb_from3);

		while(!fifo_check_data(fcb_from2));
        volatile From2_to_4 *sp_from2 = fifo_claim_data(fcb_from2);
		fifo_pull(fcb_from2);
		cbout = sp_from2->cbout;
		fifo_release_space(fcb_from2);

        raster( &sh2, &cbout );

        if ( sh2.leftover == 0 ){
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
