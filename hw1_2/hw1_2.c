#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

char* read_file(char*, int);


int numOfLines;

int main(int argc, char * argv[]) {
    
    char* filename = argv[argc-1];
    char* data;
    
    int opt;
    while((opt = getopt(argc, argv, "n:")) != -1) {
        switch(opt) {
            case 'n':
                numOfLines = atoi(optarg); break;
            case ':':
                printf("option needs a value\n"); break;
            case '?':
                printf("unknown option: %c\n", optopt); break;
        }
        
    }
   
    data = read_file(filename, numOfLines);
    
    if(data != NULL) printf("%s\n", data);
    
    free(data);
    
    return 0;
}

char* read_file(char* filename, int lines){
    ssize_t ret;
    char *dataBuffer;
    int line_count = 0;
    
    int fd = open(filename, O_RDONLY);
    
    if(fd == -1)
    {
        perror("Error opening the file");
        return 0;
        
    }
    else
    {
        
        dataBuffer = (char*) calloc(1200, sizeof(*dataBuffer));
        
        int count = 0;
        
        while( (ret = read(fd, &dataBuffer[count], 1)) > 0)
        {
            if(ret == -1)
            {
                perror("Error reading the file");
                break;
            }
            
            if(dataBuffer[count] == '\n') ++line_count;
            
            if(lines == line_count) break;
            
            count++;
        }
        
        
        if(close(fd) == -1)
            perror("Error closing the file");
        
    }
    
    return dataBuffer;
}

