#include <stdio.h>
#include <stdlib.h>

/**/

/* 
Ce projet a ete developpe par denis
 J'ai passe je crois 6 Jours a le concevoir 
 Ce qui m'a inspire c'est que je voulais comment ca marchait la commande eval() en
 Python et Javascript , mais c'etait aussi pour le fun bien sur;
Je compte aussi integrer l'interpretation des parenthese 
Les lacunes sont le fait que j'ai oublie d'integrer les variables de type float
Ce qui etonnant c la quantite de code qu'il m'a fallu . 


*/




int length(char*text){// Pour determiner la longeur d'une chaine
	int i = 0;
	char*pointe = text;
	for (i;*pointe != '\0'; ++i){
		pointe++;
	}
	return i;

}

int intString(char*z){ // pour convertir un chaine en entier
	char*zz = z;
	int len  = length(z);
	int res = 0;
	int prim;
	int w;
	for (int i = 0; i < len; ++i){
		w = 1;
		for (int j = 0; j < (len - i - 1); ++j){
			w = w*10; // Je comprends de mieux en mieux comment marches les bases des chiffres
		}
		prim = ((int)(*zz) - 48)*(w);
		res += prim;
		zz++;
	}
	return res;

}

char* reverse(char*a){// inverser une chaine de caractere
	int la = length(a);
	char*pa = a;
	char*res = (void*)malloc((la+1)*sizeof(char));
	char*sres = res;
	pa += la - 1;
	for (int i = 0; i < la; ++i){
		*res = *pa;
		res++,pa--;
	}
	return sres;
}



char* Entry(char*text){// C juste pour le style pour ameliorer scanf

	printf("%s",text);

	char*pa = (void*)malloc(100*sizeof(char));// ici la taille choisi n'est pas final car il se peut qu'il ya ait des espaces vides
	// En fait on ne doit pas surout d'oublier de faire pointer un pointeur sur quelque chpse ou de
	//lui allouer une memoire
	scanf("%s",pa);
	return pa;
}

int somme(char a,char b){// Je comptais l'utiliser pour faire la somme entre 2 char
	int c = (int)a;
	int d = (int)b;
	c -= 48,d -= 48;
	int s = c+d;
	return s;
}


char* Stringy(int n){// pour convertir un entier en chaine de caractere

	int x = n;
	int len = 1;
	while(x >= 10){// c pour d'abord determiner la taille de notre String
		len++;
		x = x/10;
	}
	char*res = (void*)malloc((len+1)*sizeof(char));
	char*sres = res;
	x = n;
	int f;
	while(x >= 10){
		f = x % 10;
		*res = (char)(f+48);
		res++;
		x = x/10;
	}
	*res = (char)(x+48);
	res = sres;
	res = reverse(res);
	return res;
}

char* fusesc(char*a,char b){// pour fusionner une chaine avec un char
	int la = length(a);
	char*aa = a;
	char*res = (void*)malloc((la + 2)*sizeof(char));
	char*sres = res;
	for (int i = 0; i < la; ++i){
		*res = *aa;
		res++,aa++;
	}
	*res = b;
	return sres;

}

char* fuses(char*a,char*b){// pour fusionner une chaine avec une chaine
	int la = length(a);
	int lb = length(b);
	char*aa = a;
	char*bb = b;
	char*res = (void*)malloc((la + lb + 1)*sizeof(char));
	char*sres = res;
	for (int i = 0; i < la; ++i){
		*res = *aa;
		res++,aa++;
	}
	for (int i = 0; i < lb; ++i){
		*res = *bb;
		res++,bb++;
	}
	return sres;

}



int somma(int a,int b){
	int c = a + b;
	return c;
}
int sous(int a,int b){
	int c = a - b;
	return c;
}
int multi(int a,int b){
	int c = a * b;
	return c;
}
int divi(int a,int b){
	int c = a/b;
	return c;
}

char* ExtractAlpha(char*para){// Exemple 4+5*8 on evite de selectionner "4+5"
	char*pointe = reverse(para);
	while(*pointe != '\0'){
		if (*pointe == '+' || *pointe == '-' || *pointe == '*' || *pointe == '/' ){
			break;
		}
		pointe++;
	}
	char*res = "";
	res = fuses(res,reverse(pointe));
	return res;

}

// Les deux qui se superposent la ont la meme concept c juste que j'ai varie le code

