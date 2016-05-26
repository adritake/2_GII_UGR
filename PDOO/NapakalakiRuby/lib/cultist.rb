# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame
  class Cultist
    attr_reader :name, :gainedLevels
    def initialize(n,gl)
      @name = n
      @gainedLevels = gl
    end

    def getGainedLevels
      @gainedLevels
    end
  end
end