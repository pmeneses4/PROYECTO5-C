#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct disco
{
	char nombre;
	char artista;
	int precio;
	int aniolanzamiento;
}disk;

typedef struct usuario
{
	char nickname[20];
	char contrasena[30];
	int numcompras;
	int cantidad;
}usr;

void elimina_esp(char *cad);
usr* datos();
void menu(usr *user);

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
	usr *user=malloc(sizeof(user));
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

void menu(usr *user){
	int opc;
	if(strcmp(user->nickname,"admin")==0){
		printf("admin\n\nOpciones\n\n1)Ver lista de liscos por orden\n2)Buscar un disco\n3)consultar datos de los discos\n4)Ver mi perfil\n5)Editar mi perfil\n6)Agregar discos\n7)Remover discos\n8)Actualizar datos de disco\n9)Consultar datos de usuario\n10)Buscar un usuario 11)remover usuario\n");
	}else{
		printf("otro\n\nOpciones\n\n1)Ver lista de discos por orden\n2)Buscar un disco\n3)consultar datos de un discos\n4)Ver mi perfil\n5)Editar mi perfil\n6)Realizar compras\n");
	}
	printf("\nElija su opcion: ");
	scanf("%d",&opc);
	switch(opc){
		case 1:
			printf("\nVer lista de discos\n");
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