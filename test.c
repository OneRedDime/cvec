#include <cvec.h>

#include <stdio.h>

int main(int argc, char *argv[])
{
    cvec_t *cv = cvec_init();
    int i = 0;

    if (argc == 1)
    {
        return 0;
    }

    for (i = 1; i < argc; i++)
    {
        cvec_cat(cv, argv[i]);
    }

    printf("%s\n", (char *)cv->buf);
    printf("len: %ld, allocated: %ld\n", cv->len, cv->allocated);

    cvec_free(cv);

    return 0;
}
