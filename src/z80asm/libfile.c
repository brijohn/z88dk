/*
     ZZZZZZZZZZZZZZZZZZZZ    8888888888888       00000000000
   ZZZZZZZZZZZZZZZZZZZZ    88888888888888888    0000000000000
                ZZZZZ      888           888  0000         0000
              ZZZZZ        88888888888888888  0000         0000
            ZZZZZ            8888888888888    0000         0000       AAAAAA         SSSSSSSSSSS   MMMM       MMMM
          ZZZZZ            88888888888888888  0000         0000      AAAAAAAA      SSSS            MMMMMM   MMMMMM
        ZZZZZ              8888         8888  0000         0000     AAAA  AAAA     SSSSSSSSSSS     MMMMMMMMMMMMMMM
      ZZZZZ                8888         8888  0000         0000    AAAAAAAAAAAA      SSSSSSSSSSS   MMMM MMMMM MMMM
    ZZZZZZZZZZZZZZZZZZZZZ  88888888888888888    0000000000000     AAAA      AAAA           SSSSS   MMMM       MMMM
  ZZZZZZZZZZZZZZZZZZZZZ      8888888888888       00000000000     AAAA        AAAA  SSSSSSSSSSS     MMMM       MMMM

Copyright (C) Paulo Custodio, 2011-2015

Handle library file contruction, reading and writing

$Header: /home/dom/z88dk-git/cvs/z88dk/src/z80asm/libfile.c,v 1.8 2015-02-08 21:58:50 pauloscustodio Exp $
*/

#include "xmalloc.h"   /* before any other include */

#include "errors.h"
#include "fileutil.h"
#include "libfile.h"
#include "objfile.h"
#include "options.h"

char Z80libhdr[] = "Z80LMF" OBJ_VERSION;

/*-----------------------------------------------------------------------------
*	define a library file name from the command line
*	if empty, use Z80_STDLIB environment variable
*	add .lib extension
*----------------------------------------------------------------------------*/
static char *search_libfile( char *filename )
{
	if ( filename != NULL && *filename != '\0' )	/* not empty */
		return get_lib_filename( filename );		/* add '.lib' extension */
	else if ( (filename = getenv("Z80_STDLIB")) != NULL )
		return filename;							/* return env var-as-is*/
	else
	{
        error_env_not_defined("Z80_STDLIB");
        return NULL;
	}
}

/*-----------------------------------------------------------------------------
*	make library from list of files; convert each source to object file name 
*----------------------------------------------------------------------------*/
void make_library(char *lib_filename, UT_array *src_files)
{
	ByteArray *obj_file_data;
	FILE	*lib_file;
	char	*obj_filename;
	size_t	 fptr, obj_size;
	char **pfile;

	lib_filename = search_libfile(lib_filename);
	if ( lib_filename == NULL )
		return;					/* ERROR */

    if ( opts.verbose )
        printf("Creating library '%s'...\n", lib_filename );

	/* write library header */
	lib_file = myfopen_atomic( lib_filename, "w+b" );	
	xfput_strz( lib_file, Z80libhdr );

	/* write each object file */
	for (pfile = NULL; (pfile = (char **)utarray_next(src_files, pfile)) != NULL; )
	{
		fptr = ftell( lib_file );

		/* read object file */
		obj_filename  = get_obj_filename( *pfile );
		obj_file_data = read_obj_file_data( obj_filename );
		if ( obj_file_data == NULL )
		{
			myfclose_remove( lib_file );			/* error */
			return;
		}

        if ( opts.verbose )
            printf( "'%s' module at %08X.\n", obj_filename, fptr );

		/* write file pointer of next file, or -1 if last */
		obj_size = ByteArray_size( obj_file_data );
		if (pfile == (char **)utarray_back(src_files))
			xfput_uint32(lib_file, -1);
        else
            xfput_uint32( lib_file, fptr + 4 + 4 + obj_size ); 

		/* write module size */
        xfput_uint32( lib_file, obj_size );

		/* write module */
        xfput_chars( lib_file, (char *) ByteArray_item( obj_file_data, 0 ), obj_size ); 
	}

	/* close and write lib file */
	myfclose( lib_file );
}
