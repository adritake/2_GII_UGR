package NapakalakiGame;

import java.util.ArrayList;
import NapakalakiGame.NumericBadConsequence;
import GUI.Dice;
/**
 *
 * @author adritake
 */
public class Player {
    
    private String name;
    private int level;
    private boolean dead;
    private boolean canISteal;
    static final int MAXLEVEL = 10;
    private ArrayList<Treasure> visibleTreasures = new ArrayList();
    private ArrayList<Treasure> hiddenTreasures = new ArrayList();
    protected Player enemy;
    private BadConsequence pendingBadConsequence = new NumericBadConsequence("",0,0,0);
    
    
    public Player( String n ){
        name = n;
        level = 1;
        dead = true;
        canISteal = true;
    }
    
    public Player( Player p){
        name = p.getName();
        level = p.getLevels();
        dead = p.isDead();
        visibleTreasures = new ArrayList(p.getVisibleTreasures());
        hiddenTreasures = new ArrayList(p.getHiddenTreasures());
        enemy = p.getEnemy();
        pendingBadConsequence = p.getPendingBadConsequence();
    }
    
    public Player( ){
        name = "Default";
        level = 0;
        dead = true;
        canISteal = true;
    }
    
    
    public String getName(){
        return name;
    }
    
    public ArrayList<Treasure> getHiddenTreasures(){
        return hiddenTreasures;
    }
    public ArrayList<Treasure> getVisibleTreasures(){
        return visibleTreasures;
    }
    
    private void bringToLife(){
        dead = false;
    }
    
     public int getCombatLevel(){
      
      int nivel=0;
      
      for(Treasure t: visibleTreasures){
          nivel += t.getBonus();
          
      }
      nivel += level; 
      
      return nivel; 
    }   
   
    
    public BadConsequence getPendingBadConsequence(){
        return pendingBadConsequence;
    }
    
    private void incrementLevels( int I ){
        
        if(  (level + I ) <= 10  )
            level += I;
        else
            level = MAXLEVEL;
        
    }
    
    
    private void decrementLevels( int I ){
        
       if( (level - I) >= 0 )
            level -= I;
       else
           level = 1;
       
    }
    
    private void setPendingBadConsequence( BadConsequence b ){
        pendingBadConsequence = b;
    }
    
    private void applyPrize( Monster m ){
        
        incrementLevels( m.getLevelsGained() );
        
        if( m.getTreasuresGained() > 0)
            
            for(int i = 0; i < m.getTreasuresGained(); i++)
                
               hiddenTreasures.add( CardDealer.getInstance().nextTreasure() );
        
    }
    
    private void applyBadConsequence( Monster m ){
        
        decrementLevels( m.getBadConsequence().getLevels() );
        
        dead = m.getBadConsequence() instanceof DeathBadConsequence; 
        
        if ( dead )
            discardAllTreasures();
        else
            setPendingBadConsequence( m.getBadConsequence().adjustToFitTreasureList( visibleTreasures, hiddenTreasures )); 
        
    } 
    
    public boolean canMakeTreasureVisible( Treasure t){
       
        int hands = 0;
        boolean doit = true;
        TreasureKind tipo = t.getType();

        // Como los casos especiales son las manos, hago las comprobaciones a parte.
        // Si ya tengo dos manos, no puedo equipar ni una más ONEHAND ni BOTHHANDS.
        for (Treasure tr : visibleTreasures) {
            if (tr.getType() == TreasureKind.ONEHAND) {
                ++hands;
            }
            if (tr.getType() == TreasureKind.BOTHHANDS) {
                hands = 2;
            }
        }

        if ((tipo == TreasureKind.ONEHAND && hands == 2) || (tipo == TreasureKind.BOTHHANDS && hands > 0)) {
            doit = false;
        }

        // ----------------------------------------------------------------------
        // Comprobación del resto de tesoros
        else if (tipo != TreasureKind.ONEHAND && tipo != TreasureKind.BOTHHANDS) {    // Las comprobaciones de las manos ya se han hecho.
            for (Treasure tr : visibleTreasures) {
                if (tr.getType() == tipo) {
                    doit = false;
                }
            }
        }

        return doit;    //Si no se ha modificado, devuelve true.
       
    }
    
