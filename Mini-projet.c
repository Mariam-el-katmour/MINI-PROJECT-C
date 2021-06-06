#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<dos.h>


typedef struct date{
	
	int jour;
	int mois;
	double annee;
	}date;
	
typedef struct Voiture
{
 int idVoiture;
 char marque[15];
 char nomVoiture[15];
 char couleur[7];
 int nbplaces;
 int prixJour;
 char EnLocation[4];
} voiture;
typedef struct Client
{
 int idClient;
 char nom[20];
 char prenom[20];
 int cin;
 char adresse[15];
 int telephone;
}client;

typedef struct contratLocation
{
 float numContrat;
 int idVoiture;
 int idClient;
 date debut;
 date fin;
 int cout;
} contrat;


	
	
	//gestion de voiture

int Recherche_voiture(int idr){
	int v_idV;
	char Buff[1000];
	//int valide=0;
	FILE *fichier=NULL;
	fichier=fopen("Voitures.txt","r");
	if(fichier!=NULL){
		while(fscanf(fichier,"%d|%s",&v_idV,&Buff)!=EOF){
            if(idr==v_idV){
                fclose(fichier);
                return 1;
            }
        }
        fclose(fichier);
    }
	return 0;
}

void ajout_voiture(){
	int N,i;
	voiture v;
    FILE*fichier = NULL;
	fichier = fopen("Voitures.txt","a");
	int idr;
	if(fichier != NULL){
        printf("\t saisir le nombre de voiture\t");
        scanf("%d",&N);
        for(i=0;i<N;i++){
            printf("\n\n Saisie Id de la voiture:\t");
            scanf("%d",&idr);
            fflush(stdin);
            while(Recherche_voiture(idr)==1){
                printf(" l'ID saisie existe dja !\n ");
                printf(" Veuilliez saisir id de  la Voiture :\t ");
                scanf("%d",&idr);
                fflush(stdin);
            }
            v.idVoiture=idr;
            printf("taper la marque de la voiture :\t");
            scanf("%s",v.marque);
            printf("taper le nom de la voitiure :\t");
            scanf("%s",v.nomVoiture);
            printf("taper la coulour de la voiture :\t");
            scanf("%s",v.couleur);
            printf("taper nombre de place :\t\t");
            scanf("%d",&v.nbplaces);
            fflush(stdin);
            printf("taper le prix par jour :\t");
            scanf("%d",&v.prixJour);
            fflush(stdin);
            printf("taper si en location ou non :\t");
            scanf("%s",v.EnLocation);
            fprintf(fichier,"%d|%s|%s|%s|%d|%d|%s\n",v.idVoiture,v.marque,v.nomVoiture,v.couleur,v.nbplaces,v.prixJour,v.EnLocation);
        }
    }
	fclose(fichier);
}

void Afficher(){
	voiture v;
	//char c;
	FILE*fichier=NULL;
	fichier=fopen("Voitures.txt","r");
	char buff1[1000];
	if(fichier!=NULL){
        while(fgets(buff1, 1000, fichier)){
            printf("%s",buff1);
        }
    }
    fclose(fichier);
}

