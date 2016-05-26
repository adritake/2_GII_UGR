//  según la versión de gcc y opciones de optimización usadas, tal vez haga falta
//  usar gcc â€“fno-omit-frame-pointer si gcc quitara el marco pila (%ebp)

#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define TEST 			    0
#define COPY_PASTE_CALC		0

#if ! TEST

	#define NBITS 20
	#define SIZE (1<<NBITS)
	unsigned lista[SIZE];
	#define RESULT (NBITS*(1<<NBITS-1))
#else

/*------------------------------------------------------------------------------------------------------- * /

	#define SIZE 4
	unsigned lista[SIZE]={0x80000000, 0x00100000, 0x00000800, 0x00000001};
	#define RESULT 4
/*------------------------------------------------------------------------------------------------------- */

	#define SIZE 8
	unsigned lista[SIZE]={0x7fffffff, 0xffefffff, 0xfffff7ff, 0xfffffffe,
			      0x01000024, 0x00356700, 0x8900ac00, 0x00bd00ef};
	#define RESULT 156
/*------------------------------------------------------------------------------------------------------- * /

	#define SIZE 8
	unsigned lista[SIZE]={0x0       , 0x10204080, 0x3590ac06, 0x70b0d0e0,
                              0xffffffff, 0x12345678, 0x9abcdef0, 0xcafebeef};
	#define RESULT 116
/*------------------------------------------------------------------------------------------------------- */


#endif

int resultado = 0;

int popcount1(unsigned* array, int len)
{
    int  i,  j,   res=0;
    unsigned x;

    for (i=0; i<len; i++){
	x = array[i];
    	for( j=0; j< 8* sizeof(unsigned); j++){
		res += x & 0x1;
		x >>= 1;
	}
    }

    return res;
}


int popcount2(unsigned* array, int len)
{
    unsigned  i,   res=0;
    unsigned x;

    for (i=0; i<len; i++){
	x = array[i];
    	do {
		res += x & 0x1;
		x >>= 1;
	} while (x);
    }

    return res;
}

int popcount3(unsigned* array, int len) {
        int result = 0;
        int i;
        unsigned x;
        for (i = 0; i < len; i++) {
                x = array[i];
                asm("\n"
                                "ini3:                 \n\t"
                                "shr $0x1, %[x]        \n\t"
                                "adc $0x0, %[r]        \n\t"
                                "test %[x], %[x]       \n\t"
                                "jnz ini3 "

                                : [r] "+r" (result)
                                : [x] "r" (x) );
        }
        return result;
}

int popcount4(unsigned* array, int len) {

        int i, j;
        int result = 0;
        for (i = 0; i < len; i++) {
                int val = 0;
                unsigned x = array[i];
                for (j = 0; j < 8; j++) {
                        val += x & 0x01010101;
                        x >>= 1;
                }

                val += (val >> 16);
                val += (val >> 8);
                result += (val & 0xff);
        }
        return result;
}

int popcount5(unsigned* array, int len) {
        int i;
        int val, result = 0;
        int SSE_mask[] = { 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f };
        int SSE_LUTb[] = { 0x02010100, 0x03020201, 0x03020201, 0x04030302 };

        if (len & 0x3)
                printf("leyendo 128b pero len no múltiplo de 4\n");
        for (i = 0; i < len; i += 4) {
                asm("movdqu        %[x], %%xmm0 \n\t"
                                "movdqa  %%xmm0, %%xmm1 \n\t" // dos copias de x
                                "movdqu    %[m], %%xmm6 \n\t"// máscara
                                "psrlw           $4, %%xmm1 \n\t"
                                "pand    %%xmm6, %%xmm0 \n\t"//; xmm0 – nibbles inferiores
                                "pand    %%xmm6, %%xmm1 \n\t"//; xmm1 – nibbles superiores

                                "movdqu    %[l], %%xmm2 \n\t"//; ...como pshufb sobrescribe LUT
                                "movdqa  %%xmm2, %%xmm3 \n\t"//; ...queremos 2 copias
                                "pshufb  %%xmm0, %%xmm2 \n\t"//; xmm2 = vector popcount inferiores
                                "pshufb  %%xmm1, %%xmm3 \n\t"//; xmm3 = vector popcount superiores

                                "paddb   %%xmm2, %%xmm3 \n\t"//; xmm3 - vector popcount bytes
                                "pxor    %%xmm0, %%xmm0 \n\t"//; xmm0 = 0,0,0,0
                                "psadbw  %%xmm0, %%xmm3 \n\t"//;xmm3 = [pcnt bytes0..7|pcnt bytes8..15]
                                "movhlps %%xmm3, %%xmm0 \n\t"//;xmm3 = [             0           |pcnt bytes0..7 ]
                                "paddd   %%xmm3, %%xmm0 \n\t"//;xmm0 = [ no usado        |pcnt bytes0..15]
                                "movd    %%xmm0, %[val] \n\t"
                                : [val]"=r" (val)
                                : [x] "m" (array[i]),
                                [m] "m" (SSE_mask[0]),
                                [l] "m" (SSE_LUTb[0])
                );
                result += val;
        }
        return result;
}

int popcount6(unsigned* array, int len) {
        int i;
        unsigned x;
        int val, result = 0;
        for (i = 0; i < len; i++) {
                x = array[i];
                asm("popcnt %[x], %[val]        \n\t"
                	: [val]"=r"(val)
                    :   [x] "r" (x)
                );
                result += val;
        }
        return result;
}

int popcount7(unsigned* array, int len) {
        int i;
        unsigned x1, x2;
        int val, result = 0;
        if (len & 0x1)
                printf("Leer 64b y len impar\n");
        for (i = 0; i < len; i += 2) {
                x1 = array[i];
                x2 = array[i + 1];
                asm("popcnt %[x1], %[val]       \n\t"
                    "popcnt %[x2], %%edi    \n\t"
                    "add    %%edi, %[val]   \n\t"
                    : [val]"=r"(val)
                    : [x1] "r" (x1),
                      [x2] "r" (x2)
                    : "edi"
                );
                result += val;
        }
        return result;
}
void crono(int (*func)(), char* msg){
    struct timeval tv1,tv2;	// gettimeofday() secs-usecs
    long           tv_usecs;	// y sus cuentas

    gettimeofday(&tv1,NULL);
    resultado = func(lista, SIZE);
    gettimeofday(&tv2,NULL);

    tv_usecs=(tv2.tv_sec -tv1.tv_sec )*1E6+
             (tv2.tv_usec-tv1.tv_usec);

#if COPY_PASTE_CALC
    printf(    "%ld" "\n",      tv_usecs);
#else
    printf("resultado = %d\t", resultado);
    printf("%s:%9ld us\n", msg, tv_usecs);
#endif

}

int main()
{


#if ! TEST
    int i;			// inicializar array
    for (i=0; i<SIZE; i++)	// se queda en cache
	 lista[i]=i;
#endif

    crono(popcount1, "popcount1 (en lenguaje C-          for)");
    crono(popcount2, "popcount2 (en lenguaje C-        while)");
    crono(popcount3, "popcount3 (lenguaje  ASM- cuerpo while)");
    crono(popcount4, "popcount4 (l.CS:APP 3.49-     group 8b)");
    crono(popcount5, "popcount5 (asm SSE3-       pshufb 128b)");
    crono(popcount6, "popcount6 (asm SSE4-      popcount 32b)");
    crono(popcount7, "popcount7 (asm SSE4-    popcount 2x32b)");


#if ! COPY_PASTE_CALC
    printf("calculado = %d\n", RESULT); /*OF*/
#endif

    exit(0);
}
