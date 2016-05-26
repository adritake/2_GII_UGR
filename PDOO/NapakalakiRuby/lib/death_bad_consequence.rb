# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative "numeric_bad_consequence"
module NapakalakiGame
class DeathBadConsequence < NumericBadConsequence
  
  public_class_method :new
  def initialize( t )
    
    super( t, 0, BadConsequence.MAXTREASURES, BadConsequence.MAXTREASURES)
    
  end
  
  def to_s
    
    @text
    
  end
  
end
end