#ifndef MEMMAP_H
#define MEMMAP_H

// actor: vld
#define MB3_FIFO_WC_to1  	  (int*)(mb3_dmamem0_BASEADDR+128*sizeof(int))
#define MB3_FIFO_RWC_to1 	  (int*)(mb1_cmemin0_pt_REMOTEADDR+sizeof(int))
#define MB3_FIFO_RC_to1  	  (int*)(mb3_cmem0_BASEADDR)
#define MB3_FIFO_RRC_to1  	  (int*)(NULL)
#define MB3_FIFO_BUFFER_to1   (int*)(mb3_dmamem0_BASEADDR+129*sizeof(int))
#define MB3_FIFO_RBUFFER_to1  (int*)(mb1_cmemin0_pt_REMOTEADDR+2*sizeof(int))

#define MB3_FIFO_WC_to2  	  (int*)(mb3_dmamem0_BASEADDR+129*sizeof(int)+1*sizeof(From3_to_1))
#define MB3_FIFO_RWC_to2 	  (int*)(mb2_cmemin0_pt_REMOTEADDR+sizeof(int))
#define MB3_FIFO_RC_to2  	  (int*)(mb3_cmem0_BASEADDR+sizeof(int))
#define MB3_FIFO_RRC_to2  	  (int*)(NULL)
#define MB3_FIFO_BUFFER_to2   (int*)(mb3_dmamem0_BASEADDR+130*sizeof(int)+1*sizeof(From3_to_1))
#define MB3_FIFO_RBUFFER_to2  (int*)(mb2_cmemin0_pt_REMOTEADDR+2*sizeof(int))

#define MB3_FIFO_WC_to4  	  (int*)(mb3_dmamem0_BASEADDR+130*sizeof(int)+1*sizeof(From3_to_1)+1*sizeof(From3_to_2))
#define MB3_FIFO_RWC_to4 	  (int*)(mb4_cmemin0_pt_REMOTEADDR+sizeof(int))
#define MB3_FIFO_RC_to4  	  (int*)(mb3_cmem0_BASEADDR+2*sizeof(int))
#define MB3_FIFO_RRC_to4  	  (int*)(NULL)
#define MB3_FIFO_BUFFER_to4   (int*)(mb3_dmamem0_BASEADDR+131*sizeof(int)+1*sizeof(From3_to_1)+1*sizeof(From3_to_2))
#define MB3_FIFO_RBUFFER_to4  (int*)(mb4_cmemin0_pt_REMOTEADDR+2*sizeof(int))


// actor: IQZZ & IDCT
#define MB1_FIFO_WC_c  	      (int*)(mb1_cmem0_BASEADDR+sizeof(int))
#define MB1_FIFO_RWC_c 	      (int*)(NULL)
#define MB1_FIFO_RC_c  	      (int*)(mb1_cmem0_BASEADDR)
#define MB1_FIFO_RRC_c 	      (int*)(mb3_cmemin0_pt_REMOTEADDR)
#define MB1_FIFO_BUFFER_c     (int*)(mb1_cmem0_BASEADDR+2*sizeof(int))
#define MB1_FIFO_RBUFFER_c    (int*)(NULL)

#define MB1_FIFO_WC_p  	      (int*)(mb1_cmem0_BASEADDR+3*sizeof(int)+4*sizeof(From3_to_1))
#define MB1_FIFO_RWC_p 	      (int*)(mb2_cmem0_pt_REMOTEADDR+3*sizeof(int)+4*sizeof(From3_to_2))
#define MB1_FIFO_RC_p  	      (int*)(mb1_cmem0_BASEADDR+2*sizeof(int)+4*sizeof(From3_to_1))
#define MB1_FIFO_RRC_p 	      (int*)(NULL)
#define MB1_FIFO_BUFFER_p     (int*)(mb1_cmem0_BASEADDR+4*sizeof(int)+4*sizeof(From3_to_1))
#define MB1_FIFO_RBUFFER_p    (int*)(mb2_cmem0_pt_REMOTEADDR+4*sizeof(int)+4*sizeof(From3_to_2))

