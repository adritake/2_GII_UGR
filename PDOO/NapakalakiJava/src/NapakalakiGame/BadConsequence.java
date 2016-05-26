package NapakalakiGame;

import java.util.ArrayList;
/**
 *
 * @author pablo
 */
public abstract class BadConsequence {
    private String text;
    private int levels;
    private boolean death;
    static final int MAXTREASURES = 10;
    
    public BadConsequence(){
        this.text = "";
        this.levels = 0;
    }
    
    public BadConsequence(String text, int levels){
        this.text = text;
        this.levels = levels;
    }
    
    public String getText(){
        return this.text; 
    }
    
    public int getLevels(){
        return this.levels; 
    }
    
    public String toString(){
        return text + "\nPierdes" + Integer.toString(levels) + " niveles"; 
    }
    
    public abstract boolean isEmpty();
    
    abstract void substractVisibleTreasure( Treasure t );
   
    abstract void substractHiddenTreasure( Treasure t );
    
    abstract BadConsequence adjustToFitTreasureList( ArrayList<Treasure> v, ArrayList<Treasure> h);
}