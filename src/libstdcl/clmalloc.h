/* clmalloc.h
 *
 * Copyright (c) 2009 Brown Deer Technology, LLC.  All Rights Reserved.
 *
 * This software was developed by Brown Deer Technology, LLC.
 * For more information contact info@browndeertechnology.com
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3 (LGPLv3)
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* DAR */


#ifndef _CLMALLOC_H
#define _CLMALLOC_H


//#include "stdcl.h"
#include "clcontext.h"


/* XXX use of CL_MEM_WRITE is deprecated! remove it -DAR */

#define CL_MEM_WRITE		0x200

//#define CL_MEM_READ				0x001
//#define CL_MEM_WRITE				0x002
//#define CL_MEM_READ_WRITE		0x003
#define CL_MEM_HOST				0x000100
#define CL_MEM_DEVICE			0x000200
#define CL_MEM_NOCOPY			0x000400
#define CL_MEM_DETACHED			0x001000

#ifdef ENABLE_CLGL
#define CL_MEM_CLBUF				0x100000
#define CL_MEM_GLBUF				0x200000
#endif

#define CL_MCTL_GET_STATUS	1
#define CL_MCTL_GET_DEVNUM	2
#define CL_MCTL_SET_DEVNUM	3
#define CL_MCTL_MARK_CLEAN	4




#define CLMEM_MAGIC     0x19661971
struct _memd_struct {
   union {
      struct {
         LIST_ENTRY(_memd_struct) memd_list;
         cl_uint magic;
         cl_uint flags;
         size_t sz;
         cl_mem clbuf;
			cl_uint devnum;
      };
      char __pad[64];
   };
};


#ifdef __cplusplus
extern "C" {
#endif

static __inline__ 
size_t clsizeofmem(void* ptr) 
{
	intptr_t ptri = (intptr_t)ptr - sizeof(struct _memd_struct);
	struct _memd_struct* memd = (struct _memd_struct*)ptri;
	return(memd->sz);
}


void* clmalloc(CONTEXT* cp, size_t size, int flag);
void clfree( void* ptr );
int clmattach( CONTEXT* cp, void* ptr );
int clmdetach( void* ptr );
int clmctl( void* ptr, int op, int arg );
void* clmrealloc(CONTEXT* cp, void* ptr, size_t size, int flag);

cl_event clmsync(CONTEXT* cp, unsigned int devnum, void* ptr, int flags);

void* clmemptr( CONTEXT* CP, void* ptr );

#ifdef ENABLE_CLGL
void* clglmalloc(CONTEXT* cp, cl_GLuint glbufobj, int flag);
cl_event clglmsync(CONTEXT* cp, unsigned int devnum, void* ptr, int flags);
#endif


#ifdef __cplusplus
}
#endif


#endif