// actor: cc 
#define MB2_FIFO_WC_c3  	  (int*)(mb2_cmem0_BASEADDR+sizeof(int))
#define MB2_FIFO_RWC_c3 	  (int*)(NULL)
#define MB2_FIFO_RC_c3  	  (int*)(mb2_cmem0_BASEADDR)
#define MB2_FIFO_RRC_c3       (int*)(mb3_cmemin0_pt_REMOTEADDR+sizeof(int))
#define MB2_FIFO_BUFFER_c3    (int*)(mb2_cmem0_BASEADDR+2*sizeof(int))
#define MB2_FIFO_RBUFFER_c3   (int*)(NULL)

#define MB2_FIFO_WC_c1  	  (int*)(mb2_cmem0_BASEADDR+3*sizeof(int)+4*sizeof(From3_to_2))
#define MB2_FIFO_RWC_c1 	  (int*)(NULL)
#define MB2_FIFO_RC_c1  	  (int*)(mb2_cmem0_BASEADDR+2*sizeof(int)+4*sizeof(From3_to_2))
#define MB2_FIFO_RRC_c1       (int*)(mb1_cmemin0_pt_REMOTEADDR+2*sizeof(int)+4*sizeof(From3_to_1))
#define MB2_FIFO_BUFFER_c1    (int*)(mb2_cmem0_BASEADDR+4*sizeof(int)+4*sizeof(From3_to_2))
#define MB2_FIFO_RBUFFER_c1   (int*)(NULL)

#define MB2_FIFO_WC_p4  	  (int*)(mb2_cmem0_BASEADDR+5*sizeof(int)+4*sizeof(From3_to_2)+4*sizeof(From1_to_2))
#define MB2_FIFO_RWC_p4 	  (int*)(mb4_cmem0_pt_REMOTEADDR+3*sizeof(int)+4*sizeof(From3_to_4))
#define MB2_FIFO_RC_p4  	  (int*)(mb2_cmem0_BASEADDR+4*sizeof(int)+4*sizeof(From3_to_2)+4*sizeof(From1_to_2))
#define MB2_FIFO_RRC_p4       (int*)(NULL)
#define MB2_FIFO_BUFFER_p4    (int*)(mb2_cmem0_BASEADDR+6*sizeof(int)+4*sizeof(From3_to_2)+4*sizeof(From1_to_2))
#define MB2_FIFO_RBUFFER_p4   (int*)(mb4_cmemin0_pt_REMOTEADDR+4*sizeof(int)+4*sizeof(From3_to_4))
//#define MB2_FIFO_RBUFFER_p4   (int*)(NULL)

// actor: raster 
#define MB4_FIFO_WC_c3  	  (int*)(mb4_cmem0_BASEADDR+sizeof(int))
#define MB4_FIFO_RWC_c3 	  (int*)(NULL)
#define MB4_FIFO_RC_c3  	  (int*)(mb4_cmem0_BASEADDR)
#define MB4_FIFO_RRC_c3 	  (int*)(mb3_cmemin0_pt_REMOTEADDR+2*sizeof(int))
#define MB4_FIFO_BUFFER_c3    (int*)(mb4_cmem0_BASEADDR+2*sizeof(int))
#define MB4_FIFO_RBUFFER_c3   (int*)(NULL)

#define MB4_FIFO_WC_c2  	  (int*)(mb4_cmem0_BASEADDR+3*sizeof(int)+4*sizeof(From3_to_4))
#define MB4_FIFO_RWC_c2 	  (int*)(NULL)
#define MB4_FIFO_RC_c2  	  (int*)(mb4_cmem0_BASEADDR+2*sizeof(int)+4*sizeof(From3_to_4))
#define MB4_FIFO_RRC_c2 	  (int*)(mb2_cmemin0_pt_REMOTEADDR+4*sizeof(int)+4*sizeof(From3_to_2)+4*sizeof(From1_to_2))
#define MB4_FIFO_BUFFER_c2    (int*)(mb4_cmem0_BASEADDR+4*sizeof(int)+4*sizeof(From3_to_4))
//#define MB4_FIFO_BUFFER_c2    (int*)(mb4_dmamem0_BASEADDR)
#define MB4_FIFO_RBUFFER_c2   (int*)(NULL)

#endif

