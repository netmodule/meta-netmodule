/*
 * phy-access.c
 *
 *  Quick and dirty code to access phy register on ZE7000
 *      Author: andrey
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>



/* Register offset definitions. Unless otherwise noted, register access is
 * 32 bit. Names are self explained here.
 */
#define XEMACPS_NWCTRL_OFFSET        0x00000000 /* Network Control reg */
#define XEMACPS_NWCFG_OFFSET         0x00000004 /* Network Config reg */
#define XEMACPS_NWSR_OFFSET          0x00000008 /* Network Status reg */
#define XEMACPS_USERIO_OFFSET        0x0000000C /* User IO reg */
#define XEMACPS_DMACR_OFFSET         0x00000010 /* DMA Control reg */
#define XEMACPS_TXSR_OFFSET          0x00000014 /* TX Status reg */
#define XEMACPS_RXQBASE_OFFSET       0x00000018 /* RX Q Base address reg */
#define XEMACPS_TXQBASE_OFFSET       0x0000001C /* TX Q Base address reg */
#define XEMACPS_RXSR_OFFSET          0x00000020 /* RX Status reg */
#define XEMACPS_ISR_OFFSET           0x00000024 /* Interrupt Status reg */
#define XEMACPS_IER_OFFSET           0x00000028 /* Interrupt Enable reg */
#define XEMACPS_IDR_OFFSET           0x0000002C /* Interrupt Disable reg */
#define XEMACPS_IMR_OFFSET           0x00000030 /* Interrupt Mask reg */
#define XEMACPS_PHYMNTNC_OFFSET      0x00000034 /* Phy Maintaince reg */
#define XEMACPS_RXPAUSE_OFFSET       0x00000038 /* RX Pause Time reg */
#define XEMACPS_TXPAUSE_OFFSET       0x0000003C /* TX Pause Time reg */
#define XEMACPS_HASHL_OFFSET         0x00000080 /* Hash Low address reg */
#define XEMACPS_HASHH_OFFSET         0x00000084 /* Hash High address reg */
#define XEMACPS_LADDR1L_OFFSET       0x00000088 /* Specific1 addr low reg */
#define XEMACPS_LADDR1H_OFFSET       0x0000008C /* Specific1 addr high reg */
#define XEMACPS_LADDR2L_OFFSET       0x00000090 /* Specific2 addr low reg */
#define XEMACPS_LADDR2H_OFFSET       0x00000094 /* Specific2 addr high reg */
#define XEMACPS_LADDR3L_OFFSET       0x00000098 /* Specific3 addr low reg */
#define XEMACPS_LADDR3H_OFFSET       0x0000009C /* Specific3 addr high reg */
#define XEMACPS_LADDR4L_OFFSET       0x000000A0 /* Specific4 addr low reg */
#define XEMACPS_LADDR4H_OFFSET       0x000000A4 /* Specific4 addr high reg */
#define XEMACPS_MATCH1_OFFSET        0x000000A8 /* Type ID1 Match reg */
#define XEMACPS_MATCH2_OFFSET        0x000000AC /* Type ID2 Match reg */
#define XEMACPS_MATCH3_OFFSET        0x000000B0 /* Type ID3 Match reg */
#define XEMACPS_MATCH4_OFFSET        0x000000B4 /* Type ID4 Match reg */
#define XEMACPS_WOL_OFFSET           0x000000B8 /* Wake on LAN reg */
#define XEMACPS_STRETCH_OFFSET       0x000000BC /* IPG Stretch reg */
#define XEMACPS_SVLAN_OFFSET         0x000000C0 /* Stacked VLAN reg */
#define XEMACPS_MODID_OFFSET         0x000000FC /* Module ID reg */
#define XEMACPS_OCTTXL_OFFSET        0x00000100 /* Octects transmitted Low
						reg */
#define XEMACPS_OCTTXH_OFFSET        0x00000104 /* Octects transmitted High
						reg */
#define XEMACPS_TXCNT_OFFSET         0x00000108 /* Error-free Frmaes
						transmitted counter */
#define XEMACPS_TXBCCNT_OFFSET       0x0000010C /* Error-free Broadcast
						Frames counter*/
#define XEMACPS_TXMCCNT_OFFSET       0x00000110 /* Error-free Multicast
						Frame counter */
#define XEMACPS_TXPAUSECNT_OFFSET    0x00000114 /* Pause Frames Transmitted
						Counter */
#define XEMACPS_TX64CNT_OFFSET       0x00000118 /* Error-free 64 byte Frames
						Transmitted counter */
