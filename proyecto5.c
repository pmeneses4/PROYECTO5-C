#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct disco
{
    int id_disco;
	char nombre[30];
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
	struct usuario *nxt;
}usr;

FILE *f;
disk *inicio=NULL;
disk *fin=NULL;
usr *Inicio=NULL;
usr *Fin=NULL;
int num;

void elimina_esp(char *cad);
usr* datos();
int menu(usr *user);
void lista_discos();
void imp_list();
void agrega(disk *a);
void ordenar(int parametro);
void cambio(disk *origen,disk *destino);
void crear();
void elim();
void actualizar();
void buscar();
void c_usr();
usr* buscar_u();
void list_usr();
void imp_listu();
void agregau(usr *a);
void elimu();
void v_p(usr *us);
void e_p(usr *user);
int login(usr *user);
void registro();

void esc();

int main(int argc, char const *argv[])
{
	//esc(); //Usar si es la primera vez que se ejecutara el programa
	int intentos=0,i;
	usr *user;
	while(1){
		printf("\nBienvenido a PrebeShop\n");
		user=datos();
		i=login(user);
		if(i==1&&intentos<3){
			int op=1;
			while(op==1){
				op = menu(user);
			}
			return 0;
		}else{
			intentos++;
			if(intentos==3){
				printf("exceso de intentos\nFavor de intentar de presionar 1 para registrarse y cero para continuar");
				scanf("%d",&i);
				if(i==1){
					registro();
				}
				intentos=0;
			}
		}
	}
	return 0;
}

void registro(){
	getchar();
	usr *user = malloc(sizeof(usr));
	printf("Idgrese un nickname: ");
	fgets(user->nickname,30,stdin);
	elimina_esp(user->nickname);
	printf("Ingrese una contrasena: ");
	fgets(user->contrasena,20,stdin);
	elimina_esp(user->contrasena);
	f = fopen("usuarios.txt","a+");
	FILE *n = fopen("cant.txt","r+");
	fwrite(user,sizeof(usr),1,f);
	num+=1;
	fseek(n,sizeof(int),SEEK_SET);
	fwrite(&num,sizeof(int),1,n);
	fclose(f);
	fclose(n);
}

int login(usr *user){
	int i;
	usr *tmp = malloc(sizeof(usr));
	f = fopen("usuarios.txt","r");
	FILE *n = fopen("cant.txt","r");
	fseek(n,sizeof(int),SEEK_SET);
	fread(&num,sizeof(int),1,n);
	for(i=0;i<num;i++){
		fread(tmp,sizeof(usr),1,f);
		if(strcmp(tmp->nickname,user->nickname)==0&&strcmp(tmp->contrasena,user->contrasena)==0){
			printf("\nencontrado\n");
			i=1;
			return i;
			break;
		}
	}
	i=0;
	fclose(f);
	fclose(n);
	return i;
}

