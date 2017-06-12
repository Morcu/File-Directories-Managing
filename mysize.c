#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#define TAM_BUFFER 128
#define TAM_NOMBRE_DIR 512
#define D_TYPE_REG_FILE 8	/*Tipo correspondiente a los ficheros normales en el campo d_type de la estructura dirent*/

//mysize
int main(int argc, char *argv[])
{
    /*Variables del programa */
    DIR* directorio;
    struct dirent* entrada;
    char nomfich[100];
    char nombreMostrar[100];
    int file;
    long posicion;
    char nombre_directorio[TAM_NOMBRE_DIR];
    
    
    if(argc != 1){//Si el numero de argumentos no es el correcto se devuelve -1
        return -1;
    }
    
    /*Obtenemos el nombre del directorio actual mediante getcwd*/
    getcwd(nombre_directorio,TAM_NOMBRE_DIR);
        
    /*Abrimos el directorio actual mediante opendir */
    if ((directorio=opendir(nombre_directorio))==NULL) {//Si no se puede abrir el directorio se devuelve -1
        return -1;
    }
    else {
        
        /*Mientras la entrada sea distinta de NULL */
        while ((entrada = readdir(directorio)) != NULL) {
            /*Imprimimos el campo nombre (d_name) de la entrada */
            
            if(entrada->d_type == DT_REG){//Se comprueba que solo trabajamos con ficheros regulares
                
                strcpy (nomfich, nombre_directorio);
                strcat (nomfich, "/");
                strcat (nomfich, entrada->d_name);
                strcpy (nombreMostrar, entrada->d_name);
                       
                file = open(nomfich, O_RDONLY);//Abrimos el fichero regular correspondiente que se encuentra en el directorio actual
                if(file == -1){//Si no se puede abrir el fichero se devuelve -1
                    return -1;
                }
                else{
                    posicion = lseek(file, 0, SEEK_END);//Situamos el puntero del descriptor al final del fichero mediante lseek para obtener el tamaño
                    close(file);
                    printf("name: %s size: %ld\n",nombreMostrar,posicion);//Imprimimos el nombre y el tamaño del fichero regular
                }
                
                    
            }
                    
            
        }/*Fin mientras*/
            
    }
    
    //Cerramos el directorio
    closedir(directorio);
            
    
    return 0;
            
}
	