#define XEMACPS_TX65CNT_OFFSET       0x0000011C /* Error-free 65-127 byte
						Frames Transmitted counter */
#define XEMACPS_TX128CNT_OFFSET      0x00000120 /* Error-free 128-255 byte
						Frames Transmitted counter */
#define XEMACPS_TX256CNT_OFFSET      0x00000124 /* Error-free 256-511 byte
						Frames transmitted counter */
#define XEMACPS_TX512CNT_OFFSET      0x00000128 /* Error-free 512-1023 byte
						Frames transmitted counter */
#define XEMACPS_TX1024CNT_OFFSET     0x0000012C /* Error-free 1024-1518 byte
						Frames transmitted counter */
#define XEMACPS_TX1519CNT_OFFSET     0x00000130 /* Error-free larger than 1519
						byte Frames transmitted
						   counter */
#define XEMACPS_TXURUNCNT_OFFSET     0x00000134 /* TX under run error
						    counter */
#define XEMACPS_SNGLCOLLCNT_OFFSET   0x00000138 /* Single Collision Frame
						Counter */
#define XEMACPS_MULTICOLLCNT_OFFSET  0x0000013C /* Multiple Collision Frame
						Counter */
#define XEMACPS_EXCESSCOLLCNT_OFFSET 0x00000140 /* Excessive Collision Frame
						Counter */
#define XEMACPS_LATECOLLCNT_OFFSET   0x00000144 /* Late Collision Frame
						Counter */
#define XEMACPS_TXDEFERCNT_OFFSET    0x00000148 /* Deferred Transmission
						Frame Counter */
#define XEMACPS_CSENSECNT_OFFSET     0x0000014C /* Carrier Sense Error
						Counter */
#define XEMACPS_OCTRXL_OFFSET        0x00000150 /* Octects Received register
						Low */
#define XEMACPS_OCTRXH_OFFSET        0x00000154 /* Octects Received register
						High */
#define XEMACPS_RXCNT_OFFSET         0x00000158 /* Error-free Frames
						Received Counter */
#define XEMACPS_RXBROADCNT_OFFSET    0x0000015C /* Error-free Broadcast
						Frames Received Counter */
#define XEMACPS_RXMULTICNT_OFFSET    0x00000160 /* Error-free Multicast
						Frames Received Counter */
#define XEMACPS_RXPAUSECNT_OFFSET    0x00000164 /* Pause Frames
						Received Counter */
#define XEMACPS_RX64CNT_OFFSET       0x00000168 /* Error-free 64 byte Frames
						Received Counter */
#define XEMACPS_RX65CNT_OFFSET       0x0000016C /* Error-free 65-127 byte
						Frames Received Counter */
#define XEMACPS_RX128CNT_OFFSET      0x00000170 /* Error-free 128-255 byte
						Frames Received Counter */
#define XEMACPS_RX256CNT_OFFSET      0x00000174 /* Error-free 256-512 byte
						Frames Received Counter */
#define XEMACPS_RX512CNT_OFFSET      0x00000178 /* Error-free 512-1023 byte
						Frames Received Counter */
#define XEMACPS_RX1024CNT_OFFSET     0x0000017C /* Error-free 1024-1518 byte
						Frames Received Counter */
#define XEMACPS_RX1519CNT_OFFSET     0x00000180 /* Error-free 1519-max byte
						Frames Received Counter */
#define XEMACPS_RXUNDRCNT_OFFSET     0x00000184 /* Undersize Frames Received
						Counter */
#define XEMACPS_RXOVRCNT_OFFSET      0x00000188 /* Oversize Frames Received
						Counter */
#define XEMACPS_RXJABCNT_OFFSET      0x0000018C /* Jabbers Received
						Counter */
#define XEMACPS_RXFCSCNT_OFFSET      0x00000190 /* Frame Check Sequence
						Error Counter */
#define XEMACPS_RXLENGTHCNT_OFFSET   0x00000194 /* Length Field Error
						Counter */
#define XEMACPS_RXSYMBCNT_OFFSET     0x00000198 /* Symbol Error Counter */
#define XEMACPS_RXALIGNCNT_OFFSET    0x0000019C /* Alignment Error Counter */
#define XEMACPS_RXRESERRCNT_OFFSET   0x000001A0 /* Receive Resource Error
						Counter */
#define XEMACPS_RXORCNT_OFFSET       0x000001A4 /* Receive Overrun Counter */
#define XEMACPS_RXIPCCNT_OFFSET      0x000001A8 /* IP header Checksum Error
						Counter */
