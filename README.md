This is a very simple library to write some tar file.

I wrote this library to store some image flow from a webcam 10 year ago.

It can interest some people.

The interface is only four funtions:
- int libmytar_newArchive(char *archiveName,
		    t_libmytar_tar_struct *tar_struct,
		    t_libmytar_archive_mode mode);

- int libmytar_closeArchive(t_libmytar_tar_struct *);

- int libmytar_newFile(t_libmytar_tar_struct *tar_struct,
		 char *name);

- int libmytar_addData(t_libmytar_tar_struct *tar_struct,
		 int size,
		 void* ptr);
