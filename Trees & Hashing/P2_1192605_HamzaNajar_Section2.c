#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define maximum_size 79



typedef struct Node {
    char name[100];
    char active_ingredient[100];
    char category[100];
    char indication[100];
    char expiry_date[100];
    int count;
    char company[100];
    int IndicationsN;
    char indicationS[5][50];
    struct Node* left;
    struct Node* right;
} Node;
typedef struct node {
    char name[100];
    char active_ingredient[100];
    char category[100];
    char indication[100];
    char expiry_date[100];
    int count;
    char company[100];
}HashNode;

typedef struct HashTable {
    HashNode* data[maximum_size];
    int size;
}HashTable;




Node* ReadMedsFile(Node *root );
void Insert_Medicine( Node* root );
Node* Insert( char name[], char active_ingredient[], char category[],char indication[],
                 char expiry_date[], int count, char company[], Node* root );
void inOrder( Node* root );
void Update_Medicine( Node* root );
Node* searching( char name[], Node* root );
Node* Delete( char name[], Node* root );
Node* MIN( Node* root );
void Update_Count( Node* root );
void List_Cateagory ( Node* root, char category[] );
void List_Indications( Node* root, char indication[]);
Node* Delete_Company( char company[], Node* root );
Node* searchingCompany( char BstCompany[], Node* root );
void Save_medicine( Node* root, FILE *out );
void Add_Record(HashTable* table, HashNode* med);
int FunctionH(char* name);
void Print_Hash(HashTable* table);
void FunctionHprint(HashTable* table);
void Hash_Size(HashTable* table);
void searching_Hash(HashTable* table, char* name);
void Delete_Hash(HashTable* table, char* name);
void Save_Hash(HashTable* table);

