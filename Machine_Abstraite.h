#ifndef MACHINE_ABSTRAITE_H_INCLUDED
#define MACHINE_ABSTRAITE_H_INCLUDED

/*****************************************************************************************************/
struct client     //Définition la structures de données correspondante à la liste des clients
{
	struct info_cl     //Structure qui contient les informations du client
	{
		char nom[256];
		char prenom[256];
		char adress[256];
		char nb_id_national[256];         //Numéro d'identité nationale
	};
	struct client* adr_cl_cl;			   //Adress vers le prochaine client
	struct reservation* adr_cl_res;       //Adress vers la reservations
};
typedef struct client client;      //Définir un type qui sert à faciliter l'accés à la structure
typedef client* cl_ptr;				//Pointure vers client
/*****************************************************************************************************/
struct reservation     //Définition la structures de données correspondante à la liste des réservtion
{
	struct info_res
	{
		int nm_res; 			//Numéro de la réservation
		char date_res[256];		//Date de la réservation
		int etat_res;       	//Etat de la réservation
	};
	struct client* adr_res_cl;		    //Adress vers client
	struct voyage* adr_res_voy;	    //Adress vers voyage
	struct reservation* adr_res_res;		//Adress vers la prochaine réservation
	struct lst_voy* adr_res_lst_voy;
};
typedef struct reservation reservation;      //Définir un type qui sert à faciliter l'accés à la structure
typedef reservation* res_ptr;				//Pointure vers réservation
/*****************************************************************************************************/
struct lst_voy           //La liste de toutes les dates de départ valides
{
	struct info
	{
		char dt_depart[256];				//Date du depare du voyage
		int nb_place;					    //Nombres de places disponibles
		int ref;							//La référence du chaque voyage
	};
	struct lst_voy* adr_lst_lst;				//Pointeur vers les prochaines information sur ce voyage
};
typedef struct lst_voy lst_voy;		//Définir un type qui sert à faciliter l'accés à la structure
typedef lst_voy* lst_voy_ptr;		//Pointure vers liste des voyages

struct voyage		//Définition la structures de données correspondante à la liste des voyages
{
	struct info_voy
	{
		char destination[256];
		char ville_dep[256];		// La ville de départ
		char duree;					// La durée du voyage
		int prix;					// Le prix du voyage
	};
	struct lst_voy* adr_voy_lst;
	struct voyage* adr_voy_voy;
	lst_voy* q_lst;
};
typedef struct voyage voyage;      //Définir un type qui sert à faciliter l'accés à la structure
typedef voyage* voy_ptr;		   //Pointure vers voyage
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************MACHINE ABSTRAITE*******************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/

							//################################################################//
							//#############################Client#############################//
							//################################################################//

void Allouer_cl(cl_ptr* p)				//Allouer un maillon pour un nouveau client
{
    *p = (cl_ptr)malloc(sizeof(client));
}
// Procédure qui affecte Nom,Prenom,Adress et Numéro d'identité nationale dans le champ (info_cl)du maillon pointé par p.
void Aff_val_cl_fich(cl_ptr p, FILE* fich_cl)
{
	char nom[256];
	char prenom[256];
	char adress[256];
	char nb_id_national[256];
    fscanf(fich_cl, "%s %s %s %s", nom, prenom, adress, nb_id_national);
    strcpy((*p).nom, nom);
    strcpy((*p).prenom, prenom);
    strcpy((*p).adress, adress);
    strcpy((*p).nb_id_national,  nb_id_national);
}
// Procédure qui affecte q dans le champ (adr) du maillon pointé par p.
void Aff_adr_cl_cl(cl_ptr p, cl_ptr q)
{
    p->adr_cl_cl = q;
}
// Procédure qui affecte q dans le champ (adr_res) du maillon pointé par p.
void Aff_adr_cl_res(cl_ptr p, res_ptr q)
{
    p->adr_cl_res = q;
}
//Procédure qui affecte les informations du champ (info_cl)du maillon pointé par p à partir du claveir
void Aff_val_cl(cl_ptr p)
{
	char nom[256];
	char prenom[256];
	char adress[256];
	char nb_id_national[256];         //Numéro d'identité nationale
    printf("Veuillez entrer Votre Nom, Prenom, Adress, Numero d'identite nationale: \n");
    printf("Nom : ");
    scanf("%s",nom);
    strcpy((*p).nom, nom);
    printf("Prenom : ");
    scanf("%s",prenom);
    strcpy((*p).prenom, prenom);
    printf("Adress : ");
    scanf("%s",adress);
    strcpy((*p).adress, adress);
    printf("Numero d'identite national : ");
    scanf("%s",nb_id_national);
    strcpy((*p).nb_id_national, nb_id_national);
}
cl_ptr Suivant_cl(cl_ptr p){
    return p->adr_cl_cl;
}
							//################################################################//
							//#############################Voyage#############################//
							//################################################################//

