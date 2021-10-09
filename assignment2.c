#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#define MAX 30  //maximum characters in the word
#define MAXCHARS 10
#define MAXSTR 23
#define MAXWORD 101

#define MAXLINE1 23
#define MAXLINE2 24
#define MAXLINE3 101

// algorithms are awesome
typedef char word_t [MAXCHARS + 1];
// struct for stage1 
typedef struct{
    char line1[MAXLINE1];
    char line2[MAXLINE2];
    char line3[MAXLINE3];
        
   
}input_t;

// struct for stage 2

struct stage2_1{
    char line12[MAXLINE1];
    char line22[MAXLINE2];
    char line32[MAXLINE3];
};
// function prototype
int getword(char W[], int limit) ;
int read_line(char str[], int max);
int search(struct stage2_1 st[101],int n ,char word[], int* pointer);



// second way
typedef struct node node_t;

typedef word_t data_t[1000];

struct node {
	char data[MAX];
	node_t *next;
};

typedef struct {
	node_t *head;
	node_t *foot;
} list_t;

list_t *make_empty_list(void);

int is_empty_list(list_t *list);

void free_list(list_t *list);



list_t *insert_at_foot(list_t *list, char value[]);

int get_head(list_t *list, char str[]);

list_t *get_tail(list_t *list);







// MAIN function
int main(int argc,char * argv[]){
    // array str to store each line
    char str[MAXLINE3];
   
    int i=0;
    // stage 1 struct
    input_t stage1;
    
    //stage 2 struct
    struct stage2_1 st[101];
    
   
    int total=0;
    int total_word = 1;
    
    // variable to store the average number of variation form per word
    double average ;
    
    
    
    // read first line
    read_line(str, 101);
    
    strcpy(stage1.line1,str);
    strcpy(st[0].line12,str);
    
    // read second line
    read_line(str, 101);
    strcpy(stage1.line2,str);
    strcpy(st[0].line22,str);
    
    // read third line
    read_line(str, 101);
    // count number of variation form
    for (int h=0; h< 101; h++){
        if (str[h] == '0' || str[h] == '1' ||
            str[h] =='2' || str[h] =='3'){
            // add it to total
            total ++;
           
                }
        }
    
   
    
 
    strcpy(stage1.line3,str);
    strcpy(st[0].line32,str);
    
    printf("==========================Stage 1==========================\n");
    printf("Word 0: %s\n",stage1.line1);
    
    printf("POS: %s\n",stage1.line2);
    printf("Form: %s\n",stage1.line3);
    
    
    // Stage 2
    
    
    // read second word
    
    read_line(str, 101);
    
    // stop reading when '*' is found
    while (str[0] != '*'){
        
    
        // copy first line
        strcpy(st[i].line12,str);
        total_word++;
        // read second line
        read_line(str, 101);
        
        // copy second line
        strcpy(st[i].line22,str);
        
        // read third line
        read_line(str, 101);
        
        
        //copy third line
        strcpy(st[i].line32,str);
        
        for ( int h=0; h< MAXLINE3; h++){
            if (st[i].line32[h] == '0' || st[i].line32[h] == '1' ||
                st[i].line32[h] =='2' || st[i].line32[h] =='3'){
                total++;
                }
        }
           
        i++;
        
        // read first line
        read_line(str,21);
        
            
        }
    
    // calculate average number of variation form
    
    average =(double)total/(double)total_word;
    
    printf("==========================Stage 2==========================\n");
    printf("Number of words: %d\n",total_word);
    printf("Average number of variation forms per word: %.2f\n",average);
    
    // Stage 3
    
    word_t one_word, all_word[1000];
    int l;
    // read the final line in stdin into str2[]
    char str2[1000];
    int max = 1000;
    int n=0,count = 0;
    int c;
    
    while ((c= getc(stdin)) != EOF && c!= '\n'){
        if (isalnum(c)|| c== '*' || c == ' ' ){
            
            str2[n++] = c;
            
            if (n == max-1){
                str2[n++] = '\0';
                
            }
        
        }
    }
    
    
    // calculate number of space to calculate number of word( = no.space+1)
   
    for ( int g = 0; g < n; g++){
        if (str2[g] == ' '){
            count++;
        }
    }
    
    
   
    // push back information into stdin to use getchar
    for ( int q =n; q > -1; q--){
        ungetc(str2[q],stdin);
    }
  
    // copy all the word into an array all_word to use in stage 4
    for ( l=0; l <count+1; l++){
        
       getword(one_word,MAXCHARS);
       strcpy(all_word[l],one_word);
        
    }
    
    
    
    // give the pointer the value of i, pass it into function
    int *pointer;
    pointer = &i;
    
    
   // linked list
    
    list_t *list = make_empty_list();
    for (int y = 0; y<count+1;y++){
        list = insert_at_foot(list,all_word[y]);
    }
    
    char str1[30];
    list_t* p = list;
    get_head(list,str1);
    printf("==========================Stage 3==========================\n");
    while (list -> head){
        get_head(list,str1);
        
    
        
        if(search(st,total_word,str1,pointer) == 1){
            
            
            printf("%-26s",str1);
            printf("%s\n", st[i].line22);
            
            
        }else{
            printf("%-26s",str1);
            printf("NOT_FOUND\n");
            
        }
       
        
      //go to next node
        list = get_tail(list);
        
    }
    free_list(p);
    
    
    
    
    // stage 4( final stage)
    
    printf("==========================Stage 4==========================\n");
    int check,check1;
    char * ret;
    char copy[25];
    
    for ( l = 0; l < count +1; l++){
        for ( int t = 0; t < total_word; t++){
            ret = strstr(st[t].line32,all_word[l]);
            
            if (ret != NULL){
                printf("%-26s",all_word[l]);
                printf("%-26s",st[t].line12);
                printf("%s\n",st[t].line22);
                
                check = 1;
                
            }
            
            if (!strcmp(st[t].line12,all_word[l])){
                strcpy(copy,st[t].line22);
                check1 = 1;
            }
        }
        if (check == 0 && check1 == 1){
            printf("%-26s",all_word[l]);
            printf("%-26s",all_word[l]);
            printf("%s\n",copy);
            
        }
       
        
        if ( check == 0 && check1 == 0){
            printf("%-26s",all_word[l]);
            printf("%-26s",all_word[l]);
            printf("NOT_FOUND\n");
        }
        check = 0;
        check1 = 0;
            
    }
                
            
        
    
 
    return 0;
    
}




