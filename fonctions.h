#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include "Machine_Abstraite.h"

							//################################################################//
							//#############################Client#############################//
							//################################################################//
//Procédure qui permet d'enrengistrer un nouveau client dans la liste des clients à partir du ficher
void Enrg_cl_fich(cl_ptr* tete, cl_ptr* q, FILE* fich_cl)
{
	cl_ptr p;
	Allouer_cl(&p);
	Aff_val_cl_fich(p, fich_cl);
	if(*tete == NULL){     //Si tete = Null on a alors une liste vide donc il faut l'initailiser
		*tete = p;
	}
	else{
		Aff_adr_cl_cl(*q, p);
	}
	Aff_adr_cl_cl(p, NULL); //La queue pointe toujour le NULL
	*q = p;                //Le nouveau mayon devient la nouvelle queuee pour cette liste
}
/*****************************************************************************************************/
//Procédure qui permet d'ajouter un client à la liste des clients à partir du clavier
void New_cl(cl_ptr* tete, cl_ptr* q)
{
    cl_ptr p;
	Allouer_cl(&p);
	Aff_val_cl(p);
	if(*tete == NULL){             //Si tete = Null on a alors une liste vide donc il faut l'initailiser
		*tete = p;
	}
	else{
		Aff_adr_cl_cl(*q, p);
	}
	*q = p;                      //Le nouveau mayon devient la nouvelle queuee pour cette liste
	Aff_adr_cl_cl(*q, NULL);     //La queue doit toujour pointé le NULL
}
//Fonction qui retourne le pointeur vers le client qui correspond à un Numero d'identité nationale
void Acces_val_cl(cl_ptr tete, char nb_id_national[256], cl_ptr* adr, cl_ptr* prec){
    cl_ptr p;
    p = tete;
    *prec = NULL;
    while ((p != NULL) && (strcmp(nb_id_national,(*p).nb_id_national) != 0)){
        *prec = p;            //On sauvegarde la valeur de p
        p = (*p).adr_cl_cl;   //On change la valeur de p vers sans suivant pour parcourir toute la liste
    }
    *adr = p;
}
//Procédure qui affiche la liste des clients
void Afficher_cl(cl_ptr tete){
    cl_ptr p;
    p = tete;
    int i = 1;
    while (p != NULL) {      //si p = NULL on ateint alors la fin de notre liste
        printf("**Client%d**\n", i);
        printf("\n");
        printf("Nom: %s\n", p->nom);
        printf("Prenom: %s\n",p->prenom);
        printf("L'Adress: %s\n",p->adress);
        printf("Le Numero d'identiter nationale: %s\n",p->nb_id_national);
        printf("\n");
        p = p->adr_cl_cl;      //on change la valeur de p pour parcourir la liste
        i++;                   //on incrémente le i pour indiquer le nomre du client
    }
}
//Fonction qui permet de supprimer un client de la liste des voyages et retourne l'adress de la résèrvations
void Supp_cl(cl_ptr* tete, char val[256], res_ptr* adr_res){
    cl_ptr adr;
    cl_ptr prec;
    Acces_val_cl(*tete, val, &adr, &prec);
    if(adr == NULL){              //si le client n'éxiste pas on a rien à suprimmer
        printf("Le client n'existe pas !! \n");
        *adr_res = NULL;
    }else{
        *adr_res = adr->adr_cl_res;
        if (adr == *tete){
            *tete = Suivant_cl(*tete);// si adr = tete on change la valeur de tete vers sans suivant  pour ne pas perdre la liste
            free(adr);                // on libére l'espace dans la mémoir
        }
        else{
            Aff_adr_cl_cl(prec, Suivant_cl(adr));   //on change la chanage pour garde la liste
            free(adr);                 // on libére l'espace dans la mémoir
        }
    }
}
//Affecter une valeur à la listes des clients ayont effectuer une reservation avant/apres une date donnée
void Aff_val_cl_date_res(cl_ptr client ,cl_ptr cl)
{
    strcpy(client->nom , cl->nom);
    strcpy(client->prenom , cl->prenom);
    strcpy(client->adress, cl->adress);
    strcpy(client->nb_id_national, cl->nb_id_national);
}
//Ajouter un nouveau client à la liste des clients ayont effectuer une reservation avant/apres une date donnée
void New_cl_date(cl_ptr* tete , cl_ptr* q , cl_ptr cl) //cl est l'adresse du client pointé par la réservation correcte
{
     cl_ptr p;
    Allouer_cl(&p);
    Aff_val_cl_date_res(p ,cl);
    if(*tete == NULL){      //si tete = NULL on a alors une liste vide on l'initialise alors
        *tete = p;
    }
    else{
        Aff_adr_cl_cl(*q, p);
    }
    *q = p;                //le nouveau mayon devient la queue de la liste
    Aff_adr_cl_cl(*q, NULL);   //la queue pointe toujour le NULL
}
// créer la liste des  clients ayant effectués des réservations avant une date donnée
void cl_avant_date( char date[256] , res_ptr tete_res ,cl_ptr* tete, cl_ptr* q )
{
    res_ptr p = tete_res;
    *tete = NULL;  // la liste est initialement vide
    *q = NULL;     // la liste est initialement vide
    cl_ptr cl = NULL;
    char annee[256] = "";
    char mois[256] = "";
    char jour[256] = "";
    int add = 0;            //joue le role d'un bouléen
    while (p != NULL){  //si p= NULL  on ateint alors la fin de la liste
        add = 0 ;
        if (annee_res(date)>annee_res(p->date_res)){
            add = 1;
        }else{
             if (annee_res(date)== annee_res(p->date_res)){
                if (mois_res(date)> mois_res(p->date_res)){
                    add = 1;
                }else{
                    if (mois_res(date) == mois_res(p->date_res)){
                        if (jour_res(date)> jour_res(p->date_res)){
                            add = 1;
                        }
                    }
               }
            }
         }
        if (add == 1 ){
            New_cl_date(tete , q ,p->adr_res_cl );
        }
        p = Suivant_res(p) ;  //on change le p vers sans suivant pourn parcourir la liste
    }
}
//Créer la liste des  clients aprés effectués des réservations avant une date donnée
void cl_apres_date( char date[256] , res_ptr tete_res ,cl_ptr* tete, cl_ptr* q )
{
    res_ptr p = tete_res;
    *tete = NULL;   //la liste est initialement vide
    *q = NULL;      //la liste est initialement vide
    cl_ptr cl = NULL;
    char annee[256] = "";
    char mois[256] = "";
    char jour[256] = "";
    int add = 0;            //joue le role d'un bouléen
    while (p != NULL){      //si p = NULL on ateeeint alors la fin de la liste
        add = 0 ;
        if (annee_res(date)<annee_res(p->date_res)){
            add = 1;
        }else{
             if (annee_res(date)== annee_res(p->date_res)){
                if (mois_res(date)< mois_res(p->date_res)){
                    add = 1;
                }else{
                    if (mois_res(date) == mois_res(p->date_res)){
                        if (jour_res(date)< jour_res(p->date_res)){
                            add = 1;
                        }
                    }
               }
            }
         }
        if (add == 1 ){
            New_cl_date(tete , q ,p->adr_res_cl );
        }
        p = Suivant_res(p) ;     //pour parcourir la liste
    }
}
							//################################################################//
							//#############################Voyage#############################//
							//################################################################//

