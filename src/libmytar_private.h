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

#ifndef _LIBMYTAR_PRIVATE_H_
#define _LIBMYTAR_PRIVATE_H_

#include <time.h>
#include <grp.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//#include <math.h>
//#include <sys/types.h>

#if HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif

#include "libmytar.h"

// Private functions
//-----------------
void libmytar_initHeader(t_libmytar_tar_struct *tar_struct);
int libmytar_processChecksum(t_libmytar_tar_struct *tar_struct);
int libmytar_readHeader(t_libmytar_tar_struct *tar_struct);
int libmytar_finishData(t_libmytar_tar_struct *tar_struct);
//int libmytar_octalString_to_dec(char *);
//int libmytar_addTrailingBlock(t_libmytar_tar_struct *tar_struct, int nb_blocks);

#endif	// _LIBMYTAR_PRIVATE_H_
