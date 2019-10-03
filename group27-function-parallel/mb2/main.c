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

SubHeader1 sh1;
PBlock pbout[10];

int main (void)
{
	// Enable stack checking.
	start_stack_check();

    int dma_num = 0;
 
	FCB *fcb_from3 = fifo_add(
		MB2_FIFO_WC_c3,
		MB2_FIFO_RC_c3,
		MB2_FIFO_RWC_c3,
		MB2_FIFO_RRC_c3,
		MB2_FIFO_BUFFER_c3,
		MB2_FIFO_RBUFFER_c3,
		4,
		sizeof(From3_to_2),
		1,1,
	    dma_num,
		1,
		0,
		0);

	FCB *fcb_from1 = fifo_add(
		MB2_FIFO_WC_c1,
		MB2_FIFO_RC_c1,
		MB2_FIFO_RWC_c1,
		MB2_FIFO_RRC_c1,
		MB2_FIFO_BUFFER_c1,
		MB2_FIFO_RBUFFER_c1,
		4,
		sizeof(From1_to_2),
		1,1,
	    dma_num,
		1,
		0,
		0);

	FCB *fcb_to4 = fifo_add(
		MB2_FIFO_WC_p4,
		MB2_FIFO_RC_p4,
		MB2_FIFO_RWC_p4,
		MB2_FIFO_RRC_p4,
		MB2_FIFO_BUFFER_p4,
		MB2_FIFO_RBUFFER_p4,
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
	for ( int i = 235929; i < 471859; i++ ){
		output_mem[i] = 0xFFFFFF00;
	}

	fifo_set_consumption_token_rate(fcb_from3, 1);
	fifo_set_consumption_token_rate(fcb_from1, 1);
	fifo_set_production_token_rate(fcb_to4, 1);

    while(1)
    {
		while(!fifo_check_data(fcb_from3));
        volatile From3_to_2 *sp_from3 = fifo_claim_data(fcb_from3);
		fifo_pull(fcb_from3);
		sh1 = sp_from3->sh1;
		volatile int leftover = sp_from3->leftover;
		fifo_release_space(fcb_from3);

		while(!fifo_check_data(fcb_from1));
        volatile From1_to_2 *sp_from1 = fifo_claim_data(fcb_from1);
		fifo_pull(fcb_from1);
		memcpy( &pbout, &sp_from1->pbout, 10*sizeof(PBlock) );
		fifo_release_space(fcb_from1);

		while(!fifo_check_space(fcb_to4));
        volatile From2_to_4 *sp_to4 = fifo_claim_space(fcb_to4);
        cc( &sp_from3->sh1, &(sp_from1->pbout[0]), &sp_to4->cbout); 
		fifo_push(fcb_to4);
		fifo_release_data(fcb_to4);

        if ( leftover == 0 ){
            break;
        }
    }

  
  t2 = hw_tifu_systimer_get();
  TIME diff = t2-t1;
  mk_mon_debug_info((int)(LO_64(diff)/50000));
  
	// Signal the monitor we are done.
	mk_mon_debug_tile_finished();
	return 0; 
}