//Procédure qui permet d'enrengistrer un nouveau voyage
void Enrg_voy_fich(voy_ptr* tete, voy_ptr* q, FILE* fich_voy)
{
	voy_ptr p;
	Allouer_voy(&p);
	Aff_val_voy_fich(p, fich_voy);
	if(*tete == NULL){        //la tete = NULL donc la liste est vide on met la tete à p
		*tete = p;
	}
	else{                     //la tete != de NULL alors on continue à faire le chainage
		Aff_adr_voy_voy(*q, p);
	}
    Aff_adr_voy_voy(p, NULL);
    p->q_lst = NULL;
    p->adr_voy_lst = NULL;       //le dernier mayon pointe toujour le NULL
	*q = p;                      //le mayon ajouté devient la queue de cette liste
}
//Procédure qui permet d'ajoutet un nouveau voyage à la liste des voyage à partir du clavier
void New_voy(voy_ptr* tete, voy_ptr* q)
{
    voy_ptr p;
	Allouer_voy(&p);
	Aff_val_voy(p);
	if(*tete == NULL){        //la tete = NULL donc la liste est vide on met la tete à p
		*tete = p;
	}
	else{                      //la tete != de NULL alors on continue à faire le chainage
		Aff_adr_voy_voy(*q, p);
	}
	*q = p;                        //le mayon ajouté devient la queue de cette liste
	Aff_adr_voy_voy(*q, NULL);     //le dernier mayon pointe toujour le NULL
}
//Procédure qui retourne le pointeur vers le voyage qui correspond à une destination
void Acces_val_voy(voy_ptr tete, char val[256], voy_ptr* adr, voy_ptr* prec){
    voy_ptr p;
    p = tete;
    *prec = NULL;
    while ((p != NULL) && (strcmp(val,(*p).destination) != 0)){
        *prec = p;
        p = (*p).adr_voy_voy;
    }
    *adr = p;    //pour faire le parcour de la liste
}
//Procédure qui permet d'afficher la liste des clients
void Afficher_voy(voy_ptr tete_voy){
    voy_ptr p = tete_voy;
    if(p != NULL){
        lst_voy_ptr q = p->adr_voy_lst;
        int i = 1, j;
        while (p != NULL) {        //si p = NULL on ateeeint alors la fin de la liste
            q = p->adr_voy_lst;
            printf("**Voyage%d**\n", i);
            printf("\n");
            printf("La destination du voyage: %s\n",p->destination);
            printf("La ville de depart: %s\n", p->ville_dep);
            printf("La duree du voyage: %d Jours\n", p->duree);
            printf("La prix du voyage: %dDA\n", p->prix);
            printf("\n");
            printf("**Les depart**\n");
            while(q != NULL){     //si q = NULL on ateeeint alors la fin de la liste
                printf("\n");
                printf("La date de depart: %s\n", q->dt_depart);
                printf("La Nombre de places disponibles: %d\n", q->nb_place);
                printf("La Referance: %d\n", q->ref);
                printf("\n");
                q = Suivant_lst(q);   //pour parcourir la liste des dates de départs
            }
            p = Suivant_voy(p);       //pour parcourir la liste dev voyages
            i++;                      //pour incrémenter et afficher le nombre des voyages
        }
    }else{
        printf("***La liste des voyages est vide*** \n");
        printf("\n");
    }

}
//Procédure qui affiche la liste des dates de départ disponibles pour un voyage
void Afficher_lst_voy(lst_voy_ptr tete)
{
    lst_voy_ptr p = tete;
    while (p != NULL)      //si q = NULL on ateeeint alors la fin de la liste
    {
        if (p->nb_place != 0 ){
            printf("Depart: %s  , Places disponibles : %d  , Referance : %d  \n",(*p).dt_depart, (*p).nb_place, (*p).ref);
        }
        p = (*p).adr_lst_lst;
    }
}
//Procédure qui permet de supprimer un voyage de la liste des voyages
void Supp_voy(voy_ptr* tete, char val[256]){
    voy_ptr adr;
    voy_ptr prec;
    Acces_val_voy(*tete, val, &adr, &prec);
    if (adr == *tete){
        *tete = Suivant_voy(*tete); //si adr = tete on change la valeur de tete vers sans suivant  pour ne pas perdre la liste
        free(adr);            //on libére l'espace dans la mémoir
    }
    else{
        Aff_adr_voy_voy(prec, Suivant_voy(adr)); /// on change le chainage
        free(adr);                //on libére l'espace dans la mémoir
    }
}

