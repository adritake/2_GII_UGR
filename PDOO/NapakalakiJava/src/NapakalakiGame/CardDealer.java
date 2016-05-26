package NapakalakiGame;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

/**
 *
 * @author adritake
 */
public class CardDealer {
    //Cuatro atributos de referencia, cuatro arrays que son mazos de usados y no usados
    private ArrayList<Monster> usedMonsters = new ArrayList();
    private ArrayList<Monster> unusedMonsters = new ArrayList();
    private ArrayList<Treasure> usedTreasures = new ArrayList();
    private ArrayList<Treasure> unusedTreasures = new ArrayList();
    private ArrayList<Cultist> unusedCultists = new ArrayList();
            
            
    private CardDealer() {
    }
    
    public static CardDealer getInstance() {
        return CardDealerHolder.INSTANCE;
    }
    
    private static class CardDealerHolder {

        private static final CardDealer INSTANCE = new CardDealer();
    }
    
    private void initTreasureCardDeck(){
        
       
        Treasure tesoro ;
        
        
        //¡Sí mi amo!        
        tesoro = new Treasure("¡Sí mi amo!",4,TreasureKind.HELMET);
        unusedTreasures.add(tesoro);
        
        //Botas de investigación
        tesoro = new Treasure("Botas de investigación",3,TreasureKind.SHOES);
        unusedTreasures.add(tesoro);
        
        //Capucha de Cthulhu
        tesoro = new Treasure("Capucha de Cthulhu",3,TreasureKind.HELMET);
        unusedTreasures.add(tesoro);
        
        //A prueba de babas
        tesoro = new Treasure("A prueba de babas",2,TreasureKind.ARMOR);
        unusedTreasures.add(tesoro);
        
        //Botas de lluvia ácida
        tesoro = new Treasure("Botas de lluvia ácida",1,TreasureKind.SHOES);
        unusedTreasures.add(tesoro);
        
        //Casco minero
        tesoro = new Treasure("Casco minero",2,TreasureKind.HELMET);
        unusedTreasures.add(tesoro);
        
        //Ametralladora Thompson
        tesoro = new Treasure("Ametralladora Thompson",4,TreasureKind.BOTHHANDS);
        unusedTreasures.add(tesoro);
        
        //Camiseta de la UGR
        tesoro = new Treasure("Camiseta de la UGR",1,TreasureKind.ARMOR);
        unusedTreasures.add(tesoro);
        
        //Clavo de rail ferroviario
        tesoro = new Treasure("Clavo de rail ferroviario",3,TreasureKind.ONEHAND);
        unusedTreasures.add(tesoro);
        
        //Cuchillo de sushi arcano
        tesoro = new Treasure("Cuchillo de sushi arcano",2,TreasureKind.ONEHAND);
        unusedTreasures.add(tesoro);
        
        //Fez alópodo
        tesoro = new Treasure("Fez alópodo",3,TreasureKind.HELMET);
        unusedTreasures.add(tesoro);
        
        //Hacha prehistórica
        tesoro = new Treasure("Hacha prehistórica",2,TreasureKind.ONEHAND);
        unusedTreasures.add(tesoro);
        
        //El aparato del Pr. Tesla 
        tesoro = new Treasure("El aparato del Pr. Tesla",4,TreasureKind.ARMOR);
        unusedTreasures.add(tesoro);
        
        //Gaita
        tesoro = new Treasure("Gaita",4,TreasureKind.BOTHHANDS);
        unusedTreasures.add(tesoro);
        
        //Insecticida
        tesoro = new Treasure("Insecticida",2,TreasureKind.ONEHAND);
        unusedTreasures.add(tesoro);
        
        //Escopeta de 3 cañones
        tesoro = new Treasure("Escopeta de 3 cañones",4,TreasureKind.BOTHHANDS);
        unusedTreasures.add(tesoro);
        
        //Garabato místico
        tesoro = new Treasure("Garabato místico",2,TreasureKind.ONEHAND);
        unusedTreasures.add(tesoro);
        
        //La rebeca metálica
        tesoro = new Treasure("La rebeca metálica",2,TreasureKind.ARMOR);
        unusedTreasures.add(tesoro);
        
        //Lanzallamas
        tesoro = new Treasure("Lanzallamas",4,TreasureKind.BOTHHANDS);
        unusedTreasures.add(tesoro);
        
        //Necro-comicón
        tesoro = new Treasure("Necro-comicón",1,TreasureKind.ONEHAND);
        unusedTreasures.add(tesoro);
        
        //Necrocomicón
        tesoro = new Treasure("Necrocomicón",5,TreasureKind.BOTHHANDS);
        unusedTreasures.add(tesoro);
        
        //Linterna a 2 manos
        tesoro = new Treasure("Linterna a 2 manos",4,TreasureKind.BOTHHANDS);
        unusedTreasures.add(tesoro);
        
        //Necrognomicón
        tesoro = new Treasure("Necrognomicón",2,TreasureKind.ONEHAND);
        unusedTreasures.add(tesoro);
        
        //Necrotelecom
        tesoro = new Treasure("Necrotelecom",2,TreasureKind.HELMET);
        unusedTreasures.add(tesoro);
        
        //Mazo de los antiguos
        tesoro = new Treasure("Mazo de los antiguos",3,TreasureKind.ONEHAND);
        unusedTreasures.add(tesoro);
        
        //Necroplayboycón
        tesoro = new Treasure("Necroplayboycón",3,TreasureKind.ONEHAND);
        unusedTreasures.add(tesoro);
        
        //Porra preternatural
        tesoro = new Treasure("Porra preternatural",2,TreasureKind.ONEHAND);
        unusedTreasures.add(tesoro);
        
        //Shogulador
        tesoro = new Treasure("Shogulador",1,TreasureKind.BOTHHANDS);
        unusedTreasures.add(tesoro);
        
        //Varita de atizamiento
        tesoro = new Treasure("Varita de atizamiento",3,TreasureKind.ONEHAND);
        unusedTreasures.add(tesoro);
        
        //Tentáculo de pega
        tesoro = new Treasure("Tentáculo de pega",2,TreasureKind.HELMET);
        unusedTreasures.add(tesoro);
        tesoro.toString();
        //Zapato deja-amigos
        tesoro = new Treasure("Zapato deja-amigos",1,TreasureKind.SHOES);
        unusedTreasures.add(tesoro);
        
        shuffleTreasures();
        
    }
    
