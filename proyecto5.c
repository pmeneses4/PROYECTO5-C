#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct disco
{
    int id_disco;
	char nombre[20];
	char artista[40];
	char precio[6];
	char aniolanzamiento[5];
	int existencia;
	struct disco *nxt;
}disk;

typedef struct usuario
{
	char nickname[20];
	char contrasena[30];
	int numcompras;
	int cantidad;
}usr;

FILE *f;
disk *inicio=NULL;
disk *fin=NULL;

void elimina_esp(char *cad);
usr* datos();
void menu(usr *user);
void lista_discos();
void imp_list();
void agrega(disk *a);
void ordenar(int parametro);
void cambio(disk *origen,disk *destino);

int main(int argc, char const *argv[])
{
	//coloque esto para pedir solo los datos
	usr *user;
	printf("Bienvenido a PrebeShop\n");
	user=datos();
	/*usamos la funcion de login*/
	//ya asumiendo que el usuario si se logueo de forma correcta (para esto opini que el nickname del usuario sea "admin")
	menu(user);
	return 0;
}

usr* datos(){
    usr *user=malloc(sizeof(usr));
    printf("Usuario: ");
    fgets(user->nickname,20,stdin);
    printf("Password: ");
    fgets(user->contrasena,30,stdin);
    elimina_esp(user->nickname);
    elimina_esp(user->nickname);
    return user;
}

void elimina_esp(char *cad){
	int tam = strlen(cad);
	cad[tam-1] = '\0';
}

void menu(usr *user){
	int opc,o;
    lista_discos();
	if(strcmp(user->nickname,"admin")==0){
		printf("admin\n\nOpciones\n\n1)Ver lista de liscos por orden\n2)Buscar un disco\n3)consultar datos de los discos\n4)Ver mi perfil\n5)Editar mi perfil\n6)Agregar discos\n7)Remover discos\n8)Actualizar datos de disco\n9)Consultar datos de usuario\n10)Buscar un usuario 11)remover usuario\n");
	}else{
		printf("otro\n\nOpciones\n\n1)Ver lista de discos por orden\n2)Buscar un disco\n3)consultar datos de un discos\n4)Ver mi perfil\n5)Editar mi perfil\n6)Realizar compras\n");
	}
	printf("\nElija su opcion: ");
	scanf("%d",&opc);
	switch(opc){
		case 1:
		    printf("\ncomo desea ver la lista de discos\n1)Por nombre del disco\n2)Por artista\n3)Por precio\n4)Por año de lanzamiento\n?");
		    scanf("%d",&o);
		    ordenar(o);
			printf("\n\n********************Lsta de discos disponibles********************\n\n");
            imp_list();
			break;
		case 2:
			printf("\nBuscar disco\n");
			break;
		case 3:
			printf("\nConsulatr datos de un disco\n");
			break;
		case 4:
			printf("\nver mi perfil\n");
			break;
		case 5:
			printf("\neditar mi perfil\n");
			break;
		case 6:
			if(strcmp(user->nickname,"admin")==0){printf("Agregar discos\n");}
			else{printf("\nEsta opcion no existe, intentalo de nuevo\n");}
			break;
		case 7:
			if(strcmp(user->nickname,"admin")==0){printf("Remover discos");}
			else{printf("\nEsta opcion no existe, intentalo de nuevo\n");}
			break;
		case 8:
			if(strcmp(user->nickname,"admin")==0){printf("Actualizar datos de discos\n");}
			else{printf("\nEsta opcion no existe, intentalo de nuevo\n");}
			break;
		case 9:
			if(strcmp(user->nickname,"admin")==0){printf("Consultar datos de un usuario\n");}
			else{printf("\nEsta opcion no existe, intentalo de nuevo\n");}
			break;
		case 10:
			if(strcmp(user->nickname,"admin")==0){printf("Buscar un usuario");}
			else{printf("\nEsta opcion no existe, intentalo de nuevo\n");}
			break;
		case 11:
			if(strcmp(user->nickname,"admin")==0){printf("Eliminar un usuario");}
			else{printf("\nEsta opcion no existe, intentalo de nuevo\n");}
			break;
		default:
			printf("\nEsta opcion no existe, intentalo de nuevo\n");
	}

	printf("\nDesea realizar otra accion?\n1)si\n2)no (se cerrara su sesion)\n");
	//scanf("%d",&opc);
}

