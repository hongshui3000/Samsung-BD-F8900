/*
 * memory-fpga_foxap.h : Define memory address space.
 * 
 * Copyright (C) 2011 Samsung Electronics co.
 * Seihee Chon <sh.chon@samsung.com>
 *
 */
#ifndef _MEMORY_FOXAP_H_
#define _MEMORY_FOXAP_H_

/* Address space for DTV memory map */
#define MACH_MEM0_BASE 		0x40000000
#define MACH_MEM1_BASE 		0xC0000000
#define MACH_MEM2_BASE 		0xE0000000

#define SYS_MEM0_SIZE		(64 << 20)
#define SYS_MEM1_SIZE		(64 << 20)
#define SYS_MEM2_SIZE		(64 << 20)

#define MACH_MEM0_SIZE 		SZ_256M
#define MACH_MEM1_SIZE 		SZ_256M
#define MACH_MEM2_SIZE 		SZ_256M

/*
#define MACH_DTVSUB0_BASE	0xF8000000
#define MACH_DTVSUB0_SIZE	SZ_4M

#define MACH_DTVSUB1_BASE	0xF8400000
#define MACH_DTVSUB1_SIZE	SZ_16M

#define MACH_DTVSUB2_BASE	0xF9400000
#define MACH_DTVSUB2_SIZE	SZ_16M
*/

/* see arch/arm/mach-sdp/Kconfig */
#if defined(CONFIG_SDP_SINGLE_DDR_B)
#define PHYS_OFFSET		MACH_MEM1_BASE
#elif defined(CONFIG_SDP_SINGLE_DDR_C)
#define PHYS_OFFSET		MACH_MEM2_BASE
#else
#define PHYS_OFFSET		MACH_MEM0_BASE
#endif

/* FoxAP DDR Bank
 * bank 0:  0x40000000-0xBFFFFFFF - 2GB
 * bank 1:  0xC0000000-0xDFFFFFFF - 512MB
 * bank 2:  0xE0000000-0xFFFFFFFF - 512MB
 */
 
#ifndef __ASSEMBLY__
extern unsigned int sdp_sys_mem0_size;
extern unsigned int sdp_sys_mem1_size;
#endif
 
#if defined(CONFIG_DISCONTIGMEM) || defined(CONFIG_SPARSEMEM)

#define RANGE(n, start, size)   \
	        ( (((unsigned long)(n)) >= (start)) && (((unsigned long)n) < ((start)+(size))) )

/* Bank size limit 512MByte */
#define MACH_MEM_MASK	(0x1FFFFFFF)
#define MACH_MEM_SHIFT	(29)

/* Kernel size limit 1024Mbyte */
#define KVADDR_MASK	(0x3FFFFFFF)

#define __phys_to_virt(x) \
	({ u32 val = PAGE_OFFSET; \
           switch((x >> MACH_MEM_SHIFT) - 2) { \
		case 5:			\
			val += sdp_sys_mem1_size; \
		case 4:			\
			val += sdp_sys_mem0_size; \
			break;		\
		default:		\
		case 0:			\
			break;		\
	   } \
	   val += (x & MACH_MEM_MASK); \
	   val;})

#define __virt_to_phys(x) \
	({ u32 val = x - PAGE_OFFSET; \
		if(val < sdp_sys_mem0_size) val += MACH_MEM0_BASE; \
		else { \
			val -= sdp_sys_mem0_size; \
			if (val < sdp_sys_mem1_size) val += MACH_MEM1_BASE; \
			else { \
				val -= sdp_sys_mem1_size; \
		    val += MACH_MEM2_BASE; \
			} \
		} \
	 val;})

#ifdef CONFIG_DISCONTIGMEM
#define KVADDR_TO_NID(addr) \
	({ u32 val = (u32)addr - PAGE_OFFSET; \
	   if(val < sdp_sys_mem0_size) val = 0; \
           else { \
		val -= sdp_sys_mem0_size; \
		if (val < sdp_sys_mem1_size) val = 1; \
		else  val = 2; \
	   } \
	 val;})


#define PFN_TO_NID(pfn) \
	(((pfn) >> (MACH_MEM_SHIFT - PAGE_SHIFT)) - 6)

#define LOCAL_MAP_PFN_NR(addr)  ((((unsigned long)addr & MACH_MEM_MASK) >> PAGE_SHIFT))

#define LOCAL_MAP_KVADDR_NR(kaddr) \
	({ u32 val = (u32)kaddr - PAGE_OFFSET; \
	   if(val >= sdp_sys_mem0_size) { \
		val -= sdp_sys_mem0_size; \
		if (val >= sdp_sys_mem1_size) \
		    val -= sdp_sys_mem1_size; \
	   } \
	 val = val >> PAGE_SHIFT; \
	 val;})
#endif

#ifdef CONFIG_SPARSEMEM
/* 0x40000000~0xBFFFFFFF 0xC0000000~0xDFFFFFFF, 0xE0000000~0xFFFFFFFF */
#define SECTION_SIZE_BITS	23
#define MAX_PHYSMEM_BITS	32
#endif

#endif

#endif