//Procédure qui permet d'afficher la destination, la durée et le prix d'un voyage qui à le prix inferieure à une valeur donnée
void Trouver_voy_prix(voy_ptr tete_voy, int prix){
    voy_ptr p = tete_voy;
    printf("Les voyages avec le prix inferieur a ** %dDA ** sont: \n", prix);
    if ((prix) < (p->prix)){
        printf("Nous somme desole car la valeur que vous avez choisis est tres petit veuillez reessayer avec une autre valeur !!\n");
    }else{
       while(p != NULL){     //p = NULL alors on a ateint la fin de la liste
            if((p->prix) <= (prix)){
                printf("Il y'a le voyage suivant: \n");
                printf("La destination : %s\n", p->destination);
                printf("La duree : %djours\n", p->duree);
                printf("Le prix: %dDA\n",p->prix);
            };
            p = Suivant_voy(p);   //pour parcourir la liste
        };
    }

};
void Trouve_voy_duree(voy_ptr tete_voy, int duree, int prix){
    voy_ptr p = tete_voy;
    printf("Les voyages avec le prix inferieur a ** %dDA ** et la duree inferieur a ** %dJOURS ** sont: \n", prix, duree);
    if ((prix) < (p->prix) || (duree)<(p->duree)){
        printf("Nous somme desole car la valeur que vous avez choisis est tres petit veuillez reessayer avec une autre valeur !!\n");
    }else{
        while(p != NULL){
            if((p->duree < duree)&&(p->prix < prix)){
                printf("La destination: %s\n",p->destination);
            }
            p = Suivant_voy(p);    //pour parcourir la liste
        };
    }

};
//Procédure qui permet d'eclater le liste des voyage en deux sous liste
void Eclatement_voy_nb_place(voy_ptr tete_voy, voy_ptr* t1, voy_ptr* t2){
    voy_ptr p = tete_voy, q1 = NULL, q2 = NULL;
    lst_voy_ptr lst = p->adr_voy_lst;
    *t1 = NULL;
    *t2 = NULL;
    while(p != NULL){              //p = NULL alors on a ateint la fin de la liste
        if(s_nb_place(p) <= 0){      //Creation de la liste des voyages pleins
            if(*t1 != NULL){
                Aff_adr_voy_voy(q1, p);
            }else{
                *t1 = p;             //Initialiser t1 : on vient de rencontrer la première valeur
            };
            q1 = p;
        }else{                      //Insertion dans la liste des voyages encore vides
            if(*t2 == NULL){
                *t2 = p;
            }else{
                Aff_adr_voy_voy(q2, p);
            };
            q2 = p;
        };
        p = Suivant_voy(p);
    };
    if(q1 == q2){
        printf("Veuillez remplir la liste des voyages\n");
    }else{
        if(q1 == NULL){
            Aff_adr_voy_voy(q2, NULL);
            printf("Il y'a de place dans tous les voyages\n");
        }else {
            if(q2 == NULL){
                Aff_adr_voy_voy(q1, NULL);
                printf("Pardon il y'a pas de places dans tous les voyages\n");
            }else{
                Aff_adr_voy_voy(q2, NULL);
                Aff_adr_voy_voy(q1, NULL);
            }
        }
    }
};
//Procédure qui permet de trier un voyage par prix
void Tri_voy_prix(voy_ptr tete_voy){
    voy_ptr p, q, temp;
    Allouer_voy(&temp);
    int permut;
    do{
        permut = 0;
        p = tete_voy;
        q = Suivant_voy(p);
        while(q != NULL){                //p = NULL alors on a ateint la fin de la liste
            if((p->prix) > (q->prix)){   //on compare les prix des voyages
                strcpy(temp->destination, q->destination);          ///    on fait le tri   ///
                strcpy(temp->ville_dep, q->ville_dep);              ///          en         ///
                temp->duree = q->duree;                             ///      permutan le    ///
                temp->prix = q->prix;                               ///       contenue      ///
                temp->adr_voy_lst = q->adr_voy_lst;                 ///       des mayon     ///
                strcpy(q->destination,p->destination);
                strcpy(q->ville_dep,p->ville_dep);
                q->duree = p->duree;
                q->prix = p->prix;
                q->adr_voy_lst = p->adr_voy_lst;
                strcpy(p->destination,temp->destination);
                strcpy(p->ville_dep,temp->ville_dep);
                p->duree = temp->duree;
                p->prix = temp->prix;
                p->adr_voy_lst = temp->adr_voy_lst;
                permut = 1;

            };
            p = q;
            q = Suivant_voy(q);                       //pour parcourir la liste
        }
    }while(permut == 1);
};

							//#####################################################################//
							//#############################Résèrvation#############################//
							//#####################################################################//

