package NapakalakiGame;

import java.util.ArrayList;

/**
 *
 * @author pablo
 */
public class SpecificBadConsequence extends BadConsequence{
    private ArrayList<TreasureKind> specificHiddenTreasures;
    private ArrayList<TreasureKind> specificVisibleTreasures;
    
    public SpecificBadConsequence(){
        super(" ", 0);
    }
    
    public SpecificBadConsequence(String text, int levels, ArrayList<TreasureKind> tVisible,
                          ArrayList<TreasureKind> tHidden){
        
        super(text, levels);
        this.specificVisibleTreasures = new ArrayList(tVisible);
        this.specificHiddenTreasures = new ArrayList(tHidden);
    }
    
    private ArrayList<TreasureKind> InterseccionTK(ArrayList<Treasure> a, ArrayList<TreasureKind>b){
        
        ArrayList<TreasureKind> interseccion = new ArrayList<TreasureKind>();
      
        boolean encontrado;
        for(int i = 0; i < a.size(); i++){
            encontrado = false;
            for(int j = 0; j < b.size() && !encontrado; j++)
                if(a.get(i).getType() == b.get(j) ){
                    encontrado = true; 
                    interseccion.add(b.get(j));
                    b.remove(j);
                }
        }
//        for(Treasure at: a)
//            for(TreasureKind bt: b)
//                if( at.getType() == bt && !interseccion.contains( at ))
//                    interseccion.add( bt );
                     
        return interseccion;
        
    }
    
    @Override
    public boolean isEmpty(){
        return specificVisibleTreasures.isEmpty() && specificHiddenTreasures.isEmpty();
    }
    
    @Override
    public void substractVisibleTreasure( Treasure t ){
        specificVisibleTreasures.remove(t.getType());
    }
    
    @Override
    public void substractHiddenTreasure( Treasure t ){
        specificHiddenTreasures.remove(t.getType());
    }
    
    @Override
    public BadConsequence adjustToFitTreasureList(ArrayList<Treasure> v, ArrayList<Treasure> h){
        SpecificBadConsequence fit = new SpecificBadConsequence("", 0, InterseccionTK( v, this.specificVisibleTreasures), 
                                                                       InterseccionTK( h, this.specificHiddenTreasures));        
        
        return fit;
    }
    
    @Override
    public String toString(){
        return super.toString();
    }
    
    public ArrayList<TreasureKind> getTvisible(){
        return this.specificVisibleTreasures;
    }
    
    public ArrayList<TreasureKind> getThidden(){
        return this.specificHiddenTreasures;
    }
}