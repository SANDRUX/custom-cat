#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L_CHARS 100

void reverse_file(const char * in_path, const char * out_path)
{
    FILE * inFile = fopen(in_path, "a+");

    fseek(inFile, 0, SEEK_END);

    size_t size = ftell(inFile);

    rewind(inFile);

    char * buf = (char *)malloc(size);

    fread(buf, size, 1, inFile);

    if (buf[size - 1] != '\n')
    {
        fprintf(inFile, "\n");
        rewind(inFile);

        buf = (char *)realloc(buf, size + 1);

        buf[size] = '\n';

        size ++;
    }

    size_t line_count = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (buf[i] == '\n')
        {
            line_count ++;
        }
    }

    char lines [line_count][L_CHARS];

    char * token = strtok(buf, "\n");

    int count = 0;

    while (token != NULL)
    {
        strcpy(lines[count], token);
        token = strtok(NULL, "\n");

        count ++;
    }

    free(buf);

    fclose(inFile);

    FILE * outFile = fopen(out_path, "w");

    for (size_t i = 0; i < line_count; i++)
    {
        fprintf(outFile, "%s\n", lines[line_count - i - 1]);
    }

    fclose(outFile);
}

int main(int argc, char ** argv)
{
    reverse_file(argv[1], argv[2]);

    return 0;
}
