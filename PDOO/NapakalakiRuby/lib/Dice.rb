# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require 'singleton'

class Dice
  
  include Singleton 
  
  def nextNumber
    
    valor = 1 + rand(6)
    valor
    
  end

end