//Enregistrer une nouvelle reservation dans la liste des reservations à partir du fichier
void Enrg_res_fich(res_ptr* tete, res_ptr* q, FILE* fich_res)
{
    res_ptr p;
    Allouer_res(&p);
    Aff_val_res_fich(p,fich_res);
    if (*tete==NULL){         //tete = NULL on a la liste vide on la mit à p
        *tete = p;
    }
    else{                     //si non on continue le chainage
        Aff_adr_res_res(*q,p);
    }
    *q = p;                       //le  nouveau mayon devient la queue de la liste
    Aff_adr_res_res(*q, NULL);   //la queue pointe toujour le NULL
}
//Ajouter une nouvelle reservation dans la liste des reservations à partir du clavier
void Insert_res(res_ptr* tete, res_ptr* q)
{
    res_ptr p;
    Allouer_res(&p);
    Aff_val_res(p);
    if (*tete == NULL){        //tete = NULL on a la liste vide on la mit à p
        *tete = p;
    }
    else{
        Aff_adr_res_res(*q, p);
    }
    *q = p;                       //le  nouveau mayon devient la queue de la liste
    Aff_adr_res_res(*q, NULL);    //la queue pointe toujour le NULL
};

//Procédure qui permet de crée une nouvelle résèrvation à un client enrengistrer à partir du clavier
void New_res(cl_ptr tete_cl, voy_ptr tete_voy, res_ptr* tete_res, res_ptr* queue){
	char nom[256];
	char prenom[256];
	char adress[256];
	char nb_id_national[256];
	char voyage[256];
	voy_ptr p, q;
	cl_ptr p_cl, q_cl;
	Afficher_cl(tete_cl);					//Permet d'afficher tous les client sans une résèrvation
    printf("Veuillez entrer le Numero d'identite national du client concerne par cette reservetion: ");
    scanf("%s", nb_id_national);
    printf("Veuillez choisir un voyage: \n");
    Afficher_voy(tete_voy);
    printf("\n");
    printf("Veuillez entrer la destination du voyage: ");
    scanf("%s", voyage);
    Acces_val_cl(tete_cl, nb_id_national, &p_cl, &q_cl);    //rechercher le client
    Acces_val_voy(tete_voy, voyage, &p, &q);                //rechercher le voyage
    Afficher_lst_voy(p->adr_voy_lst);                       //rechercher le mayon dans la liste des date de départ
    printf("Choisissez la date de depart selon sa referance : \n");
    printf("Referance : ");
    int ref;
    scanf("%d", &ref);
    lst_voy_ptr p_lst, q_lst;
    Acces_ref_lst(p->adr_voy_lst, ref, &p_lst, &q_lst);
    Insert_res(tete_res, queue);
    Aff_adr_res_voy(queue, q);      //faire les chainage
    Aff_adr_res_cl(queue, q_cl);
    Aff_adr_res_lst(queue ,q_lst);
    p_lst->nb_place = p_lst->nb_place - 1;
}
void Afficher_res(res_ptr tete_res){
    res_ptr p;
    p = tete_res;
    int i = 1;
    while (p != NULL) {     //p = NULL c'est la fin de la liste
        printf("**Reservation du Client%d**\n", i);
        printf("\n");
        printf("Numero du Reservation: %d\n", p->nm_res);
        printf("Date du Reservation: %s\n",p->date_res);
        if(p->etat_res == 1){
            printf("L'Etat du Reservation: Consommee\n");
        }else{
            printf("L'Etat du Reservation: Non Consommee\n");
        };
        printf("\n");
        p = p->adr_res_res;          //pour parcourir la liste
        i++;
    }
};
//Procédure qui permet d'accéder à une résèrvation à partir de son numéro
void Acces_nm_res(res_ptr tete, int val, res_ptr* adr, res_ptr* prec){
    res_ptr p;
    int b;
    p = tete;
    *prec = NULL;
    while ((p != NULL) && (p->nm_res != val)){
        *prec = p;
        p = Suivant_res(p);  //pour parcourir la liste
    }
    *adr = p;
}
//Procédure qui permet d'annuler une résèrvations à partir de ça Numéro
void Annuler_res(res_ptr tete_res, int nm, res_ptr* adr){
	res_ptr p, q;
	Acces_nm_res(tete_res, nm, &p, &q);				//Accéder à la résèrvation qui a le Numéro donner
	p->etat_res = 0;
}
//Procédure qui permet de supprimer un résèrvation de la liste des résèrvations
void Supp_res(res_ptr* tete, int val){
    res_ptr adr;
    res_ptr prec;
    Acces_nm_res(*tete, val, &adr, &prec);
    if (adr == *tete){               //si la tete = adr on la suprime et on la change vers suivant de adr
        *tete = Suivant_res(*tete);
        free(adr);                   //on libére l'espace mémoire
    }
    else{                        //si non  on change le chainage
        Aff_adr_res_res(prec, Suivant_res(adr));
        free(adr);                    //on libére l'espace mémoire
    }
}
//Donner l'année de la réservation en entier
int annee_res(char date[256])

