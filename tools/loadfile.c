 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

const int STEP_SIZE = 100;

 char** loadFile(char* filename);

 int main(int argc,char* argv[]){
    if(argc == 1){
        fprintf(stderr , "Must supply a filename to the program\n");
        exit(1); // terminate process 
    }

    char** words =  loadFile(argv[1]);
    if(!words){
        fprintf(stderr, "Can't build data structure\n");
        exit(1);
    }
    // print the files 100 lines
    for (int i = 0; words[i] != NULL; i++)
        printf("+[%i] %s\n",i,words[i]);
    printf("Done!\n");
 }


char** loadFile(char* filename){
    FILE* f = fopen(filename, "r");
    if (!f){
        fprintf(stderr ,  "Can't open %s for reading \n", filename);
        return NULL; 
    }

    int arr_len = 0;
    // Allocate space for 100 char pointer
    char** lines = NULL;
    
    // create a line buffer
    char buf[1000];
    int i = 0; 
    while (fgets(buf,1000,f)){
        // check if array is full ? extend if true;
        if ( i == arr_len) {
            arr_len += (STEP_SIZE * 0.5);
            char** new_lines = (char**) realloc(lines, arr_len * sizeof(char*));
            if (!new_lines){
                fprintf(stderr, "Can't reallocate due to low memory\n");
                exit(1);
            }
            lines = new_lines;
        }

        // trim away '\n' from the line
        size_t slen = strlen(buf);
        buf[slen-1] = '\0';
        // get string dynamic size
        char* str =  (char*)malloc((slen+1 ) * sizeof(char));
        // copy string from buf to string
        stpcpy(str,buf);
        // store str in data structure
        lines[i] = str ; 
        i++;
    }

   
    if( i == arr_len ){
        char** new_lines = (char**)realloc(lines,(arr_len + 1) * sizeof(char*));
        if(!new_lines){
            fprintf(stderr, "Can't reallocate due to low memory\n");
            exit(1);
        }
        lines =  new_lines;
    }
    lines[i] = NULL;
     // set length of char**
    fclose(f);
    return lines;
}