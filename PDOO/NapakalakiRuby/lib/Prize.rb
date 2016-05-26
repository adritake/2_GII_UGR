# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame
  class Prize
    attr_reader :treasures, :levels    #los consultores se generan de forma automatica. Los modificadores no. 

    def initialize (t,l)
     @treasures = t
     @levels    = l
    end

    public
    def to_s

      "\nTesoros: #{@treasures} \nNiveles: #{@levels}"

    end
  end
  
end