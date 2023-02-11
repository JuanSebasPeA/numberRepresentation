/*Integrantes: 
-Juan Sebastian Peña Angarita 
-Isabel Pérez Santos
-Irving Fernando Cmacho Baltazar
*/

/* Inclusión de bibliotecas */
#include<stdio.h>
#include<string.h>
#include<math.h>

/* Define un tamaño máximo para la cadena */
#define MAXSIZE 30
/* constantes que se restan al valor ascii del caracter correpondiente para obtener el valor de este */
#define ASCIICERO 48
#define ASCIIUPPER 55 
#define ASCIILOWER 87

/* Las variables declaradas 'value' y 'string' se encargan de almacenar el valor final de la representación y
   y la cadena de caracteres original ingresada por el usuario respectivamente.
   La variable 'number' obtiene la parte de la cadena que se interpretará como la base, la cual cuando ya es interpretada se almacena en
   la variable entera 'base', mientras que 'numstr' se encarga de guardar la parte de la cadena original que se quiere represenstar */
char stringNum[MAXSIZE],
	 numberB[1],
	 numberBTwo[1],
	 numstr[MAXSIZE];

unsigned int value = 0;	 
int base, counter;
	
/* PROTOTIPOS DE LAS FUNCIONES:
1.
  -Esta función recibe una cadena de caracteres con la representación en un sistema de numeración posicional de un número
   sin signo, permitiendo obtener el valor representado auxiliando de otras funciones.
  -El parámetro numstrptr es un apuntador a la cadena con la representación numérica, mientra que valptr es un apuntador 
   a un entero sin signo en donde se va a devolver el valor.
  -La variable entera sin signo significa que si el Rango de un entero está entre: -32768 y 32767; en un entero sin 
   signo su parte negativa la uso en la positiva, estando su Rango entre: 0 y 65535 */
int getbval(char *numstrptr, unsigned int *valptr );

/* Despliega el conjunto de instrucciones para que el usuario pueda representar la cadena de manera correcta */
void instructions();

/* Esta es una función auxiliar que permite separar la cadena en la parte que se quiere representar y en la base */
int separate (char *string, char *numstrptr, int *count, char *numberBase, char *numberBaseTwo);  

int validate(char *numberBtptr);

/* función que se encarga de interpretar la base */
int interpBase(char *numBptr, char *numBTwoptr, int *baseptr);

/* La función invierte los caracteres de la cadena introducida para ordenarla posicionalmente y obtener su representación númerica */
void inverse(char *string );

/* obtiene la potencia potencia de la base conforme a la posición en que se encuentre el caracter a por el cual se está iterando */
int potBase(int base, int position );   

/* encuentra el valor de cada caracter y va realizando la suma de cada digito multiplicado por la base elevada a la posición del digito */
int findVal(char *string, int *value, int position, int begin, int limit, int rest );

/* Estas funciones sirvieron para realizar la función findVal 
int getnumValue(char *string, int *value, int position ); 

int getUppCaseVal(char *string, int *value, int position );

int getLowCaseVal(char *string, int *value, int position ); */

/* función principal main */
int main() {
			
	int flag = 1;
	numberB[0] = '\0';
	numberBTwo[0] = '\0';
	/* llamada a la función "instructions" */
	instructions();
	
	do {
		
		if (!getbval(numstr, &value ) ) {
			printf("\n\t'%s'= INVALID", stringNum );
		}
		/* DEBUG: 
		printf("\n\nNUMSTR ES: %s", numstr);
		printf("\n\nNUMBER ES: %s", number); */
		/* DEBUG: printf("\nLa base fue encontrada adentro de la función interpBase y ahora su el valor: %d", base); 
		printf("\nLa base ahora es: %d", base); */
 		
	} while (flag == 1);
	
	
	return 0;		
} /* cierra la función principal main */