{
    int l = strlen(date);
    char ans[256]  = "";
    int i;
    int j = 0;
    for (i=6;i<l;i++){
        ans[j]=date[i];
        j++;
    }
    return atoi(ans); //on convertie l'année qui est une chaine de caractéres vers un entier et on la retourne
}
//Retourner le moi de la réservation en entier
int mois_res(char date[256])
{
    char mois[256] = "";
    int i;
    int j = 0;
    for (i=3;i<5;i++){
        mois[j]=date[i];
        j++;
    }
    return atoi(mois);       //on convertie le mois qui est une chaine de caractéres vers un entier et on la retourne
}
//Retourner le jour de la réservation en entier
int jour_res(char date[256])
{
    char jour[256]  = "";
    int i;
    int j = 0;
    for (i=0;i<2;i++){
        jour[j]=date[i];
        j++;
    }
    return atoi(jour);   //on convertie le jour qui est une chaine de caractéres vers un entier et on la retourne
}

							//##########################################################################//
							//#############################Liste des departs############################//
							//##########################################################################//

//Ajouter un nouveau départ dans la liste des départ à partir du clavier
void New_dep(lst_voy_ptr* tete, lst_voy_ptr* q)
{
    lst_voy_ptr p;
    Allouer_lst(&p);
    Aff_val_lst(p);
    if(*tete == NULL){          //tete = NULL on a la liste vide on la mit à p
		*tete = p;
	}
	else{
		Aff_adr_lst_lst(*q, p);
	}
	*q = p;                     //le  nouveau mayon devient la queue de la liste
	Aff_adr_lst_lst(*q, NULL);      //la queue pointe toujour le NULL
};
//Procédure qui retourne le pointeur vers le maillon de la liste des dates de départ d'un voyage qui correspond à une référence
void Acces_ref_lst(lst_voy_ptr tete, int ref, lst_voy_ptr* adr, lst_voy_ptr* prec)
{
    lst_voy_ptr p ;
    p = tete;
    *prec = NULL;
    while ((p != NULL) && ( p->ref != ref ))
    {
        *prec = p;
        p = Suivant_lst(p);
    }
    *adr = p;
};
int s_nb_place(voy_ptr voy){
    int s = 0;
    lst_voy_ptr q = voy->adr_voy_lst;
    while(q != NULL){
        s = s + q->nb_place;
        q = Suivant_lst(q);
    };
    return s;
};
//Enregistrer une nouvelle reservation dans la liste des reservations à partir du fichier
void Enrg_lst_fich(lst_voy_ptr* tete, lst_voy_ptr* q, FILE* fich_lst)
{
    lst_voy_ptr p;
    Allouer_res(&p);
    Aff_val_lst_fich(p, fich_lst);
    if (*tete==NULL){
        *tete = p;
    }
    else{
        Aff_adr_lst_lst(*q,p);
    }
    Aff_adr_lst_lst(p, NULL);
    *q = p;
};
void Find_q_lst(lst_voy_ptr tete_lst, lst_voy_ptr* q_lst){
    lst_voy_ptr p = tete_lst;
    while(Suivant_lst(p) != NULL){
        p = Suivant_lst(p);
    }
    *q_lst = p;
}
							//#####################################################################//
							//#############################Client ville############################//
							//#####################################################################//

