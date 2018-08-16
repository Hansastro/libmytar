# Introduction

This is a very simple library to write some tar file.

I wrote this library to store some image flow from a webcam 10 year ago.

It can interest some people.

# Interface

The interface is only four funtions:
- int **libmytar_newArchive**(char *archiveName,
		    t_libmytar_tar_struct *tar_struct,
		    t_libmytar_archive_mode mode);

- int **libmytar_closeArchive**(t_libmytar_tar_struct *);

- int **libmytar_newFile**(t_libmytar_tar_struct *tar_struct,
		 char *name);

- int **libmytar_addData**(t_libmytar_tar_struct *tar_struct,
		 int size,
		 void* ptr);

## libmytar_newArchive
This function create a new archive file. The file has the name *archiveName*. The function will populate the structure *tar_struct*. The argument *mode* was for futur usage to read the archive. It should be set to WRITE.

## libmytar_closeArchive
Close the archive.

## libmytar_newFile
Create a new file in the archive with the name *name*.

## libmytar_addData
Add data to the last added file. the *size* is the size of the object and the *ptr* is a pointer on it.

# Compilation and installation
This library use autotool.
To compile it you have to do the following steps:
 - autoreconf --install	--> This will generate the needed files.
 - automake		--> This will generate some pre-makefile
 - ./configure		
 - make
 - make install
 
 See the INSTALL file for more details.