/* Esta función simplemente enseña las instrucciones de cómo el usuario debe ingresar la cadena a representar */
void instructions() {
	printf("\noperation: read the input stream for outputting the decimal value of numbers" );
	printf("\nrepresented in different bases. The representation has the following format:" );
	printf("\n\ndndn-1...d0#base" );
	printf("\n\nWhere: " );
	/* instructiones para '#' */
	printf("\n\n  #\t\tsignal that just after this, there is a sequence of decimal\n" );
	printf("   \t\tdigits ('0'..'9') representing the base (always in decimal)\n" );
	printf("   \t\tof the starting digit sequence (dndn-1...d0 )" );
	/* instructions for the base */
	printf("\n\n  base\t\ta sequence of decimal digits ('0'..'9') representing the base\n" );
	printf("   \t\tThe base must be any value from 2 up to 36\n" );
	/* instructiones para dndn-1..d0 */
	printf("\n\n  dndn-1..d0\tA sequence of character digits, in each one dx must\n" );
	printf("   \t\trepresent a valid digit for the base. For bases greater than\n" );
	printf("   \t\t10 (up or lower case) letter are used, in alphabetic order,\n" );
	printf("   \t\t'A' (or 'a') represents digit value 10;\n" );
	printf("   \t\t'B' (or 'b') represents digit value 11;\n" );
	printf("   \t\t .\n\t\t .\n ");
	printf("   \t\t'Z' (or 'z') represents digit value 34;\n" );
}

/*Declaración de la función:
  Esta función recurre a otras funciones, como los son: inverse(función que invierte la cadena) y findval(función encuentra el valor de cada caracter de la 
  cadena y va realizando las operaciones necesarias para obtener el valor de la representación final.
  La función retorna 1 si la representación es válida, sino retorna 0 */
int getbval(char *numstrptr, unsigned int *valptr ) {
	/* declaración de las variables de la función e inicialización de la varibale en donde se alamcenará el valor representado y reinio de la base*/
	int j, sizeString, compare; 
	
	*valptr = 0;
	compare = 0;
	base = 0;
	/* sizeString = strlen(numstrptr );
	llamada a la función para invertir la cadena 
	inverse(numstrptr );
	/* lee la cadena a representar */
	printf("\n\nWaiting input: " );
	scanf("%s", &stringNum );
		
	if(separate(stringNum, numstr, &counter, numberB, numberBTwo) ) {
		if(!validate(numberB) ) {
			return 0;
		}
		else if(!validate(numberBTwo) ) {
			return 0;
		}
		else {
			interpBase(numberB, numberBTwo, &base);
		}
	} /* cierra la primera condición */
	
	else {
		base = 10;  
	}
	
	if (base < 2 || base > 35) {
		return 0;
	}
	/* Se almacena el tamaño numstrptr en una variable */
	sizeString = strlen(numstrptr );
	/* llamada a la función para invertir la cadena */
	inverse(numstrptr );					
	/* DEBUG: printf("\n ESTA ES LA CADENA INVERTIDA: %s", string );
		DEBUG: Comprobación de la función que obtiene las potencias 
		printf("\n%d", potBase(base, 2)); */
		
	for (j = 0; j != sizeString; j++ ) {
			
		if (numstrptr[j] >= 48 && numstrptr[j] <= 57 ) {
			compare = numstrptr[j] - ASCIICERO ;
			/* printf("\ncompare es: %d", compare); */
			if(compare >= base) {
				return 0;
			}
			/* llamada a la función findVal para encontrar los valores de 0-9 */
			findVal(numstrptr, valptr, j, 48, 58, ASCIICERO );
		}
			
		else if (numstrptr[j] >= 65 && numstrptr[j] <= 90 ) {
			compare = numstrptr[j] - ASCIIUPPER ;
			/* printf("\ncompare es: %d", compare); */
			if(compare >= base) {
				return 0;
			}
			/* llamada a la función findVal para encontrar los valores de A-Z */
			findVal(numstrptr, valptr, j, 65, 91, ASCIIUPPER);
		}
			
		else if (numstrptr[j] >= 97 && numstrptr[j] <= 122 ) {
			compare = numstrptr[j] - ASCIILOWER ;
			/* printf("\ncompare es: %d", compare); */
			if(compare >= base) {
				return 0;
			}
			/* llamada a la función findVal para encontrar los valores de a-z */
			findVal(numstrptr, valptr, j, 97, 123, ASCIILOWER );
		}
			
		else {
			return 0;
				
		}
	}		
		printf("\n\t'%s'= %d", stringNum, *valptr );	
	
	return 1;
}

/* Esta función se encarga de separar la cadena ingresada por el usuario para posteriormente interpretar la base y
   y obtener la cadena a representar, si la cadena no requiere ser separada la función regresa 0 */
