#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


#define TAILLE_MAX 100
#define TAILLE_SOM 10;	



typedef struct Sommet Sommet;
typedef struct AllSom AllSom;
struct Sommet{
	char name;
	int degre;
	char arret[TAILLE_MAX];
	char color;
};
struct AllSom{
	int n;
	int chroma;
	Sommet all[10];
	
};

void print(Sommet s);
void init(Sommet *s);
void insert(Sommet *s);
void insertAll(AllSom *a);
void printAll(AllSom a);
void triGraphe(AllSom *s);
int hasColor(Sommet s);
int isAdjacent(Sommet a,Sommet b);
void addColor(Sommet *a,char c);
void colorer(AllSom *s);
char read();
void videBuffer();

int main(int argc, char **argv){
	
	Sommet D,F,B,C,L,I,N;
	AllSom graphe;
	insertAll(&graphe);
	//printAll(graphe);
	triGraphe(&graphe);
	colorer(&graphe);
	//addColor(&(graphe.all[3]),'5');
	//printAll(graphe);
	printf("%c\n",graphe.chroma);
return 0;
}
void print(Sommet A){
	printf("Nom de Sommet est :%c\n",A.name);
	printf("Degré de %c est : %d\n",A.name,A.degre);
	printf("Les arrets avec les autres sommet sont \n");
	for(int i=0;i<A.degre;i++){
		printf("Arret avec %c\n",A.arret[i]);
	}
	printf("Le sommet %c porte la couleur '%c' \n",A.name,A.color);
	
}
void insert(Sommet *s){
	char name;
	int deg;
	char tab[TAILLE_MAX];
	printf("Entrez le nom de votre Sommet (un caractère)\n");
	name = read();
	printf("Entrez le degré de votre Sommet (un nombre entier) \n");
	scanf("%d",&deg);
	(*s).name = name;		
	(*s).degre = deg;
	for(int i=0; i<deg;i++){
		char c;	
		printf("Entrez le sommet %d adjacent avec ce sommet (un caractère) \n",i+1);
		c = read();
		(*s).arret[i] = c;
	}
	
}
void init(Sommet *s){
	s->name = 'X';
	s->degre = 0;
	s->color = '-';
	for(int i = 0; i<TAILLE_MAX;i++)
		s->arret[i] = '-';
}
void insertAll(AllSom *a){
	int nb = 0;
	printf("Entrez le nombre de sommet que vous avez (un nombre entier) \n");
	scanf("%d",&nb); 
	a->n = nb;
	for(int i =0; i< a->n; i++){	
		Sommet tmp;
		init(&tmp);
		printf("------------------Sommet N° %d ------------------ \n",i+1);
		insert(&tmp);
		a->all[i] = tmp;
	}
}
void printAll(AllSom s){
	for(int i =0; i<s.n;i++){
		print(s.all[i]);
		printf("--------------------------\n");
	}

}
void triGraphe(AllSom *s){
        int i,j;
        int min;
	Sommet tmp;
        for(i = (s->n)-1;i>0;i--){
                min = i;
                for(j = i;j>=0;j--){
                        if(((s->all[j]).degre) < ((s->all[min]).degre))
                                min = j;
                }
                if (min != i){
                        tmp = s->all[i];
                        s->all[i] = s->all[min];
                        s->all[min] = tmp;
                }
        }
}
void addColor(Sommet *a,char c){	
	a->color = c;		
}
int hasColor(Sommet s){
	if(s.color != '-')
		return 1;
	return 0;
}
int isAdjacent(Sommet a,Sommet b){
	int isIt = 0;
	for(int i = 0;i<a.degre;i++){
		if(a.arret[i] == b.name)
			isIt = 1;
	}
	
	return isIt;	
}
void colorer(AllSom *s){
	int cdn = 1, i = 0;
	char col = 49;
	do{
		for(int j=0;j< s->n;j++){
			if(i==0)
				addColor(&(s->all[i]),col);	
			if(!isAdjacent(s->all[j],s->all[i]) && !hasColor(s->all[j])){
				 //printf("j = %d i = %d col = %c \n",j,i,col);
				addColor(&(s->all[j]),col);				
			}
		}
		col++;
		i++;
		if(i == s->n){
                        cdn = 0;
			s->chroma = col - 1;	
		}
	}while(cdn); 
}

char read(){
	char c =0 ;
	c = getchar();
	c = toupper(c);

		while(getchar() != '\n');	
return c;
}

void videBuffer(){
        int c = 0;
        while(c != '\n' && c != EOF)
                c = getchar();
}

