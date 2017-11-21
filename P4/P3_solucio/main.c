/**
 *
 * Practica 4
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#include "red-black-tree.h"

#define MAXLINE      200
#define MAGIC_NUMBER 0x0133C8F9

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct Tree_Thread {
    RBTree *tree;
    char* fitxer; 
};

RBTree *create_tree_thread(void*);

/**
 *
 *  Counts the number of nodes of a tree
 *
 */

int count_nodes_recursive(Node *x)
{
    int nodes;

    nodes = 0;

    /* Analyze the children */
    if (x->right != NIL)
        nodes += count_nodes_recursive(x->right);

    if (x->left != NIL)
        nodes += count_nodes_recursive(x->left);

    /* Take into account the node itself */
    nodes += 1;

    return nodes;
}

int count_nodes(RBTree *tree)
{
    int nodes;

    nodes = count_nodes_recursive(tree->root);

    return nodes;
} 


/**
 *
 *  Process each line that is received from pdftotext: extract the
 *  words that are contained in it and insert them in the tree.
 *
 */

void process_line(char *line, RBTree *tree)
{
    RBData *tree_data;

    int i, j, is_word, len_word, len_line;
    char paraula[MAXLINE], *paraula_copy;

    i = 0;

    len_line = strlen(line);

    /* Search for the beginning of a candidate word */

    while ((i < len_line) && (isspace(line[i]) || (ispunct(line[i])))) i++; 

    /* This is the main loop that extracts all the words */

    while (i < len_line)
    {
        j = 0;
        is_word = 1;

        /* Extract the candidate word including digits if they are present */

        do {

            if (isalpha(line[i]))
                paraula[j] = line[i];
            else 
                is_word = 0;

            j++; i++;

            /* Check if we arrive to an end of word: space or punctuation character */

        } while ((i < len_line) && (!isspace(line[i])) && (!ispunct(line[i])));

        /* If word insert in list */

        if (is_word) {

            /* Put a '\0' (end-of-word) at the end of the string*/
            paraula[j] = 0;

            /* Now transform to lowercase */
            len_word = j;

            for(j = 0; j < len_word; j++)
                paraula[j] = tolower(paraula[j]);

            /* Search the work in the tree */
            tree_data = findNode(tree, paraula);

            if (tree_data != NULL) {
                //printf("Incremento comptador %s a l'arbre\n", paraula);

                /* We increment the number of times current item has appeared */
                tree_data->num_vegades++;

            } else {
                //printf("Insereixo %s a l'arbre\n", paraula);

                /* If the key is not in the list, allocate memory for the data and
                 * insert it in the list */

                paraula_copy = malloc(sizeof(char) * (len_word+1));
                strcpy(paraula_copy, paraula);

                tree_data = malloc(sizeof(RBData));
                tree_data->key = paraula_copy;
                tree_data->num_vegades = 1;

                insertNode(tree, tree_data);
            }
        } /* if is_word */

        /* Search for the beginning of a candidate word */

        while ((i < len_line) && (isspace(line[i]) || (ispunct(line[i])))) i++; 

    } /* while (i < len_line) */
}

/**
 *
 *  Create the tree. This function reads the file filename and opens the pipe with pdftotext and calls process_line
 *  for each line that is received from it.
 *
 */

