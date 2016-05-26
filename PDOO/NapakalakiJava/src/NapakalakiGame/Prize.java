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
public class Prize {
    private int level;
    private int treasures;
    
    public Prize() {
        level = 0;
        treasures = 0;
    }
    public Prize(int level, int treasures) {
        this.level = level;
        this.treasures = treasures;
    }  
    
    public int getLevel(){
        return level;
    }
    
    public int getTreasures(){
        return treasures;
    }
    
    public String toString(){
        return "Treasures = " + Integer.toString(treasures) + " Levels = " + Integer.toString(level);
    }
}
