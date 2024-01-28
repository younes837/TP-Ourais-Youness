#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct date{
    int day;
    int month;
    int year;
};
struct employe{
    int code;
    char nom[50];
    char prenom [50];
    struct date dateNaissance;
    char titrePoste[50];
    float salaire;
    struct employe *next;


};
struct liste{
    struct employe *head;
};
int isEmpty(struct liste *list){
    return list->head==NULL;
}

void loadData(struct liste *list){
    FILE *f=fopen("employees.txt","r");

    while(1)
    {
        struct employe * newEmp=malloc(sizeof(struct employe));
        if(fscanf(f,"%d %s %s %d/%d/%d %s %f",&newEmp->code,newEmp->nom,newEmp->prenom
                ,&newEmp->dateNaissance.day,&newEmp->dateNaissance.month,&newEmp->dateNaissance.year,newEmp->titrePoste,&newEmp->salaire)!=EOF){
            newEmp->next=NULL;
            addToListe(list,newEmp);

        }else{
            break;
        }
    }

    fclose(f);

}

void afficherList(struct liste *listEmployees){
    struct employe * it=listEmployees->head;
    while(it!=NULL){
        printf("%d %s %s %d/%d/%d %s %.2f\n",it->code,it->nom,it->prenom
                ,it->dateNaissance.day,it->dateNaissance.month,it->dateNaissance.year,it->titrePoste,it->salaire);
        it=it->next;
    }
}

void addToListe(struct liste *listEmployees,struct employe *newEmp){
    if(isEmpty(listEmployees)){
            listEmployees->head=newEmp;
    }else{
        struct employe* it=listEmployees->head;
        while(it->next!=NULL){
            it=it->next;
        }
        it->next=newEmp;
    }
}

struct employe *findByCode(struct liste * listeEmployees, int code){
    struct employe* it=listeEmployees->head;

    while(it!=NULL){
        if(it->code==code){
            return it;
        }
        it=it->next;

    }
    return NULL;
};



void ajouteEmploye(char * nom, char* prenom ,int day,int month,int year,char * titrePoste, float salaire,struct liste* listeEmployees){
    int random ;
    do{
        srand(time(NULL));
        random= rand() % 1000+700 ;

    }while(findByCode(listeEmployees,random)!=NULL);
    struct employe *newEmp=malloc(sizeof(struct employe));

    newEmp->code=random;
    strcpy(newEmp->nom,nom);
    strcpy(newEmp->prenom,prenom);
    strcpy(newEmp->titrePoste,titrePoste);
    newEmp->salaire=salaire;
    newEmp->dateNaissance.day=day;
    newEmp->dateNaissance.month=month;
    newEmp->dateNaissance.year=year;
    newEmp->next=NULL;
    addToListe(listeEmployees,newEmp);
    printf("Employe ajouté avec succes\n");

}


struct liste* initListe(){
    struct liste* listeEmployees=malloc(sizeof(struct liste));
    listeEmployees->head=NULL;
    return listeEmployees;
};


void deleteEmploye(int code,struct liste *listeEmployees){
    struct employe* deleted=findByCode(listeEmployees,code);
    if(deleted){
        int choix;
        printf("Voulez vraiment supprimer? 1 Pour supprimer. 2 Pour anuuler.  ");
        scanf("%d",&choix);
        if(choix==1){


            struct employe *it=listeEmployees->head;
            if(deleted==it){
                listeEmployees->head=deleted->next;
                free(deleted);

            }else{
                while(it->next!=NULL){
                    if(it->next->code==code){

                        struct employe * deleted=it->next;
                        it->next=it->next->next;
                        free(deleted);
                        break;
                    }
                    it=it->next;
                }
            }
        }else{
            printf("Vous avez annulé la suppression\n");
        }
    }else{
        printf("n'existe pas");
    }
}

void printEmploye(struct employe *emp){
     printf("%d %s %s %d/%d/%d %s %.2f\n",emp->code,emp->nom,emp->prenom
                ,emp->dateNaissance.day,emp->dateNaissance.month,emp->dateNaissance.year,emp->titrePoste,emp->salaire);

}

void findByNom(struct liste *listeEmployees,char *nom){
    struct employe* it=listeEmployees->head;
    int count=0;
    while(it!=NULL){
        const char *string1 = it->nom;
        const char *string2 = nom;
        if(strcmp(string1,string2)==0){
            printEmploye(it);
            count++;
        }
        it=it->next;
    }
    if(count>0){
        printf("Nombre d'employees trouve est %d",count);
    }else{
        printf("aucun employe est trouve");
    }
}


