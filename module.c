#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/sysproto.h>
#include <sys/malloc.h>
#include "kernio.h"
#include <vm/vm.h>
#include <vm/vm_param.h>
#include <vm/vm_extern.h>
#include <vm/vm_page.h>
#include <vm/vm_pageout.h>
#include <vm/vm_map.h>

#include <sys/fcntl.h>
MALLOC_DECLARE (M_PAGE);
MALLOC_DEFINE (M_PAGE, "temp_page_buffer", "Buffer for pages");
//#define PHYS_PAGE_COUNT (long len) (len/PAGE_SIZE + 1)
long  get_physical_mem_size(void);
int dump_memory(void);
//unsigned int start_value = 0;
long total_physical_mem_size = 0;
const char * filename = "/root/FreeBmAM/Memorydump.dd";
/**
 * Method to return value of total physical memory size
 */

long get_physical_mem_size(){
	int size, len;
	len = sizeof(long);
	int error =0;
	error = kernel_sysctlbyname (&thread0, "hw.realmem", &(size), &len, NULL, 0, NULL, 0);
	return size;
}


/*
 *method that does physical to virtual address translation and dumps mem
 *
 */
int dump_memory(){
	//1. Open file
	//2. Figure out physical to virtual address translation
	//3. Write range in Memory
	struct vnode * vp;

	vp = kio_open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (vp == NULL) {
		uprintf("Directory doesn't exist \n");
		return -1;
	}
	unsigned long page_count = total_physical_mem_size/PAGE_SIZE;	
	unsigned long dst = 0;
	int error = 0;
        unsigned long offset = 0;
//	void * page = malloc (PAGE_SIZE, M_PAGE, M_NOWAIT | M_USE_RESERVE);
	for (int i = 0; i < page_count; i++){
		vm_page_t virtual_address;
		virtual_address = pmap_kenter_temporary(trunc_page(dst), 0);
		if (virtual_address != 0){
// 		memcpy( page, (void *) virtual_address, PAGE_SIZE);
// 		uprintf("Copied Page 0x%x\t", dst);
		error = kio_write(vp, virtual_address, PAGE_SIZE, offset);
		if (error != 0){
			uprintf("Your file path may not be correct. This module does not create directories that do not exist. Please FIX PATH\n");
			return -1;
		}
		pause (NULL, 10);
                
		if (error != 0){
			uprintf("Can't write to file \n");
			kio_close(vp);
			return -1;
		}else{
			uprintf("Physical Address 0x%x Virtual Address 0x%x \n",(unsigned int)dst, (unsigned int) virtual_address);
		}
		dst += PAGE_SIZE;	
		}
		offset = dst;
		
	}

	return 0;
}



/*
 *Required Modevent Function
 *
 *
 */
static int BmAM_modevent(struct module *m, int what, void *arg ){
	int err = 0;
	switch(what){
		case MOD_LOAD:
			total_physical_mem_size = get_physical_mem_size();
			uprintf("Free-BmAM Module Loaded.\n");
		       	uprintf("Total memory size is 0x%lx \n", total_physical_mem_size);
			int error = 0;
			error = dump_memory();
			if (error == 0){
				uprintf("Dump Succesful. Check file\n");
			}else{
				uprintf("Dump not successful. Dump_memory threw an error that fucked things up\n");
			}

			break;
		case MOD_UNLOAD:
			uprintf("Free-BmAM Module unLoaded\n");
			break;
		default:
			err = EINVAL;
			break;
	}
	return (err);

}
/*
 *Required moduledata Struct
 *
 */

static moduledata_t FreeBSD_BmAM_mod = {
	"FreeBSD-BmAM",
	BmAM_modevent, 
	NULL
};

/*
 *Required Declare_module call
 */

DECLARE_MODULE(FreeBSD_BmAM, FreeBSD_BmAM_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);

