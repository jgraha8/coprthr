/* stdcl.h
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

#ifndef _STDCL_H
#define _STDCL_H

#include <string.h>
#include <stdio.h>
#include <sys/queue.h>

#include <CL/cl.h>


#define cl_float4_x(f) (((cl_float*)&f)[0])
#define cl_float4_y(f) (((cl_float*)&f)[1])
#define cl_float4_z(f) (((cl_float*)&f)[2])
#define cl_float4_w(f) (((cl_float*)&f)[3])


#include "clcontext.h"
#include "clinit.h"
#include "clsched.h"
#include "clmalloc.h"
#include "clfcn.h"


typedef struct clndrange_struct clndrange_t;

#define clndrange_init1d(gto0,gt0,lt0) \
	{ 1, gto0,0,0,0, gt0,0,0,0, lt0,0,0,0 }
#define clndrange_init2d(gto0,gt0,lt0,gto1,gt1,lt1) \
	{ 2, gto0,gto1,0,0, gt0,gt1,0,0, lt0,lt1,0,0 }
#define clndrange_init3d(gto0,gt0,lt0, gto1,gt1,lt1, gto2,gt2,lt2) \
	{ 3, gto0,gto1,gto2,0, gt0,gt1,gt2,0, lt0,lt1,lt2,0 }
#define clndrange_init4d(gto0,gt0,lt0,gto1,gt1,lt1,gto2,gt2,lt2,gto3,gt3,lt3) \
	{ 4, gto0,gto1,gto2,gto3, gt0,gt1,gt2,gt3, lt0,lt1,lt2,lt3 }


#define clndrange_set1d(ndr,gto0,gt0,lt0) do { \
	ndr.dim = 1; \
	ndr.gtid_offset[0]=gto0; ndr.gtid_offset[1]=0; \
	ndr.gtid_offset[2]=0; ndr.gtid_offset[3]=0; \
	ndr.gtid[0]=gt0; ndr.gtid[1]=0; \
	ndr.gtid[2]=0; ndr.gtid[3]=0; \
	ndr.ltid[0]=lt0; ndr.ltid[1]=0; \
	ndr.ltid[2]=0; ndr.ltid[3]=0; \
} while(0);

#define clndrange_set1d(ndr,gto0,gt0,lt0) do { \
	ndr.dim = 1; \
	ndr.gtid_offset[0]=gto0; ndr.gtid_offset[1]=0; \
	ndr.gtid_offset[2]=0; ndr.gtid_offset[3]=0; \
	ndr.gtid[0]=gt0; ndr.gtid[1]=0; \
	ndr.gtid[2]=0; ndr.gtid[3]=0; \
	ndr.ltid[0]=lt0; ndr.ltid[1]=0; \
	ndr.ltid[2]=0; ndr.ltid[3]=0; \
} while(0);

#define clndrange_set1d(ndr,gto0,gt0,lt0) do { \
	ndr.dim = 1; \
	ndr.gtid_offset[0]=gto0; ndr.gtid_offset[1]=0; \
	ndr.gtid_offset[2]=0; ndr.gtid_offset[3]=0; \
	ndr.gtid[0]=gt0; ndr.gtid[1]=0; \
	ndr.gtid[2]=0; ndr.gtid[3]=0; \
	ndr.ltid[0]=lt0; ndr.ltid[1]=0; \
	ndr.ltid[2]=0; ndr.ltid[3]=0; \
} while(0);


/*
 * CL kernel arguments
	printf("gloabal clSetKernelArg %d %p\n",sizeof(cl_mem),(void*)&memd->clbuf);
 */

#define clarg_set(krn,argnum,arg) \
	clSetKernelArg(krn,argnum,sizeof(typeof(arg)),(void*)&arg);

#define clarg_set_global(krn,argnum,arg) do { \
	struct _memd_struct* memd \
		= (struct _memd_struct*)((intptr_t)arg - sizeof(struct _memd_struct)); \
	clSetKernelArg(krn,argnum,sizeof(cl_mem),(void*)&memd->clbuf); \
	} while(0);

#define clarg_set_local(krn,argnum,arg) \
	clSetKernelArg(krn,argnum,arg,0);

#define clarg_assert_proto(kname,...) do { \
	typeof(_assert_proto_stub)* stub = _assert_proto_stub; \
	if (strncmp(#kname,"0\0",2)) ((typeof(kname)*)stub)( __VA_ARGS__ ); \
	} while(0)



#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif

