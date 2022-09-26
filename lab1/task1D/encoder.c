#include <stdio.h>
#include <string.h>
int main(int argc, char **argv ){
	FILE * input= stdin;
    //FILE * output= stdout;
    char ch='\0';
    int debugMode=0;
	int count=0;
    int modificationMode=0;
    int repetition=0;
    char first='\0';
	for(int i=1;i<argc;i++){
		if(strcmp(argv[i],"-D")==0){
			debugMode=1;
		}
        else if(strncmp(argv[i],"-i",2)==0){
            input=fopen(argv[i]+2,"r");
        }
        else if(strncmp(argv[i],"-e",2) == 0){
            modificationMode=1;
            char sub = argv[i][2];
            if((sub>=48) & (sub<=57)){
                repetition=-(sub-48);
            }
            else if((sub>=65) & (sub<=70)){
                repetition= -((int)sub -55);
            }
            else{
                printf("illegal repetition number!");
                return 2;
            }
        }
        else if(strncmp(argv[i],"+e",2)==0){
            modificationMode=2;
            char sub = argv[i][2];
            if((sub>=48) & (sub<=57)){
                repetition=sub-48;
            }
            else if((sub>=65) & (sub<=70)){
                repetition= ((int)sub -55);
            }
            else{
                printf("illegal repetition number!");
                return 3;
            }
        }
		else{
			printf("illegal argument");
			return 1;}
	}
	while((ch =fgetc(input))!=EOF) {
        if (modificationMode==1) {//substraction mode
            if(repetition!=0)
                repetition++;
            else
                printf("%c",ch);
        }
        else if(modificationMode==2){//repetition mode
            if(first=='\0'){
                first=ch;
            }
            if(ch==10){
                for(int i=0;i<repetition;i++)
                    printf("%c",first);
            }
            else
                printf("%c",ch);
        }
        else {
            if (ch >= 65 && ch <= 90) {
                printf(".");
                count++;
                if (debugMode) {
                    fprintf(stderr, "%d , 46\n", ch);
                }
            } else if ((int) ch == 10) {
                if (debugMode) {
                    fprintf(stderr, "the number of swaps is: %d\n", count);// might need to reset count here
                }
            } else {
                printf("%c", ch);
                if (debugMode) {
                    fprintf(stderr, "%d , %d\n", ch, ch);
                }

            }
            //ch = fgetc(stdin);
        }
    }
    fclose(input);
	return 0;
}