int separate (char *string, char *numstrptr, int *count, char *numberBase, char *numberBaseTwo) {
	
	/* declaración de las variables dentro de la función */
	int i, j, index, sizeString;
	
	*count = 0;
	/* Se almacena el tamaño del string en una variable */
	sizeString = strlen(string);
	/* se copia la cadena original en numstr */
	strcpy(numstrptr, string);
	/* con la función strtok se obtiene la parte de la cadena a represenstar */
	numstrptr = strtok(numstrptr, "#");
	/* DEBUG: printf("\n\nstrtok(numstrptr, '#') es: %s", strtok(numstrptr, "#")); */
	
	/* inicializa toda la cadena numberBase en \0 para posteriormente asignarle otros valores */
	for (i = 0; i != 1; i++) {
		numberBase[i] = '0';
	}
	/* inicializa toda la cadena numberBaseTwo en \0 para posteriormente signarle otros valores */
	 for (i = 0; i != 2; i++) {
		numberBaseTwo[i] = '0';
	} 
	
	/* se itera sobre la cadena numberBase para asignarle los valores que van después de '#' para posteriormente 
	   interpretar la base con esta cadena */   
	for (i = 0; i != sizeString; i++) {		
		if(string[i] == '#') {		
			/* DEBUG: printf("\nEncontrando el simbolo: %c", string[i]); */
			index = i + 1;
			for (j = 0; string[index] != '\0'; j++ ) {
				*count = *count + 1;
				index = index + 1;
			}
			/* DEBUG: printf("\nCOUNT tiene el valor de: %d", count ); */
			
			if(*count == 1) {
				
				index = i + 1;
				for (j = 0; string[index] != '\0'; j++ ) {
					numberBase[j] = string[index];
					index = index + 1;				
				}/* cierra el ciclo for anidado */
				/* DEBUG: printf("\nnumberBase es: %s", numberBase); */
				return 1;
			} /* cierra condición */
			
			else if(*count == 2){
				/* DEBUG: printf("\n\nnumberBaseTwo before: %s\n\n", numberBaseTwo); */
				index = i + 1;
				for (j = 0; j != *count; j++ ) {
					numberBaseTwo[j] = string[index];
					index = index + 1;				
				}/* cierra el ciclo for anidado */
				
				/* DEBUG: printf("\nnumberBaseTwo es: %s", numberBaseTwo); */
				return 1;
			}
			
			else {
				return 0;
			}
			
			/* al terminar de asignar los elementos a la cadena numberBase la función regresa 1 */		
		} /* cierra la condición que detemina si exite un caracter '#' en la cadena original */
	} /* cierra el ciclo for principal
	
	/* DEBUG: 	
		numstrptr = strtok(string, "#");
		numberBase = strtok(NULL, "#"); 
		printf("\n\nNUMSTR dentro de la funcion ES: %s", numstrptr);
		printf("\n\nNUMBER dentro de la función ES: %s", numberBase);
		printf("\nLA SEGUNDA PARTE REBANADA ES: %s", );
	    printf("\n\nLA CADENA REBANADA ES: %s", numstrptr); 
	*/				
}

/* esta función valida se los caracteres paados a la base son válidos para que esta pueda ser interpretada */
int validate(char *numberBtptr ) {
	/* declaración de las variables propias de la función */
	int i, sizeString;
	sizeString = strlen(numberBtptr );
	/* recorre la cadena en donde está la base aún sin ser interpretada, si en la cadena hay algún caracter inválido la función regresa 0, sino regresa 1 */
	for (i = 0; i != sizeString; i++ ) {
		if (numberBtptr[i] < 48 || numberBtptr[i] > 57 ) {
			/* DEBUG: printf("\n numberBtptr[%c] = %d", numberBtptr[i], i ); */
			return 0;
		}
		/* DEBUG: printf("\n numberBtptr[%c] = %d", numberBtptr[i], numberBtptr[i] ); */
	} /* cierra el ciclo for */
	
	return 1;	
}

