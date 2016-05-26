# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module NapakalakiGame
  
  class CultistPlayer < Player

    def initialize (p,c)
      super(p)
      super.copia(p)
      @myCultistCard = Cultist.new
      @@totalCultistPlayers =  @@totalCultistPlayers + 1
    end

    def self.getTotalCultistPlayers
      @@totalCultistPlayers
    end

    protected
    def getCombatLevel
      cl = super + (super)*(20/100) + (@myCultistCard.getGainedLevels)*self.getTotalCultistPlayers
      
      #Truncamos el resultado
      if cl < 10
        cl = cl%10
      else
        cl = cl%100
      end
      
      cl 
    end

    public
    def canYouGiveMeATreasure
      !@player.enemy.getVisibleTreasures().empty?
    end

    protected
    def giveMeATreasure
      tesoro = rand(@player.enemy.getVisibleTreasures().size)

      @player.enemy.getVisibleTreasures().at(tesoro)
    end

    protected
    def getOponentLevel(m)
      m.getCombatLevelAgainstCultistPlayer()
    end

    def shouldConvert
      false
    end
    
  end
end