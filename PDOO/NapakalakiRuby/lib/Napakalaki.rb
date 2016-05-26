# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require 'singleton'
require_relative "Player"
require_relative "Monster"
require_relative "CombatResult"
require_relative "Dice"
require_relative "CardDealer"
require_relative "Prize"
require_relative "Treasure"
require_relative "BadConsequence"
require_relative "TreasureKind"

module NapakalakiGame
  class Napakalaki
    include Singleton

    attr_reader :currentPlayer, :currentMonster, :players, :primera_jugada, :result


    def initialize

      @primera_jugada = true
      @players = Array.new
      @currentPlayer = Player.new("prueba")

    end

    public
    def initPlayers (p) 

      for pla in p

        insert = Player.new(pla)
        @players<<insert

      end

      for p in @players
        p.initTreasures
      end
    end

    private
    def nextPlayer

      indice = 0
      i = 0

      if  @primera_jugada 

        @primera_jugada = false
        indice = rand(@players.size)


      else

        #Esto para ver que indice ocupa el judor actual
        for p in @players

          if p == @currentPlayer

            indice = i

          end
          i = i+1
        end

        if indice == (@players.size-1)
          indice = 0
        else
          indice = indice + 1

        end

      end


      @currentPlayer = @players.at(indice)

      @currentPlayer

    end

    public
    def nextTurnAllowed

      @currentPlayer.validState 

    end

    public
    def setEnemies

      indice_enemigo = 0
      indice_jugador = 0

      for p in @players



        #indice del enemigo
        indice_enemigo = rand(@players.size)

        while indice_enemigo == indice_jugador

          indice_enemigo = rand(@players.size)

        end

        p.setEnemy(@players.at(indice_enemigo))
        indice_jugador = indice_jugador + 1

      end

    end


    def developCombat 

      combatResult = @currentPlayer.combat( @currentMonster )
      CardDealer.instance.giveMonsterBack( @currentMonster )

      if combatResult == CombatResult::LOSEANDCONVERT
        cultistcard = CardDealer.instance.nextCultist
        cultistplayer = CultistPlayer.new(@currentPlayer, cultistcard)
        indice = @players.index(@currentPlayer)
        @players.delete_at(indice)
        @players.insert(indice-1, cultistplayer)
        @currentPlayer = cultistplayer
      end

      combatResult

    end

    def discardVisibleTreasures (t)

      for tre in t

        @currentPlayer.discardVisibleTreasure(tre)
        CardDealer.instance.giveTreasureBack(tre)

      end

    end

    def discardHiddenTreasures (t)

      for tre in t
        @currentPlayer.discardHiddenTreasure(tre)
        CardDealer.instance.giveTreasureBack(tre)
      end

    end

    def makeTreasuresVisible (t)

      for tre in t

        if @currentPlayer.canMakeTreasureVisible( tre ) 
            @currentPlayer.makeTreasureVisible( tre )
        end
      end

    end

    public
    def initGame ( p )

      CardDealer.instance.initCards
      self.initPlayers( p )
      self.setEnemies
      self.nextTurn


    end

    def nextTurn

      nextturn = self.nextTurnAllowed

      if nextturn 

        @currentMonster = CardDealer.instance.nextMonster
        @currentPlayer = nextPlayer

        if @currentPlayer.isDead
          @currentPlayer.initTreasures
        end

      end

      nextturn

    end

    def endOfGame (result)

      if result == CombatResult::WINGAME
        fin = true
      else
        fin = false
      end

      fin
    end

    def getCurrentPlayer

      @currentPlayer

    end

    def getCurrentMonster

      @currentMonster

    end

  end
end