/* Esta función se encarga de interpretar la base */
int interpBase(char *numBptr, char *numBTwoptr, int *baseptr) {	

	int i, j, add;
	*baseptr = 10;
	/* printf("\nthe size of the string is: %d", size); */
	
	/* si solo hay un digito en la base se busca su valor y se asigna como la base */
	if(counter == 1) {		
		/* DEBUG: printf("\nEl counter es: %d adentro de la función interpBase", counter); */
		/* itera sobre la cadena en donde se encuentra la base */
		for (i = 0; i != counter; i++) {	
			/* itera sobre los códigos Ascii del 0 al 9 para poder obtener el valor de la base */
			for (j = 48; j != 58; j++ ) {			
				if (j == numBptr[i]) {
			/* DEBUG: printf("\nLa base fue encontrada adentro de la función interpBase con el valor: %d", numBptr[i]); */
					*baseptr = j - ASCIICERO;
					return 1;
				}
				
			} /* cierra el ciclo que itera los caracteres ascii de los caracteres 0 al 9 */
		} /* cierra ciclo for que itera sobre la cadena recibida */
	}/* cierra la condición counter == 1 */
	
	else if(counter == 2 ) {
		/* DEBUG: printf("\nEl counter es: %d adentro de la función interpBase", counter); */
		for (i = 0; i != counter; i++ ) {	
			/* itera sobre los códigos Ascii del 0 al 9 para poder obtener el valor de la base */
			for (j = 48; j != 58; j++ ) {			
				if (j == numBTwoptr[i] ) {
					/* DEBUG: printf("\n\nnumBTowptr[%d]: es %c y numBTowptr[%d]: es %c", i, numBTwoptr[i], i + 1, numBTwoptr[i+1]);
					printf("\nj es igual a %d", j); */
					*baseptr = 0;
					/* DEBUG: printf("\nLa base fue encontrada adentro de la función interpBase con el valor: %d", numBptr[i]); */
					*baseptr = (j - ASCIICERO ) * 10;
					/* printf("\n\(j - ASCIICERO) * 10 = %d", (j - ASCIICERO) * 10); */
					/* printf("\n(numBTwoptr[i + 1] = %d", (numBTwoptr[1])); */
					add = (numBTwoptr[i + 1] - ASCIICERO );
					/* printf("\n\n(numBptr[i + 1] - ASCIICERO) es: %d", (numBTwoptr[i + 1] - ASCIICERO)); */
					*baseptr = *baseptr + add;
					/* DEBUG: printf("\n La base ahora es: %d", *baseptr); */  
					return 1;
				}
			} /* cierra el for anidado que itera sobre los códigos ascii del 0 al 9 */
		} /* cierra el ciclo for que itera sobre la cadena numBTwoprt */
	} /* cierra la condición else if(counter == 2) */
	/* si la base es mayor de dos digitos la función asigna el valor de la base como 35 para que automáticamente esta se convierta en una base inválida */
	else if(counter > 2 ){
		*baseptr = 35;  
		return 1;
		
	} else {
		return 0;
	}
	
} /* cierre de la función */	

/* Esta función se encarga de invertir la cadena introducida por el usuario */
void inverse(char *string ) {
	/* declaración de las variables locales de la función */
	int i, j, sizeString;
	char temp;
	/* Se almacena el tamaño del string en una variable */
	sizeString = strlen(string );
	/* inicializo j como el último elemento de la cadena */
	j = sizeString - 1;
	/* itero sobre la cadena */
	for (i = 0; i != sizeString / 2; i++ ) {   
		temp = string[i];
		
		string[i] = string[sizeString - i - 1];
		
		string[sizeString - i - 1] = temp;
	} /* cierra el ciclo for */
	
} /* cierre de la función inverse */ 

/* Esta función se encarga de obtener la potencia de la base conforme a la posición en que se encuentre el caracter a representar */
int potBase(int base, int position ) {
	int k;
	int potenci;
	
	for (k = 0; k != position + 1; k++ ) {
		if (k == 0 ) {
			potenci = 1;
		}
		else {
			potenci = potenci * base;
		}
		/* printf("\nLa potencia de %d ^ %d = %d", base, position, potenci); */
	}
	return potenci;	
} /* cierre de la función potBase */ 

/* función que encuentra el valor numérico de cada caracter(digito) y va obteniendo el valor de la represemación multiplicando
   cada digito por la base elevada a la posición correpondiente y sumando cada uno de estos valores obtenidos con cada digito*/	
int findVal(char *string, int *value, int position, int begin, int limit, int rest ) {
	int i;
	/* bucle que itera sobre los códigos ascii de los caracteres dependiendo del inicio y el límite que se requiera */
	for (i = begin; i != limit; i++ ) {		
		/* si se encuentra de manera correcta el código del caracter se le asigna el valor correspondiente a este
		   y se va sumando al valor de final de la representación */				
		if (i == string[position] ) {				
					*value = *value + (i - rest) * potBase(base, position );		 	
		}
	} /* cierra el ciclo for */
				
	return 1;
} /* cierre de la función findVal */ 

