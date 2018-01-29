#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdlib.h>

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

void mergeFiles(int fd1, int fd2, int outFd, int w1, int h1, int w2, int h2) {

    char w1buf[w1];
    char w2buf[w2*3];
    
    lseek(fd1, 0, SEEK_SET);

    int i;
    int bytesRead = 0;
    do {
        i = read(fd1, &w1buf, sizeof(w1buf));
        bytesRead = bytesRead + i;
        if(write(outFd, w1buf, sizeof(w1buf)) == -1) write(STDOUT_FILENO, "Error has occured", 18);
    }while(i != 0);
    printf("%d %d", bytesRead, w1*h1);

    bytesRead = 0;
    int edge = w1 - w2;
    lseek(outFd, 0, SEEK_SET);
     do {
        lseek(outFd, edge*3, SEEK_CUR);
        i = read(fd2, &w2buf, sizeof(w2buf));
        bytesRead = bytesRead + i;
        if(write(outFd, w2buf, sizeof(w2buf)) == -1) write(STDOUT_FILENO, "Error has occured", 18);
    }while(i != 0);

}

int main(int argc, char *argv[]) {

    int inFileFd1, inFileFd2, outFileFd;    //file descripters
    char *inFile1, *inFile2, *outFile;
    

    char buf[7];
    char errMsg[] = "Error: Something wrong with your file";
    char errMsg2[] = "Error: File 1 is smaller than File 2!";
    char widthOfInFile1[256], widthOfInFile2[256], heightOfInFile1[256], heightOfInFile2[256];

    //Opens files from provideed by command line args
    for(int i = optind; i < argc; i++) {
        inFileFd1 = open(argv[1], O_RDONLY);
        inFileFd2 = open(argv[2], O_RDONLY);
        outFileFd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0755);   
    }
    
    
    if(inFileFd1 == -1 || inFileFd2 == -1 || outFileFd == -1) write(STDOUT_FILENO, errMsg, sizeof(errMsg));
    else {
           
        lseek(inFileFd1, 3, SEEK_SET); //set the seek to the line with dimensions
        lseek(inFileFd2, 3, SEEK_SET); //set the seek to the line with dimensions

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
     
        //Reads dimenasions for seconf file
        c = sizeOfDimension(inFileFd2, ' ');

        //Reads the width
        lseek(inFileFd2, 3, SEEK_SET); //set the seek to the line with dimensions
        bytesRead = read(inFileFd2, &widthOfInFile2, c);  //reads the width 

        printf("%d", bytesRead);
        printf("%s", widthOfInFile2);
 
        i = sizeOfDimension(inFileFd2, '\n');

        //Reads the height
        lseek(inFileFd2, c+3, SEEK_SET); //set the seek to the line with dimensions
        bytesRead = read(inFileFd2, &heightOfInFile2, i);  //reads the width 

        printf("%d", bytesRead);
        printf("%s", heightOfInFile2);
     

        if(atoi(widthOfInFile1) < atoi(widthOfInFile2) || atoi(heightOfInFile1) < atoi(heightOfInFile2)) {
            write(STDOUT_FILENO, errMsg2, sizeof(errMsg2)); 
        }else{
            mergeFiles(inFileFd1, 
                inFileFd2,
                outFileFd,
                atoi(widthOfInFile1), 
                atoi(heightOfInFile1), 
                atoi(widthOfInFile2), 
                atoi(heightOfInFile2)); 
        }
        
        close(inFileFd1);
        close(inFileFd2);
        close(outFileFd);            
    }
 
}
