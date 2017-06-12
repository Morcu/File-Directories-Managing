#include <stdio.h>		/* Cabecera llamada al sistema printf  */
#include <sys/types.h>		/* Cabeceras llamada al sistema open  */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>		/* Cabecera llamadas al sistema read, write y close  */
#include <string.h>
#include <ctype.h>

#define TAM_BUFFER 128
#define DESCRIPTOR_SALIDA_STD 1	/* Descriptor para escribir datos en la salida estandar (generalmente, la consola) */

//filter
int main(int argc, char *argv[])
{


	/*Variables del programa */
	char buffer[TAM_BUFFER];
    
	char bufferM[TAM_BUFFER];
	int f, numbyteleidos;
	
    char m[15];
    char noF[15];

	/*Si los argumentos son menores que dos (argv[0] -> programa, argv[1] -> fichero a mostrar) y retornamos -1 */
	if(argc != 3)
	{
		return -1;
	}
    
    
    //Copiamos en una cadena de caracteres los diferenetes filtros a utilizar por el usuario para modificar el fichero
    strcpy(m, "-M");
    strcpy(noF, "-nofilter");

    
    
	/*Comprobamos el argumento del filtro*/

	if ((strcmp(noF, argv[1])) == 0) {//El filtro solicitado es "nofilter" por lo que el contenido no debe ser modificado solo debe mostrarse por pantalla
        
        /*Abrimos el fichero en modo solo lectura. */
        if ((f = open (argv[2], O_RDONLY)) < 0){ /*Si el descriptor devuelto es menor que 0 retornamos -1 */
            return -1;
            
        } else {
            /*Leemos del descriptor y lo almacenamos en un buffer */
            
            numbyteleidos = read (f, buffer, sizeof(buffer));
            
            /*Mientras los bytes leidos sean distintos de 0 */
            while (numbyteleidos !=0 ){
                
                //Escribimos en el descriptor de la pantalla el contenido del fichero
                write (DESCRIPTOR_SALIDA_STD, buffer,numbyteleidos);
                printf("\n");
                
                /*Volvemos a leer del descriptor de fichero y almacenarlo en el buffer */
                numbyteleidos = read (f, buffer, sizeof(buffer));
                
            }/*Fin mientras*/
        }
        
	}else if ((strcmp(m, argv[1]))== 0) { //El filtro solicitado es "-M" por lo que el contenido del fichero se mostrará en mayúsculas
        
        /*Abrimos el fichero en modo solo lectura. */
		if ((f=open (argv[2], O_RDONLY)) < 0){ /*Si el descriptor devuelto es menor que 0 retornamos -1 */
				return -1;

			} else {
				/*Leemos del descriptor y lo almacenamos en un buffer */

				numbyteleidos = read (f, buffer, sizeof(buffer));

				/*Mientras los bytes leidos sean distintos de 0 */
                while (numbyteleidos !=0 ){
                    
                    int i;
                    //Pasamos a mayusculas el contenido del fichero
                    for (i = 0; i < strlen(buffer); i++) {
                        
                        bufferM[i] = toupper(buffer[i]);
                           
                    }
                    
                    //Escribimos en el descriptor de la pantalla el nuevo contenido del fichero
                    write (DESCRIPTOR_SALIDA_STD, bufferM, numbyteleidos);
                    printf("\n");

                    /*Volvemos a leer del descriptor de fichero y almacenarlo en el buffer */
                    numbyteleidos = read (f, buffer, sizeof(buffer));

                }/*Fin mientras*/
                
			}

            /*Cerramos el descriptor de fichero */
			close(f);

		}else {/*Si los filtros introducidos no son los espereados se devuelve -1*/

		return -1;
	}
  
	/*Retornamos 0 (exito) */
	return 0;
}