void findByPrenom(struct liste *listeEmployees,char *prenom){
    struct employe* it=listeEmployees->head;
    int count=0;
    while(it!=NULL){
        const char *string1 = it->prenom;
        const char *string2 = prenom;
        if(strcmp(string1,string2)==0){
            printEmploye(it);
            count++;
        }
        it=it->next;
    }
    if(count>0){
        printf("Nombre d'employees trouve est %d",count);
    }else{
        printf("aucun employe est trouve");
    }
}

void updateEmploye(struct liste * listeEmployees,struct employe * emp){
    char newTitrePoste[50];
    float newSalaire;

    while(1){
        printf("Nouveau titre de poste ( 'President',  'VP-Sales' ,  'VP-Marketing' ,  'Sales-Manager'  et  'Sales-Rep' )  ");
        scanf("%s",newTitrePoste);
        const char *string = newTitrePoste;
        if(strcmp(string,"President")==0 || strcmp(string,"VP-Sales")==0 || strcmp(string,"VP-Marketing")==0 || strcmp(string,"Sales-Manager")==0 ||strcmp(string,"Sales-Rep")==0){
            break;
        }
    }

    printf("Nouveau Salaire  ");
    scanf("%f",&newSalaire);
    emp->salaire=newSalaire;
    strcpy(emp->titrePoste,newTitrePoste);
    printf("Employe modifie avec success");
}

void saveData(struct liste *listeEmployees){
        FILE *f=fopen("employees.txt","w");
        struct employe* it=listeEmployees->head;
        while(it!=NULL){
            fprintf(f,"%d %s %s %d/%d/%d %s %.2f\n",it->code,it->nom,it->prenom
                ,it->dateNaissance.day,it->dateNaissance.month,it->dateNaissance.year,it->titrePoste,it->salaire);
            it=it->next;
        }


        fclose(f);

}

int main()
{
    struct liste* listEmployees=initListe();

    loadData(listEmployees);
    int choix;
    do {

        printf("\nMenu:\n");
        printf("1. Ajouter un nouvel employe\n");
        printf("2. Supprimer un employe\n");
        printf("3. Rechercher un employe par son code\n");
        printf("4. Rechercher un employe par son nom\n");
        printf("5. Rechercher un employe par son prenom\n");
        printf("6. Mettre a jour les informations d'un employe\n");
        printf("7. Enregistrer dans le fichier\n");
        printf("8. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix){
            case 1:{

                char nom[50];
                char prenom [50];
                int day;
                int month;
                int year;
                char titrePoste[50];
                float salaire;
                printf("Nom ");
                scanf("%s",nom);

                printf("Prenom ");
                scanf("%s",prenom);

                printf("Jour de naissance ");
                scanf("%d",&day);

                printf("Mois de naissance ");
                scanf("%d",&month);

                printf("Annee de naissance ");
                scanf("%d",&year);

                 while(1){
                    printf("Titre de poste ( 'President',  'VP-Sales' ,  'VP-Marketing' ,  'Sales-Manager'  et  'Sales-Rep' )  ");
                    scanf("%s",titrePoste);
                    const char *string = titrePoste;
                    if(strcmp(string,"President")==0 || strcmp(string,"VP-Sales")==0 || strcmp(string,"VP-Marketing")==0 || strcmp(string,"Sales-Manager")==0 ||strcmp(string,"Sales-Rep")==0){
                        break;
                    }
                }

                printf("Salaire ");
                scanf("%f",&salaire);


                ajouteEmploye(nom,prenom,day,month,year,titrePoste,salaire,listEmployees);
                break;
            }
            case 2:{
                int code;
                printf("Code d'employe a suprime  ");
                scanf("%d",&code);
                deleteEmploye(code,listEmployees);

                break;


            }
            case 3:{
                int code;
                printf("Code d'employe a rechercher  ");
                scanf("%d",&code);
                if(findByCode(listEmployees,code)){
                    printEmploye(findByCode(listEmployees,code));
                }else{
                    printf("Employe n'existe pas!");
                }
                break;

            }
            case 4:{
                int nom[50];
                printf("Nom d'employe a recherche  ");
                scanf("%s",nom);
                findByNom(listEmployees,nom);
                break;
            }
            case 5:{
                int prenom[50];
                printf("Prenom d'employe a recherche  ");
                scanf("%s",prenom);
                findByPrenom(listEmployees,prenom);
                break;
            }
            case 6:{
                int code;
                printf("Code d'employe a modifie  ");
                scanf("%d",&code);
                if(findByCode(listEmployees,code)!=NULL){
                    updateEmploye(listEmployees,findByCode(listEmployees,code));
                }else{
                    printf("Employe n'existe pas");
                }
                break;

            }case 7:{
                saveData(listEmployees);
                printf("Les information sont enregistre");
                break;
            }case 8:{
                saveData(listEmployees);
                printf("Les information sont enregistre\n");
                printf("Quitter");
                break;
            }
            default:{

                printf("Choix Invalide");
            }
        }
    }while(choix!=8);


    return 0;
}