void modifier_voiture(){
	voiture v;
 	int numr,choix;
 	char a;
 	printf("Saisir le  id de la voiture que vous voulez modifier :\t ");
 	scanf("%d",&numr);
 	fflush(stdin);
 	if(Recherche_voiture(numr)==1){
 		printf("voulez-vous vraiment modifier (o/n)? ");
 		scanf("%c",&a);
 		fflush(stdin);
 		if(a=='o' || a=='O'){
 			FILE *fichier,*fil;
        	fichier=fopen("Voitures.txt","r");
        	fil=fopen("cpy.txt","w");
            char buff2[1000];
            while(fgets(buff2, 1000, fichier)){
              	char *domaine= strtok(buff2, "|");
                v.idVoiture=atoi(domaine);
                domaine = strtok(NULL, "|");
                strcpy(v.marque,domaine);
                domaine = strtok(NULL, "|");
                strcpy(v.nomVoiture,domaine);
                domaine = strtok(NULL, "|");
                strcpy(v.couleur,domaine);
                domaine = strtok(NULL, "|");
                v.nbplaces=atoi(domaine);
                domaine = strtok(NULL, "|");
                v.prixJour=atoi(domaine);
                domaine = strtok(NULL, "\n");
                strcpy(v.EnLocation,domaine);
                if(numr==v.idVoiture){
                    v.idVoiture=numr;
                    
                   printf("Voulez vous modifier quel champ ? 1/marque | 2/nom_voiture| 3/couleur|4/nbre_places|5/prix/jour|6/Enlocation \n ");
                   scanf("%d",&choix);
                   switch(choix){
				   case 1:
                    printf("entrez la nouvelle marque de voiture :\t");
                    scanf("%s",v.marque);
                    break;
                    case 2:
                    printf("entrez le nouveau nom de voiture :\t");
                    scanf("%s",v.nomVoiture);
                    break;
                    case 3:
                    printf("entrez la nouvelle couleur de voiture :\t");
                    scanf("%s",v.couleur);
                    break;
                    case 4:
                    printf("entrez le nouveau nombre de place :\t");
                    scanf("%d",&v.nbplaces);
                    fflush(stdin);
                    break;
                    case 5:
                    printf("entrez le nouveau prix par jour :\t");
                    scanf("%d",&v.prixJour);
                    fflush(stdin);
                    break;
                    case 6:
                    printf("entre si en location ou non :\t");
                    scanf("%s",v.EnLocation);
                    fflush(stdin);
                    break;
                    default :
				    	    printf("ce choix n'existe pas");
				    	    break;
				 }
                }
                fprintf(fil,"%d|%s|%s|%s|%d|%d|%s\n",v.idVoiture,v.marque,v.nomVoiture,v.couleur,v.nbplaces,v.prixJour,v.EnLocation);
            }

			fclose(fichier);
			fclose(fil);
			remove("Voitures.txt");
			rename("cpy.txt","Voitures.txt");

			printf("la modification a reussi");
		 }
		else{
			printf("la voiture non modifier");
		}
	 }
	 else printf("l'Id  saisie de la voiture n'existe pas");
}

 void supprimer_voiture(){
 	voiture v;
 	int numr;
 	char a;
 	printf("Saisie le id de la voiture a supprimé : ");
 	scanf("%d",&numr);
 	fflush(stdin);
 	if(Recherche_voiture(numr)==1){
 		printf("voulez-vous vraiment supprimer (o/n)? ");
 		scanf("%c",&a);
 		fflush(stdin);
 		if(a=='o' || a=='O'){
 			FILE *fichier,*fil;
        	fichier=fopen("Voitures.txt","r");
        	fil=fopen("nouveaufich2.txt","w");

            char buff2[1000];
            while(fgets(buff2, 1000, fichier)){

                    char *domaine = strtok(buff2, "|");
                    v.idVoiture=atoi(domaine);
                    domaine = strtok(NULL, "|");
                    strcpy(v.marque,domaine);
                    domaine = strtok(NULL, "|");
                    strcpy(v.nomVoiture,domaine);
                    domaine = strtok(NULL, "|");
                    strcpy(v.couleur,domaine);
                    domaine = strtok(NULL, "|");
                    v.nbplaces=atoi(domaine);
                    domaine = strtok(NULL, "|");
                    v.prixJour=atoi(domaine);
                    domaine = strtok(NULL, "\n");
                    strcpy(v.EnLocation,domaine);

                    if(numr!=v.idVoiture){
                        fprintf(fil,"%d|%s|%s|%s|%d|%d|%s\n",v.idVoiture,v.marque,v.nomVoiture,v.couleur,v.nbplaces,v.prixJour,v.EnLocation);
                    }
			}
			fclose(fichier);
			fclose(fil);
			remove("Voitures.txt");
			rename("nouveaufich2.txt","Voitures.txt");
			printf("suppression effectuee avec success !");
		 }
		else{
			printf(" Voiture non supprimée");
		}
	 }
	 else printf("l'Id de la voiture n'existe pas");
}

//gestion des clients

int recherche_client(int idr){
	int idC;
	char Buff1[1000];
	FILE *fichier=NULL;
	fichier=fopen("Clients.txt","r");
	if(fichier!=NULL){
		while(fscanf(fichier,"%d|%s",&idC,&Buff1)!=EOF){
            if(idr==idC){
                fclose(fichier);
                return 1;
            }
        }
        fclose(fichier);
    }
	return 0;
}