    protected Treasure giveMeATreasure(){
        
        int tesoro = (int)(Math.random() * hiddenTreasures.size());
        //ELIMINAR TESORO
        return hiddenTreasures.get(tesoro);
        
    }
    
    
    private int howManyVisibleTreasures( TreasureKind tKind ){
       
       int cantidad=0;
        
       for( Treasure t: visibleTreasures )
           if(t.getType() == tKind)
               cantidad++;
       
       return cantidad;
    }
    
    private void dieIfNoTreasures(){
       
        if(hiddenTreasures.size() == 0 && visibleTreasures.size() == 0)
            dead = true;
        
    }
    
    public boolean isDead(){
      return dead;
    }
    
    protected boolean shouldConvert(){
        
        if ( Dice.getInstance().nextNumber() == 1)
            return true;
        else
            return false;
    }
   
    
    public CombatResult combat( Monster m ){
        
        CombatResult combatResult;
        
        if( getCombatLevel() > this.getOponentLevel( m ) ){
            
            if(getLevels() >= MAXLEVEL)
                combatResult = CombatResult.WINGAME;
            else
                combatResult = CombatResult.WIN;
            
            applyPrize(m);
        }
        
        else{
            
            applyBadConsequence(m);
            if( shouldConvert() )
                combatResult = CombatResult.LOSEANDCONVERT;
            else
                combatResult = CombatResult.LOSE;
            
        }
        
        return combatResult;
       
    }
    
    public void makeTreasureVisible( Treasure t ){
        
        if ( hiddenTreasures.contains(t) && canMakeTreasureVisible(t)){
            
            visibleTreasures.add(t);
            hiddenTreasures.remove(t);
            
        }
        
    }
  
    public void discardVisibleTreasure( Treasure t ){
        
        visibleTreasures.remove( t );
        pendingBadConsequence.substractVisibleTreasure( t );
        this.dieIfNoTreasures();
        
        
    }
    
    public void discardHiddenTreasure( Treasure t ){
        
        hiddenTreasures.remove( t );
        pendingBadConsequence.substractHiddenTreasure( t );
        this.dieIfNoTreasures();
        
    }
    
    public boolean validState(){
        
        boolean valido = false;
        
        if( pendingBadConsequence.isEmpty() && hiddenTreasures.size() <= 4  )
            valido = true;
        
        
        return valido;
        
    }
    
    public void initTreasures(){
        
        bringToLife();
        
        hiddenTreasures.add( CardDealer.getInstance().nextTreasure() );
        
        int number = Dice.getInstance().nextNumber() ;
        
        if( number > 1)  
            hiddenTreasures.add( CardDealer.getInstance().nextTreasure() );
     
        if( number == 6 )
            hiddenTreasures.add( CardDealer.getInstance().nextTreasure() );
        
    }
    
    public int getLevels(){
        
       return level;
        
    }
  
    public void setEnemy( Player ene ){
        
        enemy = ene;
        
    }
    
    public Player getEnemy(){
        
        return enemy;
        
    }
    
    protected int getOponentLevel( Monster m){
        
        return m.getCombatLevel();
          
    }
    
    public Treasure stealTreasure(){
        
        Treasure treasure = null;
        
        if( this.canISteal() ){
            
            if( enemy.canYouGiveMeATreasure() ){
                
                treasure = enemy.giveMeATreasure();
                hiddenTreasures.add(treasure);
                this.haveStolen();
                
                
            }
     
        }
        return treasure;    
        
    }
  
    public boolean canISteal(){
        
        return canISteal;
        
    }
    
    protected boolean canYouGiveMeATreasure(){
        
      return !hiddenTreasures.isEmpty();
           
    }
    
    private void haveStolen(){
        
        canISteal = false;
        
    }
    
    public void discardAllTreasures(){
        
        ArrayList<Treasure> copiav = new ArrayList(visibleTreasures);
        ArrayList<Treasure> copiah = new ArrayList(hiddenTreasures);
        
        for(Treasure t: copiav)
            this.discardVisibleTreasure(t);
        
        for(Treasure t: copiah)
            this.discardHiddenTreasure(t);
        
    }
    
    
    public String toString(){
        
        return name;
        
    }
   
    
}