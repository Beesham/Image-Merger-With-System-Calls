#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

char * readDimension(int inFileFd1, int inFileFd2) {
    char *dimensions;

    lseek(inFileFd1, 3, SEEK_SET); //set the seek to the line with dimensions
       
    //Cound the amount of charaters in width 
    char temp;
    int c = 0;
    do{
        c++;
        read(inFileFd1, &temp, sizeof(char));
    }while(temp != ' ');
      
    //Reads the width
    lseek(inFileFd1, 3, SEEK_SET); //set the seek to the line with dimensions
    int bytesRead = read(inFileFd1, &widthOfInFile1, c);  //reads the width 


        
    printf("%d", bytesRead);
    printf("%s", widthOfInFile1);
    
    printf("%s", "inReadDImen Fnuc");

    return dimensions;
}

int main(int argc, char *argv[]) {

    int inFileFd1, inFileFd2, outFileFd;    //file descripters
    char *inFile1, *inFile2, *outFile;
    char buf[7];
    char errMsg[] = "Error: Something wrong with your file";
    char widthOfInFile1[256], widthOfInFile2, heightOfInFile1, heightOfInFile2;

    //Opens files from provideed by command line args
    for(int i = optind; i < argc; i++) {
        inFileFd1 = open(argv[1], O_RDONLY);
        inFileFd2 = open(argv[2], O_RDONLY);
        outFileFd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0755);   
    }
    
    
    if(inFileFd1 == -1 || inFileFd2 == -1 || outFileFd == -1) write(STDOUT_FILENO, errMsg, sizeof(errMsg));
    else {
        
   /*
        lseek(inFileFd1, 3, SEEK_SET); //set the seek to the line with dimensions
       
        //Cound the amount of charaters in width 
        char temp;
        int c = 0;
        do{
            c++;
            read(inFileFd1, &temp, sizeof(char));
        }while(temp != ' ');
        
        //Reads the width
        lseek(inFileFd1, 3, SEEK_SET); //set the seek to the line with dimensions
        int bytesRead = read(inFileFd1, &widthOfInFile1, c);  //reads the width 


        
        printf("%d", bytesRead);
        printf("%s", widthOfInFile1);
     */   
        close(inFileFd1);
        close(inFileFd2);
        close(outFileFd);            
    }
 
}
