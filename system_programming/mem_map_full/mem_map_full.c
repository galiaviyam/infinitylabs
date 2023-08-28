#include <dlfcn.h>	/* dlopen */
#include <stddef.h>	/*  NULL  */
#include <stdio.h>	/* printf */

#include "header.h"

typedef int *(func)(int, char**, char**);

int main(int argc, char **argv, char **envp)
{
	void *exp_ptr  = NULL;
	func *exp_func  = NULL;
	
	StatFunc(argc, argv, envp);
	ImpFunc(argc, argv, envp);

	exp_ptr = dlopen("./lib_dynamic_exp.so", RTLD_LAZY | RTLD_GLOBAL);
	if (NULL == exp_ptr)
	{
		return -1;
	}
	
	*(void **)&exp_func = dlsym(exp_ptr, "ExpFunc");
	if (NULL == exp_func)
	{
		return -1;
	}
	
	exp_func(argc, argv, envp);
	
	dlclose(exp_ptr);

	return 0;
}



/******************************************************************************************************
(gdb) info proc mapping
process 115305
Mapped address spaces:

          Start Addr           End Addr       Size     Offset  Perms  objfile
      0x555555554000     0x555555555000     0x1000        0x0  r--p   /home/gali/git/gali.aviyam/system_programming/mem_map_full/mem_map_full
      0x555555555000     0x555555556000     0x1000     0x1000  r-xp   /home/gali/git/gali.aviyam/system_programming/mem_map_full/mem_map_full
      0x555555556000     0x555555557000     0x1000     0x2000  r--p   /home/gali/git/gali.aviyam/system_programming/mem_map_full/mem_map_full
      0x555555557000     0x555555558000     0x1000     0x2000  r--p   /home/gali/git/gali.aviyam/system_programming/mem_map_full/mem_map_full
      0x555555558000     0x555555559000     0x1000     0x3000  rw-p   /home/gali/git/gali.aviyam/system_programming/mem_map_full/mem_map_full
      0x555555559000     0x55555557a000    0x21000        0x0  rw-p   [heap]
      0x7ffff7d7c000     0x7ffff7d7f000     0x3000        0x0  rw-p   
      0x7ffff7d7f000     0x7ffff7da7000    0x28000        0x0  r--p   /usr/lib/x86_64-linux-gnu/libc.so.6
      0x7ffff7da7000     0x7ffff7f3c000   0x195000    0x28000  r-xp   /usr/lib/x86_64-linux-gnu/libc.so.6
      0x7ffff7f3c000     0x7ffff7f94000    0x58000   0x1bd000  r--p   /usr/lib/x86_64-linux-gnu/libc.so.6
      0x7ffff7f94000     0x7ffff7f98000     0x4000   0x214000  r--p   /usr/lib/x86_64-linux-gnu/libc.so.6
      0x7ffff7f98000     0x7ffff7f9a000     0x2000   0x218000  rw-p   /usr/lib/x86_64-linux-gnu/libc.so.6
      0x7ffff7f9a000     0x7ffff7fa7000     0xd000        0x0  rw-p   
      0x7ffff7fb1000     0x7ffff7fb2000     0x1000        0x0  r--p   /home/gali/git/gali.aviyam/system_programming/mem_map_full/lib_dynamic_exp.so
      0x7ffff7fb2000     0x7ffff7fb3000     0x1000     0x1000  r-xp   /home/gali/git/gali.aviyam/system_programming/mem_map_full/lib_dynamic_exp.so
      0x7ffff7fb3000     0x7ffff7fb4000     0x1000     0x2000  r--p   /home/gali/git/gali.aviyam/system_programming/mem_map_full/lib_dynamic_exp.so
      0x7ffff7fb4000     0x7ffff7fb5000     0x1000     0x2000  r--p   /home/gali/git/gali.aviyam/system_programming/mem_map_full/lib_dynamic_exp.so
      0x7ffff7fb5000     0x7ffff7fb6000     0x1000     0x3000  rw-p   /home/gali/git/gali.aviyam/system_programming/mem_map_full/lib_dynamic_exp.so
      0x7ffff7fb6000     0x7ffff7fb7000     0x1000        0x0  r--p   /home/gali/git/gali.aviyam/system_programming/mem_map_full/lib_dynamic_imp.so
      0x7ffff7fb7000     0x7ffff7fb8000     0x1000     0x1000  r-xp   /home/gali/git/gali.aviyam/system_programming/mem_map_full/lib_dynamic_imp.so
      0x7ffff7fb8000     0x7ffff7fb9000     0x1000     0x2000  r--p   /home/gali/git/gali.aviyam/system_programming/mem_map_full/lib_dynamic_imp.so
      0x7ffff7fb9000     0x7ffff7fba000     0x1000     0x2000  r--p   /home/gali/git/gali.aviyam/system_programming/mem_map_full/lib_dynamic_imp.so
      0x7ffff7fba000     0x7ffff7fbb000     0x1000     0x3000  rw-p   /home/gali/git/gali.aviyam/system_programming/mem_map_full/lib_dynamic_imp.so
      0x7ffff7fbb000     0x7ffff7fbd000     0x2000        0x0  rw-p   
      0x7ffff7fbd000     0x7ffff7fc1000     0x4000        0x0  r--p   [vvar]
      0x7ffff7fc1000     0x7ffff7fc3000     0x2000        0x0  r-xp   [vdso]
      0x7ffff7fc3000     0x7ffff7fc5000     0x2000        0x0  r--p   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
      0x7ffff7fc5000     0x7ffff7fef000    0x2a000     0x2000  r-xp   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
      0x7ffff7fef000     0x7ffff7ffa000     0xb000    0x2c000  r--p   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
      0x7ffff7ffb000     0x7ffff7ffd000     0x2000    0x37000  r--p   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
      0x7ffff7ffd000     0x7ffff7fff000     0x2000    0x39000  rw-p   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
      0x7ffffffde000     0x7ffffffff000    0x21000        0x0  rw-p   [stack]
  0xffffffffff600000 0xffffffffff601000     0x1000        0x0  --xp   [vsyscall]

      
      
      
      
nm mem_map_full

000000000000038c r __abi_tag
0000000000004014 B __bss_start
0000000000004014 b completed.0
00000000000020a8 R const_global_variable
00000000000020ac r const_static_global_variable
0000000000002204 r const_static_local_variable.1
                 w __cxa_finalize@GLIBC_2.2.5
0000000000004000 D __data_start
0000000000004000 W data_start
0000000000001190 t deregister_tm_clones
                 U dlclose@GLIBC_2.34
                 U dlopen@GLIBC_2.34
                 U dlsym@GLIBC_2.34
0000000000001200 t __do_global_dtors_aux
0000000000003d60 d __do_global_dtors_aux_fini_array_entry
0000000000004008 D __dso_handle
0000000000003d68 d _DYNAMIC
0000000000004014 D _edata
0000000000004020 B _end
00000000000015cd T ExternFunction
00000000000015f8 T _fini
0000000000001240 t frame_dummy
0000000000003d58 d __frame_dummy_init_array_entry
0000000000002368 r __FRAME_END__
                 U free@GLIBC_2.2.5
0000000000003f78 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
0000000000002208 r __GNU_EH_FRAME_HDR
0000000000001000 T _init
0000000000002000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __libc_start_main@GLIBC_2.34
0000000000001249 T main
                 U malloc@GLIBC_2.2.5
                 U MapImpl
000000000000137b T MapStatic
0000000000004010 D non_const_global_variable
0000000000004018 b non_const_static_global_variable
000000000000401c b non_const_static_local_variable.0
                 U printf@GLIBC_2.2.5
                 U puts@GLIBC_2.2.5
00000000000011c0 t register_tm_clones
                 U __stack_chk_fail@GLIBC_2.4
0000000000001160 T _start
00000000000015a2 t StaticFunction
0000000000004018 D __TMC_END__
     
     */ 
      
      

