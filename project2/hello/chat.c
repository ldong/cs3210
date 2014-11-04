#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

#define BUFFSIZE 1024

/*
 * Author: Lin Dong, YiXin Chen
 * Date: Fri Oct 31 14:00:43 EDT 2014
 */

/* functions */
void ask_input();
void write_to_file(char*, char*);
void read_from_file(char*, char*);
bool is_file_exists(const char* file);
void print_me(char* file_name);

/* variables */
char input[BUFFSIZE];
char output[BUFFSIZE*5];

int main(){
    ask_input();
    char file_name[] = "a.txt";
    /* char file_name[] = "/proc/text"; */
    write_to_file(file_name, input);
    /* char file_to_read[] = "/proc/text_out"; */
    /* char file_to_read[] = "/Users/ldong/GDrive/School/2014Fall/cs3210/Project2/hello/file.txt"; */
    /* read_from_file(file_to_read, output); */
    /* print_me(file_to_read); */
    /* print_me(file_name); */
    return 0;
}

bool is_file_exists(const char* file) {
    struct stat buf;
    return (stat(file, &buf) == 0);
}

void ask_input(){
    printf("Please input the string converts to morse code: ");
    fgets (input, 100, stdin);
    printf("Your input is: %s", input);
}

void write_to_file(char* file_name, char* text){
    FILE *f = fopen(file_name, "w");
    printf("%s\n", file_name);
    fprintf(f, "%s\n", text);
    fclose(f);
}

void read_from_file(char* file_name, char* text){
    if(is_file_exists(file_name)){
        char ch;
        FILE *fp = fopen(file_name, "r");
        printf("Reading file from\n%s\n", file_name);
        while( ( ch = fgetc(fp) ) != EOF ){
            printf("%c",ch);
        }
        fclose(fp);
    }
}

void print_me(char* file_name){
    if(is_file_exists(file_name)){
        char ch;
        FILE *fp = fopen(file_name, "r");
        printf("Reading file from: %s\n", file_name);
        while( ( ch = fgetc(fp) ) != EOF ){
            printf("%c",ch);
        }
        fclose(fp);
    } else {
        printf("Not found\n");
    }
}