void lista_discos(){
    int i,num;
    f=fopen("db.txt","r");
    fread(&num,sizeof(int),1,f);
    for(i=0;i<num;i++){
        disk *a=malloc(sizeof(disk));
        fread(a,sizeof(disk),1,f);
        agrega(a);
        a->nxt=NULL;
    }
    fclose(f);
}

void agrega(disk *a){
    if(a->existencia>0){
            if(inicio==NULL){
                inicio=a;
                fin=a;
            }else{
                fin->nxt=a;
                fin=a;
            }
        }
}

void imp_list(){
    disk *tmp;
    tmp=inicio;
    while(tmp!=NULL){
        printf("************************************\nid del producto: %d\nNombre del disco: %s\nArtista: %s\naño lanzamiento: %s\nPrecio: $%s\nNumero de discos disponibles: %d\n************************************\n\n",tmp->id_disco,tmp->nombre,tmp->artista,tmp->aniolanzamiento,tmp->precio,tmp->existencia);
        tmp=tmp->nxt;
    }
}

void ordenar(int parametro){
if(inicio!=NULL){
    disk *pivote,*actual;
    disk *temp=malloc(sizeof(disk));
    pivote = inicio;
    while(pivote!=fin){
        actual=pivote->nxt;
        while(actual!=NULL){
            if(parametro==1){
                    if(strcmp(pivote->nombre,actual->nombre)>0){
                    cambio(pivote,temp);
                    cambio(actual,pivote);
                    cambio(temp,actual);
                }
            }
            if(parametro==2){
                    if(strcmp(pivote->artista,actual->artista)>0){
                    printf("hizo cambio entre %d y %d\n",pivote->existencia,actual->existencia);
                    cambio(pivote,temp);
                    cambio(actual,pivote);
                    cambio(temp,actual);
                }
            }
            if(parametro==3){
                    if(strcmp(pivote->precio,actual->precio)>0){
                    printf("hizo cambio entre %d y %d\n",pivote->existencia,actual->existencia);
                    cambio(pivote,temp);
                    cambio(actual,pivote);
                    cambio(temp,actual);
                }
            }
            if(parametro==4){
                if(strcmp(pivote->aniolanzamiento,actual->aniolanzamiento)>0){
                    printf("hizo cambio entre %d y %d\n",pivote->existencia,actual->existencia);
                    cambio(pivote,temp);
                    cambio(actual,pivote);
                    cambio(temp,actual);
                }
            }
            actual=actual->nxt;
        }
        pivote=pivote->nxt;
    }
}

}

void cambio(disk *origen,disk *destino){
    strcpy(destino->nombre,origen->nombre);
    strcpy(destino->artista,origen->artista);
    strcpy(destino->precio,origen->precio);
    strcpy(destino->aniolanzamiento,origen->aniolanzamiento);
    destino->id_disco=origen->id_disco;
    destino->existencia=origen->existencia;
}

/*
	disk a = {1,"The national","Sleep Well Beast","60.95","2017",100};
	disk b = {2,"Process","Sampha","50.00","2007",200};
	disk c = {3,"The animal spirits","James Holden & The Animal Spirits","23.00","2001",50};
	disk d = {4,"Big fish theory","Vince staples","40.98","2002",10};
	disk e = {5,"Pure comedy","Father John Misty","41.54","1997",4000};
	disk f1 = {6,"Pleasure","Feist","32.54","2000",800};
	disk g = {7,"Hippopotamus","Sparks","43.65","2005",1000};
	disk h = {8,"¡Viva!","Los punsetes","46.54","2010",1500};
	disk i = {9,"Witness","Katy Perry","76.78","2013",10000};
	int num = 9;
	f=fopen("db.txt","w");
	fwrite(&num,sizeof(int),1,f);
	fwrite(&a,sizeof(disk),1,f);
	fwrite(&b,sizeof(disk),1,f);
	fwrite(&c,sizeof(disk),1,f);
	fwrite(&d,sizeof(disk),1,f);
	fwrite(&e,sizeof(disk),1,f);
	fwrite(&f1,sizeof(disk),1,f);
	fwrite(&g,sizeof(disk),1,f);
	fwrite(&h,sizeof(disk),1,f);
	fwrite(&i,sizeof(disk),1,f);
	fclose(f);*/