#define XEMACPS_RXTCPCCNT_OFFSET     0x000001AC /* TCP Checksum Error
						Counter */
#define XEMACPS_RXUDPCCNT_OFFSET     0x000001B0 /* UDP Checksum Error
						Counter */

#define XEMACPS_1588S_OFFSET         0x000001D0 /* 1588 Timer Seconds */
#define XEMACPS_1588NS_OFFSET        0x000001D4 /* 1588 Timer Nanoseconds */
#define XEMACPS_1588ADJ_OFFSET       0x000001D8 /* 1588 Timer Adjust */
#define XEMACPS_1588INC_OFFSET       0x000001DC /* 1588 Timer Increment */
#define XEMACPS_PTPETXS_OFFSET       0x000001E0 /* PTP Event Frame
						Transmitted Seconds */
#define XEMACPS_PTPETXNS_OFFSET      0x000001E4 /* PTP Event Frame
						Transmitted Nanoseconds */
#define XEMACPS_PTPERXS_OFFSET       0x000001E8 /* PTP Event Frame Received
						Seconds */
#define XEMACPS_PTPERXNS_OFFSET      0x000001EC /* PTP Event Frame Received
						Nanoseconds */
#define XEMACPS_PTPPTXS_OFFSET       0x000001E0 /* PTP Peer Frame
						Transmitted Seconds */
#define XEMACPS_PTPPTXNS_OFFSET      0x000001E4 /* PTP Peer Frame
						Transmitted Nanoseconds */
#define XEMACPS_PTPPRXS_OFFSET       0x000001E8 /* PTP Peer Frame Received
						Seconds */
#define XEMACPS_PTPPRXNS_OFFSET      0x000001EC /* PTP Peer Frame Received
						Nanoseconds */

/* network control register bit definitions */
#define XEMACPS_NWCTRL_RXTSTAMP_MASK    0x00008000 /* RX Timestamp in CRC */
#define XEMACPS_NWCTRL_ZEROPAUSETX_MASK 0x00001000 /* Transmit zero quantum
						pause frame */
#define XEMACPS_NWCTRL_PAUSETX_MASK     0x00000800 /* Transmit pause frame */
#define XEMACPS_NWCTRL_HALTTX_MASK      0x00000400 /* Halt transmission
						after current frame */
#define XEMACPS_NWCTRL_STARTTX_MASK     0x00000200 /* Start tx (tx_go) */

#define XEMACPS_NWCTRL_STATWEN_MASK     0x00000080 /* Enable writing to
						stat counters */
#define XEMACPS_NWCTRL_STATINC_MASK     0x00000040 /* Increment statistic
						registers */
#define XEMACPS_NWCTRL_STATCLR_MASK     0x00000020 /* Clear statistic
						registers */
#define XEMACPS_NWCTRL_MDEN_MASK        0x00000010 /* Enable MDIO port */
#define XEMACPS_NWCTRL_TXEN_MASK        0x00000008 /* Enable transmit */
#define XEMACPS_NWCTRL_RXEN_MASK        0x00000004 /* Enable receive */
#define XEMACPS_NWCTRL_LOOPEN_MASK      0x00000002 /* local loopback */

/* name network configuration register bit definitions */
#define XEMACPS_NWCFG_BADPREAMBEN_MASK 0x20000000 /* disable rejection of
						non-standard preamble */
#define XEMACPS_NWCFG_IPDSTRETCH_MASK  0x10000000 /* enable transmit IPG */
#define XEMACPS_NWCFG_FCSIGNORE_MASK   0x04000000 /* disable rejection of
						FCS error */
#define XEMACPS_NWCFG_HDRXEN_MASK      0x02000000 /* RX half duplex */
#define XEMACPS_NWCFG_RXCHKSUMEN_MASK  0x01000000 /* enable RX checksum
						offload */
#define XEMACPS_NWCFG_PAUSECOPYDI_MASK 0x00800000 /* Do not copy pause
						Frames to memory */
#define XEMACPS_NWCFG_MDC_SHIFT_MASK   18         /* shift bits for MDC */
#define XEMACPS_NWCFG_MDCCLKDIV_MASK   0x001C0000 /* MDC Mask PCLK divisor */
#define XEMACPS_NWCFG_FCSREM_MASK      0x00020000 /* Discard FCS from
						received frames */
