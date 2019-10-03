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

int main (void)
{
	// Enable stack checking.
	start_stack_check();
    
    int dma_num = 0;
 
	FCB *fcb_from3 = fifo_add(
		MB1_FIFO_WC_c,
		MB1_FIFO_RC_c,
		MB1_FIFO_RWC_c,
		MB1_FIFO_RRC_c,
		MB1_FIFO_BUFFER_c,
		MB1_FIFO_RBUFFER_c,
		2,
		sizeof(From3_to_1),
		1,1,
	    dma_num,
		1,
		0,
		0);

	FCB *fcb_to4 = fifo_add(
		MB1_FIFO_WC_p,
		MB1_FIFO_RC_p,
		MB1_FIFO_RWC_p,
		MB1_FIFO_RRC_p,
		MB1_FIFO_BUFFER_p,
		MB1_FIFO_RBUFFER_p,
		2,
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
	for ( int i = 0 ; i < 235929; i++ ){
		output_mem[i] = 0xFFFFFF00;
	}

	fifo_set_consumption_token_rate(fcb_from3, 1);
	fifo_set_production_token_rate(fcb_to4, 1);

    From3_to_1 local;

    while(1)
    {
		while(!fifo_check_data(fcb_from3));
        volatile From3_to_1 *sp_from3 = fifo_claim_data(fcb_from3);
		fifo_pull(fcb_from3);
        local = *sp_from3;
		fifo_release_space(fcb_from3);

        PBlock pbout[10];
        for ( int i = 0; i < 10 ; i++ )
        {
            FBlock fbout;
            iqzz( &(local.fv[i]), &fbout);
            idct( &fbout, &(pbout[i]));
        }

		while(!fifo_check_space(fcb_to4));
        volatile From1_to_4 *sp_to4 = fifo_claim_space(fcb_to4);
        memcpy( &sp_to4->pbout, &pbout, 10*sizeof(PBlock));
		fifo_push(fcb_to4);
		fifo_release_data(fcb_to4);

    //mk_mon_debug_info(local.leftover);
        if ( local.leftover == 0 || local.leftover == 1 ){
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
