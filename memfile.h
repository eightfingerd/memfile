/*
 * memfile.h - A fake mem FILE
 * Created: 2017-04-26
 * Author:  eightfingerd@gmail.com
 */

#ifndef __MEM_FILE_H
#define __MEM_FILE_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */

typedef enum {
	False = 0,
	True = 1
} Bool;

typedef struct _MEMFILE {
    char*       ptr;
    long int    size;
    long int    cursor;
} MEMFILE;

/* Create an new mem file. */
extern MEMFILE* mfcreate(int size);

/* Open an exist mem file. */
extern MEMFILE* mfopen(char* ptr, int size);

/* Close an mem file. */
extern void mfclose(MEMFILE* mf, Bool created);

/* Seek to a certain position on MEMFILE. */
extern int mfseek (MEMFILE *mf, long int offset, int whence);

/* Return the current position of MEMFILE. */
extern long int mftell (MEMFILE *mf);

/* Rewind to the beginning of MEMFILE. */
extern void mfrewind (MEMFILE *mf);

/* Read chunks of generic data from MEMFILE. */
extern size_t mfread (void *ptr, size_t size, size_t n, MEMFILE *mf);

/* Write chunks of generic data to MEMFILE. */
extern size_t mfwrite (const void *ptr, size_t size, size_t n, MEMFILE *mf);

#ifdef __cplusplus
}
#endif

#endif // __MEM_FILE_H
