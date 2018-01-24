#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

int main(int argc, char *argv[]) {

    int inFileFd1, inFileFd2, outFileFd;    //file descripters
    char *inFile1, *inFile2, *outFile;
    char buf[7];
    char errMsg[] = "Error: Something wrong with your file";
    int widthOfInFile1, widthOfInFile2, heightOfInFile1, heightOfInFile2;

    //Opens files from provideed by command line args
    for(int i = optind; i < argc; i++) {
        inFileFd1 = open(argv[1], O_RDONLY);
        inFileFd2 = open(argv[2], O_RDONLY);
        outFileFd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0755);   
    }
    
    if(inFileFd1 == -1 || inFileFd2 == -1 || outFileFd == -1) write(STDOUT_FILENO, errMsg, sizeof(errMsg));
    else {
        lseek(inFileFd1, 3, SEEK_SET);
        read(inFileFd1, &buf, sizeof(buf));
        
        printf("%s", buf);
    
        close(inFileFd1);
        close(inFileFd2);
        close(outFileFd);            
    }
 
}