void Remplir_client(int idr){
    client c;
    FILE *fichier = NULL;
    fichier = fopen("Clients.txt","a");
    c.idClient=idr;
    printf("Saisie le  nom de client :\t");
    scanf("%s",c.nom);
    fflush(stdin);
    printf("Saisie le prenom de client :\t");
    scanf("%s",c.prenom);
    fflush(stdin);
    printf("Saisie CIN de client :\t");
    scanf("%d",&c.cin);
    fflush(stdin);
    printf("Saisie l'adresse de client :\t");
    scanf("%s",c.adresse);
    fflush(stdin);
    printf("Saisie le numero tel de client :\t");
    scanf("%d",&c.telephone);
    fflush(stdin);
    fprintf(fichier,"%d|%s|%s|%d|%s|%d\n",c.idClient,c.nom,c.prenom,c.cin,c.adresse,c.telephone);
	fclose(fichier);
}

void ajout_client(){
 	int N,i,idr;
 	FILE *fichier = NULL;
	fichier = fopen("Clients.txt","r");
	if(fichier != NULL){
        printf("\t saisir le nombre de clients\t");
        scanf("%d",&N);
        for(i=0;i<N;i++){
            printf("\n Merci de saisie Id de client:\t");
            scanf("%d",&idr);
            fflush(stdin);
            while(recherche_client(idr)==1){
                printf("l'ID saisie existe deja . ");
                printf(" Saisie id de client :\t ");
                scanf("%d",&idr);
                fflush(stdin);
            }
            Remplir_client(idr);
        }
    }
    else{
        fichier = fopen("Clients.txt","w");
        fclose(fichier);
        ajout_client();
    }
    fclose(fichier);
}

void afficher_client(){
    //char k;
    FILE*fichier=NULL;
    fichier=fopen("Clients.txt","r");
    char buff1[1000];
    if(fichier!=NULL){
        while(fgets(buff1, 1000, fichier)){
            printf("%s",buff1);
        }
    }
    fclose(fichier);
}

void modifier_client(){
	client c;
 	int numr,choix;
 	char a;
 	printf("Saisissez id de client a modifier :\t ");
 	scanf("%d",&numr);
 	fflush(stdin);
 	if(recherche_client(numr)==1){
 		printf("voulez-vous vraiment modifier (o/n)? ");
 		scanf("%c",&a);
 		fflush(stdin);
 		if(a=='o' || a=='O'){
 			FILE *fichier,*fil;
        	fichier=fopen("Clients.txt","r");
        	fil=fopen("cpy.txt","w");
            char buff1[1000];
            while(fgets(buff1, 1000, fichier)){
              	char *domaine = strtok(buff1, "|");
                c.idClient=atoi(domaine);
                domaine = strtok(NULL, "|");
                strcpy(c.nom,domaine);
                domaine = strtok(NULL, "|");
                strcpy(c.prenom,domaine);
                domaine = strtok(NULL, "|");
                c.cin=atoi(domaine);
                domaine = strtok(NULL, "|");
                strcpy(c.adresse,domaine);
                domaine = strtok(NULL, "\n");
                c.telephone=atoi(domaine);
                if(numr==c.idClient){
                    c.idClient=numr;
                    printf("Voulez vous modifier quel champ ? 1/nom_client | 2/prenom_client| 3/CIN|4/Adresse|5/N°_telephone\n ");
                   scanf("%d",&choix);
                   switch(choix){
                   	case 1:
                    printf("entrez le nouveau nom de client:\t");
                    scanf("%s",c.nom);
                    break;
                    case 2:
                    printf("entrez le nouveau prenom de client :\t");
                    scanf("%s",c.prenom);
                    break;
                    case 3:
                    printf("entrez la nouvelle CIN :\t");
                    scanf("%s",&c.cin);
                    fflush(stdin);
                    break;
                    case 4:
                    printf("entrez le nouveau adresse :\t");
                    scanf("%s",c.adresse);
                    break;
                    case 5:
                    printf("entrez le nouveau numero de tel :\t");
                    scanf("%d",&c.telephone);
                    fflush(stdin);
                    break;
                    default :
				    	    printf("ce choix n'existe pas");
				    	    break;
				}

                }
                fprintf(fil,"%d|%s|%s|%d|%s|%d\n",c.idClient,c.nom,c.prenom,c.cin,c.adresse,c.telephone);
            }
			fclose(fichier);
			fclose(fil);
			remove("Clients.txt");
			rename("cpy.txt","Clients.txt");
			printf("la modification a reussi !");
		 }
		else{
			printf("client non modifier");
		}
	 }
	 else printf("l'Id de client saisie n'existe pas\n");
}