//Allouer un maillon pour un nouveau voyage
void Allouer_voy(voy_ptr* p)
{
	*p = (voy_ptr)malloc(sizeof(voyage));
}
//Procédure qui permet de remplir les informations du voyage
void Aff_val_voy_fich(voy_ptr p, FILE* fich_voy)
{
	char destination[256];
	char ville_dep[250];
	int duree;
	int prix;
	fscanf(fich_voy, "%s %s %d %d", destination, ville_dep, &duree, &prix);
	strcpy(p->destination, destination);
	strcpy(p->ville_dep, ville_dep);
	p->duree = duree;
	p->prix = prix;
}
//Procédure qui permet de remplir les informations d'un voyage à partir du clavier
void Aff_val_voy(voy_ptr p)
{
	char destination[256];
	char ville_dep[256];
	int duree;
	int prix;
	printf("Veuillez entrer la destination, ville du depart, la duree et le prix du voyage: \n");
    printf("Destination : ");
    scanf("%s",destination);
	strcpy((*p).destination, destination);
    printf("Ville de depart : ");
    scanf("%s",ville_dep);
    strcpy((*p).ville_dep, ville_dep);
    printf("Duree : ");
    scanf("%d", &duree);
    (*p).duree = duree;
    printf("Prix : ");
    scanf("%d",&prix);
    (*p).prix = prix;
}
// Procédure qui affecte q dans le champ (adr_voy) du maillon pointé par p.
void Aff_adr_voy_voy(voy_ptr p, voy_ptr q)
{
    p->adr_voy_voy = q;
}
// Procédure qui affecte q dans le champ (adr_liste) du maillon pointé par p.
void Aff_adr_voy_lst(voy_ptr p, lst_voy_ptr q){
	p->adr_voy_lst = q;
}
voy_ptr Suivant_voy(voy_ptr p){
    return p->adr_voy_voy;
}

							//####################################################################//
							//#############################Résèrvation############################//
							//####################################################################//
//Allouer une resérvation
void Allouer_res(res_ptr* p)
{
    *p = (res_ptr)malloc(sizeof(reservation));
}
//Remplir les informations d'une résèrvation à partir du fichier
void Aff_val_res_fich(res_ptr p,FILE* fich_res)
{
    int nm_res;
    char date_res[256];
    int etat_res;
	fscanf(fich_res, "%d %s %d ", &nm_res, date_res, &etat_res);
	(*p).nm_res = nm_res;
	strcpy((*p).date_res,date_res);
	(*p).etat_res = etat_res;

}
//Procédure qui permet de remplir les information d'une reservation à partir du clavier
void Aff_val_res(res_ptr p)
{
	int nm_res;
	char date_res[256];
	int etat_res;
    printf("Veuillez entrer le numero de la reservation ,la date de la reservation, l'etat de cette reservation \n");
    printf("Numero du reservation : ");
    scanf("%d", &nm_res);
    (*p).nm_res = nm_res;
    printf("Date de reservation : ");
    scanf("%s", &date_res);
    strcpy((*p).date_res, date_res);
    printf("Etat de cette reservation (Consommee = 1 / Non Consommee = 0): ");
    scanf("%d", &etat_res);
    (*p).etat_res = etat_res;
}
//Affecter q dans le champ (adr) de la structre reservation
void Aff_adr_res_res(res_ptr p, res_ptr q)
{
    (*p).adr_res_res = q;
}
//Affecter q dans le champ (adr_cl) de la structre reservation
void Aff_adr_res_cl(res_ptr p, cl_ptr q)
{
    (*p).adr_res_cl = q;
}
//Affecter q dans le champ (adr_voy) de la structre reservation
void Aff_adr_res_voy(res_ptr p, voy_ptr q)
{
    (*p).adr_res_voy = q;
}
//Affecter q dans le champ (adr_voy) de la structre reservation
void Aff_adr_res_lst(res_ptr p, lst_voy_ptr q)
{
    (*p).adr_res_lst_voy = q;
}
res_ptr Suivant_res(res_ptr p){
    return p->adr_res_res;
}

							//##########################################################################//
							//#############################Liste des departs############################//
							//##########################################################################//
