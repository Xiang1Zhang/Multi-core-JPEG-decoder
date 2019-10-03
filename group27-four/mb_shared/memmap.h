#ifndef MEMMAP_H
#define MEMMAP_H

// actor: vld
#define MB3_FIFO_WC_to1  	  (int*)(mb3_dmamem0_BASEADDR+192*sizeof(int))
#define MB3_FIFO_RWC_to1 	  (int*)(mb1_cmemin0_pt_REMOTEADDR+sizeof(int))
#define MB3_FIFO_RC_to1  	  (int*)(mb3_cmem0_BASEADDR)
#define MB3_FIFO_RRC_to1  	  (int*)(NULL)
#define MB3_FIFO_BUFFER_to1   (int*)(mb3_dmamem0_BASEADDR+192*sizeof(int)+sizeof(int))
#define MB3_FIFO_RBUFFER_to1  (int*)(mb1_cmemin0_pt_REMOTEADDR+2*sizeof(int))

#define MB3_FIFO_WC_to2  	  (int*)(mb3_dmamem0_BASEADDR+192*sizeof(int)+sizeof(int)+sizeof(From3_to_1))
#define MB3_FIFO_RWC_to2 	  (int*)(mb2_cmemin0_pt_REMOTEADDR+sizeof(int))
#define MB3_FIFO_RC_to2  	  (int*)(mb3_cmem0_BASEADDR+sizeof(int))
#define MB3_FIFO_RRC_to2  	  (int*)(NULL)
#define MB3_FIFO_BUFFER_to2   (int*)(mb3_dmamem0_BASEADDR+192*sizeof(int)+2*sizeof(int)+sizeof(From3_to_1))
#define MB3_FIFO_RBUFFER_to2  (int*)(mb2_cmemin0_pt_REMOTEADDR+2*sizeof(int))

#define MB3_FIFO_WC_to4  	  (int*)(mb3_dmamem0_BASEADDR+192*sizeof(int)+2*sizeof(int)+sizeof(From3_to_1)+sizeof(From3_to_2))
#define MB3_FIFO_RWC_to4 	  (int*)(mb4_cmemin0_pt_REMOTEADDR+sizeof(int))
#define MB3_FIFO_RC_to4  	  (int*)(mb3_cmem0_BASEADDR+2*sizeof(int))
#define MB3_FIFO_RRC_to4  	  (int*)(NULL)
#define MB3_FIFO_BUFFER_to4   (int*)(mb3_dmamem0_BASEADDR+192*sizeof(int)+3*sizeof(int)+sizeof(From3_to_1)+sizeof(From3_to_2))
#define MB3_FIFO_RBUFFER_to4  (int*)(mb4_cmemin0_pt_REMOTEADDR+2*sizeof(int))

#define MB3_FIFO_WC_c         (int*)(mb3_cmemin0_BASEADDR+3*sizeof(int))
#define MB3_FIFO_RWC_c        (int*)(NULL)
#define MB3_FIFO_RC_c     	  (int*)(mb3_dmamem0_BASEADDR+192*sizeof(int)+3*sizeof(int)+sizeof(From3_to_1)+sizeof(From3_to_2)+sizeof(From3_to_4))
#define MB3_FIFO_RRC_c    	  (int*)(mb2_cmemin0_pt_REMOTEADDR+2*sizeof(int)+2*sizeof(From3_to_2))
#define MB3_FIFO_BUFFER_c     (int*)(mb3_dmamem0_BASEADDR+192*sizeof(int)+4*sizeof(int)+sizeof(From3_to_1)+sizeof(From3_to_2)+sizeof(From3_to_4))
#define MB3_FIFO_RBUFFER_c    (int*)(mb2_cmemin0_pt_REMOTEADDR+4*sizeof(int)+2*sizeof(From3_to_2))

// core 1
#define MB1_FIFO_WC_c  	      (int*)(mb1_cmem0_BASEADDR+sizeof(int))
#define MB1_FIFO_RWC_c 	      (int*)(NULL)
#define MB1_FIFO_RC_c  	      (int*)(mb1_cmem0_BASEADDR)
#define MB1_FIFO_RRC_c 	      (int*)(mb3_cmemin0_pt_REMOTEADDR)
#define MB1_FIFO_BUFFER_c     (int*)(mb1_cmem0_BASEADDR+2*sizeof(int))
#define MB1_FIFO_RBUFFER_c    (int*)(NULL)

// mmio write from core1 to 4
/*#define MB1_FIFO_WC_p  	      (int*)(mb1_cmem0_BASEADDR+3*sizeof(int)+2*sizeof(From3_to_1))
#define MB1_FIFO_RWC_p 	      (int*)(mb4_cmemin0_pt_REMOTEADDR+3*sizeof(int)+2*sizeof(From3_to_4))
#define MB1_FIFO_RC_p  	      (int*)(mb1_cmem0_BASEADDR+2*sizeof(int)+2*sizeof(From3_to_1))
#define MB1_FIFO_RRC_p 	      (int*)(NULL)
#define MB1_FIFO_BUFFER_p     (int*)(mb1_cmem0_BASEADDR+4*sizeof(int)+2*sizeof(From3_to_1))
#define MB1_FIFO_RBUFFER_p    (int*)(mb4_cmemin0_pt_REMOTEADDR+4*sizeof(int)+2*sizeof(From3_to_4))*/