void supprimer_client(){
    client c;
 	int numr;
 	char a;
 	printf("entrez id de client a supperime : ");
 	scanf("%d",&numr);
 	fflush(stdin);
 	if(recherche_client(numr)==1){
 		printf("voulez-vous vraiment supperime (o/n)? ");
 		scanf("%c",&a);
 		fflush(stdin);
 		if(a=='o' || a=='O'){
 			FILE *fichier,*fil;
        	fichier=fopen("Clients.txt","r");
        	fil=fopen("cpy.txt","w");
            char buff1[1000];
            while(fgets(buff1, 1000, fichier)){
                char *domaine = strtok(buff1, "|");
                c.idClient=atoi(domaine);
                domaine = strtok(NULL, "|");
                strcpy(c.nom,domaine);
                domaine = strtok(NULL, "|");
                strcpy(c.prenom,domaine);
                domaine = strtok(NULL, "|");
                c.cin=atoi(domaine);
                domaine = strtok(NULL, "|");
                strcpy(c.adresse,domaine);
                domaine = strtok(NULL, "\n");
                c.telephone=atoi(domaine);
                if(numr!=c.idClient){
                    fprintf(fil,"%d|%s|%s|%d|%s|%d\n",c.idClient,c.nom,c.prenom,c.cin,c.adresse,c.telephone);
                }
			}
			fclose(fichier);
			fclose(fil);
			remove("Clients.txt");
			rename("cpy.txt","Clients.txt");
			printf("suppression effectuee avec success");
		 }
		else{
			printf("client non supprimée");
		}
	 }
	 else printf("l'Id de client saisie n'existe pas");
}

//Location d'une voiture

int recherche_contrat(float idr){
	float numcontrat;
	int Buff[1000];
	FILE *fichier=NULL;
	fichier=fopen("ContratsLocations.txt","r");
	if(fichier!=NULL){
		while(fscanf(fichier,"%f|%s",&numcontrat,&Buff)!=EOF){
            if(idr==numcontrat){
                fclose(fichier);
                return 1;
            }
        }
        fclose(fichier);
    }
	return 0;
}

void visualiser_contrat(){
	FILE*fichier=NULL;
	float numCont;
	char debut[9],fin[9],buf[1000];
	fichier=fopen("ContratsLocations.txt","r");
	printf("donnez le numero de contract à voire :\t");
    scanf("%f",&numCont);
    if (recherche_contrat(numCont)==1){
        if(fichier!=NULL){
            while(fgets(buf, 1000, fichier)){
                char *domaine = strtok(buf, "|");
                if (numCont==atof(domaine)){
                    printf("Numero de contract : \t\t%.1f\n",atof(domaine));
                    domaine = strtok(NULL, "|");
                    printf("L'Id de la voiture est : \t%d\n",atoi(domaine));
                    domaine = strtok(NULL, "|");
                    printf("l'Id du client est : \t\t%d\n",atoi(domaine));
                    domaine = strtok(NULL, "|");
                    printf("La date de début est : \t\t%s\n",domaine);
                    domaine = strtok(NULL, "|");
                    printf("La date de fin est : \t\t%s\n",domaine);
                    domaine = strtok(NULL, "|");
                    printf("le Cout est : \t%d\n",atoi(domaine));
                    domaine = strtok(NULL, "\n");
                }
            }
        }
    }
    fclose(fichier);
}

