#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

//Counts the amount of bytes up to a specified character
int sizeOfDimension(int fd, char stopChar) {
    char aChar;
    int count = 0;
    do{
        count++;
        read(fd, &aChar, sizeof(char));
    }while(aChar != stopChar);
    
    return count;    
}

//Mergers the 2 files into a new file
void mergeFiles(int fd1, int fd2, int outFd, int w1, int h1, int w2, int h2) {

    char w1buf[w1];
    char w2buf[w2*3];
    
    lseek(fd1, 0, SEEK_SET);

    int i;
    int bytesRead = 0;
    //Makes a copy of the largest file
    do {
        i = read(fd1, &w1buf, sizeof(w1buf));
        bytesRead = bytesRead + i;
        if(write(outFd, w1buf, sizeof(w1buf)) == -1) write(STDOUT_FILENO, "Error has occured", 18);
    }while(i > 0);


    bytesRead = 0;
    int edge = w1 - w2; //the starting point to merge the second file into the new file
    lseek(outFd, 0, SEEK_SET);
    //Writes the second file into the new file overwriting the necessary portion
    do {
        lseek(outFd, edge*3, SEEK_CUR);
        i = read(fd2, &w2buf, sizeof(w2buf));
        bytesRead = bytesRead + i;
        if(write(outFd, w2buf, sizeof(w2buf)) == -1) write(STDOUT_FILENO, "Error has occured", 18);
    }while(i > 0);

}

int main(int argc, char *argv[]) {

    int inFileFd1, inFileFd2, outFileFd;    //file descripters
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
           
        int sizeOfWidth = sizeOfDimension(inFileFd1, ' ');
        int sizeOfHeight = sizeOfDimension(inFileFd1, '\n');
        
        //Reads the width of first file
        lseek(inFileFd1, 3, SEEK_SET); //set the seek to the line with dimensions
        int bytesRead = read(inFileFd1, &widthOfInFile1, sizeOfWidth);  //reads the width 

        printf("%d", bytesRead);
        printf("%s", widthOfInFile1);
 
        //Reads the height of first file
        lseek(inFileFd1, sizeOfWidth+3, SEEK_SET); //set the seek to the line with dimensions
        bytesRead = read(inFileFd1, &heightOfInFile1, sizeOfHeight);  //reads the height 

        //Get size of width dimensions for second file
        sizeOfWidth = sizeOfDimension(inFileFd2, ' ');

        //Reads the width of the second file
        lseek(inFileFd2, 3, SEEK_SET); 
        bytesRead = read(inFileFd2, &widthOfInFile2, sizeOfWidth);  

        printf("%d", bytesRead);
        printf("%s", widthOfInFile2);
 
        sizeOfHeight = sizeOfDimension(inFileFd2, '\n');

        //Reads the height of the second file
        lseek(inFileFd2, sizeOfWidth+3, SEEK_SET); //set the seek to the line with dimensions height
        bytesRead = read(inFileFd2, &heightOfInFile2, sizeOfHeight); 

        //Checks for mismatch dimensions of the 2 files
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
