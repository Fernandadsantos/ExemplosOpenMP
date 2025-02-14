#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

struct Medicacao{
   char nome[50];
   int intervalo;
   int total;
}; 

void *Lembrete(void* medicacao); 

int main(int argc, char* argv[]) {
    struct Medicacao *m1, *m2, *m3, *m4; 
    
   // Medicação 1
   m1 = malloc(sizeof(struct Medicacao));
   strcpy(m1->nome, "Paracetamol");
   m1->intervalo = 8;
   m1->total =  10;

   // Medicação 2
   m2 = malloc(sizeof(struct Medicacao));
   strcpy(m2->nome, "Dorflex");
   m2->intervalo = 6;
   m2->total = 12;

   // Medicação 3
   m3 = malloc(sizeof(struct Medicacao));
   strcpy(m3->nome, "Cataflan");
   m3->intervalo = 12;
   m3->total = 8;
   
   //vitamina 
   m4 = malloc(sizeof(struct Medicacao));
   strcpy(m4->nome, "B12");
   m4->intervalo = 24;
   m4->total = 7;
   
   //paraleliza as 4 threads por vez
   omp_set_num_threads(4);
   
   # pragma omp parallel sections
   {
       #pragma omp section 
       {
           Lembrete(m1); 
       }
       
       #pragma omp section 
       {
           Lembrete(m2); 
       }
       
       #pragma omp section 
       {
           Lembrete(m3); 
       }
       
       #pragma omp section 
       {
           Lembrete(m4); 
       }
   }
    

   return 0; 
}

void *Lembrete(void* medicacao)  {
    struct Medicacao *med = (struct Medicacao*) medicacao; 
   
   int i;
   time_t t;    
   
   for  (i = 1; i <= med->total; i++){
      time(&t);
      printf("Tomar %s %d/%d ## %s", med->nome, i, med->total, ctime(&t));
      sleep(med->intervalo);
   }
   printf("FIM: %s\n", med->nome);
   free(med);
   return NULL;

} 