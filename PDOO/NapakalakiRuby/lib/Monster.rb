# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame
  class Monster
    attr_reader :name, :combatLevel, :badConsequence, :buenrollo

    private_class_method :new

    def initialize(n,cl,ml,br,lcacp)
      @name        = n
      @combatLevel = cl
      @badConsequence = ml
      @buenrollo   = br
      @levelChangeAgainstCultistPlayer = lcacp
    end

    def self.newMonsterLevelChangeAgainstCultistPlayer(n,i,bc,p,ic)
      new(n,i,bc,p,ic)
    end

    def self.newMonster(n,i,bc,p)
      new(n,i,bc,p,0)
    end

    def to_s

         "\nSoy #{@name} \nNivel: #{@combatLevel} \nMi mal rollo es: " + @badConsequence.to_s + "\nMi buen rollo es: " + @buenrollo.to_s

    end

    public
    def getCombatLevel
      @combatLevel
    end

    def getLevelsGained

      @buenrollo.levels

    end

    def getTreasuresGained

      @buenrollo.treasures

    end

    def getCombatLevelAgainstCultistPlayer
      @combatLevel + @levelChangeAgainstCultisPlayer
    end
  end
end