int menu(usr *user){
	int opc,o;
	if(strcmp(user->nickname,"admin")==0){
		printf("admin\n\nOpciones\n\n1)Ver lista de liscos por orden\n2)Buscar un disco\n3)consultar datos de los discos\n4)Ver mi perfil\n5)Editar mi perfil\n6)Agregar discos\n7)Remover discos\n8)Actualizar datos de disco\n9)Consultar datos de usuario\n10)Buscar un usuario 11)remover usuario\n");
	}else{
		printf("otro\n\nOpciones\n\n1)Ver lista de discos por orden\n2)Buscar un disco\n3)consultar datos de un discos\n4)Ver mi perfil\n5)Editar mi perfil\n6)Realizar compras\n");
	}
	printf("\nElija su opcion: ");
	scanf("%d",&opc);
	switch(opc){
		case 1:
		    lista_discos();
		    printf("\ncomo desea ver la lista de discos\n1)Por nombre del disco\n2)Por artista\n3)Por precio\n4)Por año de lanzamiento\n?");
		    scanf("%d",&o);
		    ordenar(o);
			printf("\n\n********************Lsta de discos disponibles********************\n\n");
            imp_list();
			break;
		case 2:
			printf("\nBuscar disco\n");
			buscar();
			break;
		case 3:
			printf("\nConsultar de los discos\n");
			lista_discos();
			imp_list();
			break;
		case 4:
			printf("\nver mi perfil\n");
			v_p(user);
			break;
		case 5:
			printf("\neditar mi perfil\n");
			e_p(user);
			break;
		case 6:
			if(strcmp(user->nickname,"admin")==0){printf("Agregar discos\n");crear();}
			else{printf("\nEsta opcion no existe, intentalo de nuevo\n");}
			break;
		case 7:
			if(strcmp(user->nickname,"admin")==0){printf("Remover discos");elim();}
			else{printf("\nEsta opcion no existe, intentalo de nuevo\n");}
			break;
		case 8:
			if(strcmp(user->nickname,"admin")==0){printf("Actualizar datos de discos\n");actualizar();}
			else{printf("\nEsta opcion no existe, intentalo de nuevo\n");}
			break;
		case 9:
			if(strcmp(user->nickname,"admin")==0){printf("Consultar datos los usuarios\n");c_usr();}
			else{printf("\nEsta opcion no existe, intentalo de nuevo\n");}
			break;
		case 10:
			if(strcmp(user->nickname,"admin")==0){
				printf("Buscar un usuario");
				buscar_u();
			}
			else{printf("\nEsta opcion no existe, intentalo de nuevo\n");}
			break;
		case 11:
			if(strcmp(user->nickname,"admin")==0){printf("Eliminar un usuario");elimu();}
			else{printf("\nEsta opcion no existe, intentalo de nuevo\n");}
			break;
		default:
			printf("\nEsta opcion no existe, intentalo de nuevo\n");
	}

	printf("\nDesea realizar otra accion?\n1)si\n2)no (se cerrara su sesion)\n");
	scanf("%d",&opc);
	return opc;
}

usr* datos(){
    usr *user=malloc(sizeof(usr));
    printf("Usuario: ");
    fgets(user->nickname,20,stdin);
    printf("Password: ");
    fgets(user->contrasena,30,stdin);
    elimina_esp(user->nickname);
    elimina_esp(user->contrasena);
    return user;
}

void elimina_esp(char *cad){
	int tam = strlen(cad);
	cad[tam-1] = '\0';
}

