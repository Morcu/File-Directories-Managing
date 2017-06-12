#include <stdio.h>		/* Cabecera llamada al sistema printf  */
#include <unistd.h>		/* Cabecera llamada al sistema gtcwd  */
#include <sys/types.h>	/* Cabeceras llamadas al sistema opendir, readdir y closedir  */
#include <dirent.h>
#include <string.h>

#define TAM_NOMBRE_DIR 512

//dircount
int main(int argc, char *argv[])
{
	/*Variables del programa */
	char nombre_directorio[TAM_NOMBRE_DIR];
	DIR* directorio;
	struct dirent* entrada;
	int countDir = 0, countFich = 0;

    //Uso 2
	/*Si los argumenos son solo uno (argv[0] -> programa) */
    if(argc == 1)
    {
        /*Obtenemos el nombre del directorio actual mediante getcwd */
        getcwd(nombre_directorio,TAM_NOMBRE_DIR);
        
        /*Abrimos el directorio actual mediante opendir */
        if ((directorio = opendir(nombre_directorio)) == NULL) {//Si no se puede abrir el directorio se devuelve -1
            return -1;
        }
        else {

            /*Mientras la entrada sea distinta de NULL */
            while ((entrada = readdir(directorio)) != NULL) {
                /*Imprimimos el campo nombre (d_name) de la entrada */
                if ((strcmp(entrada->d_name, ".") == 0) || (strcmp(entrada->d_name, "..") == 0)){//Si los directorios son "." o ".." añadimos uno al contador de directorios
               
                    countDir++;
     			
                }

                //Imprimimos el nombre del directorio o fichero correspondiente
                printf ("%s", entrada->d_name);
                printf("\n");
                    
                /*Aumentamos el contador correspondiente al tipo de entrada (d_type) */
                if(entrada->d_type == DT_REG){
                    countFich++;
                }
                else if (entrada->d_type == DT_DIR){
                    countDir++;
                }
                   
                
            }/*Fin mientras*/
            
            /*Imrpimios el número de directorios y ficheros*/
            printf("Dirs: %d\n", countDir);
            printf("Files: %d\n",countFich);
            /*Cerramos el directorio */
            closedir(directorio);

            return 0;

        }
        
    //Uso 1
    /*Si no (argv[0] -> programa, argv[1] -> directorio a lista) */
    }else if(argc == 2) {

        strcpy(nombre_directorio, argv[1]);//Copiamos el nombre del directorio pasado como argumento
        
        /*Abrimos el directorio a listar mediante opendir */
        if ((directorio=opendir(nombre_directorio)) == NULL) {//Si no se puede abrir el directorio, o este no existe, se devuelve -1
            return -1;
     
        }
        else {
    
            /*Leemos el directorio con readdir */

            /*Mientras la entrada sea distinta de NULL */
            while ((entrada = readdir(directorio)) != NULL) {
                /*Imprimimos el campo nombre (d_name) de la entrada */
                if ((strcmp(entrada->d_name, ".") == 0) || (strcmp(entrada->d_name, "..") == 0)){//Si los directorios son "." o ".." añadimos uno al contador de directorios

                    
                    countDir++;
                    
                }
                
                //Imprimimos el nombre del directorio o fichero correspondiente
                printf ("%s", entrada->d_name);
                printf("\n");
                
                /*Aumentamos el contador correspondiente al tipo de entrada (d_type) */
                if(entrada->d_type == DT_REG){
                    countFich++;
        
                }
                else if (entrada->d_type == DT_DIR){
                    countDir++;
                }
                
            }
                
        }/*Fin mientras*/
            
            /*Imrpimios el número de directorios y ficheros*/
            printf("Dirs: %d\n", countDir);
            printf("Files: %d\n",countFich);
            /*Cerramos el directorio */
            closedir(directorio);
        
    }else {
        return -1; // Número de argumentos inválido
    }


	/*Retornamos 0 (exito) */
	return 0;
}

