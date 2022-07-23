
/*
 * Copyright (C) 2001 Alessandro Rubini and Jonathan Corbet
 * Copyright (C) 2001 O'Reilly & Associates
 *
 * The source code in this file can be freely used, adapted,
 * and redistributed in source or binary form, so long as an
 * acknowledgment appears in derived source files.  The citation
 * should list that the code comes from the book "Linux Device
 * Drivers" by Alessandro Rubini and Jonathan Corbet, published
 * by O'Reilly & Associates.   No warranty is attached;
 * we cannot take responsibility for errors or fitness for use.
 *
 */

#include <linux/ioctl.h>

/*
 * Macros to help debugging
 */

#undef PDEBUG             /* undef it, just in case */
#undef PINFO

#ifdef MODULE_DEBUG
	#ifdef __KERNEL__
		/* This one if debugging is on, and kernel space */
		#define PDEBUG(fmt, args...) printk( KERN_DEBUG "[%s]: " fmt, MODULE_NAME, ## args)

	#else
		/* This one for user space */
		#define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)

	#endif
#else
	#define PDEBUG(fmt, args...) /* not debugging: nothing */
	
#endif

#ifdef __KERNEL__
	#define PINFO(fmt, args...) printk( KERN_INFO "[%s]: " fmt, MODULE_NAME, ## args)
#else
	#define PINFO(fmt, args...) fprintf( stdout, fmt, ## args)
#endif

#undef PDEBUGG

#define PDEBUGG(fmt, args...) /* nothing: it's a placeholder */

/* ---------------- user define ---------------------- */
#define MODULE_NAME ("jony_char_test")
#define MODULE_CNT (1)

/* ---------------- user define end ----------------- */
