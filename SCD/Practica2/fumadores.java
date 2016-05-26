
import monitor.* ;

class Estanco extends AbstractMonitor{


    //Condiciones que indican si cada fumador puede recoger su ingrediente
    // y si el estanquero puede fabricar o no
    private Condition puede_recoger_0 = makeCondition();
    private Condition puede_recoger_1 = makeCondition();
    private Condition puede_recoger_2 = makeCondition();
    private Condition puede_fabricar = makeCondition();

    // Invocado por cada fumador, indicando su ingrediente o numero
    public void obtenerIngrediente( int miIngrediente ){

        enter();


        /*
           Lógicamente se deberia de poner este signal despúes de las siguientes
           ya que se debe indicar, que se puede fabricar una vez recogidos los
           ingredientes. Pero si lo hago así las hebras se interbloquean, así que
           he optado por ponerla antes de las condiciones. No hay problema ya que
           este trozo de código se ejecuta en exclusión mutua y no importa si se
           pone antes o despues
        */
        puede_fabricar.signal();

        //Condiciones
        //Según el ingrediente que se pase como argumento se esperará a que el
        // estanquero indique que se puede recoger
        if( miIngrediente == 0 ){
            puede_recoger_0.await();
        }
        else if( miIngrediente == 1 ){
            puede_recoger_1.await();
        }
        else if( miIngrediente == 2 ){
            puede_recoger_2.await();
        }


        leave();

    }



    // Invocado por el estanquero, indicando el ingrediente que pone
    public void ponerIngrediente( int ingrediente ){

        enter();

        //Condiciones
        //Se indica que se puede recoger el ingrediente que se pasa como argumento
        if( ingrediente == 0 ){
            puede_recoger_0.signal();
        }
        else if( ingrediente == 1 ){
            puede_recoger_1.signal();
        }
        else if( ingrediente == 2 ){
            puede_recoger_2.signal();
        }

        leave();

    }



    // Invocado por el estanquero
    public void esperarRecogidaIngrediente(){

        enter();

        //Se espera a que una hebra fumadora recoja su ingrediente
        // y indique que se puede fabricar
        puede_fabricar.await();

        leave();
    }

}

/*
    Al fumador 0 le falta tabaco,
    al fumador 1 le falta papel y
    al fumador 2 le faltan cerillas
*/

class Fumador implements Runnable{

    private int miIngrediente;
    private String ingre;
    public Thread thr ;
    public Estanco estanco;

    //Constructor
    public Fumador( int p_miIngrediente, String nombre, Estanco es  ){

        miIngrediente = p_miIngrediente;
        thr = new Thread(this, nombre);
        estanco = es;

        //Almaceno el nombre del ingreiente en un String simplemente
        // por comodidad a la hora de imprimir por pantalla
        if( p_miIngrediente == 0)
            ingre = "tabaco";
        else if( p_miIngrediente == 1)
            ingre = "papel";
        else if( p_miIngrediente == 2)
            ingre = "cerillas";

    }

    public void run(){
        while ( true ){

             /*
                Se imprime por pantalla que el fumador esta esperando, y se indica al estanco
                que se quiere recoger el ingrediente indicado. Cuando se obtiene se imprime
                por pantalla que se ha obtenido el ingrediente.
             */
             System.out.println("El fumador "+ miIngrediente +" esta esperando " + ingre );
             estanco.obtenerIngrediente( miIngrediente );
             System.out.println("El fumador "+ miIngrediente +" ha recibdo " + ingre );

             /*
                Una vez obtenido el ingrediente, se imprime que se ha comenzado a fumar
                y se expera un tiempo entre 0 y 2 segundos. Cuando se acaba ese tiempo,
                se imprime que se ha terminado de fumar y se vuelve a la parte inicial
                del bucle donde se indica que se quiere el ingrediente.
             */
             System.out.println("El fumador "+ miIngrediente +" ha comenzado a fumar.");
             aux.dormir_max( 2000 );
             System.out.println("El fumador "+ miIngrediente +" ha terminado de fumar.");

         }
    }

}

class Estanquero implements Runnable{

    public Thread thr ;
    public Estanco estanco;
    String ingre;

    //Constructor
    public Estanquero( Estanco es ){

        thr = new Thread(this);
        estanco = es;

    }

    public void run(){

        int ingrediente ;

        while (true){

            //Se genera de forma aleatorio un ingrediente
            ingrediente = (int) (Math.random () * 3.0); // 0,1 o 2

            //Se almacena el nombre del ingrediente en un String
            if( ingrediente == 0)
                ingre = "tabaco";
            else if( ingrediente == 1)
                ingre = "papel";
            else if( ingrediente == 2)
                ingre = "cerillas";

            //Se imprime que se ha producido el ingrediente
            System.out.println("El estanquero ha producido " + ingre);

            //Se llama a esta función que se encarga de indicar a la hebra fumadora
            // que se ha puesto su ingrediente
            estanco.ponerIngrediente( ingrediente );

            //Se espera a que la hebra fumadora recoja el ingrediente
            estanco.esperarRecogidaIngrediente() ;
        }
    }

}

class MainFumadores{

    public static void main( String[] args ) {


        final int N_FUMADORES = 3;

        Fumador[] fumadores = new Fumador[N_FUMADORES];
        Estanco estanco = new Estanco();
        Estanquero estanquero = new Estanquero( estanco );

        //Creación de hebras
        for( int i=0; i < N_FUMADORES; i++)
            fumadores[i] = new Fumador( i, "El fumador "+i, estanco);
            
        //Puesta en marcha de hebras
        for( int i=0; i < N_FUMADORES; i++)
            fumadores[i].thr.start();

        estanquero.thr.start();

    }




}
