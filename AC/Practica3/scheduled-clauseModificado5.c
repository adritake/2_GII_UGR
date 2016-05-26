#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif


main(int argc, char **argv) {

    int i, n=200,chunk,a[n],suma=0;
    omp_sched_t kind = omp_sched_dynamic; // omp_sched_dynamic
    int modifier = 8;

    if(argc < 3) {
        fprintf(stderr,"\nFalta iteraciones o chunk \n");
        exit(-1);
    }

    n = atoi(argv[1]); if (n>200) n=200; chunk = atoi(argv[2]);

    for (i=0; i<n; i++) a[i] = i;

    omp_set_dynamic(1);
    omp_set_num_threads(8);
    omp_set_schedule(kind, modifier);

    #pragma omp parallel for firstprivate(suma) lastprivate(suma) schedule(dynamic,chunk)  num_threads(4)


    for (i=0; i<n; i++)
    {

        if( i == 0)
        printf("Dentro del parallel; dyn-var = %d, nthreads-var = %d, thread-limit-var = %d\n",omp_get_dynamic(), omp_get_max_threads(),omp_get_thread_limit() );

        suma = suma + a[i];
        printf(" thread %d suma a[%d]=%d suma=%d \n",omp_get_thread_num(),i,a[i],suma);

    }

    printf("Fuera de 'parallel for' suma=%d\n",suma);
    printf("Fuera del parallel; dyn-var = %d, nthreads-var = %d, thread-limit-var = %d\n",omp_get_dynamic(), omp_get_max_threads(),omp_get_thread_limit() );

}