    private void initMonsterCardDeck(){
        
        
        //El Rey de Rosa
        BadConsequence badConsequence = new NumericBadConsequence("Pierdes 5 niveles y 3 tesoros visibles.",5,3,0);
        Prize prize = new Prize(4,2);
        
        unusedMonsters.add(new Monster("El rey de rosa", 13, badConsequence, prize));
        
        //El que redacta en las tinieblas
        badConsequence = new NumericBadConsequence("Toses los pulmones y pierdes 2 niveles",2,0,0);
        prize = new Prize(1,1);
                
        unusedMonsters.add(new Monster("El que redacta en las tinieblas", 10, badConsequence, prize)); 
        
        // 3 Byakhees de bonanza
        badConsequence = new SpecificBadConsequence("Pierdes tu armadura visible y otra oculta", 0, 
            new ArrayList(Arrays.asList(TreasureKind.ARMOR)),
            new ArrayList(Arrays.asList(TreasureKind.ARMOR)));
        prize = new Prize(2,1);
                //CAMBIAR NIVEL -> 2
        unusedMonsters.add(new Monster("3 Byakhees de bonanza", 10, badConsequence, prize)); 
        
        //Chibithulhu
        badConsequence = new SpecificBadConsequence("Embobados con el lindo primigenio te descartas de tu casco visible", 
            0, new ArrayList(Arrays.asList(TreasureKind.HELMET)),new ArrayList());
        prize = new Prize(1,1); 
        unusedMonsters.add(new Monster("Chibithulhu", 2, badConsequence, prize));
        
        //Los Hondos
        badConsequence = new DeathBadConsequence("Estos monstruos resultan bastante superficiales y te aburren " +
            "mortalmente. Estas muerto");
        prize = new Prize(2,1);
        unusedMonsters.add(new Monster("Los Hondos", 8, badConsequence, prize));
        
        //El sopor de Dunwich
        badConsequence = new SpecificBadConsequence("El primordial bostezo contagioso. Pierdes el calzado visible",0, 
                                            new ArrayList(Arrays.asList(TreasureKind.SHOES)),
                                            new ArrayList() );
        prize = new Prize(1, 1);
        unusedMonsters.add(new Monster("El sopor de Dunwich", 2, badConsequence, prize));
        
        


        // Ángeles de la noche ibicenca
        badConsequence = new SpecificBadConsequence("Te atrapan para llevarte " +
                                            "de fiesta y te dejan caer en mitad del " +
                                            "vuelo. Descarta 1 mano visible y 1 " +
                                            "mano oculta",0, 
                                            new ArrayList(Arrays.asList(TreasureKind.ONEHAND)),
                                            new ArrayList(Arrays.asList(TreasureKind.ONEHAND)) );
        prize = new Prize(1, 4);
        unusedMonsters.add(new Monster("Ángeles de la noche ibicenca", 14, badConsequence, prize));
        
        
        
         // ́El gorrón en el umbral (Falta saber como quitar todos los tesoros visbles)
        badConsequence = new NumericBadConsequence("Pierdes todos tus tesoros visibles",0, 5,0);
        prize = new Prize(1, 3);
        unusedMonsters.add(new Monster("El gorrón en el umbral", 10, badConsequence, prize));
        
        
         // H.P. Munchcraft
        badConsequence = new SpecificBadConsequence("Pierdes la armadura visible",0, 
                                            new ArrayList(Arrays.asList(TreasureKind.ARMOR)),
                                            new ArrayList(Arrays.asList() ));
        prize = new Prize(1, 2);
        unusedMonsters.add(new Monster("H.P. Munchcraft", 6, badConsequence, prize));
        
        
        
        
        // Bichgooth
        badConsequence = new SpecificBadConsequence("Sientes bichos bajo la ropa. Descarta la armadura visible",0, 
                                            new ArrayList(Arrays.asList(TreasureKind.ARMOR)),
                                            new ArrayList(Arrays.asList() ));
        prize = new Prize(1, 1);
        unusedMonsters.add(new Monster("Bichgooth", 2, badConsequence, prize));
        
        



        // Dameargo
        badConsequence = new SpecificBadConsequence("Te intentas escaquear. Pierdes una mano visible.",0, 
                                            new ArrayList(Arrays.asList(TreasureKind.ONEHAND)),
                                            new ArrayList(Arrays.asList() ));
        prize = new Prize(1, 2);
        unusedMonsters.add(new Monster("Dameargo", 1, badConsequence, prize));
        
        
        
        
        
        // Pollipólipo volante
        badConsequence = new NumericBadConsequence("Da mucho asquito. Pierdes 3 niveles.",3, 0, 0);
                                            
        prize = new Prize(1, 1);
        unusedMonsters.add(new Monster("Pollipólipo volante", 3, badConsequence, prize));
        
        
        
         // Yskhtihyssg-Goth
        badConsequence = new DeathBadConsequence("No le hace gracia que pronuncien mal su nombre. Estás muerto");
                                            
        prize = new Prize(1, 3);
        unusedMonsters.add(new Monster("Yskhtihyssg-Goth", 12, badConsequence, prize));
        
        
         // Familia feliz
        badConsequence = new DeathBadConsequence("La familia te atrapa. Estás muerto.");
                                            
        prize = new Prize(1, 4);
        unusedMonsters.add(new Monster("Familia feliz", 1, badConsequence, prize));
        
        
         // Roboggoth
        badConsequence = new SpecificBadConsequence("La quinta directiva primaria te obliga a perder 2 niveles y un tesoro 2 manos visible", 
                                             2,new ArrayList(Arrays.asList(TreasureKind.BOTHHANDS)), 
                                              new ArrayList( ));
                                            
        prize = new Prize(1, 2);
        unusedMonsters.add(new Monster("Roboggoth", 8, badConsequence, prize));
        
       
        

        // El espia
        badConsequence = new SpecificBadConsequence("Te asusta en la noche. Pierdes un casco visible.", 
                                             0,new ArrayList(Arrays.asList(TreasureKind.HELMET)), 
                                              new ArrayList( ));
                                            
        prize = new Prize(1, 1);
        unusedMonsters.add(new Monster("El espia", 5, badConsequence, prize));
        
        
        
        // El Lenguas
        badConsequence = new NumericBadConsequence("Menudo susto te llevas. Pierdes 2 niveles y 5 tesoros visibles.", 
                                             2,5,0);
                                            
        prize = new Prize(1, 1);
        unusedMonsters.add(new Monster("El Lenguas", 20, badConsequence, prize));
        
        
        
        // Bicéfalo
        badConsequence = new SpecificBadConsequence("Te faltan manos para " +
                                            "tanta cabeza. Pierdes 3 niveles y tus " +
                                            "tesoros visibles de las manos.",
                                             2,
                                            new ArrayList(Arrays.asList(TreasureKind.ONEHAND, TreasureKind.ONEHAND, TreasureKind.BOTHHANDS)),
                                            new ArrayList());
                                            
        prize = new Prize(1, 1);
        unusedMonsters.add(new Monster("Bicéfalo", 20, badConsequence, prize));
        
        
        /////////////////////////////////////////////////////
        ///
        /// AÑADIR NUEVOS MONSTRUOS CON EL NUEVO CONSTRUCTOR
        ///
        /////////////////////////////////////////////////////
        
        // El mal indecible impronunciable
        badConsequence = new SpecificBadConsequence("Pierdes 1 mano visible", 0, new ArrayList(Arrays.asList(TreasureKind.ONEHAND)), new ArrayList());
                                            
        prize = new Prize(1, 3);
        unusedMonsters.add(new Monster("El mal indecible impronunciable", 10, badConsequence, prize,-2));
        
        
        // Testigos oculares
        badConsequence = new NumericBadConsequence("Pierdes tus tesoros visbles. Jajaja", 
                                             0,BadConsequence.MAXTREASURES,0);
                                            
        prize = new Prize(1, 2);
        unusedMonsters.add(new Monster("Testigos oculares", 6, badConsequence, prize,2));
        
        
        // El gran cthulhu
        badConsequence = new DeathBadConsequence("Hoy no es tu día de suerte. Mueres");
                                            
        prize = new Prize(5, 3);
        unusedMonsters.add(new Monster("El gran cthulhu", 20, badConsequence, prize,4));
        
        
        // Serpiente Político
        badConsequence = new NumericBadConsequence("Tu gobierno te recorta 2 niveles", 
                                             2,0,0);
                                            
        prize = new Prize(5, 3);
        unusedMonsters.add(new Monster("Serpiente Político", 8, badConsequence, prize,-2));
        
        
        
        // Felpuggoth
        badConsequence = new SpecificBadConsequence("Pierdes tu casco y tu armadura visible. Pierdes tus manos ocultas", 
                                             0,new ArrayList(Arrays.asList(TreasureKind.HELMET,TreasureKind.ARMOR)),
                                             new ArrayList(Arrays.asList(TreasureKind.ONEHAND,TreasureKind.ONEHAND,TreasureKind.BOTHHANDS,TreasureKind.BOTHHANDS)));
                                            
        prize = new Prize(1, 1);
        unusedMonsters.add(new Monster("Felpuggoth", 2, badConsequence, prize,5));
        
        
        // Shoggoth
        badConsequence = new NumericBadConsequence("Pierdes 2 niveles", 
                                             2,0,0);
                                            
        prize = new Prize(2, 4);
        unusedMonsters.add(new Monster("Shoggoth", 16, badConsequence, prize,-4));
        
        
        
        // Lolitagooth
        badConsequence = new NumericBadConsequence("Pintalabios negro. Pierdes 2 niveles", 
                                             2,0,0);
                                            
        prize = new Prize(1, 1);
        unusedMonsters.add(new Monster("Lolitagooth", 16, badConsequence, prize,3));
        
        
        shuffleMonsters();
        
        
    }
    