void verification_voiture(){
  	voiture v;

  	FILE*fichier=NULL;
  	fichier=fopen("Voitures.txt","r");
  	if(fichier!=NULL){
  	//	while(!feof(fichier)){
            char buf[1000];
            printf("idVoiture\t marque\t nom Voiture\t couleur\t nbplaces\t prixJour\t EnLocation\n");
            while(fgets(buf, 1000, fichier)){
                char *domaine = strtok(buf, "|");
                v.idVoiture=atoi(domaine);
                domaine = strtok(NULL, "|");
                strcpy(v.marque,domaine);
                domaine = strtok(NULL, "|");
                strcpy(v.nomVoiture,domaine);
                domaine = strtok(NULL, "|");
                strcpy(v.couleur,domaine);
                domaine = strtok(NULL, "|");
                v.nbplaces=atoi(domaine);
                domaine = strtok(NULL, "|");
                v.prixJour=atoi(domaine);
                domaine = strtok(NULL, "\n");
                strcpy(v.EnLocation,domaine);
                if(strcmp(v.EnLocation,"oui")!=0 && strcmp(v.EnLocation,"OUI")!=0 && strcmp(v.EnLocation,"Oui")!=0){
                    printf("%d \t %s\t %s\t %s\t %d\t %d \t %s\n",v.idVoiture,v.marque,v.nomVoiture,v.couleur,v.nbplaces,v.prixJour,v.EnLocation);
                }
		  }
		  fclose(fichier);
	  }
}

void louer_voiture(){
    contrat cont;
    voiture v;
  	int idC,idV,d,p=0;
  	char a;
  	printf("donner l'ID du client :\t");
  	scanf("%d",&idC);
  	fflush(stdin);
  	if(recherche_client(idC)==0) {
        printf(" Ce client n'existe pas. \n\n Voulez-vous l'ajouter (o/n) ?\t");
        scanf("%c",&a);
 		fflush(stdin);
 		if(a=='o' || a=='O'){
            ajout_client(idC);
  		}
    }
    else{
        printf("Voila les voitures que vous pouvez louer :\n");
        verification_voiture();
        printf("\ndonner l'ID de voiture que vous voulez louer a partir de la liste affichee :\t");
        scanf("%d",&idV);
        FILE *fichier,*fil;
        fichier=fopen("Voitures.txt","r");
        fil=fopen("cpy.txt","w");
        char buf[1000];
        while(fgets(buf, 1000, fichier)){
            char *domaine = strtok(buf, "|");
            v.idVoiture=atoi(domaine);
            domaine = strtok(NULL, "|");
            strcpy(v.marque,domaine);
            domaine = strtok(NULL, "|");
            strcpy(v.nomVoiture,domaine);
            domaine = strtok(NULL, "|");
            strcpy(v.couleur,domaine);
            domaine = strtok(NULL, "|");
            v.nbplaces=atoi(domaine);
            domaine = strtok(NULL, "|");
            v.prixJour=atoi(domaine);
            domaine = strtok(NULL, "\n");
            strcpy(v.EnLocation,domaine);
            if(idV==v.idVoiture){
                    if(strcmp(v.EnLocation,"non")==0 || strcmp(v.EnLocation,"NON")==0 || strcmp(v.EnLocation,"Non")==0){
                        strcpy(v.EnLocation,"oui");
                        p=v.prixJour;
                    }
                    else{
                        printf("La voitures est déjà réservée\n");
                        p=-1;
                    }
            }
            fprintf(fil,"%d|%s|%s|%s|%d|%d|%s\n",v.idVoiture,v.marque,v.nomVoiture,v.couleur,v.nbplaces,v.prixJour,v.EnLocation);
        }
        fclose(fichier);
        fclose(fil);
        remove("Voitures.txt");
        rename("cpy.txt","Voitures.txt");
        if (p!=-1){
            printf("taper la durée(jours) de location  :");
            scanf("%d",&d);
            p= p*d;
            printf("le prix de location est : %d\n",p);
            FILE * fichier=NULL;
            fichier=fopen("ContratsLocations.txt","a");
            if(fichier!=NULL){
                printf("Le numero de contrat :\t");
                scanf("%f",&cont.numContrat);
                fflush(stdin);
                while(recherche_contrat(cont.numContrat)){
                    printf("Ce numero existe deja ! \n");
                    printf("Le numero de contrat :\t ");
                    scanf("%2f",&cont.numContrat);
                    fflush(stdin);
                }
                printf("ID de voiture : %d\n",idV);

                cont.idVoiture=idV;

                printf("ID de client :%d\n",idC);

                cont.idClient=idC;

                printf("la date de debut :\n");
                printf("jour :\t");
                scanf("%d",&cont.debut.jour);
                fflush(stdin);
                printf("mois :\t");
                scanf("%d",&cont.debut.mois);
                fflush(stdin);
                printf("annee :\t");
                scanf("%d",&cont.debut.annee);
                fflush(stdin);
                printf("la date de fin :\n");
                printf("jour :\t");
                scanf("%d",&cont.fin.jour);
                fflush(stdin);
                printf("mois :\t");
                scanf("%d",&cont.fin.mois);
                fflush(stdin);
                printf("annee :\t");
                scanf("%d",&cont.fin.annee);
                fflush(stdin);
                printf("le cout : %d\t",p);
				//cont.cout=p;

                fprintf(fichier,"%.2f|%d|%d|%d/%d/%d|%d/%d/%d|%d\n",cont.numContrat,cont.idVoiture,cont.idClient,cont.debut.jour,cont.debut.mois,cont.debut.annee,cont.fin.jour,cont.fin.mois,cont.fin.annee,cont.cout);

              }
              fclose(fichier);
        }
    }
    system("PAUSE");
}

