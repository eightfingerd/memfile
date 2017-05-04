#include "memfile.h"

#include <assert.h>
#include <string.h>

/* Create an new mem file. */
MEMFILE* mfcreate(int size)
{
    MEMFILE* mf = (MEMFILE*)malloc(sizeof(MEMFILE));
    mf->ptr = (char*)malloc(size);
    mf->size = size;
    mf->cursor = 0;
    return mf;
}

/* Open an exist mem file. */
MEMFILE* mfopen(char* ptr, int size)
{
    MEMFILE* mf = (MEMFILE*)malloc(sizeof(MEMFILE));
    mf->ptr = ptr;
    mf->size = size;
    mf->cursor = 0;
    return mf;
}

/* Close an mem file. */
extern void mfclose(MEMFILE* mf, Bool created)
{
    if (created) {
        free(mf->ptr);
    }
    free(mf);
}

/* Seek to a certain position on MEMFILE. */
int mfseek (MEMFILE *mf, long int offset, int whence)
{
    int idxEnd = mf->size - 1;

    switch (whence) {
    case SEEK_SET:
    {
        if (offset >= 0 && offset <= idxEnd) {
            mf->cursor = offset;
            return 0;
        }
    }
        break;
    case SEEK_CUR:
    {
        if ((offset + mf->cursor) >= 0 && (offset + mf->cursor) <= idxEnd) {
            mf->cursor += offset;
            return 0;
        }
    }
        break;
    case SEEK_END:
    {
        if ((offset + idxEnd) >= 0 && (offset + idxEnd) <= idxEnd) {
            mf->cursor += offset;
            return 0;
        }
    }
        break;
    default:
        break;
    }

    return -1;
}

/* Return the current position of MEMFILE. */
long int mftell (MEMFILE *mf)
{
    return mf->cursor;
}

/* Rewind to the beginning of MEMFILE. */
void mfrewind (MEMFILE *mf)
{
    mf->cursor = 0;
}

/* Read chunks of generic data from MEMFILE. */
size_t mfread (void *ptr, size_t size, size_t n, MEMFILE *mf)
{
    if (size > (mf->size - mf->cursor)) {
        return 0;
    }

    int read_count = 0;
    while ((read_count < n) && (read_count*size <= (mf->size - mf->cursor))) {
        read_count++;
    }
    memcpy(ptr, mf->ptr, read_count*size);
    mf->cursor += read_count*size;
    assert(mf->cursor <= mf->size - 1);
    return read_count;
}

/* Write chunks of generic data to MEMFILE. */
size_t mfwrite (const void *ptr, size_t size, size_t n, MEMFILE *mf) //TODO: memfile will *NOT* malloc incrementlly!
{
    if (size > (mf->size - mf->cursor)) {
        return 0;
    }

    int write_count = 0;
    while ((write_count < n) && (write_count*size <= (mf->size - mf->cursor))) {
        write_count++;
    }
    memcpy(mf->ptr, ptr, write_count*size);
    mf->cursor += write_count*size;
    assert(mf->cursor <= mf->size - 1);
    return write_count;
}
