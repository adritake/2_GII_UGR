
import monitor.*;

class Buffer extends AbstractMonitor{

  private int      numSlots = 0    ,
                   cont     = 0    ;
  private double[] buffer   = null ;

  //Condiciones que uso para evitar que consuma o produzca cuando el vector esta en sus límites
  private Condition producir = makeCondition();
  private Condition consumir = makeCondition();

  //Constructor
  public Buffer( int p_numSlots )
  {
    numSlots = p_numSlots ;
    buffer = new double[numSlots] ;
  }

  //Función que deposita un valor en la posición correspondiente del vector
  public  void depositar( double valor )
  {

    enter();

    if(cont == numSlots)        //Si el vector esta completo...
        producir.await();       //Se espera a que otra hebra saque un dato

    buffer[cont] = valor ;      //Se mete el dato y se actualiza el contador
    cont++ ;
    consumir.signal();          //Se indica que se puede consumir

    leave();
  }

  //Función que extrae un valor del vector en la posición correspondiente
  public double extraer()
  {


    enter();

    if( cont == 0)                  //Si el vector esta vacio...
        consumir.await();           //Se espera a que otra hebra meta un dato en el vector

    cont--;                         //Se actualiza contador
    double valor = buffer[cont] ;   //Se almacena en "valor" el dato del vector

    producir.signal();              //Se indica que se puede producir

    leave();
    return valor;


  }
}

// ****************************************************************************

class Productor implements Runnable
{
  private Buffer bb    ;
  private int    veces ,
                 numP  ;
  public  Thread thr   ;


  //Constructor
  public Productor( Buffer pbb, int pveces, int pnumP )
  {
    bb    = pbb;
    veces = pveces;
    numP  = pnumP ;
    thr   = new Thread(this,"productor "+numP);
  }

  public void run()
  {

      double item = 100*numP ;

      for( int i=0 ; i < veces ; i++ )
      {
        System.out.println(thr.getName()+", produciendo " + item);
        bb.depositar( item++ );
      }


  }
}

// ****************************************************************************

class Consumidor implements Runnable
{
  private Buffer  bb    ;
  private int     veces ,
                  numC  ;
  public  Thread  thr   ;

  //Constructor
  public Consumidor( Buffer pbb, int pveces, int pnumC )
  {
    bb    = pbb;
    veces = pveces;
    numC  = pnumC ;
    thr   = new Thread(this,"consumidor "+numC);
  }
  public void run()
  {

      for( int i=0 ; i<veces ; i++ )
      {
        double item = bb.extraer ();
        System.out.println(thr.getName()+", consumiendo "+item);
      }


  }
}

// ****************************************************************************

class MainProductorConsumidorMonitor
{
  public static void main( String[] args )
  {
    if ( args.length != 5 )
    {
      System.err.println("Uso: ncons nprod tambuf niterp niterc");
      return ;
    }

    // leer parametros, crear vectores y buffer intermedio
    Consumidor[] cons      = new Consumidor[Integer.parseInt(args[0])] ;
	Productor[]  prod      = new Productor[Integer.parseInt(args[1])] ;
    Buffer       buffer    = new Buffer(Integer.parseInt(args[2]));
	int          iter_cons = Integer.parseInt(args[3]);
	int          iter_prod = Integer.parseInt(args[4]);

    if ( cons.length*iter_cons != prod.length*iter_prod )
	  {
      System.err.println("no coinciden número de items a producir con a cosumir");
      return ;
    }

	  // creación hebras
	  for(int i = 0; i < cons.length; i++)
	    cons[i] = new Consumidor(buffer,iter_cons,i) ;
	  for(int i = 0; i < prod.length; i++)
	    prod[i] = new Productor(buffer,iter_prod,i) ;

	  // puesta en marcha las hebras
	  for(int i = 0; i < prod.length; i++)
        prod[i].thr.start();
	  for(int i = 0; i < cons.length; i++)
        cons[i].thr.start();

  }
}
