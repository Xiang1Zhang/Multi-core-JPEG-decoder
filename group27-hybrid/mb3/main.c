#include <comik.h>
#include <global_memmap.h>
#include <5kk03-utils.h>
#include <fifo.h>
#include <memmap.h>
#include <hw_dma.h>
#include <string.h>

#include "fifo_structures.h"
#include "structures.h"
#include "actors.h"

volatile unsigned int *output_mem = (unsigned int*) shared_pt_REMOTEADDR;
volatile unsigned int *shared_mem = (unsigned int*) (shared_pt_REMOTEADDR + 4*1024*1024);
volatile unsigned char *remote_buffer = (unsigned int*) (shared_pt_REMOTEADDR + 4*1024*1024 + 512*1024);

FValue fv_to1[10];
FValue fv_to2[10];
SubHeader1 sh1_to1;
SubHeader2 sh2_to1;
SubHeader1 sh1_to2;
SubHeader2 sh2_to2;

int main (void)
{
	// Enable stack checking.
    start_stack_check();

    int dma_num = 1;

    hw_declare_dmas(1);
	hw_dma_add(1, (int*) mb3_dma0_BASEADDR);

	FCB *fcb_to1 = fifo_add(
		MB3_FIFO_WC_to1,
		MB3_FIFO_RC_to1,
		MB3_FIFO_RWC_to1,
		MB3_FIFO_RRC_to1,
		MB3_FIFO_BUFFER_to1,
		MB3_FIFO_RBUFFER_to1,
		2,
		sizeof(From3_to_1),
		1,1,
		dma_num,
		1,
		0,
		0);

	FCB *fcb_to2 = fifo_add(
		MB3_FIFO_WC_to2,
		MB3_FIFO_RC_to2,
		MB3_FIFO_RWC_to2,
		MB3_FIFO_RRC_to2,
		MB3_FIFO_BUFFER_to2,
		MB3_FIFO_RBUFFER_to2,
		2,
		sizeof(From3_to_2),
		1,1,
		dma_num,
		1,
		0,
		0);

	FCB *fcb_to4 = fifo_add(
		MB3_FIFO_WC_to4,
		MB3_FIFO_RC_to4,
		MB3_FIFO_RWC_to4,
		MB3_FIFO_RRC_to4,
		MB3_FIFO_BUFFER_to4,
		MB3_FIFO_RBUFFER_to4,
		4,
		sizeof(From3_to_4),
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
	for ( int i = 471859 ; i < 629145;i++ ){
	output_mem[i] = 0xFFFFFF00;
	}

	VldHeader header;   
	// Start decoding the JPEG.
    init_header_vld ( &header, shared_mem, output_mem);

	fifo_set_production_token_rate(fcb_to1, 1);
	fifo_set_production_token_rate(fcb_to2, 1);
	fifo_set_production_token_rate(fcb_to4, 1);

    while(1)
    {
        header_vld ( &header, &header, &(fv_to1[0]), &sh1_to1, &sh2_to1  );

		while(!fifo_check_space(fcb_to1));
		volatile From3_to_1 *sp_to1 = fifo_claim_space(fcb_to1);
       	memcpy( &(sp_to1->fv), &fv_to1, 10*sizeof(FValue));
		sp_to1->leftover = sh2_to1.leftover;
		fifo_push(fcb_to1);
		fifo_release_data(fcb_to1);

        header_vld ( &header, &header, &(fv_to2[0]), &sh1_to2, &sh2_to2  );

		while(!fifo_check_space(fcb_to2));
		volatile From3_to_2 *sp_to2 = fifo_claim_space(fcb_to2);
       	memcpy( &(sp_to2->fv), &fv_to2, 10*sizeof(FValue));
		sp_to2->leftover = sh2_to1.leftover;
		fifo_push(fcb_to2);
		fifo_release_data(fcb_to2);

		while(!fifo_check_space(fcb_to4));
	    volatile From3_to_4 *sp_to4 = fifo_claim_space(fcb_to4);
       	sp_to4->sh1_to1 = sh1_to1;
       	sp_to4->sh2_to1 = sh2_to1;
       	sp_to4->sh1_to2 = sh1_to2;
       	sp_to4->sh2_to2 = sh2_to2;
		fifo_push(fcb_to4);
		fifo_release_data(fcb_to4);

    //mk_mon_debug_info(header.leftover);
        if ( header.leftover <= 0 ){
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