RBTree *create_tree(char *filename)
{
    FILE *fp;
    RBTree *tree;
    pthread_t* threads;                                            ///////////////////////////// CAMBIO
    struct Tree_Thread* arguments;                                        ///////////////////////////// CAMBIO
    
    int i, num_pdfs;
    char line[MAXLINE];
    char** fitxers;                                                ///////////////////////////// CAMBIO
    

    /* Allocate memory for tree */
    tree = (RBTree *) malloc(sizeof(RBTree));
    arguments = malloc(sizeof(struct Tree_Thread));

    /* Initialize the tree */
    initTree(tree);

    /* Open filename that contains all PDF files */
    fp = fopen(filename, "r");
    if (!fp) {
        printf("ERROR: no he pogut obrir fitxer.\n");
        return NULL;
    }

    /* Llegim el fitxer. Suposem que el fitxer esta en un format correcte */
    fgets(line, MAXLINE, fp);
    num_pdfs = atoi(line);
    
    threads = (pthread_t *) malloc(sizeof(pthread_t)*num_pdfs);    ///////////////////////////// CAMBIO
    fitxers = (char **) malloc(sizeof(char*)*num_pdfs);            ///////////////////////////// CAMBIO
    
    /* Llegim els noms dels fitxers PDF a processar */
    for(i = 0; i < num_pdfs; i++)
    {
        fgets(line, MAXLINE, fp); 
        line[strlen(line)-1]=0;
        
        /* Can I open the pipe ? */
        if(access(line, R_OK ) == -1) {
            printf("ERROR: no puc obrir fitxer d'entrada %s.\n", line);
            continue;
        }
        
        fitxers[i] = (char *) malloc(sizeof(char)*strlen(line));   ///////////////////////////// CAMBIO
        strcpy(fitxers[i], line);
    }
    fclose(fp);
    
    arguments->tree = tree;                                      ///////////////////////////// CAMBIO
    
    for(i = 0; i < num_pdfs; i++)                                  ///////////////////////////// CAMBIO (TOD0 EL BUCLE)
    {                                                              ///////////////////////////// CAMBIO
        arguments->fitxer = fitxers[i];                                              ///////////////////////////// CAMBIO
        if(pthread_create( &threads[i], NULL, (void*)create_tree_thread, (void*) arguments))/////////// CAMBIO
        {                                                          ///////////////////////////// CAMBIO
            fprintf(stderr,"Error - Thread: %d\n",i);              ///////////////////////////// CAMBIO
            exit(EXIT_FAILURE);                                    ///////////////////////////// CAMBIO
        }                                                          ///////////////////////////// CAMBIO
    }                                                              ///////////////////////////// CAMBIO
    return tree;
}


RBTree *create_tree_thread(void* arguments){//////////////////////////// NUEVA FUNCION

    FILE *fp_pipe;                                                 ///////////////////////////// CAMBIO
    char line[MAXLINE], command[MAXLINE];                          ///////////////////////////// CAMBIO
    RBTree *localtree;                                             ///////////////////////////// CAMBIO
                                                                   ///////////////////////////// CAMBIO
    //RBTree *tree = (*arguments).tree;                            ///////////////////////////// CAMBIO
    char* fitxer = ((struct Tree_Thread*)arguments)->fitxer;    ///////////////////////////// CAMBIO
                                                                   ///////////////////////////// CAMBIO
                                                                   ///////////////////////////// CAMBIO
    /* Allocate memory for local tree */                           ///////////////////////////// CAMBIO
    localtree = (RBTree *) malloc(sizeof(RBTree));                 ///////////////////////////// CAMBIO
                                                                   ///////////////////////////// CAMBIO
    /* Initialize the local tree */                                ///////////////////////////// CAMBIO
    initTree(localtree);                                           ///////////////////////////// CAMBIO
    
    /*
     * 
     * Elegir un Archivo no bloquedao y bloquearlo
     * 
     */
    pthread_mutex_lock(&mutex); // lock
    
    printf("Processant fitxer %s\n", line);                        ///////////////////////////// CAMBIO
    
    /*
     * This is the command we have to execute. Observe that we have to specify
     * the parameter "-" in order to indicate that we want to output result to
     * stdout.  In addition, observe that we need to specify \n at the end of the
     * command to execute. 
     */
	printf("Fitxers: %s\n", fitxer);
	sprintf(command, "pdftotext %s -\n", fitxer);                    ///////////////////////////// CAMBIO
	fp_pipe = popen(command, "r");   
	if(fp_pipe){
	    printf("PID: %d\n", getpid());
	}else if (!fp_pipe){                                                              ///////////////////////////// CAMBIO
	    printf("ERROR: no puc crear canonada per al fitxer %s.\n", line);/////////////////////// CAMBIO
	}                            ///////////////////////////// CAMBIO
                                                              ///////////////////////////// CAMBIO
    //Metemos las lineas en el arbol local                         ///////////////////////////// CAMBIO
    while (fgets(line, MAXLINE, fp_pipe) != NULL) {                ///////////////////////////// CAMBIO
        /* Remove the \n at the end of the line */                 ///////////////////////////// CAMBIO
                                                                   ///////////////////////////// CAMBIO
        line[strlen(line) - 1] = 0;                                ///////////////////////////// CAMBIO
                                                                   ///////////////////////////// CAMBIO
        /* Process the line */                                     ///////////////////////////// CAMBIO
        process_line(line, localtree);                             ///////////////////////////// CAMBIO
    }                                                              ///////////////////////////// CAMBIO
    pclose(fp_pipe);                                               ///////////////////////////// CAMBIO
    
    
    /*
     * 
     * Desbloquear el Archivo
     * 
     * Esperar a que el arbol global este desbloqueado.
     * 
     * Bloqueando el acceso al arbol global, meter el arbol local en el arbol global, 
     * 
     */
    pthread_mutex_unlock(&mutex);// unlock
    
    return 0;                                                      ///////////////////////////// CAMBIO
}