void main() {
    Node* root = NULL;
    FILE *out, *in;
    root= ReadMedsFile( root);
    int option;
    while (1) {
        printf("Menu:\n");
        printf("1. To show menu 1 (BST) enter 1\n");
        printf("2. To show menu 2 (Hash) enter 2\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
    if(option == 1){
    while(1){
        printf("1. Insert Medicine\n");
        printf("2. List the medicines with their associated information\n");
        printf("3. Update a medicine\n");
        printf("4. Update the Count of a medicine\n");
        printf("5. List medicines by a specific category\n");
        printf("6. List medicines by indication\n");
        printf("7. Delete a medicine\n");
        printf("8. Delete a medicine from a specific company\n");
        printf("9. Save medicines to Pharmacy.txt\n");
        printf("10. Exit\n");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                Insert_Medicine(root);
                break;
            case 2:
                printf("==========================================\n");
                inOrder(root);
                printf("==========================================\n");
                break;
            case 3:
                Update_Medicine(root);
                break; 
            case 4:
                Update_Count(root);
                break;
            case 5:
                printf("insert category: ");
                char category[50];
                scanf("%s", category);
                List_Cateagory (root, category);
                break;
            case 6:
                printf("insert indication: ");
                char indication[50];
                scanf("%s", indication);
                List_Indications(root, indication);
                break;
            case 7:
                printf("Name of medicine you want to delete: ");
                char name[50];
                scanf("%s", name);
                root = Delete(name, root);
                break;
            case 8:
                printf("name of company want to delete: ");
                char company[40];
                scanf("%s", company);
                root = Delete_Company(company, root);
                break;
            case 9:
                printf("your file has been save succesfully\n");
                out = fopen("Pharmacy.txt", "w");
                Save_medicine( root, out );
                fclose(out);
                break;
            case 10:
                exit(0); 
            default:
                    printf("Your input is invalid\n");
                    break;

            


        }
    }
    }
    else if( option == 2){
        int choice;
        char TName[50];
        in = fopen("Pharmacy.txt", "r");
        HashTable* table = (HashTable*)malloc(sizeof(HashTable));
        if (table == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        table->size = 0;

        if (in == NULL) {
                    printf("Pharmacy.txt doesnt open!! \n");
                    exit(3);
        }
        for (int i = 0; i < maximum_size; i++) {
                    table->data[i] = NULL;
        }
        char linee[150];
        while(fgets(linee,sizeof(linee), in) != NULL){
                    HashNode* med = (HashNode*) malloc(sizeof(HashNode));
                    for (int i = 0; i < 150; i++) {
                        if (linee[i] == ' ')
                            linee[i] = '_';
                    }
                    sscanf(linee, "%[a-zA-Z_0-9]:%[a-zA-Z_0-9]:%[a-zA-Z_0-9]:%[^:]:%[^:]:%d:%[a-zA-Z_0-9]",
                           med->name, med->active_ingredient, med->category, med->indication,
                           med->expiry_date, &med->count, med->company);
                    Add_Record(table, med);
                }
                fclose(in);

                while(1){
                    HashNode* temp = (HashNode*) malloc(sizeof(HashNode));
                    printf("1. Print the hash table\n");
                    printf("2. Insert a NEW record\n");
                    printf("3. Print hash function\n");
                    printf("4. Print the size of the hash table\n");
                    printf("5. Search for a record\n");
                    printf("6. Delete Record\n");
                    printf("7. Save the table Records back to Pharmacy.txt\n");
                    printf("8. Exit\n");
                    scanf("%d", &choice);

                    switch (choice)
                    {
                    case 1:
                        Print_Hash(table);
                        break;
                    case 2:
                        printf("Enter the name of the medicine: ");
                            scanf("%s", temp->name);
                            printf("Enter the active ingredient: ");
                            scanf("%s", temp->active_ingredient);
                            printf("Enter the category: ");
                            scanf("%s", temp->category);
                            printf("Enter the indication: ");
                            scanf("%s", temp->indication);
                            printf("Enter the expiry date: ");
                            scanf("%s", temp->expiry_date);
                            printf("Enter the count: ");
                            scanf("%d", &temp->count);
                            printf("Enter the company: ");
                            scanf("%s", temp->company);
                            Add_Record(table, temp);
                            break;
                    case 3:
                           FunctionHprint(table);
                           break;
                    case 4:
                            Hash_Size(table);
                            break;
                    case 5:
                            printf("name of the medicine to searching: ");
                            scanf("%s", TName);
                            searching_Hash(table, TName);
                            break;
                    case 6:
                            printf("medicine you want to delete: ");
                            scanf("%s", TName);
                            Delete_Hash(table, TName);
                            break;
                    case 7:
                            Save_Hash(table);
                            break;
                    case 8:
                           exit(10); 
                    default:
                    
                      printf("Your input is invalid\n");
                
                        break;
                    }
                }
                

    }
    else if (option == 3){
            exit(7);
        }
    else { printf("bye\n");exit(1);}
    }


}


Node* ReadMedsFile( Node* root ) {
    FILE *fp;
    char name[100], active_ingredient[100], category[100], indication[100], expiry_date[100], company[100];
    int count;
    fp = fopen("Meds.txt", "r");
    if (fp == NULL) {
        printf("file no opening !!!\n");
        exit(1);
    }
    char line[150];
    while (fgets(line, sizeof(line), fp) != NULL) {
        for (int i = 0; i < 150; i++) {
            if(line[i] == ' ')
                line[i] = '_';
        }
        sscanf(line, "%[a-zA-Z0-9_]:%[a-zA-Z0-9_]:%[a-zA-Z0-9_]:%[a-zA-Z0-9,_]:%[a-zA-Z0-9/]:%d:%[a-zA-Z0-9_]", name, active_ingredient, category, indication, expiry_date, &count, company);
        root = Insert(name, active_ingredient, category, indication, expiry_date, count, company, root);
    }
    fclose(fp);
    return root;
}


//add a new medicine to the BST
void Insert_Medicine( Node* root ){
    char name[100], active_ingredient[100], category[100], indication[100], expiry_date[100], company[100];
    int count;
    printf("Enter the name of the the new medicine: ");
    scanf("%s", name);
    printf("Enter the active ingredient: ");
    scanf("%s", active_ingredient);
    printf("Enter the category: ");
    scanf("%s", category);
    printf("Enter the indication: ");
    scanf("%s", indication);
    printf("Enter the expiry date: ");
    scanf("%s", expiry_date);
    printf("Enter the count: ");
    scanf("%d", &count);
    printf("Enter the company: ");
    scanf("%s", company);
    root = Insert(name, active_ingredient, category, indication, expiry_date, count, company, root);
}

Node* Insert( char name[], char active_ingredient[], char category[],char indication[],
                 char expiry_date[], int count, char company[], Node* root ){
    if( root == NULL ){
        root = (struct Node*) malloc( sizeof( struct Node ) );
        if( root == NULL)
            printf("NO space");
        else{
            strcpy(root->name, name);

            strcpy(root->active_ingredient, active_ingredient);
            strcpy(root->category, category);
            strcpy(root->indication, indication);
            char* token;
            int i=0;
            token = strtok(indication, ",");
            while(token != NULL){
                root->IndicationsN++;
                strcpy(root->indicationS[i], token);
                token = strtok(NULL, ",");
                i++;
            }
            strcpy(root->expiry_date, expiry_date);
            root->count = count;
            strcpy(root->company, company);
            root->left = root->right = NULL;
        }
    }
    else if( strcmp(name, root->name) < 0 ){
        root->left = Insert( name, active_ingredient, category,
                             indication,expiry_date, count, company, root->left );
    }
    else if( strcmp(name, root->name) > 0 ){
        root->right = Insert( name, active_ingredient, category,
                              indication,expiry_date, count, company, root->right );
    }
    return root;
}
//function to print all the medicine in order
void inOrder( Node* root ){
    if( root ){
        inOrder( root->left );//we start from the left
        printf("Name: %s\n", root->name);
        printf("Active Ingredient: %s\n", root->active_ingredient);
        printf("Category: %s\n", root->category);
        printf("Indication: %s\n", root->indication);
        printf("Expiry Date: %s\n", root->expiry_date);
        printf("Count: %d\n", root->count);
        printf("Company: %s\n", root->company);
        printf("\n");
        inOrder( root->right );
    }
}


Node* searching( char name[], Node* root ){
    if( root == NULL )//if it is not found return null
        return NULL;
    if( strcmp( name, root->name ) < 0 )//we are searching in the tree if its left or right node
        return searching( name, root->left );
    else if( strcmp( name, root->name) > 0 )// here is right
        return searching( name, root->right );
    else
        return root;
}

//update a medicine with new data
void Update_Medicine( Node* root ){
    char name[100], active_ingredient[100], category[100], indication[100], expiry_date[100], company[100];
    int count;
    printf("Enter Medicine Name: ");
    scanf("%s", name);
    root = searching(name, root);//search for the name of medicine
    if(root == NULL){
        printf("Medicine not found\n");//if medicine is not in Bst
    }
    else{
        root = Delete(name, root);//if its found we delete the old data and get new data
        printf("Enter the new name of the medicine: ");
        scanf("%s", name);
        printf("Enter the new active ingredient: ");
        scanf("%s", active_ingredient);
        printf("Enter the new category: ");
        scanf("%s", category);
        printf("Enter the new indication: ");
        scanf("%s", indication);
        printf("Enter the new expiry date: ");
        scanf("%s", expiry_date);
        printf("Enter the new count: ");
        scanf("%d", &count);
        printf("Enter the new company: ");
        scanf("%s", company);
        root = Insert(name, active_ingredient, category, indication, expiry_date, count, company, root);
    }
}


Node* MIN( Node* root ){
    if( root != NULL )
        while( root->left != NULL )
            root = root->left;
    return root;
}


Node* Delete( char name[], Node* root ){
    Node* Cells;
    if( root == NULL )
        printf( "Medicine not found\n" );
    else if( strcmp( name, root->name ) < 0 )    //left >>>>
        root->left = Delete( name, root->left );
    else if( strcmp( name,root->name ) > 0 )    //right>>>>
        root->right = Delete( name, root->right );
    else
    if( root->left && root->right )//if it has 2 children
    {
        //replace with smallest in right sub
        Cells= MIN( root->right );
        strcpy(root->name, Cells->name);
        strcpy(root->active_ingredient, Cells->active_ingredient);
        strcpy(root->category, Cells->category);
        strcpy((char *) root->indication, (char *) Cells->indication);
        strcpy(root->expiry_date, Cells->expiry_date);
        root->count = Cells->count;
        strcpy(root->company, Cells->company);
        root->right = Delete( root->name, root->right );
    }
    else    //if it has no children or only 1
    {
        Cells = root;
        if( root->left == NULL )
           //0 children
            root = root->right;
        else if( root->right == NULL )
            root = root->left;
        free( Cells);
    }
    return root;
}

//update medicine count
void Update_Count( Node* root ){
    char name[50];
    int count;
    printf("Enter the name of the medicine you wnt to update count: ");
    scanf("%s", name);
    root = searching(name, root);//we search for the medicine
    if(root == NULL){
        printf("Medicine not found\n");
    }
    else{
        printf("Enter the new count: ");
        scanf("%d", &root->count);
    }
}


//function to list category of a medicine and find if it is found
void List_Cateagory ( Node* root, char category[]){
    if( root != NULL ){
        List_Cateagory ( root->left, category);
        if(strcmp(root->category, category) == 0){//we try to find the category
            if(root->count == 0){
                printf("%s - not found", root->name); //if the category is not found in any of meds
            }
            else{
                printf("has it = %s\n", root->name);//if its found
            }
        }
        List_Cateagory ( root->right, category);
    }
}

//function to list indication of a medicine and find if it is found
void List_Indications( Node* root, char indication[]){
    if( root != NULL ){
        List_Indications( root->left, indication);
        for (int i = 0; i < 5; ++i) {
            if(strcmp(root->indicationS[i], indication) == 0){
                if(root->count == 0){
                    printf("%s - not found", root->name);
                }
                else{
                    printf("has it =%s\n", root->name);
                }
            }
        }
        List_Indications( root->right, indication);
    }
}


//searching a node in the tree by company name
//search for medicine(s) by company name in the tree and return the first found node
Node* searchingCompany( char company[], Node* root ){
    if( root != NULL ){
        if(strcmp(root->company, company) == 0){
            return root;
        }
        else{
            Node* Cells;
            Cells = searchingCompany( company, root->left);
            if(Cells == NULL){
                Cells = searchingCompany( company, root->right);
            }
            return Cells;
        }
    }
    else{
        return NULL;
    }
}

Node* Delete_Company( char company[], Node* root ){
// This function will delete all the nodes of a specific company
    while (1){
        Node* Cells=NULL;
// searchingCompany function will search for the company in the BST
        Cells = searchingCompany(company, root);
        if(Cells == NULL){
// if company not found then break the loop
            break;
        }
        else{
// Delete function is called to delete the specific node
            root = Delete(Cells->name, root);
        }
    }
    return root;
}



//save the medicines in the tree to a file
// save the medicines in the tree to a file
void Save_medicine( Node* root, FILE *out ){
    if (out == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
// check if the root is not null
    if( root != NULL ){
// recursively save left subtree
        Save_medicine( root->left, out );
        char line[150];
// copy the data of the node to a line
        sprintf(line, "%s:%s:%s:%s:%s:%d:%s", root->name, root->active_ingredient, root->category, root->indication,
                root->expiry_date, root->count, root->company);
// replace "" with "_"
        for (int i = 0; i < 150; i++) {
            if(line[i] == ' '){
                line[i] = '_';
            }
        }
// write the line to the file
        fprintf(out, "%s\n", line);
// recursively save right subtree
        Save_medicine( root->right, out );
    }
}

void Add_Record(HashTable* table, HashNode* med) {
    int c = 0, i = FunctionH(med->name);
    while (table->data[i] != NULL) {
//increment number of collisions
        c++;
//use the quadratic probing method to find the next empty spot in the table
        i = (FunctionH(med->name) + c * c ) % maximum_size;
    }
//insert the new medicine into the empty spot
    table->data[i] = med;
//increment the size of the table
    table->size++;
//print the number of collisions that happened in this insertion
    printf("%d collisions happened in %s\n", c,
           table->data[i]->name);
}

int FunctionH(char* name) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += name[i];
    }
    return sum % maximum_size;
}

