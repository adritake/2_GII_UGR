/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

/**
 *
 * @author pablo
 */
public class Treasure {
    private String name;
    private int bonus;
    private TreasureKind type;
    
    public Treasure( String n, int bon, TreasureKind t){
        name = n;
        bonus = bon;
        type = t;
    }
    public Treasure(){
        
    }
    
    public String getName(){
        
        return name;
        
    }
    
    public int getBonus(){
        
        return bonus;
        
    }
    
    public TreasureKind getType(){
       return type;
    }
    
    public String toString(){
        return "Nombre: " + name + "\nBonus: " + bonus + "\nTipo: " + type;
    }
}
