import monitor.*;


class Barberia extends AbstractMonitor{


    private Condition durmiendo = makeCondition();
    private Condition puede_pelar = makeCondition();
    
    private int n_clientes = 0;

    // Invcado por los clientes para cortarse el pelo
    public void cortarPelo (){

        enter();

        //Si no hay clientes es que el barbero esta dormido y hay que despertarlo
        if( n_clientes == 0 )
            durmiendo.signal();
        else
            puede_pelar.await();

        //Si se llama a cortarPelo() quiere decir que ha entrado un cliente nuevo
        //por lo tanto se aumenta el numero de clientes
        n_clientes++;


        leave();


    }

    // Invocado por el barbero para esperar (si procede) a un nuevo cliente y
    //sentarlo para el corte
    public void siguienteCliente (){

        enter();

        //Esta función básicamente sirve para comprabar si no hay clientes en
        //la barbería y que se duerma el barbero
        if(n_clientes == 0){
            System.out.println("El barbero se ha dormido.********************************************\n");
            durmiendo.await();
            System.out.println("El barbero se ha despertado.*******************************************\n");
        }

        leave();

    }

    // Invocado por el barbero para indicar que ha terminado de cortar el pelo
    public void finCliente (){

        enter();

        //Se indica que ya puede pelar y se decrementa el número de clientes
        puede_pelar.signal();
        n_clientes--;

        leave();

    }

}


class Cliente implements Runnable{

    public Thread thr;

    private Barberia bar;
    private int n_cliente;

    //Constructor
    public Cliente( Barberia nbar, int cli){

        bar = nbar;
        thr   = new Thread(this,"cliente " + cli);
        n_cliente = cli;

    }

    public void run(){

        while( true ){
            System.out.println("El cliente " + n_cliente + " esta esperando a ser pelado.\n");
            bar.cortarPelo(); // el cliente espera (si procede) y se corta el pelo
            System.out.println("El cliente " + n_cliente + " se ha pelado y se sale fuera.\n");
            aux.dormir_max(2000);  // el cliente está fuera de la barberia un tiempo
            System.out.println("El cliente " + n_cliente + " ha vuelto a entrar a la barberia.\n");

        }
    }
}

class Barbero implements Runnable{

    public Thread thr;

    private Barberia bar;

    //Constructor
    public Barbero( Barberia nbar){

        bar = nbar;
        thr   = new Thread(this,"barbero ");

    }



    public void run(){

        while( true ){

            //Primero siempre se llama al siguiente cliente y si no hay se duerme
            bar.siguienteCliente ();

            //Cuando llega un cliente se imprime que se esta pelando
            System.out.println("El barbero esta pelando a un cliente\n");
            aux.dormir_max( 2500 ); // el barbero esta cortando el pelo
            System.out.println("El barbero ha pelado a un cliente\n");

            //Se llama a finCliente que se encarga de indicar que se puede
            //pelar y de reducir el numero de clientes
            bar.finCliente ();

        }
    }
}


class MainBarbero{

  public static void main( String[] args ){

    if ( args.length != 1 ){

      System.err.println("Uso: <n_clientes>");
      return ;
    }

    int n_clientes = Integer.parseInt(args[0]);

    Cliente[] clientes = new Cliente[ Integer.parseInt(args[0]) ];
    Barberia barberia = new Barberia();

    //Creacion de hebras
    for( int i=0; i < n_clientes; i++)
        clientes[i] = new Cliente( barberia, i );

    Barbero barbero = new Barbero( barberia );

    //Puesta en marcha de las hebras
    barbero.thr.start();

    for( int i=0; i < n_clientes; i++)
        clientes[i].thr.start();


    }
}