//function to print the hash table data including empty spots
void Print_Hash(HashTable* table){
    for (int i = 0; i < maximum_size; i++) {
        if(table->data[i]->name == NULL){
            printf("cell %d -> empty cell\n", i);
        }
        else{
            printf("cell %d -> %s\n", i, table->data[i]->name);
        }
    }
}

//prints the hash function
void FunctionHprint(HashTable* table) {
    printf("The hash function used is (x + i^2) mod %d, where x is the input key, i is the number of collisions, and %d is the size of the hash table.\n", maximum_size, maximum_size);
}


//function to print the count of non-empty spots in a hash table
void Hash_Size(HashTable* table) {
    int count = 0;
    for (int i = 0; i < maximum_size; i++) {
        if (table->data[i] != NULL) {
            count++;
        }
    }
    printf("The size of the hash table is %d\n", count);
}



void searching_Hash(HashTable* table, char* name) {
    int c = 0, i = FunctionH(name);
    while (1) {
        if (table->data[i] == NULL || table->data[i]->name == NULL) {
            printf("Medicine not found.\n");
            return;
        }
        if (strcmp(table->data[i]->name, name) == 0) {
            break;
        }
        c++;
        i = (FunctionH(name) + c * c ) % maximum_size;
    }
    printf("%d collisions happened before searchinging the medicine.\n", c);
    printf("Name: %s\n", table->data[i]->name);
    printf("Active Ingredient: %s\n", table->data[i]->active_ingredient);
    printf("Category: %s\n", table->data[i]->category);
    printf("Indication: %s\n", table->data[i]->indication);
    printf("Expiry Date: %s\n", table->data[i]->expiry_date);
    printf("Count: %d\n", table->data[i]->count);
    printf("Company: %s\n", table->data[i]->company);
}