// supporting function for stage 1 and 2

int read_line(char str[], int max){
    int n=0, c;
    while ((c= getc(stdin)) != EOF && c!= '\n'){
        if (isalnum(c)|| c== '*' || c == ' ' ){
            
            str[n++] = c;
            if (n == max-1){
                str[n++] = '\0';
                return 1;
            }
        
        }
    }
    if (c == EOF && n ==0) {
        return 0;
    }
    str[n++] = '\0';
    return 1;
        
}



int getword(char W[], int limit) {
	int  c,len=0;
    
    
            
 
	while ((c=getchar())!=EOF && !isalpha(c))  {
        
    }
    
   
     
	if (c==EOF) {
		return EOF;
	}
    
        
        
	W[len++] = c;
	while (len<limit && (c=getchar())!=EOF && isalpha(c)) {
        W[len++] = c;
            
        }
	
	
	W[len] = '\0';
    
   
   
	return 0;
}

// from the textbook, remember to reference correctly

int search(struct stage2_1 st[101],int n,char word[],int* pointer)
{
    int lb, mid, ub;
    lb = 0;                             //lower bound to 0
    ub = n;                             //upper bound to n
    do
    {
        mid = (lb + ub) / 2;             //finding the mid of the array
        if ((strcmp(word,st[mid].line12))<0)       //compare the word with mid
            ub = mid - 1;                          //if small then decrement ub
        else if ((strcmp(word,st[mid].line12))>0)
            lb = mid + 1;                          //if greater then increment lb
       
    } while ((strcmp(word,st[mid].line12)!=0) && lb <= ub);
    if ((strcmp(word,st[mid].line12))==0){
        *pointer = mid;
        return 1;
    
        
    } 
    
    
    return 0 ;
}


// listops.c

list_t
*make_empty_list(void) {
	list_t *list;
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}

int
is_empty_list(list_t *list) {
	assert(list!=NULL);
	return list->head==NULL;
}

void
free_list(list_t *list) {
	node_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;
	while (curr) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(list);
}


list_t
*insert_at_foot(list_t *list, char value[]) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	strcpy(new->data, value);
	new->next = NULL;
	if (list->foot==NULL) {
		  
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}

list_t
*get_tail(list_t *list) {
	node_t *oldhead;
	assert(list!=NULL && list->head!=NULL);
	oldhead = list->head;
	list->head = list->head->next;
	if (list->head==NULL) {
		 
		list->foot = NULL;
	}
	free(oldhead);
	return list;
}


int
get_head(list_t *list, char str[]) {
	assert(list!=NULL && list->head!=NULL);
    strcpy(str, list->head->data);
	return 0;
    }


                
                
               
                
                
                
        
        
        
    
      
                
    







