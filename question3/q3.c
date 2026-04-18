#include <stdio.h>
#include <string.h>

struct nlist {              // table entry:
    struct nlist *next;     // next entry in chain
    char *name;             // defined name
    char *defn;             // replacement text
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; // pointer table

// hash: form hash value for string
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

// lookup:look for s in hashtab
struct nlist *lookup(char *s)
{
    struct nlist *np;

    // loop through linked list
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; // found

    return NULL;       // not found
}

struct nlist *lookup(char *);

// install:put (name, defn) in hashtab
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { // not found
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else // already there
        free((void *) np->defn); // free previous defn
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}

void intersection(int output[], int array1[], int lenArr1, int array2[], int lenArr2){
    int count = 0;
    char buffer[12];

    for (int i = 0; i < lenArr1; i++){
        sprintf(buffer, "%d", array1[i]);
        install(buffer, "1");
    }
    
    for (int i = 0; i < lenArr2; i++) {
        sprintf(buffer, "%d", array2[i]);
        struct nlist *found = lookup(buffer);
        if (found != NULL && strcmp(found->defn, "-1") != 0) {
            output[count++] = array2[i];  
            free(found->defn);
            found->defn = strdup("-1");
        }
    }
    output[count] = -1;
}

int main()
{
    int n1, n2;
    scanf("%d", &n1);
    int array1[n1];
    for (int i = 0; i < n1; i++){
        scanf("%d", &array1[i]);
    }

    scanf("%d", &n2);
    int array2[n2];
    for(int i = 0; i < n2; i++){
        scanf("%d", &array2[i]);
    }

    int size = n1 > n2? n1 : n2;
    int output[size+1];
    intersection(output, array1, n1, array2, n2);

    
    for (int i = 0; i < size && output[i] != -1; i++){
        printf("%d ", output[i]);
    }
    printf("\n");

    return 0;
}

