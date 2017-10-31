/*
  Copyright 2006 Jean-Philippe Bonnet
  This file is part of libmytar.
  
  libmytar is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  ar is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with Foobar; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _LIBMYTAR_H_
#define _LIBMYTAR_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
  {
    READ  = 0,
    WRITE = 1
  } t_libmytar_archive_mode;

typedef struct s_libmyar_posix_header
{                               /* byte offset */
  char name[100];               /*   0 */
  char mode[8];                 /* 100 */
  char uid[8];                  /* 108 */
  char gid[8];                  /* 116 */
  char size[12];                /* 124 */
  char mtime[12];               /* 136 */
  char chksum[8];               /* 148 */
  char typeflag;                /* 156 */
  char linkname[100];           /* 157 */
  char magic[6];                /* 257 */
  char version[2];		/* 263 */
  char uname[32];               /* 265 */
  char gname[32];               /* 297 */
  char devmajor[8];             /* 329 */
  char devminor[8];             /* 337 */
  char prefix[167];             /* 345 */
                                /* 512 */
} t_libmytar_posix_header;

typedef struct s_libmytar_tar_struct
{
  int is_first_data;		// This field is used to write tar file
  int block_is_finish;		// This field is used to write tar file
  int fd;
  FILE* stream;
  t_libmytar_archive_mode mode;
  long size_field_pos;		// Index of the current size field
  long chksum_field_pos;	// Index of the current chksum field
  t_libmytar_posix_header header;
  long current_file_pos;	// Index of data of the current file
  unsigned long written_size;
} t_libmytar_tar_struct;

// Public functions to write tar files
//------------------------------------
int libmytar_newArchive(char *archiveName,
		    t_libmytar_tar_struct *tar_struct,
		    t_libmytar_archive_mode mode);
int libmytar_closeArchive(t_libmytar_tar_struct *);
int libmytar_newFile(t_libmytar_tar_struct *tar_struct,
		 char *name);
int libmytar_addData(t_libmytar_tar_struct *tar_struct,
		 int size,
		 void* ptr);
//long libmytar_getNextFile(t_libmytar_tar_struct *tar_struct);


#ifdef __cplusplus
}
#endif

#endif		// _LIBMYTAR_H_
