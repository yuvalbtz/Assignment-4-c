#include <string.h>
#include <stdio.h>
#include "compress.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s -c|-d input_filename\n", argv[0]);
        return 1;
    }

    const char *flag = argv[1];
    const char *input_filename = argv[2];

    if (strcmp(flag, "-c") == 0) {
        compress_text(input_filename, "compressed_file.bin");
    } else if (strcmp(flag, "-d") == 0) {
        decompress_binary(input_filename, "decompressed_file.txt");
    } else {
        fprintf(stderr, "Invalid flag. Use -c to compress or -d to decompress.\n");
        return 1;
    }

    return 0;
}