void suppression_contrat(float numr){
    FILE *fichier,*fil;
    char buf[1000];
    float(numCont);
    fichier=fopen("ContratsLocations.txt","r");
    fil=fopen("cpycontrat.txt","w");
    if(fichier!=NULL){
        while(fscanf(fichier,"%f|%s",&numCont,&buf)!=EOF){
            if(numr!=numCont){
                fprintf(fil,"%f|%s\n",numCont,buf);
            }
        }
    }
    fclose(fichier);
    fclose(fil);
    remove("ContratsLocations.txt");
    rename("cpycontrat.txt","ContratsLocations.txt");
}

void Retourner_voiture(){

 	float numr;
 	char a;
 	printf("entrez numero de contrat à retourner :\t ");
 	scanf("%f",&numr);
 	fflush(stdin);
 	if(recherche_contrat(numr)==1){
 		printf("voulez-vous retourner la voiture (o/n)? ");
 		scanf("%c",&a);
 		fflush(stdin);
 		if(a=='o' || a=='O'){
            suppression_contrat(numr);
 			FILE *fichier,*fil;
        	fichier=fopen("Voitures.txt","r");
        	fil=fopen("cpy.txt","w");
            char buf[1000];
            while(fgets(buf, 1000, fichier)){
                voiture v;
              	char *domaine = strtok(buf, "|");
                v.idVoiture=atoi(domaine);
                domaine = strtok(NULL, "|");
                strcpy(v.marque,domaine);
                domaine = strtok(NULL, "|");
                strcpy(v.nomVoiture,domaine);
                domaine = strtok(NULL, "|");
                strcpy(v.couleur,domaine);
                domaine = strtok(NULL, "|");
                v.nbplaces=atoi(domaine);
                domaine = strtok(NULL, "|");
                v.prixJour=atoi(domaine);
                domaine = strtok(NULL, "\n");
                strcpy(v.EnLocation,domaine);
                if(numr==v.idVoiture){
                    strcpy(v.EnLocation,"non");
                }
                fprintf(fil,"%d|%s|%s|%s|%d|%d|%s\n",v.idVoiture,v.marque,v.nomVoiture,v.couleur,v.nbplaces,v.prixJour,v.EnLocation);
            }

			fclose(fichier);
			fclose(fil);
			remove("Voitures.txt");
			rename("cpy.txt","Voitures.txt");

			printf("la Voiture est retournée");
		 }
		else{
			printf("contrat non supprimé");
		}
	 }
	 else printf("Ce numero de contrat n'existe pas");
}

