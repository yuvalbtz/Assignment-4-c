#include "compress.h"
#include <stdio.h>

void compress_text(const char *input_filename, const char *output_filename) {
  
  FILE *input_file = fopen(input_filename, "r");
    FILE *output_file = fopen(output_filename, "wb");

    if (input_file == NULL || output_file == NULL) {
        fprintf(stderr, "Error opening files.\n");
        return;
    }

    char ch;
    int digitCount = 0;

    while ((ch = fgetc(input_file)) != EOF) {
        // Check if the character is a digit
        if (ch >= '0' && ch <= '9') {
            int digit = ch - '0';

            // Reverse the binary representation and write to the binary file
            for (int i = 3; i >= 0; i--) {
                fputc((digit & (1 << i)) ? '0' : '1', output_file);
            }

            digitCount++;
        }
    }

    // Pad with four zeros if the number of digits is odd
    if (digitCount % 2 == 1) {
        for (int i = 0; i < 4; i++) {
            fputc('0', output_file);
        }
    }

    fclose(input_file);
    fclose(output_file);

    printf("Compression completed successfully.\n");
}

int binaryToDecimal(const char *binaryString) {
    
    int decimalNumber = 0;
    while (*binaryString) {
        decimalNumber = (decimalNumber << 1) + (*binaryString++ - '0');
    }
    return decimalNumber;
}

void decompress_binary(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "r");
    FILE *output_file = fopen(output_filename, "w");

    if (input_file == NULL || output_file == NULL) {
        fprintf(stderr, "Error opening files.\n");
        return;
    }

    char ch;
    int bitCount = 0;
    char binaryString[5]; // Assuming 4-bit binary representation

    while ((ch = fgetc(input_file)) != EOF) {
        // Check if the character is a binary digit
        if (ch == '0' || ch == '1') {
            
            // Accumulate the bits to form a binary string
            binaryString[bitCount++] = (ch == '1' ? '0' : '1');
              
            // If 4 bits have been accumulated, convert to decimal and write to the output file
            if (bitCount == 4) {
                binaryString[bitCount] = '\0';
                int decimalDigit = binaryToDecimal(binaryString);
                if(decimalDigit >=0 && decimalDigit <=9 ){
                  fputc(decimalDigit + '0', output_file);
                }
                bitCount = 0;
            }
        } 
    }

    fclose(input_file);
    fclose(output_file);

    printf("Decoding completed successfully.\n");
}
