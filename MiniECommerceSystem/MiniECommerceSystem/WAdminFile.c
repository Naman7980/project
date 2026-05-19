#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct person{
    
    char name[20];
    int password;
};
int main()
{
    FILE *outfile;
    outfile = fopen("admin.bin","wb");

    if (outfile==NULL)
    {
        fprintf(stderr,"error opened file\n");
        exit(1);
    }
    
    struct person input1 = {"admin", 1234};
    
    int flag=0;
    flag=fwrite(&input1,sizeof(struct person),1, outfile);

    if(flag)
    {
        printf("Contents of the structure written sucessfully");
    }
    else{
        printf("error written to the file");
    }
    fclose(outfile);
    
    
    return 0;
}