char* ExtractDelta(char*para){// Exemple 4+5*8 on evite de selectionner "4+5"
	char*pointe = para;
	pointe += length(para) - 1;
	char*tempo = "";
	while(*pointe != '\0'){
		if (*pointe == '+' || *pointe == '-' || *pointe == '*' || *pointe == '/'){
			break;
		}
		tempo = fusesc(tempo,*pointe);
		pointe--;
	}
	char*res = reverse(tempo);
	return res;

}


void evalNoob(char*toEvaluate){
	char*entree = toEvaluate;
	char*sentree = entree;
	char*tempo = "";
	char*tempo0 = "";
	char*pron = "";
	char*pont = "";
	char*pont1;

	while(*entree != '\0'){// on cherche d'abord les multiplications

		if (*entree == '*'){
			//Faut filtrer pont ex : 4+5+2*8 on separe 4+5+ et 2
			pron = ExtractAlpha(pont);
			pont = ExtractDelta(pont);
			pont1 = "";
			entree++;
			while (*entree != '\0'){
				if (*entree == '+' || *entree == '-' || *entree == '*' || *entree == '/'){
					break;
				}
				pont1 = fusesc(pont1,*entree);
				entree++;
			}
			int x = multi(intString(pont),intString(pont1));
			tempo0 = fuses(pron,Stringy(x));
			tempo = fuses(tempo0,entree);
			entree = tempo;
			sentree = entree;
			pont = "";

		}
		else{
			pont = fusesc(pont,*entree); 
			entree++;
		}
	}

	entree = sentree;
	sentree = entree;
	pont = "";

	while(*entree != '\0'){// on cherche d'abord les divisions
		if (*entree == '/'){
			pron = ExtractAlpha(pont);
			pont = ExtractDelta(pont);
			pont1 = "";
			entree++;
			while (*entree != '\0'){
				if (*entree == '+' || *entree == '-' || *entree == '*' || *entree == '/'){
					break;
				}
				pont1 = fusesc(pont1,*entree);
				entree++;
			}
			int x = divi(intString(pont),intString(pont1));
			tempo0 = fuses(pron,Stringy(x));
			tempo = fuses(tempo0,entree);
			entree = tempo;
			sentree = entree;
			pont = "";

		}
		else{
			pont = fusesc(pont,*entree); 
			entree++;
		}
	}

	entree = sentree;
	sentree = entree;
	pont = "";

	while(*entree != '\0'){
		if (*entree == '+'){

			pron = ExtractAlpha(pont);
			pont = ExtractDelta(pont);
			pont1 = "";
			entree++;
			while(*entree != '\0' ){// saisie du deuxieme operande
				if (*entree == '+' || *entree == '-' || *entree == '*' || *entree == '/'){
					break;
				}
				pont1 = fusesc(pont1,*entree);
				entree++;
			}

			int x = somma(intString(pont),intString(pont1));
			tempo0 = fuses(pron,Stringy(x));
			tempo = fuses(tempo0,entree);
			entree = tempo;
			sentree = entree;
			pont = "";
		}
		else if (*entree == '-'){
			pron = ExtractAlpha(pont);
			pont = ExtractDelta(pont);			
			pont1 = "";
			entree++;
			while(*entree != '\0' ){
				if (*entree == '+' || *entree == '-'){
					break;
				}
				pont1 = fusesc(pont1,*entree);
				entree++;
			}

			//int g = (int)(*(entree + 1)) - 48;
			int x = sous(intString(pont),intString(pont1));
			tempo0 = fuses(pron,Stringy(x));
			tempo = fuses(tempo0,entree);
			entree = tempo;
			sentree = entree;
			pont = "";		
		}
		else{
			pont = fusesc(pont,*entree);
			entree++;
		}
	}
	
	printf("==> %s\n",sentree );
/*	char*a = "1387";
	printf("%i\n",intString(a));
*/

}


int isEqual(char*a,char*b){
	char*pa = a;
	char*pb = b;

	int verite = 1;

	for (int i = 0; i < length(a); ++i){
		if (*pa != *pb){
			verite = 0;
			break;
		}
		pa++;
		pb++;
	}
	return verite;

}

void Introduction(){
	printf("Tapez exit pour quittez sensible a la casse ,desole ;) \n \n");
}

void main(){
	while(1){
		Introduction();
		char*entree = Entry("Entrez une equation \n--> ");
		printf("\e[1;1H\e[2J"); 
		//system("clear"); Je sais pas encore le faire en multiforme windows et linux
		if (isEqual(entree,"exit")){
			break;
		}
		evalNoob(entree);
	}
}
