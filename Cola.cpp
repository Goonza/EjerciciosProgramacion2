#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{ int tipo, cant;
 } t_dato;

typedef struct
{ int tipo,cod,cant;
} t_carga;

typedef struct s_nodo
{ t_dato dato;
  struct s_nodo *sig;
  } t_nodo;

typedef struct
{ t_nodo *pri;
 t_nodo *ult;
 } t_cola;

void crearCola (t_cola *);
int acolar(t_cola *, t_dato *);
int desacolar(t_cola*, t_dato *);
int haystock(t_carga *,t_dato* ,FILE *,int,FILE**,FILE*);


void main()
{ char op;
  int op1;
  int flag=0;
  int flag2=0;
  int corrimiento=0;
  t_carga stock;
  t_carga nstock;
  t_cola cola;
  t_dato dato;
  FILE *pf;
  FILE *pf2;
  FILE *aux;
  FILE *resta;
  FILE *actualizado;


 	resta=fopen("resta.txt","w+t");
  	if(!resta)
      {printf("\nError al abrir archivo");
       getch();
       exit(1); }

 crearCola (&cola);
 pf2=fopen("Nostock.txt","r+t");
 aux= fopen("Nostock.txt","wt");
   	if(!aux)
      {printf("Error al abrir archivo");
       getch();
       exit(1);}

  pf=fopen("stock.txt","r+t");
  	if(!pf)
   {printf("Error al abrir archivo");
   getch();
   exit(1);}


do
{
         system("cls");
   printf("-----------------------------------------\n"
          "|                                       |\n"
          "| EJERCICIO COLA + ARCHIVO DE TEXTO     |\n"
          "|                                       |\n"
          "| 1) Alta de Stock                      |\n"
          "| 2) Tomar Pedido                       |\n"
          "|                                       |\n"
          "|        0 Para Salir                   |\n"
          "-----------------------------------------\n");
           scanf("%d", &op1);
           fflush(stdin);
         switch (op1)
         {
         case 1:  do {
      printf("Ingrese tipo y cantidad para el alta: ");
      scanf("%d %d", &dato.tipo,&dato.cant);
      fflush(stdin);
      dato.cant=-1*dato.cant;
      	if (acolar(&cola,&dato))
         {printf ("\nPedido tomado\n");
      	printf ("Desea hacer otro pedido? ");
      	scanf("%c", &op);
      	fflush(stdin);
         }
     			 else {
                   printf("\nNo se puede realizar pedido por el momento");
                   op='n';
                  }
     } while (op!='N' && op!='n');
          break;
          case 2:
              do {
      printf("Ingrese tipo y cantidad para el pedido: ");
      scanf("%d %d", &dato.tipo,&dato.cant);
      fflush(stdin);
      	if (acolar(&cola,&dato))
         {printf ("\nPedido tomado\n");
      	printf ("Desea hacer otro pedido? ");
      	scanf("%c", &op);
      	fflush(stdin);
         }
     			 else {
                   printf("\nNo se puede realizar pedido por el momento");
                   op='n';
                  }
     } while (op!='N' && op!='n');
     break;

          case 0:    printf("Saliendo...");
          			   getch();
							fclose(pf);
							fclose(actualizado);
							fclose(resta);
 							fclose(aux);
							remove("resta.txt");
							remove("stock.txt");
							rename("actualizado.txt","stock.txt");
                     exit(1);
                      break;
                        }


     while (desacolar(&cola,&dato))
     {      printf("\n\nPEDIDO ES: %d %d\n", dato.tipo, dato.cant);
            corrimiento=0;
     			printf("\nRealizando pedido/s\n\n");
            fseek(pf,0,0);
     			fscanf(pf,"%d %d %d", &stock.tipo,&stock.cod,&stock.cant);


            while (stock.tipo < dato.tipo)
                   {
                    corrimiento++;

                  if(fscanf(pf,"%d %d %d", &stock.tipo,&stock.cod,&stock.cant)==EOF)
                          stock.tipo=dato.tipo+1;

                       }
             if(stock.tipo ==dato.tipo)            //stock.tipo es en Stock.txt, dato.tipo es la pila.
                 haystock( &stock,&dato,pf,corrimiento,&resta,pf2);
                 else
                 { printf("\nNo existe tipo ingresado");
                 }

       }
                 //Pasar archivos, actualizar y demas...
                actualizado= fopen("actualizado.txt","wt");
                  if(!actualizado)
                         {printf("\nError al abrir archivo");
                   getch();
                   exit(1); }

                 fseek(resta,0,0);
                 fseek(pf,0,0);
                 fseek(actualizado,0,0);
                 fscanf(pf,"%d %d %d", &stock.tipo,&stock.cod,&stock.cant) ;

                 //EL SIGUIENTE WHILE ME VOLVIO LOCO

                   while( flag!=1) //NO SE HACER EL CORTE DE OTRA FORMA, pf NUNCA SE HACE NULL Y NO ANDA feof(pf);
                   {
                    flag2=0;

                      while(fscanf(resta,"%d %d %d", &nstock.tipo,&nstock.cod,&nstock.cant)!=EOF )
                          {
                                 if (nstock.tipo==stock.tipo)
                                     {fprintf(actualizado,"%d %d %d\n", nstock.tipo,nstock.cod,nstock.cant);

                                      flag2=1;
                                       if(fscanf(pf,"%d %d %d", &stock.tipo,&stock.cod,&stock.cant)==EOF)
                                          {
                                          flag=1;}
                                     }
                           }
                               if (flag2==0)
                                   {fprintf(actualizado,"%d %d %d\n", stock.tipo,stock.cod,stock.cant);
                                      if (fscanf(pf,"%d %d %d", &stock.tipo,&stock.cod,&stock.cant)==EOF)
                                            flag=1;

                                   }

                                    fseek(resta,0,0);
                    }

 }  while(op1!=0);
}


