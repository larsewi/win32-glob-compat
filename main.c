#define _CRTDBG_MAP_ALLOC

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <crtdbg.h>

#include "glob.h"

int main(int argc, char *argv[])
{
    int flags = GLOB_BRACE;
    glob_t pglob;

    for (size_t i = 1; i < argc; i++)
    {
        int ret = glob(argv[i], flags, NULL, &pglob);
        switch (ret)
        {
        case 0:
            printf("Found:\n");
            for (size_t i = 0; i < pglob.gl_pathc; i++)
            {
                printf("\t%s\n", pglob.gl_pathv[i]);
            }
            break;
        case GLOB_NOSPACE:
            fprintf(stderr, "Memory error");
            return EXIT_FAILURE;
        case GLOB_ABORTED:
            fprintf(stderr, "Read error");
            break;
        case GLOB_NOMATCH:
            printf("No match\n");
            break;
        default:
            /* We should never end up here */
            assert(false);
        }
        flags |= GLOB_APPEND;
    }
    globfree(&pglob);

    _CrtDumpMemoryLeaks();
    return EXIT_SUCCESS;
}
