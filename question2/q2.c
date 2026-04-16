#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD 100

struct tnode {           // the tree node:
    char *word;          // points to the text
    int count;           // number of occurrences
    struct tnode *left;  // left child
    struct tnode *right; // right child
};


//First tree
struct tnode *addtree(struct tnode *, char *);
struct tnode *addbycount(struct tnode *, struct tnode *);
struct tnode *addcounttree(struct tnode *, struct tnode *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
char *mystrdup(char *);

// word frequency count
int main() {
    struct tnode *root = NULL;
    struct tnode *sortroot = NULL;
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF){
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    sortroot = addcounttree(sortroot, root);

    treeprint(sortroot);
    return 0;
}


// addtree: add a node with w, at or below p
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    if (p == NULL) {    // a new word has arrived
        p = talloc();   // make a new node
        p->word = mystrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;     // repeated word
    else if (cond < 0)  // less than into left subtree
        p->left = addtree(p->left, w);
    else                // greater than into right subtree
        p->right = addtree(p->right, w);
    return p;
}

//create the NEW tree, by counting
struct tnode *addbycount(struct tnode *p, struct tnode *node_new) {
    if (p == NULL) { //base case, when counting tree node hasn't been made yet
        p = talloc();
        p->word = mystrdup(node_new->word);
        p->count = node_new->count;
        p->left = p->right = NULL;
    } else if (node_new->count >= p->count) { //higher or equal freqency goes left
        p->left = addbycount(p->left, node_new);
    } else { //lower frequency goes right
        p->right = addbycount(p->right, node_new);
    }
    return p;
}

//traverse the OLD tree, and add to the new tree when needed
struct tnode *addcounttree(struct tnode *p, struct tnode *q) {
    if (q != NULL) {
        p = addcounttree(p, q->left); //go down left of tree 1

        p = addbycount(p, q); //process node, add to new tree

        p = addcounttree(p, q->right); //go down right of tree 1
    }
    return p;
}

//bad logic--
/*
struct tnode *addcounttree(struct tnode *p, struct tnode *q) {
    if (q->left != NULL) {   //recurse on left branch
        p = addcounttree(p, q->left);
    }

    
    else if (q->left == NULL && q->right == NULL) {    // end of the line
        int cond;
        if (p == NULL) {
            p = talloc();   // make a new node
            p->word = mystrdup(q->word);
            p->count = q->count;
            p->left = p->right = NULL;
        }
        else if (cond = p->count - q->count == 0) { //equal count
            p->left = addcounttree(p->left, q);
        }
        else if (cond = p->count - q->count < 0) { //less count
            p->left = addcounttree(p->left, q);
        }
        else if (cond = p->count - q->count == 0) { //more count
            p->right = addcounttree(p->right, q);
        }
    }

        if (q->right != NULL) {   //recurse on right branch
        p = addcounttree(p, q->right);
    }

    return p;    
}
*/

//Input function
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}


char *mystrdup(char *s) // make a duplicate of s
{
    char *p;
    p = (char *) malloc(strlen(s)+1); // +1 for '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}


//other functions
#define BUFSIZE 100
char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0; // next free position in buf
int getch(void) // get a (possibly pushed back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push character back on input
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many caracters\n");
    else
        buf[bufp++] = c;
}

void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

