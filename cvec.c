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

#include <cvec.h>

#include <stdlib.h>
#include <string.h>

/* helpers */

/* return x rounded up to the next power of 2. This function will promote
 * floor values as well. ie. 2 will return 4. */
size_t ceil_power(size_t x)
{
    size_t val = 1;
    while (val <= x)
    {
        val = val << 1;
    }

    return val;
}

size_t min(size_t x, size_t y)
{
    if (x < y)
    {
        return x;
    }

    return y;
}

/* init a new cvec_t on the heap and return its pointer */
cvec_t *cvec_init(void)
{
    return calloc(1, sizeof(cvec_t));
}

/* free the memory of a cvec_t */
void cvec_free(cvec_t *cv)
{
    free(cv->buf);
    memset(cv, 0, sizeof(cvec_t));
    free(cv);
}

/* append src to the end of dest */
void cvec_append(cvec_t *dest, const void *src, size_t slen)
{
    dest->allocated = ceil_power(dest->len + slen);
    dest->buf = realloc(dest->buf, dest->allocated);

    memmove(dest->buf + dest->len, src, slen);
    dest->len += slen;
}

/* like cvec_append, but appends a null-terminating byte. */
void cvec_cat(cvec_t *dest, const char *src)
{
    cvec_append(dest, src, strlen(src) * sizeof(char));
    ((char *)dest->buf)[dest->len] = 0;
}

/* resize cv->buf to be of size n. The bytes between n and allocated
 * will be zeroed out. */
void cvec_resize(cvec_t *cv, size_t n)
{
    cv->allocated = ceil_power(n);
    cv->buf = realloc(cv->buf, cv->allocated);
    cv->len = n;
    memset(cv->buf + cv->len, 0, cv->allocated - cv->len);
}

/* remove n bytes starting at offset in cv->buf */
void cvec_remove(cvec_t *cv, size_t offset, size_t n)
{
    if (offset > cv->len)
    {
        return;
    }

    n = min(n, cv->len - offset);

    void *rbdd = cv->buf + cv->allocated;
    void *dest = cv->buf + offset;
    void *src = dest + n;

    memmove(dest, src, rbdd - src);
    cv->len -= n;
    cv->allocated = ceil_power(cv->len);
    cv->buf = realloc(cv->buf, cv->allocated);

    memset(cv->buf + cv->len, 0, cv->allocated - cv->len);
}
