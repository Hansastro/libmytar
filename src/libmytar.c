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

#include "libmytar_private.h"

/*--------------------------------------------------------------------------------*/
void
libmytar_initHeader(t_libmytar_tar_struct *tar_struct)
{
  time_t actual_time;
  struct stat file_stat;
  struct group *user_group;
  char *uname;

  if(fstat(tar_struct->fd, &file_stat) == -1)
    perror("fstat");
  
  time(&actual_time);
  user_group = getgrgid((gid_t)(file_stat.st_gid));

  sprintf(tar_struct->header.mode, "%07o", file_stat.st_mode);
  sprintf(tar_struct->header.uid,  "%07o", file_stat.st_uid);
  sprintf(tar_struct->header.gid,  "%07o", file_stat.st_gid);
  sprintf(tar_struct->header.mtime,"%011o", (unsigned int)actual_time);

  // Init chksum with white space is important for the checksum processing
  strcpy(tar_struct->header.chksum, "        ");

  memset(tar_struct->header.name,   0, 100);
  memset(tar_struct->header.size,   0, 12);
  tar_struct->header.typeflag = '0';
  strcpy(tar_struct->header.magic, "ustar");
  strcpy(tar_struct->header.version, "00");
  uname = getlogin();
  if(uname)
    strncpy(tar_struct->header.uname, uname, 32);
  strcpy(tar_struct->header.gname, user_group->gr_name);
}

/*--------------------------------------------------------------------------------*/
int
libmytar_processChecksum(t_libmytar_tar_struct *tar_struct)
{
  int i,sum;
  char* header_ptr = (char*)&(tar_struct->header);

  sum = 0;
  for(i = 0; i < 512; i++)
    sum += 0xFF & header_ptr[i];

  return sum;
}

/*--------------------------------------------------------------------------------*/
int
libmytar_newArchive(char *archive_name, t_libmytar_tar_struct *tar_struct, t_libmytar_archive_mode mode)
{
  memset(tar_struct, 0, sizeof(t_libmytar_posix_header));
  tar_struct->fd = open(archive_name,
			O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  tar_struct->stream = fdopen(tar_struct->fd, (mode?"w":"r"));
  libmytar_initHeader(tar_struct);
  tar_struct->written_size = 0;
  tar_struct->is_first_data = 1;

  return(1);
}

/*--------------------------------------------------------------------------------*/
int
libmytar_closeArchive(t_libmytar_tar_struct *tar_struct)
{
  if( !(tar_struct->block_is_finish) )
    libmytar_finishData(tar_struct);

  fclose(tar_struct->stream);
  close(tar_struct->fd);

  return(1);
}

/*--------------------------------------------------------------------------------*/
int
libmytar_newFile(t_libmytar_tar_struct *tar_struct, char *name)
{
  if ( !(tar_struct->is_first_data) )
    {
      libmytar_finishData(tar_struct);
    }
  else
    tar_struct->is_first_data = 0;

  tar_struct->written_size = 0;
  strcpy(tar_struct->header.name, name);  
  memset(tar_struct->header.size,   0, 12);
  strcpy(tar_struct->header.chksum, "        ");

  // Memorization of the size and the checksum field
  // 124 is the offset of ths field in the posix header
  // 148, the offset of the checksum field
  tar_struct->size_field_pos = ftell(tar_struct->stream) + 124;
  tar_struct->chksum_field_pos = ftell(tar_struct->stream) + 148;

  fwrite(&(tar_struct->header), 1, 512, tar_struct->stream);  

  tar_struct->block_is_finish = 0;

  return(1);
}

/*--------------------------------------------------------------------------------*/
int
libmytar_addData(t_libmytar_tar_struct *tar_struct, int size, void* ptr)
{
  char* char_ptr = (char*)ptr;
  
  fwrite(char_ptr, 1, size, tar_struct->stream);
  tar_struct->written_size += size;

  tar_struct->block_is_finish = 0;

  return(1);
}

/*--------------------------------------------------------------------------------*/
int
libmytar_finishData(t_libmytar_tar_struct *tar_struct)
{
  int gap = 512 - (tar_struct->written_size % 512);
  char null[512];

  memset(null, 0, 511);
  fwrite(&null, gap, 1, tar_struct->stream);  
  //write size and chksum
  
  fseek(tar_struct->stream, tar_struct->size_field_pos, SEEK_SET);
  sprintf(tar_struct->header.size, "%011o", (unsigned int)(tar_struct->written_size));
  fwrite(&(tar_struct->header.size), 1, sizeof(tar_struct->header.size), tar_struct->stream);  
      
  fseek(tar_struct->stream, tar_struct->chksum_field_pos, SEEK_SET);
  sprintf(tar_struct->header.chksum, "%06o", (unsigned int)(libmytar_processChecksum(tar_struct)));
  fwrite(&(tar_struct->header.chksum), 1, sizeof(tar_struct->header.chksum), tar_struct->stream);  

  fseek(tar_struct->stream, 0, SEEK_END);

  tar_struct->block_is_finish = 1;
  //  tar_struct->is_first_data = 1;

  return(1);
}