    public void initCultistCardDeck(){
        
        
        
        unusedCultists.add(new Cultist("+1 por cada sectario en juego. No puedes dejar de ser sectario.",1));
        unusedCultists.add(new Cultist("+2 por cada sectario en juego. No puedes dejar de ser sectario.",2));
        unusedCultists.add(new Cultist("+1 por cada sectario en juego. No puedes dejar de ser sectario.",1));
        unusedCultists.add(new Cultist("+2 por cada sectario en juego. No puedes dejar de ser sectario.",2));
        unusedCultists.add(new Cultist("+1 por cada sectario en juego. No puedes dejar de ser sectario.",1));
        unusedCultists.add(new Cultist("+1 por cada sectario en juego. No puedes dejar de ser sectario.",1));
        
        Collections.shuffle(unusedCultists);
        
    }
    
    private void shuffleTreasures(){
       //Con la clase collections que trabajan con los arrays y que hay un metodo que baraja un array (shuffle())
       //En ruby la propia clase arraylist tiene este metodo
       Collections.shuffle(unusedTreasures);
        
    }
    
    
    private void shuffleMonsters(){
        
       Collections.shuffle(unusedMonsters);
        
    }
    
    private void shuffleCultist(){
        
        Collections.shuffle(unusedCultists);
        
    }
    
    public Cultist nextCultist(){
        
        
        return unusedCultists.remove(0);
        
        
    }
    
    public Treasure nextTreasure(){
        
        Treasure siguiente ;
        
        if( unusedTreasures.isEmpty()){
            
            unusedTreasures.addAll(usedTreasures);
            shuffleTreasures();
            usedTreasures.clear();
   
        }
        
        siguiente = unusedTreasures.get( 0 );
        unusedTreasures.remove( 0 );
        
        return siguiente;
        
    }
    
    public Monster nextMonster(){
        
        
        
        if( unusedMonsters.isEmpty()){
            
            unusedMonsters.addAll( usedMonsters);
            shuffleMonsters();
            usedMonsters.clear();
   
        }
        
        
        
        
        return unusedMonsters.remove( 0 );
        

   
    }
    
    public void giveTreasureBack( Treasure t ){
        
       usedTreasures.add(t);
        
    }
    
    public void giveMonsterBack( Monster m ){
        
       usedMonsters.add(m);
        
    }
    
    public void initCards(){
        
        initMonsterCardDeck();
        initTreasureCardDeck();
        initCultistCardDeck();
    }
    
    
    
   
}