/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

/**
 *
 * @author adritake
 */
public class Monster {
    private String name; 
    private int combatLevel;
    private Prize buenrollo;
    private BadConsequence malrollo;
    private int levelChangeAgainstCultistPlayer;
            
    public Monster(String name, int level, BadConsequence bc, Prize price){
        this.name = name;
        this.combatLevel = level;
        this.malrollo = bc;
        this.buenrollo = price;
        this.levelChangeAgainstCultistPlayer = 0;
    }
    
    public Monster(String name, int level, BadConsequence bc, Prize price ,int ic){
        this.name = name;
        this.combatLevel = level;
        this.malrollo = bc;
        this.buenrollo = price;
        this.levelChangeAgainstCultistPlayer = ic;
    }
    
    public Monster(){
        
        
    }
    
    public int getCombatLevelAgainstCultistPlayer(){
        
        return combatLevel + levelChangeAgainstCultistPlayer;
        
    }
    public String getName(){
        return name; 
    }
    
    public int getCombatLevel(){
        return combatLevel;
    }
    
    public BadConsequence getBadConsequence(){
        return malrollo;
    }
    
    public Prize getBuenRollo(){
        return buenrollo;
    }
    
    public int getLevelsGained(){
        
        return buenrollo.getLevel();
        
    }
    
    public int getTreasuresGained(){
        
        return buenrollo.getTreasures();
        
    }
    
    public String toString(){
        return "Nombre: " + name + "\nLevel: " + Integer.toString(combatLevel)
                + "\nBuen rollo: " + buenrollo.toString() + "\nMal rollo: " 
                + malrollo.toString();
                        
    }
    
    
    
  
}
