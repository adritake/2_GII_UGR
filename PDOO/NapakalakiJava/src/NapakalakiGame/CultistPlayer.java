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
public class CultistPlayer extends Player {
    
    private static int totalCultistPlayers = 0;
    private Cultist myCultistCard;
    
    public static int getTotalCultistPlayers(){
        
        return totalCultistPlayers;
        
    }
    
    public CultistPlayer( Player p, Cultist c){
        
        super(p);
        myCultistCard = c;
        totalCultistPlayers++;
        
    }
    
    @Override
    protected int getOponentLevel( Monster m){
        
        return m.getCombatLevelAgainstCultistPlayer();
          
    }
    
    @Override
    public int getCombatLevel(){
        
        return super.getCombatLevel() + super.getCombatLevel()*(20/100) + myCultistCard.getGainedLevels() * totalCultistPlayers ;
    
    }
    
    @Override
    protected Treasure giveMeATreasure(){
        
         int tesoro = (int)(Math.random() * super.getVisibleTreasures().size());
        
         return super.getVisibleTreasures().get(tesoro);
        
    }
    
    @Override
    protected boolean canYouGiveMeATreasure(){
        
        return !super.getVisibleTreasures().isEmpty();
        
    }
    
    @Override
    protected boolean shouldConvert(){
        
       return false;
        
    }
    
    
}