// affecter valeur à au client de la liste de client de vlle
void Aff_val_cl_ville(cl_ville_ptr p , cl_ptr q)
{
    strcpy(p->nom,  q->nom);
    strcpy(p->prenom, q->prenom);
}
// crérer un nouveau client pour la liste des client ville
void New_cl_ville(cl_ville_ptr* tete , cl_ville_ptr* queue,cl_ptr cl )
{
    cl_ville_ptr p;
    Allouer_cl_ville(&p);
    Aff_val_cl_ville(p, cl);
    if(*tete == NULL)
    {
        *tete = p;
    }
    else{
        Aff_adr_cl_ville(*queue, p);
    }
    Aff_adr_cl_ville(p,NULL);
    *queue = p;
}

// génerer la liste des clients ayont la meme destination
void Trouver_cl_ville(res_ptr tete_res, char destination[256], cl_ville_ptr* tete_new, cl_ville_ptr* queue)
{
    *tete_new = NULL;
    *queue = NULL;
    res_ptr p = tete_res;
    int i = 1;
    while(p != NULL)
    {
        if(strcmp(p->adr_res_voy->destination,destination)==0)
        {
            New_cl_ville(tete_new, queue, p->adr_res_cl);
        };
        p = Suivant_res(p);
    };
}
void Tri_cl_ville(cl_ville_ptr tete_new_cl){
    cl_ville_ptr p,q,temp;
    int permut;
    Allouer_cl_ville(&temp);
    do{
        permut = 0;
        p = tete_new_cl;
        q = Suivant_cl_ville(p);
        while(q != NULL){
                if (strcmp(p->nom, q->nom) > 0 ){
                    strcpy(temp->nom , q->nom);
                    strcpy(temp->prenom, q->prenom);
                    strcpy(q->nom, p->nom);
                    strcpy(q->prenom, p->prenom);
                    strcpy(p->nom, temp->nom);
                    strcpy(p->prenom, temp->prenom);
                    permut = 1;
                };
            p = q;
            q = Suivant_cl_ville(q);
        };
    }while (permut == 1);
};
//Afficher la liste de client ville
void Afficher_cl_ville(cl_ville_ptr tete , char destination[256])
{
    cl_ville_ptr p = tete;
    int i = 1 ;
    printf("Les clients qui voyagent vers ** %s ** sont : ", destination);
    printf("\n");
    while (p!= NULL){
        printf("**Client%d**\n", i);
        printf("\n");
        printf("Nom: %s\n", p->nom);
        printf("Prenom: %s\n",p->prenom);
        printf("\n");
        p = p->adr;
        i++;
    }
}
                            //################################################################//
							//#####################liste des villes visitée###################//
							//################################################################//

