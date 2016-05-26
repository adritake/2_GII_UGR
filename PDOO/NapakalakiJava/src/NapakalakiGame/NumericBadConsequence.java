package NapakalakiGame;

import java.util.ArrayList;

/**
 *
 * @author pablo
 */
public class NumericBadConsequence extends BadConsequence{
    private int nVisibleTreasures;
    private int nHiddenTreasures;
    
    public NumericBadConsequence(){
        super(" ", 0);
    }
    
    public NumericBadConsequence(String text, int levels, int nVisible, int nHidden){
        super(text, levels);
        this.nVisibleTreasures = nVisible; 
        this.nHiddenTreasures = nHidden;
    }
    
    @Override
    public boolean isEmpty(){
        return nVisibleTreasures == 0 && nHiddenTreasures == 0;
    }
    
    @Override
    public void substractVisibleTreasure( Treasure t ){
        if(--nVisibleTreasures < 0)
            nVisibleTreasures = 0;
    }
    
    @Override
    public void substractHiddenTreasure( Treasure t ){
        if(--nHiddenTreasures < 0)
            nHiddenTreasures = 0;
    }
    
    @Override
    public BadConsequence adjustToFitTreasureList(ArrayList<Treasure> v, ArrayList<Treasure> h){
        NumericBadConsequence fit = new NumericBadConsequence();
        
        if( this.nVisibleTreasures > v.size() )
            fit.nVisibleTreasures = v.size();

        if( this.nHiddenTreasures > h.size() )
            fit.nHiddenTreasures = h.size();
        
        return fit;
    }
    
    @Override
    public String toString(){
        return "Soy un numeric BadConsequence";
    }
    
    public int getnVisible(){
        return this.nVisibleTreasures; 
    }
    
    public int getnHidden(){
        return this.nHiddenTreasures; 
    }
}