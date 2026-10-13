#include "bytecode.h"
#include <stdio.h>
#include <stdlib.h>


void bc_init(ByteCode *bc)
{
    bc->bytes = NULL;
    bc->size = 0;
}

int bc_create(ByteCode *bc, char* file)
{
    // If a previous bytecode is still loaded, free it first
    bc_delete(bc);

    FILE* fp = fopen(file, "rb");
    if (!fp) {
        return 0;
    }

    // Determine file size
    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return 0;
    }
    long size = ftell(fp);
    if (size < 0) {
        fclose(fp);
        return 0;
    }
    rewind(fp);

    // Allocate buffer (if file is empty, keep bytes = NULL)
    byte_t* buffer = NULL;
    if (size > 0) {
        buffer = (char*)malloc(size);
        if (!buffer) {
            fclose(fp);
            return 0;
        }
    }


    // Read the whole file
    size_t read_count = fread(buffer, 1, size, fp);
    if (read_count != (size_t)size) {
        free(buffer);
        fclose(fp);
        return 0;
    }

    fclose(fp);

    // Store the bytecode
    bc->bytes = buffer;
    bc->size = (int)size;
    return 1;
}

void bc_delete(ByteCode *bc)
{
    if (bc->bytes) {
        free(bc->bytes);
        bc->bytes = NULL;
    }
    bc->size = 0;
}