//Ajouetr une nouvelle ville à la liste des villes visitées
void New_ville_visitee(ville_visitee_ptr* tete, ville_visitee_ptr* q , voy_ptr v)
{
    ville_visitee_ptr p;
    Allouer_ville_visitee(&p);
    strcpy(p->ville, v->destination);
    p->visite = 1;
    if(*tete == NULL){
        *tete = p;
    }
    else{
        Aff_adr_ville_visitee(*q, p);
    }
    *q = p;
    Aff_adr_ville_visitee(*q,NULL);
}
//Retourne une adresse si la ville existe déja dans la liste des ville visitées et NULL si non
ville_visitee_ptr ville_existe(ville_visitee_ptr tete, char ville[256])
{
    ville_visitee_ptr p = tete ;
    ville_visitee_ptr adr = NULL;
    int found = 0;
    if(tete == NULL){
        return adr;
    }else{
        while((p != NULL ) && (found != 1)){
            if (strcmp(p->ville, ville) == 0){
                found = 1;
                adr = p;
            }
            p = p->adr;
        }
        return adr ;
    }
}
//Afficher la liste des villes visitées
void Afficher_ville_visitee(ville_visitee_ptr tete)
{
    ville_visitee_ptr p =tete;
    int i = 1 ;
    while(p != NULL ){
        printf("%d\ ** %s ** : %d visites \n", i, p->ville, p->visite);
        p = p->adr;
        i++;
    }
}
//Trier la liste des villes visitées
void Trier_ville_visitee(ville_visitee_ptr tete)
{
    ville_visitee_ptr p,q,temp;
    int permut;
    Allouer_ville_visitee(&temp);
    do{
        permut = 0;
        p = tete;
        q = p->adr ;
        int i = 1;
        while(q != NULL){
                if (q->visite > p->visite){
                    strcpy(temp->ville, p->ville);
                    temp->visite = p->visite ;
                    strcpy(p->ville, q->ville);
                    p->visite = q->visite;
                    strcpy(q->ville, temp->ville);
                    q->visite = temp->visite;
                    permut = 1;
                };
            p = q;
            q = q->adr;
            i++;
        };
    }while (permut == 1);
}
//Creer la liste des villes visitée
void Creer_ville_visitee(ville_visitee_ptr* tete , ville_visitee_ptr* q ,res_ptr tete_res)
{
    res_ptr r = tete_res;
    *tete = NULL;
    *q = NULL;
    int date_deb, date_fin;
    printf("Veuiller donner la periode de votre recherche (l'annee sous forme AAAA) : \n" );
    printf("La recherche commence de : " );
    scanf("%d", &date_deb);
    printf("La recherche s'arrete a : " );
    scanf("%d",&date_fin);
    ville_visitee_ptr p = *tete , adr = NULL;
    while(r != NULL ){
        if(r->etat_res == 1){
            if(annee_res(r->date_res) >= date_deb){
                    if(annee_res(r->date_res) <= date_fin){
                        adr = ville_existe(*tete , r->adr_res_voy->destination);
                        if(adr != NULL){
                                adr->visite = adr->visite + 1;
                        }else{
                            New_ville_visitee(tete, q, r->adr_res_voy);
                        }
                    }
            }
        }
        r = Suivant_res(r);
    }
    Trier_ville_visitee(*tete);
    Afficher_ville_visitee(*tete);
}
void color1(){
    textbackground(LIGHTGREEN);
}
void color2(){
    textbackground(BLACK);
}
void color3(){
    textcolor(WHITE);
}
void print_plane(){
    int i, c = 0;
    do{
        for(i=1; i<91; i+=2){
            system("cls");
            textcolor(GREEN);
            printf("                                \t   #######  #####  ###        ####### ######  \n");
            printf("                                \t   #       #     #  #            #    #     # \n");
            printf("                                \t   #       #        #            #    #     # \n");
            printf("                                \t   #####    #####   #            #    ######  \n");
            printf("                                \t   #             #  #            #    #       \n");
            printf("                                \t   #       #     #  #            #    #      \n");
            printf("                                \t   #######  #####  ###           #    #     \n");
            gotoxy(i,14);
            textbackground(BLACK);
            printf("__  _                                \n");
            gotoxy(i, 15);
            printf("\ `/ |                               \n");
            gotoxy(i, 16);
            printf(" \__`!                               \n");
            gotoxy(i, 17);
            printf(" / ,' `-.__________________          \n");
            gotoxy(i, 18);
            printf("'-'\_____                LI`-.       \n");
            gotoxy(i, 19);
            printf("<____()-=O=O=O=O=O=[]====--)  )       \n");
            gotoxy(i, 20);
            printf("     `.___ ,-----,_______...-'       \n");
            gotoxy(i, 21);
            printf("          /    .'                    \n");
            gotoxy(i, 22);
            printf("         /   .'                      \n");
            gotoxy(i, 23);
            printf("        /  .'                        \n");
            gotoxy(i, 24);
            printf("        `-'                          \n");

        }
        printf("Cliquer Sur ** ENTRER ** Pour Continuer.\n");
        c = getch();
    }while(c != 13);
    clrscr();
}
void print_menu(int* choix){
    int c = 0, cpt = 0;
    do{
        textcolor(GREEN);
        textbackground(BLACK);
        gotoxy(40,4);
        printf("###################################");
        gotoxy(40,5);
        printf("#                                 #");
        gotoxy(40,6);
        printf("#     BIENVENUE DANS NOTRE TP     #");
        gotoxy(40,7);
        printf("#                                 #");
        gotoxy(40,8);
        printf("###################################");
        c = getche();
        if(c == 80){cpt%=18;cpt++;}
        if(c == 72){cpt--;if(cpt==0)cpt=18;}
        clrscr();
        gotoxy(40,9);
        printf("\n");
        printf("\n");
        printf("\n");
        if(cpt == 1)color1();color3();printf("   [01] Construire les listes a partir du fichier                                            \n");color2();
        if(cpt == 2)color1();color3();printf("   [02] Afficher la liste des Clients                                                        \n");color2();
        if(cpt == 3)color1();color3();printf("   [03] Afficher la liste des Reservation                                                    \n");color2();
        if(cpt == 4)color1();color3();printf("   [04] Afficher la liste des Voyages                                                        \n");color2();
        if(cpt == 5)color1();color3();printf("   [05] Enregistrer un nouveau client                                                        \n");color2();
        if(cpt == 6)color1();color3();printf("   [06] Enregistrer un nouveau voyage                                                        \n");color2();
        if(cpt == 7)color1();color3();printf("   [07] Cree une reservation                                                                 \n");color2();
        if(cpt == 8)color1();color3();printf("   [08] Supprimer un client et sa reservation a partir du numero d'identiter national        \n");color2();
        if(cpt == 9)color1();color3();printf("   [09] Supprimer un voyage a partir de la destination                                       \n");color2();
        if(cpt == 10)color1();color3();printf("   [10] Rajouter un nouveau depart a un voyage choisit                                       \n");color2();
        if(cpt == 11)color1();color3();printf("   [11] Trouver tous les clients d'une ville donnee                                          \n");color2();
        if(cpt == 12)color1();color3();printf("   [12] Afficher tous les voyages dont le prix est inferieur a une valeur donne              \n");color2();
        if(cpt == 13)color1();color3();printf("   [13] Afficher tous les voyages dont le prix et la duree sont inferieur a une valeur donne \n");color2();
        if(cpt == 14)color1();color3();printf("   [14] Afficher les clients ayant effectues des reservations avant/apres une date donnee    \n");color2();
        if(cpt == 15)color1();color3();printf("   [15] Eclatement de la liste des voyages selon le nombre de place disponible               \n");color2();
        if(cpt == 16)color1();color3();printf("   [16] Le tri des deux listes de voyages eclater                                            \n");color2();
        if(cpt == 17)color1();color3();printf("   [17] Afficher les villes les plus visite durant une periode donnee                        \n");color2();
        if(cpt == 18)color1();color3();printf("   [18] Quitter                                                                              \n");color2();
    }while(c != 13);
    *choix = cpt;
}

#endif // FONCTIONS_H_INCLUDED