// This function is used to delete a specific medicine from the hash table using its name as the key.
// It starts by calculating the initial index using the hash function with the input name, and then it iterates
void Delete_Hash(HashTable* table, char* name) {
    int c = 0, i = FunctionH(name);
    while (1) {
        if (table->data[i] == NULL) {
            printf("Record with name %s not found.\n", name);
            return;
        }
        if (strcmp(table->data[i]->name, name) == 0) {
            break;
        }
        c++;
        i = (FunctionH(name) + c * c ) % maximum_size;
    }
    free(table->data[i]);
    table   ->data[i] = NULL;
    table->size--;
    printf("Record with name %s deleted successfully!\n", name);
}




//function to save the medicines data to the file
void Save_Hash(HashTable* table) {
    FILE *out = fopen("Pharmacy.txt", "w");
    if (out == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < maximum_size; i++) {
        HashNode* medicine = table->data[i];
        if (medicine != NULL) {
            char line[150];
            sprintf(line, "%s:%s:%s:%s:%s:%d:%s", medicine->name, medicine->active_ingredient,
                    medicine->category, medicine->indication, medicine->expiry_date,
                    medicine->count, medicine->company);
            for (int j = 0; j < 150; j++) {
                if(line[j] == '_'){
                    line[j] = ' ';
                }
            }
            fprintf(out, "%s\n", line);
        }
    }
    fclose(out);
    printf("Data saved successfully to Pharmacy.txt!\n");
}