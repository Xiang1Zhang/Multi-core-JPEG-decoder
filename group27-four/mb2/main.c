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
		MB2_FIFO_WC_c,
		MB2_FIFO_RC_c,
		MB2_FIFO_RWC_c,
		MB2_FIFO_RRC_c,
		MB2_FIFO_BUFFER_c,
		MB2_FIFO_RBUFFER_c,
		2,
		sizeof(From3_to_2),
		1,1,
	    dma_num,
		1,
		0,
		0);

	FCB *fcb_to3 = fifo_add(
		MB2_FIFO_WC_p,
		MB2_FIFO_RC_p,
		MB2_FIFO_RWC_p,
		MB2_FIFO_RRC_p,
		MB2_FIFO_BUFFER_p,
		MB2_FIFO_RBUFFER_p,
		3,
		sizeof(From2_to_3),
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
	for ( int i = 235929 ; i < 471859; i++ ){
		output_mem[i] = 0xFFFFFF00;
	}

	fifo_set_consumption_token_rate(fcb_from3, 1);
	fifo_set_production_token_rate(fcb_to3, 1);

    From3_to_2 local;
    PBlock pbout[10];

    while(1)
    {
		while(!fifo_check_data(fcb_from3));
        volatile From3_to_2 *sp_from3 = fifo_claim_data(fcb_from3);
		fifo_pull(fcb_from3);
        local = *sp_from3;
		fifo_release_space(fcb_from3);

        for ( int i = 0; i < 10 ; i++ )
        {
            FBlock fbout;
            iqzz( &(local.fv[i]), &fbout);
            idct( &fbout, &(pbout[i]));
        }

		while(!fifo_check_space(fcb_to3));
        volatile From2_to_3 *sp_to3 = fifo_claim_space(fcb_to3);
        memcpy( &(sp_to3->pbout), &pbout, 10*sizeof(PBlock));
        sp_to3->sh2 = local.sh2;
        sp_to3->sh1 = local.sh1;
        fifo_push(fcb_to3);
		fifo_release_data(fcb_to3);

        if ( local.sh2.leftover == 0 || local.sh2.leftover == 1 || local.sh2.leftover == 2){
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