// dma read from core1 to 4
#define MB1_FIFO_WC_p  	      (int*)(mb1_cmem0_BASEADDR+3*sizeof(int)+2*sizeof(From3_to_1))
#define MB1_FIFO_RWC_p 	      (int*)(mb4_cmemin0_pt_REMOTEADDR+3*sizeof(int)+2*sizeof(From3_to_4))
#define MB1_FIFO_RC_p  	      (int*)(mb1_cmem0_BASEADDR+2*sizeof(int)+2*sizeof(From3_to_1))
#define MB1_FIFO_RRC_p 	      (int*)(NULL)
#define MB1_FIFO_BUFFER_p     (int*)(mb1_cmem0_BASEADDR+4*sizeof(int)+2*sizeof(From3_to_1))
#define MB1_FIFO_RBUFFER_p    (int*)(NULL)

// core 2
#define MB2_FIFO_WC_c  	      (int*)(mb2_cmem0_BASEADDR+sizeof(int))
#define MB2_FIFO_RWC_c 	      (int*)(NULL)
#define MB2_FIFO_RC_c  	      (int*)(mb2_cmem0_BASEADDR)
#define MB2_FIFO_RRC_c        (int*)(mb3_cmemin0_pt_REMOTEADDR+sizeof(int))
#define MB2_FIFO_BUFFER_c     (int*)(mb2_cmem0_BASEADDR+2*sizeof(int))
#define MB2_FIFO_RBUFFER_c    (int*)(NULL)

#define MB2_FIFO_WC_p  	      (int*)(mb2_cmem0_BASEADDR+3*sizeof(int)+2*sizeof(From3_to_2))
#define MB2_FIFO_RWC_p 	      (int*)(mb3_cmemin0_pt_REMOTEADDR+3*sizeof(int))
#define MB2_FIFO_RC_p  	      (int*)(mb2_cmem0_BASEADDR+2*sizeof(int)+2*sizeof(From3_to_2))
#define MB2_FIFO_RRC_p        (int*)(NULL)
#define MB2_FIFO_BUFFER_p     (int*)(mb2_cmem0_BASEADDR+4*sizeof(int)+2*sizeof(From3_to_2))
#define MB2_FIFO_RBUFFER_p    (int*)(NULL)


// core 4
#define MB4_FIFO_WC_c3  	  (int*)(mb4_cmem0_BASEADDR+sizeof(int))
#define MB4_FIFO_RWC_c3 	  (int*)(NULL)
#define MB4_FIFO_RC_c3  	  (int*)(mb4_cmem0_BASEADDR)
#define MB4_FIFO_RRC_c3 	  (int*)(mb3_cmemin0_pt_REMOTEADDR+2*sizeof(int))
#define MB4_FIFO_BUFFER_c3    (int*)(mb4_cmem0_BASEADDR+2*sizeof(int))
#define MB4_FIFO_RBUFFER_c3   (int*)(NULL)

// mmio write from core1 to 4 
/*#define MB4_FIFO_WC_c1  	  (int*)(mb4_cmem0_BASEADDR+3*sizeof(int)+2*sizeof(From3_to_4))
#define MB4_FIFO_RWC_c1 	  (int*)(NULL)
#define MB4_FIFO_RC_c1  	  (int*)(mb4_cmem0_BASEADDR+2*sizeof(int)+2*sizeof(From3_to_4))
#define MB4_FIFO_RRC_c1 	  (int*)(mb1_cmemin0_pt_REMOTEADDR+2*sizeof(int)+2*sizeof(From3_to_1))
#define MB4_FIFO_BUFFER_c1    (int*)(mb4_cmem0_BASEADDR+4*sizeof(int)+2*sizeof(From3_to_4))
#define MB4_FIFO_RBUFFER_c1   (int*)(NULL)*/

// dma read from core1 to 4
#define MB4_FIFO_WC_c1  	  (int*)(mb4_cmem0_BASEADDR+3*sizeof(int)+2*sizeof(From3_to_4))
#define MB4_FIFO_RWC_c1 	  (int*)(NULL)
#define MB4_FIFO_RC_c1  	  (int*)(mb4_dmamem0_BASEADDR+64*sizeof(int))
#define MB4_FIFO_RRC_c1 	  (int*)(mb1_cmemin0_pt_REMOTEADDR+2*sizeof(int)+2*sizeof(From3_to_1))
#define MB4_FIFO_BUFFER_c1    (int*)(mb4_dmamem0_BASEADDR+64*sizeof(int)+sizeof(int))
#define MB4_FIFO_RBUFFER_c1   (int*)(mb1_cmemin0_pt_REMOTEADDR+4*sizeof(int)+2*sizeof(From3_to_1))

#endif

