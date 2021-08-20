#include <stdio.h>  /* include declarations for i/o routines */


//function definition:
int isEqual(char str1[] , char str2[]);
int isKeayword(char str[]);
int isNumber(char str[]);

int main() {
    //printf("Hello, World!\n");
    FILE *myfile = fopen("test.txt","r");
    char str[30], c;

    int identifier = 0;

    int i = 0;
    if(!myfile){
        printf("Check the address of file!");
        return 0;
    }
    // while until file is not empty !
    // get char of our file
    printf("TYPE\tVALUE\n");
    while(!feof(myfile)){
        c = fgetc(myfile); //get char
        //check if char is < > / % ! ( ) { } [ ] ...
        if( c=='<' || c=='>' || c=='(' || c==')' ||
            c=='}' || c=='{' || c=='[' || c==']' ||
            c=='!' || c==';' || c==',' || c=='=' ||
            c=='*' || c=='^' || c=='+' || c=='-' ||
            c=='/' || c=='%' )
        {
            str[i]='\0';
            char next;
            next = fgetc(myfile);
            // ++ and -- and == and !=
            if  (
                    ( next=='+' && c=='+' ) ||   // ++
                    ( next=='-' && c=='-' ) ||   // --
                    ( next=='=' && c=='=' ) ||   // ==
                    ( next=='=' && c=='!' ) ||   // !=
                    ( next=='=' && c=='+' ) ||   // +=
                    ( next=='=' && c=='-' ) ||   // -=
                    ( next=='=' && c=='/' ) ||   // /=
                    ( next=='=' && c=='*' )      // *=
                 )
            {

                if(str[0]!='\0'){
                    printf("ID\t%d\t(TOKEN_IDENTIFIER)",identifier);
                    identifier++;
                    printf("\n");
                    printf("%c%c\tNONE\t(TOKEN_OPERATOR)\n",c,next);
                    i = 0;
                    str[0] = '\0';
                    continue;
                }
                else{
                    printf("%c\tNONE\t(TOKEN_OPERATOR)\n",c);
                    continue;
                }
            }


            // coment: /
            if( next=='/' && c=='/' ){
                char comment[100];
                fgets(comment , 100 , myfile);
                printf("\t\tCOMMENT\n");
                continue;
            }

            //send back next for other check
            ungetc(next , myfile);

            //if it's a symbol between two spaces
            if(str[0] == '\0') {
                printf("%c\tNONE\t(TOKEN_OPERATOR)\n",c);
                continue;
            }
            // the word before --> number
            if(isNumber(str)){
                i = 0;
                str[0] = '\0';
                printf("%c\tNONE\t(TOKEN_OPERATOR)\n",c);
                continue;
            }
            //if the word before --> keyword
            if(isKeayword(str)) {
                i = 0;
                str[0] = '\0';
                printf("%c\tNONE\t(TOKEN_OPERATOR)\n",c);
                continue;
            }
            // identifier
            else{
                printf("ID\t%d\t(TOKEN_IDENTIFIER)",identifier);
                identifier++;
                printf("\n");
                printf("%c\tNONE\t(TOKEN_OPERATOR)\n",c);
                i = 0;
                str[0] = '\0';
                continue;
            }
        }

        // string and char
        if(c=='"' || c=='\'') {
            int count = 0;
            char start = c;
            c = fgetc(myfile);

            //"   "
            if( start == '"' ){
                while(c !='"'){
                    c = fgetc(myfile);
                    count++;
                }
            }
            //'   '
            if( start == '\'' ) {
                while (c != '\'') {
                    c = fgetc(myfile);
                    count++;
                }
            }
            // string
            if(count>1)
                printf("STRING\t100\t(TOKEN_STRING)\n");
            // char
            if(count==1)
                printf("CHARACTER\t101\t(TOKEN_STRING)\n");
            continue;
        }


        //encountering a white space
        if(c== ' '){
            str[i]= '\0';

            // checked before
            if(str[0] == '\0')
                continue;
            // the word before --> number
            if(isNumber(str)){
                i = 0;
                str[0] = '\0';
                continue;
            }
            // the word before --> keyword
            if(isKeayword(str)) {
                i = 0;
                str[0] = '\0';
                continue;
            }
            // identifier
            else{
                printf("ID\t%d\t(TOKEN_IDENTIFIER)",identifier);
                identifier++;
                printf("\n");
                i = 0;
                str[0] = '\0';
                continue;
            }
        }

        // new identifier like put,...
        if(c == ':'){
            printf("ID\t%d\t(TOKEN_IDENTIFIER)",identifier);
            identifier++;
            printf("\n");
            printf("%c\tNONE\t(TOKEN_OPERATOR)\n",c);
            i = 0;
            str[0] = '\0';
            continue;
        }

        // enter and tab
        if(c=='\n' || c=='\t'){
            continue;
        }


        //the characters
        str[i]=c;
        i++;
    }
    printf(str);

    return 0;
}


/*
 *
 * functions
 *
 */

// if str1 is equal ti str 2 return 1
int isEqual(char str1[] , char str2[]){
    int i =0;
    while(str1[i]!='\0' && str2[i]!='\0'){
        if(str1[i]!= str2[i])
            return 0;
        i++;
    }
    if(str1[i]=='\0' && str2[i]=='\0')
        return 1;
    else
        return 0;
}

//checks keaywords
int isKeayword(char str[]){
    char KEYWORDS[16][12]= {
            "function",
            "integer" , "int",
            "boolean" , "Boolean",
            "array" ,
            "return",
            "if", "else",
            "while", "for",
            "char", "string", "String",
            "void" , "print" ,
    };
    for(int i = 0; i < 16 ; i++){
        if(isEqual(KEYWORDS[i], str)) {
            printf("KEYWORD\t%d\t(TOKEN_KEYWORD)\n",i);
            return 1;
        }
    }
    return 0;
}

// word is number
int isNumber(char str[]){
    if( str[0] >= '0' && str[0] <='9') {
        printf("CONST\tNONE\t(TOKEN_CONSTANT)\n");
        return 1;
    }
    return 0;
}