#define XEMACPS_NWCFG_LENGTHERRDSCRD_MASK 0x00010000
/* RX length error discard */
#define XEMACPS_NWCFG_RXOFFS_MASK      0x0000C000 /* RX buffer offset */
#define XEMACPS_NWCFG_PAUSEEN_MASK     0x00002000 /* Enable pause TX */
#define XEMACPS_NWCFG_RETRYTESTEN_MASK 0x00001000 /* Retry test */
#define XEMACPS_NWCFG_1000_MASK        0x00000400 /* Gigbit mode */
#define XEMACPS_NWCFG_EXTADDRMATCHEN_MASK 0x00000200


/* PHY Maintenance bit definitions */
#define XEMACPS_PHYMNTNC_OP_MASK    0x40020000	/* operation mask bits */
#define XEMACPS_PHYMNTNC_OP_R_MASK  0x20000000	/* read operation */
#define XEMACPS_PHYMNTNC_OP_W_MASK  0x10000000	/* write operation */
#define XEMACPS_PHYMNTNC_ADDR_MASK  0x0F800000	/* Address bits */
#define XEMACPS_PHYMNTNC_REG_MASK   0x007C0000	/* register bits */
#define XEMACPS_PHYMNTNC_DATA_MASK  0x0000FFFF	/* data bits */
#define XEMACPS_PHYMNTNC_PHYAD_SHIFT_MASK   23	/* Shift bits for PHYAD */
#define XEMACPS_PHYMNTNC_PHREG_SHIFT_MASK   18	/* Shift bits for PHREG */


/* network status register bit definitaions */
#define XEMACPS_NWSR_MDIOIDLE_MASK     0x00000004 /* PHY management idle */
#define XEMACPS_NWSR_MDIO_MASK         0x00000002 /* Status of mdio_in */


/**************************************************/

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

int mem_access(unsigned int addr, char access_type, unsigned long * value, int write) {
    int fd;
    void *map_base, *virt_addr;
	unsigned long readval;

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
    	printf ("open error\n");
    	return -1;
    }

    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, addr & ~MAP_MASK);
    if(map_base == (void *) -1) {
    	printf ("map error\n");
    	return -1;
    }

    virt_addr = map_base + (addr & MAP_MASK);
    switch(access_type) {
		case 'b':
			readval = *((unsigned char *) virt_addr);
			break;
		case 'h':
			readval = *((unsigned short *) virt_addr);
			break;
		default:
		case 'w':
			readval = *((unsigned long *) virt_addr);
			break;
	}
    // printf("Value at address 0x%X (%p): 0x%X\n", addr, virt_addr, readval);
    fflush(stdout);

	/* write access */
    if(write > 0) {
		switch(access_type) {
			case 'b':
				*((unsigned char *) virt_addr) = *value;
				readval = *((unsigned char *) virt_addr);
				break;
			case 'h':
				*((unsigned short *) virt_addr) = *value;
				readval = *((unsigned short *) virt_addr);
				break;
			case 'w':
				*((unsigned long *) virt_addr) = *value;
				readval = *((unsigned long *) virt_addr);
				break;
		}
		// printf("Written 0x%X; readback 0x%X\n", *value, readval);
		fflush(stdout);
	}
    /* read access */
    else {
    	*value = readval;
    }

	if(munmap(map_base, MAP_SIZE) == -1) {
		printf ("error unmap\n");
		return -1;

	}
    close(fd);
    return 0;
}


unsigned long xemacps_read(unsigned int base, unsigned int reg) {
	int ret;
	unsigned long value;

	/*
	printf ("%s() base:0x%08X, reg:%d\n",
				__FUNCTION__, base, reg);
	 */
	ret = mem_access((unsigned int)(base) + (unsigned int)(reg), 'w', &value, 0);

	if (ret == 0)
		return value;
	else {
		printf ("error reading the register\n");
		return 0;
	}
}

unsigned long xemacps_write(unsigned int base, unsigned int reg, unsigned long value) {
	int ret;

	/*
	printf ("%s() base:0x%08X, reg:%d, value:0x%08X\n",
			__FUNCTION__, base, reg, value);
	 */
	ret = mem_access((unsigned int)(base) + (unsigned int)(reg), 'w', &value, 1);

	if (ret == 0)
		return value;
	else {
		printf ("error writing the register\n");
		return 0;
	}
}


