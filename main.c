#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.c"
#include "conio2.h"
#include "fonctions.h"

int main()
{
	FILE* fich_cl = fopen("fich_cl.txt", "r");
    FILE* fich_voy = fopen("fich_voy.txt", "r");
    FILE* fich_res = fopen("fich_res.txt", "r");
    FILE* fich_lst = fopen("fich_lst.txt", "r");
	int choix, stop = 0, retour, i, j, k, nm_res, prix, duree, continu;
	char nb_national[256], destination[256], date[259];
	cl_ptr tete_cl = NULL, q_cl = NULL, tete_cl_avant = NULL, q_cl_avant = NULL;
    cl_ptr tete_cl_apres = NULL, q_cl_apres = NULL;
    res_ptr tete_res = NULL, q_res = NULL, adr_res;
    voy_ptr tete_voy = NULL, q_voy = NULL, adr_voy, prec_voy, t1_voy = NULL, t2_voy = NULL;
    lst_voy_ptr tete_lst = NULL, q_lst = NULL;
    cl_ville_ptr tete_cl_ville, q_cl_ville;
    ville_visitee_ptr tete_ville_visitee = NULL, q_ville_visitee = NULL;

	print_plane();        //Afficher l'avion du programme!!

    while(stop == 0){
        print_menu(&choix);
        switch (choix){
            case 1:
                clrscr();
                for(i = 0; i<10; i++){
                    Enrg_voy_fich(&tete_voy, &q_voy, fich_voy);
                    for(j = 0; j<3; j++){
                        Enrg_lst_fich(&tete_lst, &q_lst, fich_lst);
                        for(k = 0; k<5; k++){
                            Enrg_cl_fich(&tete_cl, &q_cl, fich_cl);
                            Enrg_res_fich(&tete_res, &q_res, fich_res);
                            Aff_adr_cl_res(q_cl, q_res);
                            Aff_adr_res_cl(q_res,q_cl);
                            Aff_adr_res_voy(q_res, q_voy);
                            Aff_adr_res_lst(q_res, q_lst);
                            q_lst->nb_place -= 1;
                        };
                    };
                    Aff_adr_voy_lst(q_voy, tete_lst);
                    q_voy->q_lst = q_lst;
                    tete_lst = NULL;
                };
                printf("La creation des listes a ete effectuer correctement.\n");
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 2:
                clrscr();
                printf("-----------La liste des Clients: -----------\n");
                printf("\n");
                Afficher_cl(tete_cl);
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 3:
                clrscr();
                printf("-----------La liste des Reservations: -----------\n");
                printf("\n");
                Afficher_res(tete_res);
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 4:
                clrscr();
                printf("-----------La liste des Voyages: -----------\n");
                printf("\n");
                Afficher_voy(tete_voy);
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 5:
                clrscr();
                if(tete_cl == NULL){
                    printf("Veuillez d'abord cree la liste des client\n");
                }else{
                    New_cl(&tete_cl, &q_cl);
                    printf("Le nouveau client a ete bien ajouter\n");
                }
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 6:
                clrscr();
                if(tete_voy == NULL){
                    printf("Veuillez d'abord cree la liste des voyages\n");
                }else{
                    New_voy(&tete_voy, &q_voy);
                    do{
                        New_dep(&tete_lst, &q_lst);
                        Aff_adr_voy_lst(q_voy, tete_lst);
                        printf("Voulez vous cree un nouveau depart?\n");
                        printf("{1} = Oui / {0} = Non : ");
                        scanf("%d", &continu);
                        if(continu != 0 && continu != 1){
                            printf("Erreur de choix\n");
                            break;
                        }
                    }while(continu != 0);
                    printf("Le nouveau voyage a ete bien ajouter\n");
                }
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 7:
                clrscr();
                if((tete_cl == NULL) || (tete_voy == NULL)){
                    printf("Veuillez d'abord cree la liste des voyages et des clients\n");
                }else{
                    New_res(tete_cl, tete_voy, &tete_res, &q_res);
                    printf("La nouvelle reservation a ete bien ajouter\n");
                }
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 8:
                clrscr();
                if(tete_cl == NULL){
                    printf("Veuillez d'abord cree la liste des client et des reservations\n");
                }else{
                    Afficher_cl(tete_cl);
                    printf("Veuillez entrer le numero d'identite national du client choisis: ");
                    scanf("%s", nb_national);
                    Supp_cl(&tete_cl, nb_national, &adr_res);
                    if(adr_res != NULL){
                        printf("Suppression du client avec succes\n");
                        nm_res = adr_res->nm_res;
                        adr_res->adr_res_lst_voy->nb_place = adr_res->adr_res_lst_voy->nb_place + 1;
                        Supp_res(&tete_res, nm_res);
                        printf("Suppression de la reservation avec succes\n");
                    }
                }
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 9:
                clrscr();
                if(tete_voy == NULL){
                    printf("Veuillez d'abord cree la liste des voyages\n");
                }else{
                    Afficher_voy(tete_voy);
                    printf("Veuillez choisir le voyage que vous voulez le supprimer: ");
                    scanf("%s", destination);
                    Acces_val_voy(tete_voy, destination, &adr_voy, &prec_voy);
                    adr_voy->adr_voy_lst = NULL;
                    Supp_voy(&tete_voy, destination);
                    printf("La suppression du voyage a ete effectuer avec succes!!\n");
                }
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 10:
                clrscr();
                if(tete_voy == NULL){
                    printf("Veuillez d'abord cree la liste des depart\n");
                }else{
                    Afficher_voy(tete_voy);
                    printf("Veuillez choisir une destination: ");
                    scanf("%s", destination);
                    Acces_val_voy(tete_voy, destination, &adr_voy, &prec_voy);
                    Find_q_lst(adr_voy->adr_voy_lst, &q_lst);
                    New_dep(&(adr_voy->adr_voy_lst), &q_lst);
                    printf("Creation d'un nouveau depart avec succes!!\n");
                }
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 11:
                clrscr();
                if((tete_cl == NULL) || (tete_voy == NULL) ){
                    printf("Veuillez d'abord cree la liste des clients et voyage\n");
                }else{
                    Afficher_voy(tete_voy);
                    printf("Veuillez choisir une destination: ");
                    scanf("%s", destination);
                    Trouver_cl_ville(tete_res, destination, &tete_cl_ville, &q_cl_ville);
                    Tri_cl_ville(tete_cl_ville);
                    Afficher_cl_ville(tete_cl_ville, destination);
                }
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 12:
                clrscr();
                if(tete_voy == NULL){
                    printf("Veuillez d'abord cree la liste des voyages\n");
                }else{
                    printf("Affichage des voyages inferieur a une valeur donne\n");
                    printf("Choisissez le prix que vous voullez: ");
                    scanf("%d", &prix);
                    Trouver_voy_prix(tete_voy, prix);
                }
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 13:
                clrscr();
                if(tete_voy == NULL){
                    printf("Veuillez d'abord cree la liste des voyages\n");
                }else{
                    printf("Affichage des voyages inferieur a une valeur donne\n");
                    printf("Choisissez la duree et le prix que vous voullez\n");
                    printf("Duree : ");
                    scanf("%d", &duree);
                    printf("Prix : ");
                    scanf("%d", &prix);
                    Trouve_voy_duree(tete_voy, duree, prix);
                }
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 14:
                clrscr();
                if(tete_voy == NULL){
                    printf("Veuillez d'abord cree la liste voyage\n");
                }else{
                    printf("Veuillez donner une date de recherche sous la forme JJ/MM/AAAA \n");
                    printf("La date de recherche  : ");
                    scanf("%s", date);
                    cl_avant_date(date,tete_res,&tete_cl_avant,&q_cl_avant);
                    cl_apres_date(date,tete_res,&tete_cl_apres,&q_cl_apres);
                    printf("Les clients ayant effectuer une reservation avant le %s  sont :\n", date);
                    Afficher_cl(tete_cl_avant);
                    printf("Les clients ayant effectuer une reservation apres le %s  sont :\n", date);
                    Afficher_cl(tete_cl_apres);
                }
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 15:
                clrscr();
                if(tete_voy == NULL){
                    printf("Veuillez d'abord cree la liste des voyages et des clients\n");
                }else{
                    Eclatement_voy_nb_place(tete_voy, &t1_voy, &t2_voy);
                    printf("############La liste des voyages pleins############\n");
                    printf("\n");
                    Afficher_voy(t1_voy);
                    printf("############La liste des voyages contient encore de place############\n");
                    printf("\n");
                    Afficher_voy(t2_voy);
                }
                 printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);

                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 16:
                clrscr();
                if(tete_voy == NULL){
                    printf("Veuillez d'abord cree la liste des voyages \n");
                }else{
                    if((t1_voy == NULL) || (t2_voy == NULL)){
                        printf("Veuillez d'abord eclater les deux listes de voyages\n");
                    }else{
                    printf("***** Le tri des deux liste de voyages obtenue *****\n");
                    printf("\n");
                    Tri_voy_prix(t1_voy);
                    printf("### La premier liste de voyage trier par prix ###\n");
                    printf("\n");
                    Afficher_voy(t1_voy);
                    Tri_voy_prix(t2_voy);
                    printf("### La deuxieme liste de voyage trier par prix ###\n");
                    printf("\n");
                    Afficher_voy(t2_voy);
                    }
                }
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);

                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 17:
                clrscr();
                if(tete_voy == NULL){
                    printf("Veuillez d'abord cree la liste des voyages \n");
                }else{
                    Creer_ville_visitee(&tete_ville_visitee, &q_ville_visitee,tete_res);
                }
                printf("{1} Retourner vers le menu, {2} Quittez: ");
                scanf("%d", &retour);
                if(retour == 1){
                    break;
                }else{
                    stop = 1;
                }
                break;
            case 18:
                clrscr();
                stop = 1;
                break;
            default :
                printf("Erreur Veuillez entrer une des valeurs precedentes!!\n");
            };
        system("cls");
    };
	fclose(fich_cl);
	fclose(fich_voy);
	fclose(fich_res);
	fclose(fich_lst);
	return 0;
}
