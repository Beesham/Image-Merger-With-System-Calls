#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

int main(int argc, char *argv[]) {

    int inFileFd1, inFilefd2, outFilefd;    //file descripters
    char *inFile1, *inFile2, *outFile;

    for(int i = optind; i < argc; i++) {
        fprintf(stdout, "%s", argv[i]);
        inFileFd1 = open(arg[i], O_RDONLY);
    }

}
