#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

struct Nodo{
	int dato;
	int altura;
	Nodo *der;
	Nodo *izq;

};

void menu();
bool es_vacio(Nodo *);
Nodo *izquierdo(Nodo *);
Nodo *derecho(Nodo *);
int raiz(Nodo *);
int altura(Nodo *);
void nivel(Nodo *&);
void actualizar_altura(Nodo*);
void rotar_s(Nodo *&,bool);
void rotar_d(Nodo *&,bool); 
void balancear(Nodo *&);
void insertar(Nodo *&,int);
Nodo *CrearNodo(int);
void preorden(Nodo *,int,int,int);

Nodo *arbol1=NULL;
int tipo;
int velocidad=500;

int main(){
	menu();
	while(!kbhit());
	closegraph();
	return 0;
}

void menu(){
	int n,tam;
	printf("DAME LA CANTIDAD DE ELEMENTOS A INTRODUCIR: \n");
	scanf("%d",&tam);
		initwindow(1200,700);
	do{
		printf("1.RELLENAR MANUAL,\n");
		printf("2.RELLENAR AUTOMATICO.\n");
		scanf("%d",&tipo);
		if(tipo==1){
				for(int i=0;i<tam;i++){

				printf("dato[%d]: ",i);
				scanf("%d",&n);
		
				insertar(arbol1,n);
				
			}
			return;
		}
		
		if(tipo==2){
			delay(2000);	
			for(int i=0;i<tam;i++){

				insertar(arbol1,i);
			}
			return;

		}
		printf("\ntipo: %d\n",tipo);
		
	}while(1);
	
}



int raiz(Nodo *arbol){

	int valorRaiz;
	
	valorRaiz=arbol->dato;
	
	return valorRaiz;
}


int maxi(int a,int b){

	if(a>b)
		return a;
	else
		return b;	

}

bool es_vacio(Nodo *arbol){

	if(arbol==NULL)
		return true;
	else
		return false;
}



int altura(Nodo *arbol){

	if(es_vacio(arbol))
		return -1;
	else
		return arbol->altura;
}



void actualizar_altura(Nodo *arbol){
	
	if(!es_vacio(arbol))
		arbol->altura = maxi(altura((arbol)->izq), altura((arbol)->der))+1;
}


Nodo *izquierdo(Nodo *arbol){

	return arbol->izq;
}
Nodo *derecho(Nodo *arbol){

	return arbol->der;
}


void rotar_s(Nodo *&arbol, bool izq){
	

	Nodo *aux;

	if(izq){
		
		aux=izquierdo(arbol);
		(arbol)->izq=derecho(aux);
		aux->der=arbol;
		
	}else{
		aux=derecho(arbol);
		(arbol)->der=izquierdo(aux);
		aux->izq = arbol;
	}
	actualizar_altura(arbol);
	actualizar_altura(aux);

	arbol=aux;
}



void rotar_d(Nodo *&arbol, bool izq){
	
	
	if (izq){
		
		rotar_s((arbol)->izq, false);
		rotar_s(arbol, true);
		
	}else{
		rotar_s ((arbol)->der, true);
		rotar_s (arbol, false);
	}

}


void balancear(Nodo *&arbol){
	
	if(!es_vacio(arbol)){
		
		if(altura (izquierdo (arbol)) - altura (derecho (arbol)) == 2){ 
		
			if (altura ((arbol)->izq->izq) >= altura((arbol)->izq->der))
				rotar_s(arbol, true);
			else
				rotar_d(arbol, true);
				
		}else if(altura(derecho (arbol)) - altura(izquierdo (arbol)) == 2){ 
		
			if (altura((arbol)->der->der) >= altura ((arbol)->der->izq))
				rotar_s(arbol, false);
			else
				rotar_d(arbol, false);
		}
	}
}

Nodo *CrearNodo(int n){

	Nodo *nuevo_nodo=(struct Nodo*)malloc(sizeof(struct Nodo));
	
	nuevo_nodo->altura=0;
	nuevo_nodo->dato=n;
	nuevo_nodo->der=NULL;
	nuevo_nodo->izq=NULL;
	//nuevo_nodo->nivel=0;
	
	return nuevo_nodo;
}

void insertar(Nodo *&arbol, int n){
	
	char cx[100];

	
		if (arbol==NULL){
			
			Nodo *nuevo_nodo=CrearNodo(n);
			arbol=nuevo_nodo;
			//arbol->nivel=nivel;
		
		
		}else{
			
			if (n<raiz(arbol)){
			

				insertar((arbol)->izq,n);
				
			}else{
		

				insertar((arbol)->der,n);
			}
			

			preorden(arbol,0,600,75);
			balancear(arbol);
			actualizar_altura(arbol);
			
			delay(velocidad);
			cleardevice();
			preorden(arbol,0,600,75);
		}
}


void preorden(Nodo *arbol,int nivel,int dx,int dy){
	
	char cx[100];
	setbkcolor(WHITE);
	
	float facx; 
	
	switch(nivel){
	
		case 0:facx=300/(nivel+1);break;
		case 1:facx=300/(nivel+1);break;
		case 2:facx=200/(nivel+1);break;
		case 3:facx=170/(nivel+1);break;
		case 4:facx=70/(nivel+1);break;
		default:facx=300/(nivel+1);break;
	}
	
	if(arbol==NULL){
		
		return;
		
	}else{
		
		outtextxy(550,30,"ARBOL AVL");
		outtextxy(600,50,"raiz");
		setcolor(LIGHTBLUE);
		setfillstyle(1,LIGHTBLUE);
		circle(dx+5,dy+5,15);
		floodfill(dx+5,dy+5,LIGHTBLUE);
		
		setbkcolor(LIGHTBLUE);
		setcolor(WHITE);
		itoa(arbol->dato,cx,10);
		outtextxy(dx-5,dy,cx);
		
		setcolor(BLACK);
		circle(dx+5,dy+5,16);
		if(arbol->izq !=NULL){
				
			setcolor(BLACK);
			line(dx+10,dy+15,dx-facx,dy+40);
		}
		
		if(arbol->der !=NULL){		
			setcolor(BLACK);
			line(dx+10,dy+15,dx+facx,dy+40);
		}
	
		preorden(arbol->izq,nivel+1,dx-facx,(dy+50));
		preorden(arbol->der,nivel+1,dx+facx,(dy+50));
	}
}