void lista_discos(){
    int i;
    f=fopen("db.txt","r");
    FILE *n = fopen("cant.txt","r");
    fread(&num,sizeof(int),1,n);
    for(i=0;i<num;i++){
        disk *a=malloc(sizeof(disk));
        fread(a,sizeof(disk),1,f);
        agrega(a);
        a->nxt=NULL;
    }
    fclose(f);
    fclose(n);
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
                    //printf("hizo cambio entre %d y %d\n",pivote->existencia,actual->existencia);
                    cambio(pivote,temp);
                    cambio(actual,pivote);
                    cambio(temp,actual);
                }
            }
            if(parametro==3){
                    if(strcmp(pivote->precio,actual->precio)>0){
                    //printf("hizo cambio entre %d y %d\n",pivote->existencia,actual->existencia);
                    cambio(pivote,temp);
                    cambio(actual,pivote);
                    cambio(temp,actual);
                }
            }
            if(parametro==4){
                if(strcmp(pivote->aniolanzamiento,actual->aniolanzamiento)>0){
                    //printf("hizo cambio entre %d y %d\n",pivote->existencia,actual->existencia);
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

void crear(){
	f = fopen("db.txt","a+");
	FILE *n = fopen("cant.txt","r+");
	disk *datos = malloc(sizeof(disk));
	int respuesta;

	fread(&num,sizeof(int),1,n);
    do{
    num+=1;
	fseek(n,0,SEEK_SET);
	fwrite(&num,sizeof(int),1,n);

	setbuf(stdin,NULL);

    datos->id_disco=num;
    printf("\nIngresa el nombre del disco: ");
    fgets(datos->nombre,30,stdin);
    elimina_esp(datos->nombre);
    printf("Ingresa el artista: ");
    fgets(datos->artista,40,stdin);
    elimina_esp(datos->artista);
    printf("Ingresa precio a 4 digitos (ej. 24.32): $");
    fgets(datos->precio,6,stdin);
    getchar();
    printf("Ingresa el anio de lanzamiento a 4 digitos: ");
    fgets(datos->aniolanzamiento,5,stdin);
    printf("Ingresa el numero de unidades en existencia: ");
    scanf("%d",&datos->existencia);
    //Guardamos dentro de nuestro inventario
    fwrite(datos,sizeof(disk),1,f);
    printf("\nPresione 1 para regresar al menu principal: ");
    scanf("%d",&respuesta);
	}while(respuesta != 1);
	//fwrite(&i,sizeof(disk),1,f);
	fclose(f);
	fclose(n);
}

void elim(){
    long int pos;
    int id_e,i;
    printf("coloque es id del disco a eliminar: ");
    scanf("%d",&id_e);
    f = fopen("db.txt","r");
    disk *tmp = malloc(sizeof(disk));
    for(i=0;i<id_e;i++){
        fread(tmp,sizeof(disk),1,f);
        if(i==(id_e-2)){
            pos=ftell(f);
        }
    }
    fclose(f);
    printf("\n************************************\nid del producto: %d\nNombre del disco: %s\nArtista: %s\naño lanzamiento: %s\nPrecio: $%s\nNumero de discos disponibles: %d\n************************************\n\n",tmp->id_disco,tmp->nombre,tmp->artista,tmp->aniolanzamiento,tmp->precio,tmp->existencia);
    printf("\nSeguro de eliminar este disco\n1)Si\n2)No\n? ");
    scanf("%d",&i);
    if(i==1){
        inicio = NULL;
        fin = NULL;
        lista_discos();
        f = fopen("db.txt","w");
        tmp = inicio;
        while(tmp!=NULL){
            if(tmp->id_disco!=id_e){
                fwrite(tmp,sizeof(disk),1,f);
            }
            tmp = tmp->nxt;
        }
        fclose(f);
        FILE *n = fopen("cant.txt","r+");
        fread(&num,sizeof(int),1,n);
        num-=1;
        fseek(n,0,SEEK_SET);
        fwrite(&num,sizeof(int),1,n);
        fclose(n);
    }
}

void actualizar(){
    int id_a,i,en=0;
    long int pos;
    printf("ingrese el id del disco a modificar: ");
    scanf("%d",&id_a);
    f = fopen("db.txt","r+");
    disk *tmp = malloc(sizeof(disk));
    FILE *n = fopen("cant.txt","r+");
    fread(&num,sizeof(int),1,n);
    fclose(n);
    for(i=0;i<id_a;i++){
        fread(tmp,sizeof(disk),1,f);
        if(tmp->id_disco==id_a){
            en=1;
            break;
        }
    }
    if(en==1){
        printf("\n************************************\nid del producto: %d\nNombre del disco: %s\nArtista: %s\naño lanzamiento: %s\nPrecio: $%s\nNumero de discos disponibles: %d\n************************************\n\n",tmp->id_disco,tmp->nombre,tmp->artista,tmp->aniolanzamiento,tmp->precio,tmp->existencia);
        printf("Que desea actualizar\n1)Nombre del disco\n2)Artista\n3)Año de lanzamiento\n4)Precio\n5)Numero de unidades\n6)Todo\n? ");
        scanf("%d",&i);
        
        if(i==1){
            getchar();
            printf("\nIngresa el nombre del disco: ");
            fgets(tmp->nombre,30,stdin);
            elimina_esp(tmp->nombre);
        }

        if(i==2){
            getchar();
            printf("Ingresa el artista: ");
            fgets(tmp->artista,40,stdin);
            elimina_esp(tmp->artista);
        }

        if(i==3){
            getchar();
            printf("Ingresa el anio de lanzamiento a 4 digitos: ");
            fgets(tmp->aniolanzamiento,5,stdin);
        }

        if(i==4){
            getchar();
            printf("Ingresa precio a 4 digitos (ej. 24.32): $");
            fgets(tmp->precio,6,stdin);
        }

        if(i==5){
            getchar();
            printf("Ingresa el numero de unidades en existencia: ");
            scanf("%d",&tmp->existencia);            
        }

        if(i==6){   
					 getchar();
                printf("\nIngresa el nombre del disco: ");
                fgets(tmp->nombre,30,stdin);
                elimina_esp(tmp->nombre);
                printf("Ingresa el artista: ");
                fgets(tmp->artista,40,stdin);
                elimina_esp(tmp->artista);
                printf("Ingresa precio a 4 digitos (ej. 24.32): $");
                fgets(tmp->precio,6,stdin);
                getchar();
                printf("Ingresa el anio de lanzamiento a 4 digitos: ");
                fgets(tmp->aniolanzamiento,5,stdin);
                printf("Ingresa el numero de unidades en existencia: ");
                scanf("%d",&tmp->existencia);
        }

        fseek(f,-(sizeof(disk)),SEEK_CUR);
        fwrite(tmp,sizeof(disk),1,f);
        fseek(f,-(sizeof(disk)),SEEK_CUR);
        fread(tmp,sizeof(disk),1,f);
        printf("\n************************************\nid del producto: %d\nNombre del disco: %s\nArtista: %s\naño lanzamiento: %s\nPrecio: $%s\nNumero de discos disponibles: %d\n************************************\n\n",tmp->id_disco,tmp->nombre,tmp->artista,tmp->aniolanzamiento,tmp->precio,tmp->existencia);

    }else{
        printf("no encontrado");
    }
    fclose(f);
}

void buscar(){
	int i,bandera=0;
	disk *tmp = malloc(sizeof(disk));
	char campo[40];
	printf("Como desea buscar el disco\n1)Por nombre\n2)Por artista\n3)Por precio\n4)Por año\n? ");
	scanf("%d",&i);
	f = fopen("db.txt","r");
	FILE *n = fopen("cant.txt","r+");
	fread(&num,sizeof(int),1,n);
	fclose(n);
	getchar();
	if (i==1){
		printf("Ingrese el nombre del disco: ");
		fgets(campo,40,stdin);
		elimina_esp(campo);
		for(i=0;i<num;i++){
		    fread(tmp,sizeof(disk),1,f);
		    if(strcmp(tmp->nombre,campo)==0){
		    	bandera = 1;
		    	printf("\n************************************\nid del producto: %d\nNombre del disco: %s\nArtista: %s\naño lanzamiento: %s\nPrecio: $%s\nNumero de discos disponibles: %d\n************************************\n\n",tmp->id_disco,tmp->nombre,tmp->artista,tmp->aniolanzamiento,tmp->precio,tmp->existencia);
		        break;
		    }
		}

		if(bandera==0){
			printf("\nDisco no encontrado\n");
		}

	}
	if (i==2){
		printf("Ingrese el nombre del artista: ");
		fgets(campo,40,stdin);
		elimina_esp(campo);
		for(i=0;i<num;i++){
		    fread(tmp,sizeof(disk),1,f);
		    if(strcmp(tmp->artista,campo)==0){
		    	bandera = 1;
		    	printf("\n************************************\nid del producto: %d\nNombre del disco: %s\nArtista: %s\naño lanzamiento: %s\nPrecio: $%s\nNumero de discos disponibles: %d\n************************************\n\n",tmp->id_disco,tmp->nombre,tmp->artista,tmp->aniolanzamiento,tmp->precio,tmp->existencia);
		    }
		}

		if(bandera==0){
			printf("\nArtista no encontrado\n");
		}
	}
	if (i==3){
		printf("Ingrese el precio deseado: ");
		fgets(campo,40,stdin);
		elimina_esp(campo);
		for(i=0;i<num;i++){
		    fread(tmp,sizeof(disk),1,f);
		    if(strcmp(tmp->precio,campo)==0){
		    	bandera = 1;
		    	printf("\n************************************\nid del producto: %d\nNombre del disco: %s\nArtista: %s\naño lanzamiento: %s\nPrecio: $%s\nNumero de discos disponibles: %d\n************************************\n\n",tmp->id_disco,tmp->nombre,tmp->artista,tmp->aniolanzamiento,tmp->precio,tmp->existencia);
		    }
		}

		if(bandera==0){
			printf("\nNo tenemos ese precio disponible\n");
		}	
	}
	if (i==4){
		printf("Ingrese el año: ");
		fgets(campo,40,stdin);
		elimina_esp(campo);
		for(i=0;i<num;i++){
		    fread(tmp,sizeof(disk),1,f);
		    if(strcmp(tmp->aniolanzamiento,campo)==0){
		    	bandera = 1;
		    	printf("\n************************************\nid del producto: %d\nNombre del disco: %s\nArtista: %s\naño lanzamiento: %s\nPrecio: $%s\nNumero de discos disponibles: %d\n************************************\n\n",tmp->id_disco,tmp->nombre,tmp->artista,tmp->aniolanzamiento,tmp->precio,tmp->existencia);
		    }
		}

		if(bandera==0){
			printf("\nNo tenemos discos de ese año\n");
		}
	}
	fclose(f);
}

void c_usr(){
	int i;
	usr *tmp = malloc(sizeof(usr));
	f = fopen("usuarios.txt","r");
	FILE *n = fopen("cant.txt","r");
	fseek(n,sizeof(int),SEEK_SET);
	fread(&num,sizeof(int),1,n);
	printf("Num usr: %d",num);
	printf("\n*****Datos de usuarios*****\n");
	for(i=0;i<num;i++){
		fread(tmp,sizeof(usr),1,f);
		if(strcmp(tmp->nickname,"admin")==0){
			printf("\n***********************\nNombre: %s\n***********************\n",tmp->nickname);
		}else{
			printf("\n***********************\nNombre: %s\nNo.compras: %d\n***********************\n",tmp->nickname,tmp->numcompras);
		}
	}
	fclose(n);
	fclose(f);
}

usr* buscar_u(){
	getchar();
	char cadena[20];
	printf("\nIngrese nombre de usuario: ");
	fgets(cadena,20,stdin);
	elimina_esp(cadena);
	int i,bandera=0;
	usr *tmp = malloc(sizeof(usr));
	f = fopen("usuarios.txt","r");
	FILE *n = fopen("cant.txt","r");
	fseek(n,sizeof(int),SEEK_SET);
	fread(&num,sizeof(int),1,n);
	for(i=0;i<num;i++){
		fread(tmp,sizeof(usr),1,f);
		if(strcmp(tmp->nickname,cadena)==0){
			printf("\n***********************\nNombre: %s\nNo.compras: %d\n***********************\n",tmp->nickname,tmp->numcompras);
			bandera = 1;
			break;
		}
	}
	if(bandera==0){
		printf("El usuario no existe\n");
	}
	fclose(f);
	fclose(n);

	return tmp;
}

void list_usr(){
	Inicio = NULL;
	int i;
	f=fopen("usuarios.txt","r");
	FILE *n = fopen("cant.txt","r");
	fseek(n,sizeof(int),SEEK_SET);
	fread(&num,sizeof(int),1,n);
	for(i=0;i<num;i++){
	    usr *a=malloc(sizeof(usr));
	    fread(a,sizeof(usr),1,f);
	    agregau(a);
	    a->nxt=NULL;
	}
	fclose(f);
	fclose(n);
}

void imp_listu(){
    usr *tmp;
    tmp=Inicio;
    while(tmp!=NULL){
        printf("->%s\n",tmp->nickname);
        tmp=tmp->nxt;
    }
}

void agregau(usr *a){
            if(Inicio==NULL){
                Inicio=a;
                Fin=a;
            }else{
                Fin->nxt=a;
                Fin=a;
            }
}

void elimu(){
	usr *tmp;
	int i;
	char cade[20];
	list_usr();
	printf("\n\n****Lista de usuarios****\n");
	imp_listu();
	getchar();
	printf("escriba el nombre del usuario a eliminar: ");
	fgets(cade,20,stdin);
	elimina_esp(cade);
	f=fopen("usuarios.txt","w");
	FILE *n = fopen("cant.txt","r");
	fseek(n,sizeof(int),SEEK_SET);
	fread(&num,sizeof(int),1,n);
	num-=1;
	fseek(n,sizeof(int),SEEK_SET);
	fwrite(&num,sizeof(int),1,n);
	tmp=Inicio;
	while(tmp!=NULL){
		
		if(strcmp(tmp->nickname,cade)!=0){
			fwrite(tmp,sizeof(usr),1,f);
		}
		tmp=tmp->nxt;
	}
	fclose(f);
	fclose(n);
}

void v_p(usr *us){
	int i,bandera=0;
	usr *tmp = malloc(sizeof(usr));
	f = fopen("usuarios.txt","r");
	FILE *n = fopen("cant.txt","r");
	fseek(n,sizeof(int),SEEK_SET);
	fread(&num,sizeof(int),1,n);
	for(i=0;i<num;i++){
		fread(tmp,sizeof(usr),1,f);
		if(strcmp(tmp->nickname,us->nickname)==0){
			printf("\n***********************\nNombre: %s\nNo.compras: %d\n***********************\n",tmp->nickname,tmp->numcompras);
			bandera = 1;
			break;
		}
	}
	if(bandera==0){
		printf("El usuario no existe\n");
	}
	fclose(f);
	fclose(n);

}

void e_p(usr *user){

	int i;
	usr *tmp = malloc(sizeof(usr));
	f = fopen("usuarios.txt","r");
	FILE *n = fopen("cant.txt","r");
	fseek(n,sizeof(int),SEEK_SET);
	fread(&num,sizeof(int),1,n);
	for(i=0;i<num;i++){
		fread(tmp,sizeof(usr),1,f);
		if(strcmp(tmp->nickname,user->nickname)==0){
			getchar();
			printf("Insgrese nuevo nickname: ");
			fgets(user->nickname,20,stdin);
			elimina_esp(user->nickname);
			printf("Insgrese nueva contraseña: ");
			fgets(user->contrasena,30,stdin);
			elimina_esp(user->contrasena);
			fseek(f,-(sizeof(usr)),SEEK_CUR);
			fwrite(user,sizeof(usr),1,f);
		}
	}
	fclose(f);
	fclose(n);

	
}

void esc(){
	disk a = {1,"the national","sleep well beast","60.95","2017",100};
	disk b = {2,"process","sampha","50.00","2007",200};
	disk c = {3,"the animal spirits","james Holden & The Animal Spirits","23.00","2001",50};
	disk d = {4,"big fish theory","vince staples","40.98","2002",10};
	disk e = {5,"pure comedy","father John Misty","41.54","1997",4000};
	disk f1 = {6,"pleasure","feist","32.54","2000",800};
	disk g = {7,"hippopotamus","fparks","43.65","2005",1000};
	disk h = {8,"¡viva!","los punsetes","46.54","2010",1500};
	disk i = {9,"witness","katy perry","76.78","2013",10000};

	usr v = {"admin","1234",0,0};
	usr w =	{"jav123","5674",0,0};
	usr x = {"Yadfani","1o1123",0,0};

	num = 9;
	f=fopen("db.txt","w");
	FILE *u = fopen("usuarios.txt","w");
	FILE *n = fopen("cant.txt","w");

	fwrite(&num,sizeof(int),1,n);
	num = 3;
	fwrite(&num,sizeof(int),1,n);

	fwrite(&a,sizeof(disk),1,f);
	fwrite(&b,sizeof(disk),1,f);
	fwrite(&c,sizeof(disk),1,f);
	fwrite(&d,sizeof(disk),1,f);
	fwrite(&e,sizeof(disk),1,f);
	fwrite(&f1,sizeof(disk),1,f);
	fwrite(&g,sizeof(disk),1,f);
	fwrite(&h,sizeof(disk),1,f);
	fwrite(&i,sizeof(disk),1,f);

	fwrite(&v,sizeof(usr),1,u);
	fwrite(&w,sizeof(usr),1,u);
	fwrite(&x,sizeof(usr),1,u);

	fclose(f);
	fclose(n);
	fclose(u);
}