void modifier_contrat(){
contrat cont;
int nbrjours,prixjour,choix;
 	float numr;
 	char a;
 	printf("entrez numero de contrat a modifier :\t ");
 	scanf("%f",&numr);
 	fflush(stdin);
 	if(recherche_contrat(numr)==1){
 		printf("voulez-vous vraiment modifier o/n? ");
 		scanf("%c",&a);
 		fflush(stdin);
 		if(a=='o' || a=='O'){
 			FILE *fichier,*fil;
        	fichier=fopen("ContratsLocations.txt","r");
        	fil=fopen("cpycontrat.txt","w");
        	char buf[1000];
            while(fgets(buf, 1000, fichier)){

                    char *domaine = strtok(buf, "|");
                    cont.numContrat=atof(domaine);
                    domaine = strtok(NULL, "|");
                    cont.idVoiture=atoi(domaine);
                    domaine = strtok(NULL, "|");
                    cont.idClient=atoi(domaine);
                    domaine = strtok(NULL, "/");
                    cont.debut.jour=atoi(domaine);
                    domaine = strtok(NULL, "/");
                    cont.debut.mois=atoi(domaine);
                    domaine = strtok(NULL, "|");
                    cont.debut.annee=atoi(domaine);
                    domaine = strtok(NULL, "/");
                    cont.fin.jour=atoi(domaine);
                    domaine = strtok(NULL, "/");
                    cont.fin.mois=atoi(domaine);
                    domaine = strtok(NULL, "|");
                    cont.fin.annee=atoi(domaine);
                    domaine = strtok(NULL, "\n");
                    cont.cout =atoi(domaine);
                    if(numr==cont.numContrat){
                    	 
                      printf("Voulez vous modifier quel champ ? 1/fin_jour | 2/fin_mois| 3/fin_annee|4/nbre_jour+|5/prix/jour \n ");
                      scanf("%d",&choix);
                       switch(choix){
				        case 1:
                            printf("la nouvelle date de fin :\n");
                            printf("jour :\t");
                            scanf("%d",&cont.fin.jour);
                            fflush(stdin);
                             break;
                        case 2:
                            printf("mois :\t");
                            scanf("%d",&cont.fin.mois);
                            fflush(stdin);
                            break;
                        case 3:
                            printf("annee :\t");
                            scanf("%d",&cont.fin.annee);
                            fflush(stdin);
                            break;
                        case 4:
                             printf(" le nombre de jour ajoute dont la voiture sera louer :");
					        scanf("%d",&nbrjours); 
					        fflush(stdin);
					        break;
					    case 5:
					     printf("le prix par jour du voirure :");
					     scanf("%d",&prixjour);
					     fflush(stdin);
					     break;
					     default :
				    	    printf("ce choix n'existe pas");
				    	    break;
					}
					    cont.cout=nbrjours*prixjour;
					

                }
                fprintf(fil,"%02f|%d|%d|%d/%d/%d|%d/%d/%d|%d\n",cont.numContrat,cont.idVoiture,cont.idClient,cont.debut.jour,cont.debut.mois,cont.debut.annee,cont.fin.jour,cont.fin.mois,cont.fin.annee,cont.cout);
            }

			fclose(fichier);
			fclose(fil);
			remove("ContratsLocations.txt");
			rename("cpycontrat.txt","ContratsLocations.txt");
			printf("la modification a reussi");
		 }
		else{
			printf("contrat non modifier !");
		}
	 }
	 else printf("Ce numero de contrat n'existe pas");
}

void supprimer_contrat(){
  	float numr;
 	char a;
 	printf("entrez numero de contrat a supperimé :\t ");
 	scanf("%f",&numr);
 	fflush(stdin);
 	if(recherche_contrat(numr)==1){
 		printf("voulez-vous vraiment supperime o/n? ");
 		scanf("%c",&a);
 		fflush(stdin);
 		if(a=='o' || a=='O'){
 			suppression_contrat(numr);
            printf("suppression effectuee avec success");
		 }
		else{
			printf("contrat non supprimée");
		}
	 }
	 else printf("le numero de contrat n'existe pas");
}


