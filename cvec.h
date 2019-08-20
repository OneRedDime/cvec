/*******************************************************************************
 * cvec - C-Vector: A dynamically resizing buffer for C programs.
 * 
 *  Copyright (C) 2019  Bo Cimino
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*******************************************************************************/

#include <stddef.h>

/* cvec - c-vector. Dynamically resizing array and suite of functions.
 *
 * allocated will be no greater than len rounded up to the next power of 2
 * bytes. This minimizes calls to *alloc and guarantees this structure never
 * wastes more than 50% of its memory.
 **/
typedef struct cvec
{
    void *buf;
    size_t len;
    size_t allocated;
} cvec_t;

/* init a new cvec_t on the heap and return its pointer */
cvec_t *cvec_init(void);

/* free the memory of a cvec_t */
void cvec_free(cvec_t *cv);

/* append src to the end of dest */
void cvec_append(cvec_t *dest, const void *src, size_t slen);

/* like cvec_append, but appends a null-terminating byte. */
void cvec_cat(cvec_t *dest, const char *src);

/* resize cv->buf to be of len n */
void cvec_resize(cvec_t *cv, size_t n);

/* remove n bytes starting at offset in cv->buf */
void cvec_remove(cvec_t *cv, size_t offset, size_t n);