static int mdio_read(unsigned int interface, unsigned int phyaddr, int phyreg)
{
	int mii_id;
	unsigned int baseaddr;
	unsigned int regval;
	int value;
	volatile unsigned int ipisr;
	unsigned int cnt = 0;

	if (interface == 0) {
		baseaddr = 0xE000B000;
	}
	else {
		baseaddr = 0xE000C000;
	}

	// printf ("%s() phy:%d, reg:%d\n", __FUNCTION__, phyaddr, phyreg);


	regval  = XEMACPS_PHYMNTNC_OP_MASK;
	regval |= XEMACPS_PHYMNTNC_OP_R_MASK;
	regval |= (phyaddr << XEMACPS_PHYMNTNC_PHYAD_SHIFT_MASK);
	regval |= (phyreg << XEMACPS_PHYMNTNC_PHREG_SHIFT_MASK);

	xemacps_write(baseaddr, XEMACPS_PHYMNTNC_OFFSET, regval);

	/* wait for end of transfer */
	do {
		usleep(1);
		ipisr = xemacps_read(baseaddr, XEMACPS_NWSR_OFFSET);
		cnt++;
	} while (((ipisr & XEMACPS_NWSR_MDIOIDLE_MASK) == 0) && (cnt < 1000));

	if (cnt >= 1000) printf ("timeOut\n");

	value = xemacps_read(baseaddr, XEMACPS_PHYMNTNC_OFFSET) &
			XEMACPS_PHYMNTNC_DATA_MASK;

	return value;
}


static int mdio_write(unsigned int interface, unsigned int phyaddr, int phyreg, unsigned int value)
{
	int mii_id;
	unsigned int baseaddr;
	unsigned int regval;
	volatile unsigned int ipisr;
	unsigned int cnt = 0;

	if (interface == 0) {
		baseaddr = 0xE000B000;
	}
	else {
		baseaddr = 0xE000C000;
	}

	// printf ("%s() phy:%d, reg:%d\n", __FUNCTION__, phyaddr, phyreg);

	regval  = XEMACPS_PHYMNTNC_OP_MASK;
	regval |= XEMACPS_PHYMNTNC_OP_W_MASK;
	regval |= (phyaddr << XEMACPS_PHYMNTNC_PHYAD_SHIFT_MASK);
	regval |= (phyreg << XEMACPS_PHYMNTNC_PHREG_SHIFT_MASK);
	regval |= (value & 0xFFFF);

	xemacps_write(baseaddr, XEMACPS_PHYMNTNC_OFFSET, regval);

	/* wait for end of transfer */
	do {
		usleep(1);
		ipisr = xemacps_read(baseaddr, XEMACPS_NWSR_OFFSET);
		cnt++;
	} while (((ipisr & XEMACPS_NWSR_MDIOIDLE_MASK) == 0) && (cnt < 1000));

	if (cnt >= 1000) printf ("timeOut\n");

	return 0;
}

void usage (char * progname) {
	printf ("Usage: %s -i <interface> -a <phyaddr> -r <regaddr> [-v <register value>]\n", progname);
}


int main(int argc, char **argv) {
	char * progname = argv[0];
	int ret;
	int opt;
	unsigned int interface = 0;
	unsigned int phyaddr = 0;
	unsigned int regaddr = 0;
	unsigned int value = 0;
	int interfaceflag = 0;
	int phyaddrflag = 0;
	int regaddrflag = 0;
	int valueflag = 0;

	while ((opt = getopt(argc, argv, "i:a:r:v:")) != -1) {
	        switch (opt) {
	        case 'i':
	        	interface = atoi(optarg);
	        	interfaceflag = 1;
	            break;
	        case 'a':
	        	phyaddr = atoi(optarg);
	        	phyaddrflag = 1;
	            break;
	        case 'r':
	        	regaddr = atoi(optarg);
	        	regaddrflag = 1;
	            break;
	        case 'v':
	        	value = atoi(optarg);
	        	valueflag = 1;
	            break;
	        default: /* '?' */
	            usage (progname);
	            exit(EXIT_FAILURE);
	        }
	}

	if (!interfaceflag || !phyaddrflag || !regaddrflag) {
		printf("missing mandatory arguments !\n");
		usage(progname);
		exit(EXIT_FAILURE);
	}

	/* write some register */
	if (valueflag) {
		mdio_write(interface, phyaddr, regaddr, value);
	}

	ret = mdio_read(interface, phyaddr, regaddr);
	printf("MAC: %d - PHY: %d - REG: %u ( 0x%02X ) - VAL: 0x%04X\n",
			interface,
			phyaddr,
	        regaddr, regaddr,
	        ret);

	return 0;
}
