#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_SIZE 20 
#define ARRAY_SIZE 59  
int collisions=0;
int num_terms=0;

typedef struct Element Element;
struct Element{
    char key[MAX_STRING_SIZE];
    int value;  
};

Element* hashTable[ARRAY_SIZE];

int hash3(char* s)
{ 
    int hash = 0; 
    while(*s){
        hash = 1+ (hash + *s) % (ARRAY_SIZE-1);
        s++;
    }
    return hash;
}

int hash(char* s){ int hash = 0; while(*s){
hash = (hash + *s) % ARRAY_SIZE;
s++;
}
return hash;
}

Element *createNewElement(char *name){
    Element *e;
    strcpy(e->key, name);
	e->value = 1;
    return e;
}

int insert(char *name, int pos)
{
    int i = pos;
    int compare;
    compare = strcmp("",hashTable[i]->key);
    if(compare!=0){
        collisions++;
        int idx = hash3(name);
        hashTable[idx] = createNewElement(name);
    }
    return 0;
}
 
int search( char *name)
{
    int hv = hash(name);
    int compare;
    compare = strcmp(name,hashTable[hv]->key);
    if(compare==0){
        return hv;
    }
    else{
        int idx = hash3(name);
        compare = strcmp(name,hashTable[idx]->key);
        
        if(compare==0){
            return idx;
        }
    }
    return -1;
}

int addOrIncrement(char *name)
{
    int index = search(name);
    if (index!=-1){
        hashTable[index]->value++;
        return 1;
    }
    else{
        int pos=hash(name);
        int status=insert(name,pos);
        if(status==1){
            return 1;
        }
        else if(status==0){
            return 0;
        }
    }
}

void printNumberOfOccurences(char* name)
{
    int index = search(name);
    if (index!=-1){
        printf("%s - %i \n", name, hashTable[index]->value);
    }
    else{
        printf("%s not in table", name);
    }
}


void next_token ( char *buf, FILE *f, int string_max ) {
    num_terms++;
	buf[0] = fgetc(f);
	while ( !isalnum(buf[0]) && !feof(f) ) { buf[0] = fgetc(f); }
	int i=1;
	for (;;) {
		buf[i] = fgetc(f);
		if( !(isalnum(buf[i]) || buf[i]==" ") ) { break; } 
		if( feof(f) ) { break; }          
		if( i < (string_max-1) ) { ++i; } 
	}
	buf[i] = '\0'; 
}

int load_file ( char *fname ) {
	FILE *f;
	char buf[MAX_STRING_SIZE];
	f = fopen(fname, "r");
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}
	while ( !feof(f) ) {
		next_token(buf, f, MAX_STRING_SIZE);
		addOrIncrement( buf);                           
	}
	fclose(f);
	return 1;
}



int main()
{
	for(int j=0;j<ARRAY_SIZE;j++){
	    strcpy(hashTable[j]->key,"");
	    hashTable[j]->value = 0;
	}
	char filename[]="names.csv";
	printf("%s loaded", filename);
	printf("\t Capacity : %i",ARRAY_SIZE);
	printf("\t Num Terms : %i",num_terms);
	printf("\t Collisions : %i",collisions);
	printf("\t Load : %f",num_terms/ARRAY_SIZE);
	char surname[MAX_STRING_SIZE];
	scanf("%s", &surname);
	printNumberOfOccurences(surname);
	//char arr[5] = "hello";
// 	int hval;
// 	hval = hash(arr);
// 	hashTable[hval] = createNewElement(arr);
    return 0;
}