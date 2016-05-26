# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative 'Dice'

module NapakalakiGame
  
  class Player

    attr_reader :name, :level, :dead, :canISteal, :hiddenTreasures, :visibleTreasures, :pendingBadConsequence
    attr_accessor :enemy
    @@MAXLEVEL = 10
    #protected :enemy
    
    def initialize( n )

      @name = n
      @level = 1
      @canISteal = true
      @dead = true
      @hiddenTreasures = Array.new
      @visibleTreasures = Array.new
      @pendingBadConsequence = NumericBadConsequence.new("Default", 0, 0, 0)

    end

    def copia(p)
      @name = p.name
      @level = p.level
      @canISteal = p.canISteal
      @dead = p.death
      @hiddenTreasures = p.hiddenTreasures
      @visibleTreasures = p.visibleTreasures
      @pendingBadConsequence = p.pendingBadConsequence
      @enemy = p.enemy
    end

    private
    def bringToLife

      @dead = false

    end

    public
    def getCombatLevel

      cl = 0

      for t in visibleTreasures
        cl += t.bonus
      end

      cl += @level    
      cl

    end

    private 
    def incrementLevels (l)

      @level = @level + l
      if @level > @@MAXLEVEL
        @level = 10
      end

    end

    private
    def decrementLevels( i )

      @level = @level - i
      if @level < 0
        @level = 1
      end

    end

    private
    def setPendingBadConsequence( b )

      @pendingBadConsequence = b

    end

    private
    def applyPrize( m )

      incrementLevels( m.getLevelsGained )

      if m.getTreasuresGained > 0

        for i in 0..m.getTreasuresGained

          @hiddenTreasures << CardDealer.instance.nextTreasure

        end

      end

    end

    private
    def applyBadConsequence( m )

      decrementLevels( m.badConsequence.levels)

      if m.badConsequence.is_a?(DeathBadConsequence)
        @dead = true
      end

      setPendingBadConsequence( m.badConsequence.adjustToFitTreasureList( @visibleTreasures , @hiddenTreasures))


    end


    #metodo auxiliar para ver si un array contiene un elemento
    private
    def contiene (array, objeto)

      contiene = false

      for a in array

        if objeto == a
          contiene = true
        end

      end

      contiene

    end

    private
    def canMakeTreasureVisible( t )

      hands = 0
      doit = true
      tipo = t.type

      for tr in @visibleTreasures

        if tr.type == TreasureKind::ONEHAND
          hands = hands + 1
        end

        if tr.type == TreasureKind::BOTHHANDS
          hands = 2
        end
      end

      if (tipo == TreasureKind::ONEHAND and hands == 2) or (tipo == TreasureKind::BOTHHANDS and hands > 0)
        doit = false
      else

        if tipo != TreasureKind::ONEHAND and tipo != TreasureKind::BOTHHANDS 

          for tr in @visibleTreasures
            if tr.type == tipo
              doit = false
            end
          end
        end

      end

      doit
    end

    private
    def howManyVisibleTreasures( tKind )

      count = 0

      for t in @visibleTreasures
        if t.type == tKind
          count = count + 1
        end
      end


      count

    end

    private
    def dieIfNoTreasures()


      if(@visibleTreasures.size == 0 and @hiddenTreasures.size == 0 )

        @dead = true
      end
    end

    public
    def isDead()

      @dead

    end

    def getHiddenTreasures()

      @hiddenTreasures

    end

    def getVisibleTreasures()

      @visibleTreasures

    end

    def combat( m )

      if self.getCombatLevel > self.getOponentLevel(m)

        if self.getCombatLevel >= @@MAXLEVEL
          combatResult = CombatResult::WINGAME

        else
          combatResult = CombatResult::WIN
        end

        applyPrize(m)


      else

        applyBadConsequence(m)

        if shouldConvert
          combatResult = CombatResult::LOSEANDCONVERT
        else
          combatResult = CombatResult::LOSE
        end
      end

      combatResult

    end
    
    def self.MAXLEVEL
    
      @@MAXLEVEL
    
    end
    
    #metodo auxiliar para ver si un array contiene un elemento
    private
    def contiene (array, objeto)

      contiene = false

      for a in array

        if objeto == a
          contiene = true
        end

      end

      contiene

    end

    #metodo auxiliar para ver si un array contiene un elemento y devuelve su posicion
    private
    def contiene_index (array, objeto)

      i = 0    
      indice = -1 #Si no lo encuentra devuelve este menos uno

      for a in array

        if objeto == a
          indice = i
        end

        i = i+1

      end

      indice

    end

    public
    def makeTreasureVisible( t )

        cont = contiene(@hiddenTreasures,t)

        if cont  and canMakeTreasureVisible(t)
          @visibleTreasures<<t
          @hiddenTreasures.delete(t) 
        end

    end

    def discardVisibleTreasure( t )

      i=0

      for itv in @visibleTreasures

        if itv == t

          @visibleTreasures.delete_at(i)
          @pendingBadConsequence.substractVisibleTreasure(t)
        end

        i = i+1

      end


      dieIfNoTreasures

        if(@visibleTreasures.size == 0 and @hiddenTreasures.size == 0 )
          @dead = true
        end

      end

    public
    def discardHiddenTreasure( t )


      @hiddenTreasures.delete(t)

      @pendingBadConsequence.substractHiddenTreasure(t)


      dieIfNoTreasures

    end

    public
    def validState

      state = false
      if @pendingBadConsequence.isEmpty and @hiddenTreasures.size <= 4
        state = true
      end

      state 

    end

    public
    def initTreasures

      bringToLife

      @hiddenTreasures<<CardDealer.instance.nextTreasure
      number = Dice.instance.nextNumber

      if number > 1
        @hiddenTreasures<<CardDealer.instance.nextTreasure 
      end

      if number == 6
        @hiddenTreasures<<CardDealer.instance.nextTreasure 

      end
    end

    def getLevels()

      @level

    end

    def stealTreasure()

      if self.canISteal

        if @enemy.canYouGiveMeATreasure

          treasure = @enemy.giveMeATreasure
          @hiddenTreasures<<treasure
          haveStolen

        end

        treasure
      else
        nil

      end

    end

    public
    def setEnemy( enemy )

      @enemy = enemy

    end

    protected
    def giveMeATreasure

      tesoro = rand(@hiddenTreasures.size)

      @hiddenTreasures.at(tesoro)

    end

    public
    def canISteal()

      @canISteal

    end

    public
    def canYouGiveMeATreasure()

      can = false
      if @hiddenTreasures.size > 0
        can = true
      end

      can

    end

    private
    def haveStolen()

      @canISteal = false

    end

    public
    def discardAllTreasures

      copiav = Array.new(@visibleTreasures)
      copiah = Array.new(@hiddenTreasures)

      for itv in copiav
        self.discardVisibleTreasure(itv)
      end

      for ith in copiah
        self.discardHiddenTreasure(ith)
      end

    end

    public
    def to_s

      @name

    end
    
    protected
    def getOponentLevel(m)
      m.getCombatLevel()
    end

    def shouldConvert
      if Dice.instance.nextNumber == 1
        true
      else
        false
      end
    end

  end
end