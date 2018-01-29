#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

int sizeOfDimension(int fd, char stopChar) {
    //Cound the amount of charaters in width 
    char temp;
    int c = 0;
    do{
        c++;
        read(fd, &temp, sizeof(char));
    }while(temp != stopChar);
    
    return c;    
}

int main(int argc, char *argv[]) {

    int inFileFd1, inFileFd2, outFileFd;    //file descripters
    char *inFile1, *inFile2, *outFile;
    char buf[7];
    char errMsg[] = "Error: Something wrong with your file";
    char widthOfInFile1[256], widthOfInFile2, heightOfInFile1[256], heightOfInFile2;

    //Opens files from provideed by command line args
    for(int i = optind; i < argc; i++) {
        inFileFd1 = open(argv[1], O_RDONLY);
        inFileFd2 = open(argv[2], O_RDONLY);
        outFileFd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0755);   
    }
    
    
    if(inFileFd1 == -1 || inFileFd2 == -1 || outFileFd == -1) write(STDOUT_FILENO, errMsg, sizeof(errMsg));
    else {
           
        lseek(inFileFd1, 3, SEEK_SET); //set the seek to the line with dimensions

        int c = sizeOfDimension(inFileFd1, ' ');

        //Reads the width
        lseek(inFileFd1, 3, SEEK_SET); //set the seek to the line with dimensions
        int bytesRead = read(inFileFd1, &widthOfInFile1, c);  //reads the width 

        printf("%d", bytesRead);
        printf("%s", widthOfInFile1);
 
        int i = sizeOfDimension(inFileFd1, '\n');

        //Reads the height
        lseek(inFileFd1, c+3, SEEK_SET); //set the seek to the line with dimensions
        bytesRead = read(inFileFd1, &heightOfInFile1, i);  //reads the width 

        printf("%d", bytesRead);
        printf("%s", heightOfInFile1);
     
     
        
        close(inFileFd1);
        close(inFileFd2);
        close(outFileFd);            
    }
 
}