/**
 *
 *  Save tree to disc
 *
 */

void save_tree_recursive(Node *x, FILE *fp)
{
    int i;

    if (x->right != NIL)
        save_tree_recursive(x->right, fp);

    if (x->left != NIL)
        save_tree_recursive(x->left, fp);

    i = strlen(x->data->key);
    fwrite(&i, sizeof(int), 1, fp);

    fwrite(x->data->key, sizeof(char), i, fp);

    i = x->data->num_vegades;
    fwrite(&i, sizeof(int), 1, fp);
}


void save_tree(RBTree *tree, char *filename)
{
    FILE *fp;

    int magic, nodes;

    fp = fopen(filename, "w");
    if (!fp) {
        printf("ERROR: could not open file for writing.\n");
        return;
    }

    magic = MAGIC_NUMBER;
    fwrite(&magic, sizeof(int), 1, fp);

    nodes = count_nodes(tree);
    fwrite(&nodes, sizeof(int), 1, fp);

    save_tree_recursive(tree->root, fp);

    fclose(fp);  
}

/**
 *
 *  Load tree from disc
 *
 */

RBTree *load_tree(char *filename)
{
    FILE *fp;
    RBTree *tree;
    RBData *tree_data;

    int i, magic, nodes, len, num_vegades;
    char *paraula;

    fp = fopen(filename, "r");
    if (!fp) {
        printf("ERROR: could not open file for reading.\n");
        return NULL;
    }

    /* Read magic number */
    fread(&magic, sizeof(int), 1, fp);
    if (magic != MAGIC_NUMBER) {
        printf("ERROR: magic number is not correct.\n");
        return NULL;
    }

    /* Read number of nodes */
    fread(&nodes, sizeof(int), 1, fp);
    if (nodes <= 0) {
        printf("ERROR: number of nodes is zero or negative.\n");
        return NULL;
    }

    /* Allocate memory for tree */
    tree = (RBTree *) malloc(sizeof(RBTree));

    /* Initialize the tree */
    initTree(tree);

    /* Read all nodes. If an error is produced, the current read tree is
     * returned to the user. */
    for(i = 0; i < nodes; i++)
    {
        fread(&len, sizeof(int), 1, fp);
        if (len <= 0) {
            printf("ERROR: len is zero or negative. Not all tree could be read.\n");
            return tree;
        }

        paraula = malloc(sizeof(char) * (len + 1));
        fread(paraula, sizeof(char), len, fp);
        paraula[len] = 0;

        fread(&num_vegades, sizeof(int), 1, fp);
        if (num_vegades <= 0) {
            printf("ERROR: num_vegades is zero or negative. Not all tree could be read.\n");
            free(paraula);
            return tree;
        }

        tree_data = malloc(sizeof(RBData));

        tree_data->key = paraula;
        tree_data->num_vegades = num_vegades;

        insertNode(tree, tree_data); 
    }

    fclose(fp);

    return tree;
}


/**
 * 
 *  Menu
 * 
 */