int Menu_principal(){
	int i,j,a,l,break_=0;
	printf("\n                               \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
	printf("\n                               \xb3 Menu Principal  \xb3");
	printf("\n                               \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
	printf("\n\n");
	printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
    printf("\n               \xba                                              \xba");
	printf("\n               \xba       Location..........................1    \xba");
	printf("\n               \xba       Gestion voitures..................2    \xba");
	printf("\n               \xba       Gestion clients...................3    \xba");
	printf("\n               \xba       Quitter...........................4    \xba");
	printf("\n               \xba                                              \xba");
	printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
	printf("\n\n       \t\tVotre choix :  ");
	scanf("%d",&i);
	system("cls");
	switch(i){
		case 1:
            do{
                printf("\n                               \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
                printf("\n                               \xb3 Location  d'une voiture   \xb3");
                printf("\n                               \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
                printf("\n\n");
                printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
                printf("\n               \xba                                                      \xba");
                printf("\n               \xba   Visualiser contrat............................1    \xba");
                printf("\n               \xba   Louer voiture.................................2    \xba");
                printf("\n               \xba   Retourner voiture.............................3    \xba");
                printf("\n               \xba   Modifier contrat..............................4    \xba");
                printf("\n               \xba   Suppprimer contrat............................5    \xba");
                printf("\n               \xba   Retour........................................6    \xba");
                printf("\n               \xba                                                      \xba");
                printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
                printf("\n\n               Votre choix :  ");
                fflush(stdin);
                scanf("%d",&j);
                system("cls");
                switch(j){
                    case 1:
                        visualiser_contrat();
                        printf("\nAppuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 2:
                        louer_voiture();
                        printf("\nAppuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 3:
                        Retourner_voiture();
                        printf("\nAppuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 4:
                        modifier_contrat();
                        printf("\nAppuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 5:
                        supprimer_contrat();
                        printf("\nAppuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 6:
                        break_=1;
                        break;
                }
            }while(break_==0);
            break_=0;
            Menu_principal();
			break;
		case 2:
            do{
                printf("\n                               \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
                printf("\n                               \xb3   Gestion des Voitures   \xb3 ");
                printf("\n                               \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
                printf("\n\n");
                printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
                printf("\n               \xba                                                     \xba");
                printf("\n               \xba   Liste des voitures..........................1     \xba");
                printf("\n               \xba   Ajouter voiture.............................2     \xba");
                printf("\n               \xba   Modifier voiture............................3     \xba");
                printf("\n               \xba   Supprimer voiture...........................4     \xba");
                printf("\n               \xba   Retour......................................5     \xba");
                printf("\n               \xba                                                     \xba");
                printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
                printf("\n\n               \t\tVotre choix :   ");
                scanf("%d",&a);
                system("cls");
                int b=1;
                switch(a){
                    case 1:
                        Afficher();
                        printf("\nAppuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 2:
                        ajout_voiture();
                        printf("\nAppuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 3:
                        modifier_voiture();
                        printf("\nAppuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 4:
                        supprimer_voiture();
                        printf("\nAppuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 5:
                        break_=1;
                        break;
                }
			}while(break_==0);
            break_=0;
            Menu_principal();
			break;

		case 3:
            do{
                printf("\n                               \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
                printf("\n                               \xb3 Gestion des Clients \xb3           ");
                printf("\n                               \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
                printf("\n\n");
                printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
                printf("\n               \xba                                              \xba");
                printf("\n               \xba   Liste des clients.....................1    \xba");
                printf("\n               \xba   Ajouter client........................2    \xba");
                printf("\n               \xba   Modifier client.......................3    \xba");
                printf("\n               \xba   Suprimer client.......................4    \xba");
                printf("\n               \xba   Retour................................5    \xba");
                printf("\n               \xba                                              \xba");
                printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
                printf("\n\n               Votre choix :  ");
                scanf("%d",&l);
                system("cls");
                switch(l){
                    case 1:
                        afficher_client();
                        printf("\nAppuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 2:
                        ajout_client();
                        printf("\nAppuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 3:
                        modifier_client();
                        printf("\n Appuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 4:
                        supprimer_client();
                        printf("\n Appuyez sur entrer pour continuer \n");
                        getch();
                        system("cls");
                        break;
                    case 5:
                        break_=1;
                        break;
                }
			}while(break_==0);
            break_=0;
            Menu_principal();
			break;
		case 4:
		exit(0);

        }
}

int main(){
    Menu_principal();

    return 0;
}