//Remlire les informations d'un mayon de la liste des dates de depart d'un voyage à partir du ficher
void Aff_val_lst_fich(lst_voy_ptr p , FILE* fich_lst)
{
    char dt_depart[256];				//Date du depare du voyage
	int nb_place;					    //Nombres de places disponibles
	int ref;							//La référence du chaque voyage
	fscanf(fich_lst,"%s %d %d",dt_depart,&nb_place,&ref);
	strcpy(p->dt_depart,dt_depart);
	p->nb_place = nb_place;
	p->ref = ref;
}
//Alouer un mayon de la liste des dates de depart
void Allouer_lst(lst_voy_ptr* p)
{
    *p = (lst_voy_ptr)malloc(sizeof(lst_voy));
}
// Procédure qui affecte q dans le champ adr_lst_lst de p
void Aff_adr_lst_lst(lst_voy_ptr p, lst_voy_ptr q)
{
    p->adr_lst_lst = q;
}
//Procédure qui affecte les informations du champ (info )du maillon pointé par p à partir du claveir
void Aff_val_lst(lst_voy_ptr p)
{
    char dt_depart[256];				//Date du depare du voyage
	int nb_place;					//Nombres de places disponibles
	int ref;
    printf("Veillez donner la date de depart , nombre de places disponibles et la referance :\n");
    printf("la date de depart : ");
    scanf("%s",dt_depart);
    strcpy((*p).dt_depart, dt_depart);
    printf("Nombre de places disponibles : ");
    scanf("%d",&nb_place);
    (*p).nb_place = nb_place;
    printf("La referance : ");
    scanf("%d",&ref);
    (*p).ref = ref;
}
//Fonction qui retourne l'adresse du mayon pointé par p
lst_voy_ptr Suivant_lst(lst_voy_ptr p){
    return p->adr_lst_lst;
}

							//#####################################################################//
							//#############################Client ville############################//
							//#####################################################################//
//liste des client (nom et prenom) qui on la meme destination
struct client_ville
{
    char nom[256];
    char prenom[256];
    struct client_ville*  adr;
};
typedef struct client_ville client_ville ;          //Définir un type qui sert à faciliter l'accés à la structure
typedef client_ville* cl_ville_ptr;                 //Pointure vers client ville
//Alouer un mayon pour la liste des client qui on la meme destination
void Allouer_cl_ville(cl_ville_ptr* p)
{
    *p = (cl_ville_ptr)malloc(sizeof(client_ville));
}
// Affecter une adresse au champs adr de la liste des clients qui ont la meme destination
void Aff_adr_cl_ville(cl_ville_ptr p,cl_ville_ptr q)
{
    p->adr = q;
}
// l'adresse du myon pointé par p
cl_ville_ptr Suivant_cl_ville(cl_ville_ptr p)
{
    return p->adr;
}
                            //################################################################//
							//#####################liste des villes visitée###################//
							//################################################################//
//Liste des villes les plus visitées
struct ville_visitee
{
       char ville [256];
       int visite ;

    struct ville_visitee* adr;
};
typedef struct ville_visitee ville_visitee;             //Définir un type qui sert à faciliter l'accés à la structure
typedef ville_visitee* ville_visitee_ptr;               //Pointure vers client ville
//Allouer un maillon pour la structure ville_vistee
void Allouer_ville_visitee(ville_visitee_ptr* p)
{
    *p = (ville_visitee_ptr)malloc(sizeof(ville_visitee));
}
//Affecter une adresse dans les champs adr du maillon p de la structuer vill_visitee
void Aff_adr_ville_visitee( ville_visitee_ptr p, ville_visitee_ptr q )
{
    p->adr = q;
}

/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************MACHINE ABSTRAITE*******************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/



#endif // MACHINE_ABSTRAITE_H_INCLUDED