int menu() 
{
    char str[5];
    int opcio;

    printf("\n\nMenu\n\n");
    printf(" 1 - Creacio de l'arbre\n");
    printf(" 2 - Emmagatzemar arbre a disc\n");
    printf(" 3 - Llegir arbre de disc\n");
    printf(" 4 - Consultar informacio d'un node\n");
    printf(" 5 - Sortir\n\n");
    printf("   Escull opcio: ");

    fgets(str, 5, stdin);
    opcio = atoi(str); 

    return opcio;
}

/** 
 *
 * Search the number of times a word appears in the tree
 *
 */

void search_word(RBTree *tree, char *word)
{
    RBData *tree_data;

    tree_data = findNode(tree, word);

    if (tree_data)
        printf("La paraula %s ha aparegut %d vegades als documents analitzats\n", word, tree_data->num_vegades);
    else
        printf("La paraula %s no apareix a l'arbre\n", word);
}


/**
 * 
 *  Main procedure
 *
 */

int main(int argc, char **argv)
{
    char str[MAXLINE];
    int opcio;

    RBTree *tree;

    if (argc != 1)
        printf("Opcions de la linia de comandes ignorades\n");

    /* Inicialitzem a un punter NULL */
    tree = NULL;

    do {
        opcio = menu();
        printf("\n\n");

        switch (opcio) {
            case 1:
                if (tree) {
                    printf("Alliberant arbre actual\n");
                    deleteTree(tree);
                    free(tree);
                }

                printf("Introdueix fitxer que conte llistat fitxers PDF: ");
                fgets(str, MAXLINE, stdin);
                str[strlen(str)-1]=0;

                printf("Creant arbre...\n");
                tree = create_tree(str);
                break;

            case 2:
                if (!tree) {
                    printf("No hi ha cap arbre a memoria\n");
                    break;
                }

                printf("Introdueix el nom de fitxer en el qual es desara l'arbre: ");
                fgets(str, MAXLINE, stdin);

                str[strlen(str)-1]=0;

                printf("Desant arbre...\n");
                save_tree(tree, str);
                break;

            case 3:
                if (tree) {
                    printf("Alliberant arbre actual\n");
                    deleteTree(tree);
                    free(tree);
                }

                printf("Introdueix nom del fitxer amb l'arbre: ");
                fgets(str, MAXLINE, stdin);

                str[strlen(str)-1]=0;

                printf("Llegint arbre de disc...\n");
                tree = load_tree(str);
                break;

            case 4:
                if (!tree) {
                    printf("No hi ha cap arbre a memoria\n");
                    break;
                }

                printf("Introdueix la paraula: ");
                fgets(str, MAXLINE, stdin);
                str[strlen(str)-1]=0;

                if (strlen(str) == 0) {
                    printf("No s'ha introduit cap paraula\n");
                    break;
                }

                search_word(tree, str);
                break;

            case 5:
                if (tree) {
                    printf("Alliberant memoria\n");
                    deleteTree(tree);
                    free(tree);
                }
                break;

            default:
                printf("Opcio no valida\n");

        } /* switch */
    }
    while (opcio != 5);

    return 0;
}



/*
 * fill principal = menu
 * 
 * crear arbre -> principal llegeix l'arxiu i delega la lectura dels arbres a threads que crea
 *                i s'adorm fins que acabin i mostra menu altra vegada.
 *                  -Llegeix el llistat de fixers i el guarda en un vector que pasa als fils.
 *                  -Creacio amb pthread_create i unio/espera amb pthread_join.
 * 
 * A cada fil:
 *              -Cada fil sap quin arbre treballar, compte que dos fills no vulguin treballar el mateix
 *                 fitxer. Per aixo utilitzem: pthread_mutex_lock i pthread_mutex_unlock.
 *              -Llegira el pdf en un arbre local exclusiu per cada fill.
 *              -En llegirles les guardaran a l'arbre global, com han d'accedir varis fils fara falta
 *                 les funcions: pthread_mutex_lock i pthread_mutex_unlock.
 *              -En acabar, el fill allibera l'arbre i si n'hi ha altre pdf el llegira, si no finalitza.
 *              -Informacio necesaria pels fills: Vector de fitxers, punter a l'arbre global, 
 */