int haystock(t_carga *stock,t_dato *d,FILE *pf, int desp,FILE**resta,FILE*pf2)          //  FILE**resta=resta
{     int i,cont=0;
      FILE *aux;
        aux=pf;


      while(stock->tipo==d->tipo)
      { if(stock->cant >= d->cant)
          { cont++;

           if(fscanf(pf,"%d %d %d", &stock->tipo,&stock->cod,&stock->cant)==EOF)         //BUCLE INFINITO SI NO PREGUNTO POR EOF.
              stock->tipo=-1;
          }
           else {
           					if(!pf2)
                        {printf("\nError al abrir archivo");
                         getch();
                        exit(1);}
                   fprintf(pf2,"No hay stock suficiente para %d %d\n", d->tipo,d->cant);
                   fclose(pf2);
                   return 0;
                }
      }

         fseek(aux,0,0);

         for (i=0;i<desp;i++)
              fscanf(aux,"%d %d %d", &stock->tipo,&stock->cod,&stock->cant);       //CORRIMIENTO

          for (i=0;i<cont;i++)
          {
            fscanf(aux,"%d %d %d", &stock->tipo,&stock->cod,&stock->cant);
            stock->cant-=d->cant;
            printf("\nEL STOCK ACTUALIZADO ES: %d %d %d\n", stock->tipo,stock->cod,stock->cant);
            fprintf(*resta,"%d %d %d\n", stock->tipo,stock->cod,stock->cant);

          }
         printf("\nStock modificado\n");
        return 1;
}


void crearCola(t_cola *p)                      //CREAR COLA
{ p->pri=NULL;
  p->ult=NULL;
 }

int acolar(t_cola *p, t_dato *d)                //ACOLAR
{
  t_nodo *nue;

   if (nue=(t_nodo*)malloc(sizeof(t_nodo)))
     { nue->dato=*d;
      nue->sig=NULL;
      if (p->pri==NULL)
          p->pri=nue;
          else{ p->ult->sig=nue;}
      p->ult=nue;
      return 1;}
      else { return 0;}
 }


int desacolar(t_cola *p, t_dato *d)
{
    t_nodo *aux;
     if (p->pri==NULL)
         {printf("\n\n\n::::::::::::::PEDIDOS PROCESADOS:::::::::::::::\n");
         return 0;}
     aux=p->pri;
    *d= p->pri->dato;
     p->pri= p->pri->sig;
      free(aux);
      if (p->pri==NULL)
        p->ult=NULL;
        return 1;
}