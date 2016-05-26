#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <chrono>




struct {
   int a;
   int b;
   s[5000];
}
main(){

   using namespace std::chrono;

   for (ii=0; ii<40000;ii++) {

      X1=0; X2=0;

      for(i=0; i<5000;i++)
         X1+=2*s[i].a+ii;

      for(i=0; i<5000;i++)
         X2+=3*s[i].b-ii;

      if (X1<X2)
         R[ii]=X1
      else
         R[ii]=X2;
   }

}
