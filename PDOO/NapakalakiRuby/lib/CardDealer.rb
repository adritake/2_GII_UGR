# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require 'singleton'
require_relative 'cultist'

module NapakalakiGame

class CardDealer
  include Singleton
  
  def initialize
    @unusedTreasures = Array.new
    @usedTreasures = Array.new
    @unusedMonsters = Array.new
    @usedMonsters = Array.new
    @unusedCultists = Array.new
  end
  
  
  ###########################################    PRIVADO     ##############################################

  private
  def initTreasureCardDeck
    
    
    #Por lo visto ruby no acepta en los strings acentos, la ñ ni el primer signo de admiración
    #¡Sí mi amo! 
    tesoro = Treasure.new("Si mi amo!",4,[TreasureKind::HELMET])
    @unusedTreasures<<tesoro
    
    
    #Botas de investigación 
    tesoro = Treasure.new("Botas de investigacion",3,[TreasureKind::SHOES])
    @unusedTreasures<<tesoro
    
    #Capucha de Cthulhu
    tesoro = Treasure.new("Capucha de Cthulhu",3,[TreasureKind::HELMET])
    @unusedTreasures<<tesoro
    
    #A prueba de babas
    tesoro = Treasure.new("A prueba de babas",2,[TreasureKind::ARMOR])
    @unusedTreasures<<tesoro
    
    #Botas de lluvia ácida
    tesoro = Treasure.new("Botas de lluvia acida",1,[TreasureKind::BOTHHANDS])
    @unusedTreasures<<tesoro
    
    #Casco minero
    tesoro = Treasure.new("Casco minero",2,[TreasureKind::HELMET])
    @unusedTreasures<<tesoro
    
    #Ametralladora Thompson
    tesoro = Treasure.new("Ametralladora Thompson",4,[TreasureKind::BOTHHANDS])
    @unusedTreasures<<tesoro
    
    #Camiseta de la UGR
    tesoro = Treasure.new("Camiseta de la UGR",1,[TreasureKind::ARMOR])
    @unusedTreasures<<tesoro
    
    #Clavo de rail ferroviario
    tesoro = Treasure.new("Clavo de rail ferroviario",3,[TreasureKind::ONEHAND])
    @unusedTreasures<<tesoro
    
    #Cuchillo de sushi arcano
    tesoro = Treasure.new("Cuchillo de sushi arcano",2,[TreasureKind::ONEHAND])
    @unusedTreasures<<tesoro
    
    #Fez alópodo
    tesoro = Treasure.new("Fez alopodo",3,[TreasureKind::HELMET])
    @unusedTreasures<<tesoro
    
    #Hacha prehistórica
    tesoro = Treasure.new("Hacha prehistorica",2,[TreasureKind::ONEHAND])
    @unusedTreasures<<tesoro
    
    #El aparato del Pr. Tesla
    tesoro = Treasure.new("El aparato del Pr. Tesla",4,[TreasureKind::ARMOR])
    @unusedTreasures<<tesoro
    
    #Gaita
    tesoro = Treasure.new("Gaita",4,[TreasureKind::BOTHHANDS])
    @unusedTreasures<<tesoro
    
    #Insecticida
    tesoro = Treasure.new("Insecticida",2,[TreasureKind::ONEHAND])
    @unusedTreasures<<tesoro
    
    #Escopeta de 3 cañones
    tesoro = Treasure.new("Escopeta de 3 caniones",4,[TreasureKind::BOTHHANDS])
    @unusedTreasures<<tesoro
    
    #Garabato místico
    tesoro = Treasure.new("Garabato mistico",2,[TreasureKind::ONEHAND])
    @unusedTreasures<<tesoro
    
    #La rebeca metálica
    tesoro = Treasure.new("La rebeca metalica",2,[TreasureKind::ARMOR])
    @unusedTreasures<<tesoro
    
    #Lanzallamas
    tesoro = Treasure.new("Lanzallamas",4,[TreasureKind::BOTHHANDS])
    @unusedTreasures<<tesoro
    
    #Necrocomicón
    tesoro = Treasure.new("Necrocomicon",1,[TreasureKind::ONEHAND])
    @unusedTreasures<<tesoro
    
    #Necronomicón
    tesoro = Treasure.new("Necronomicon",5,[TreasureKind::BOTHHANDS])
    @unusedTreasures<<tesoro
    
    #Linterna a 2 manos
    tesoro = Treasure.new("Linterna a 2 manos",4,[TreasureKind::BOTHHANDS])
    @unusedTreasures<<tesoro
    
    #Necrognomicón
    tesoro = Treasure.new("Necrognomicon",2,[TreasureKind::ONEHAND])
    @unusedTreasures<<tesoro
    
    #Necrotelecom
    tesoro = Treasure.new("Necrotelecom",2,[TreasureKind::HELMET])
    @unusedTreasures<<tesoro
    
    #Mazo de los antiguos
    tesoro = Treasure.new("Mazo de los antiguos",3,[TreasureKind::ONEHAND])
    @unusedTreasures<<tesoro
    
    #Necroplayboycón
    tesoro = Treasure.new("Necroplayboycon",3,[TreasureKind::ONEHAND])
    @unusedTreasures<<tesoro
    
    #Porra preternatural
    tesoro = Treasure.new("Porra preternatural",2,[TreasureKind::ONEHAND])
    @unusedTreasures<<tesoro
    
    #Shogulador
    tesoro = Treasure.new("Shogulador",1,[TreasureKind::BOTHHANDS])
    @unusedTreasures<<tesoro
    
    #Varita de atizamiento
    tesoro = Treasure.new("Varita de atizamiento",3,[TreasureKind::ONEHAND])
    @unusedTreasures<<tesoro
    
    #Tentáculo de pega
    tesoro = Treasure.new("Tentaculo de pega",2,[TreasureKind::HELMET])
    @unusedTreasures<<tesoro
    
    #Zapato deja-amigos
    tesoro = Treasure.new("Zapato deja-amigos",1,[TreasureKind::SHOES])
    @unusedTreasures<<tesoro
    
    shuffleTreasures

  end
  
  def initMonsterCardDeck
    
    #Byakhees de bonanza
    p = Prize.new(2, 1)
    bc = SpecificBadConsequence.new("Pierdes tu armadura visible y otra oculta.", 
                                     0, Array.new([TreasureKind::ARMOR]), Array.new([TreasureKind::ARMOR]))
    @unusedMonsters << Monster.newMonster("Byakhees de bonanza", 8, bc, p) 
    
    
    #Chibithulhu
    p = Prize.new(1,1)
    bc = SpecificBadConsequence.new("Embobados con el lindo primigenio te descartas de tu casco visible.", 
      0, Array.new([TreasureKind::HELMET]), Array.new)
    @unusedMonsters << Monster.newMonster("Chibithulhu", 2, bc, p)

    #El sopor de Dunwich
    p = Prize.new(1,1) 
    bc = SpecificBadConsequence.new("El primordial bostezo ontagioso. Pierdes el calzado visible.", 
      0, Array.new([TreasureKind::SHOES]), 0)
    @unusedMonsters << Monster.newMonster("El sopor de Dunwich", 2, bc, p)

    #Angeles de la noche ibicenca
    p = Prize.new(4,1) 
    bc = SpecificBadConsequence.new("Te atrapan para llevarte de fiesta y te dejan caer en mitad del vuelo. 
      Descarta 1 mano visible y 1 mano oculta.",0, Array.new([TreasureKind::ONEHAND]), Array.new([TreasureKind::ONEHAND]))
    @unusedMonsters << Monster.newMonster("Angeles de la noche ibicenca", 14, bc, p)

    #El gorron en el umbral
    p = Prize.new(3,1) 
    bc = NumericBadConsequence.new("Pierdes todos tus tesoros visibles",0 , BadConsequence.MAXTREASURES, 0)
    @unusedMonsters << Monster.newMonster("El gorron del umbral", 10, bc, p)

    #H.P. Munchcraft
    #### PONER ARRAY.NEW
    p = Prize.new(2,1) 
    bc = SpecificBadConsequence.new("Pierdes la armadura visible.", 0, Array.new([TreasureKind::ARMOR]), 0)
    @unusedMonsters << Monster.newMonster("H.P. Munchcraft", 6, bc, p)

    #Bichgooth
    p = Prize.new(1,1) 
    bc = SpecificBadConsequence.new("Sientes bichos bajo la ropa. Descarta la armadura visible", 
      0, Array.new([TreasureKind::ARMOR]), Array.new)
    @unusedMonsters << Monster.newMonster("Bichgooth", 2, bc, p)

    #El rey de rosa
    p = Prize.new(4,2) 
    bc = NumericBadConsequence.new("Pierdes 5 niveles y 3 tesoros visibles.",5 , 3, 0)
    @unusedMonsters << Monster.newMonster("El rey de rosa", 13, bc, p)

    #La que redacta en las tinieblas
    p = Prize.new(1,1) 
    bc = NumericBadConsequence.new("Toses los pulmones y pierdes 2 niveles.", 2, 0, 0)
    @unusedMonsters << Monster.newMonster("La que redacta en las tinieblas", 2, bc, p)

    #Los hondos
    p = Prize.new(2,1) 
    bc = DeathBadConsequence.new("Estos monstruos resultan bastante superficiales y te aburren mortalmente. Estas muerto.")
    @unusedMonsters << Monster.newMonster("Los hondos", 8, bc, p)

    #Semillas Cthulhu
    p = Prize.new(2,1) 
    bc = NumericBadConsequence.new("Pierdes 2 niveles y 2 tesoros ocultos.", 2, 0, 2)
    @unusedMonsters << Monster.newMonster("Semillas Cthulhu", 4, bc, p)

    #Dameargo
    p = Prize.new(2,1) 
    bc = SpecificBadConsequence.new("Te intentas escaquear. Pierdes una mano visible.", 
      0, Array.new([TreasureKind::ONEHAND]), Array.new)
    @unusedMonsters << Monster.newMonster("Dameargo", 1, bc, p)

    #Pollipólipo volante
    p = Prize.new(1,1) 
    bc = NumericBadConsequence.new("Da mucho asquito. Pierdes 3 niveles.", 3, 0, 0)
    @unusedMonsters << Monster.newMonster("Pollipolipo volante", 3, bc, p)

    #Yskhtihyssg-Goth
    p = Prize.new(3,1) 
    bc = DeathBadConsequence.new("No le hace gracia que pronuncien mal su nombre. Estas muerto.")
    @unusedMonsters << Monster.newMonster("Yskhtihyssg-Goth", 12, bc, p)

    #Familia feliz
    p = Prize.new(4,1) 
    bc = DeathBadConsequence.new("La familia te atrapa. Estas muerto")
    @unusedMonsters << Monster.newMonster("Familia feliz", 1, bc, p)

    #Roboggoth
    p = Prize.new(2,1) 
    bc = SpecificBadConsequence.new("La quinta directiva primaria te obliga a perder 2 niveles y un tesoro 2 manos visible.", 
      2, Array.new([TreasureKind::BOTHHANDS]), Array.new)
    @unusedMonsters << Monster.newMonster("Roboggoth", 8, bc, p)

    #El espia
    p = Prize.new(1,1) 
    bc = SpecificBadConsequence.new("Te asusta en la noche. Pierdes un casco visible.", 
      0, Array.new([TreasureKind::HELMET]), Array.new)
    @unusedMonsters << Monster.newMonster("El espia", 5, bc, p) 

    #El lenguas
    p = Prize.new(1,1) 
    bc = NumericBadConsequence.new("Menudo susto te llevas. Pierdes 2 niveles y 5 tesoros visibles.", 2, 5, 0)
    @unusedMonsters << Monster.newMonster("El lenguas", 20, bc, p) 
    
    #Bicéfalo
    tesoros = Array.new
    tesoros << [TreasureKind::BOTHHANDS]
    tesoros << [TreasureKind::ONEHAND]
    p = Prize.new(1,1) 
    bc = SpecificBadConsequence.new("Te faltan manos para tanta cabeza. Pierdes 3 niveles y tus tesoros visibles de las manos.", 
      3, tesoros, 0)
    @unusedMonsters << Monster.newMonster("Bicefalo", 20, bc, p)
    
    #El mal impredecible impronunciable
    p = Prize.new(3, 1)
    bc = SpecificBadConsequence.new("Pierdes una mano visible", 0, [TreasureKind::ONEHAND], Array.new)
    @unusedMonsters << Monster.newMonsterLevelChangeAgainstCultistPlayer("El mal impredecible impronunciable", 10, bc, p, -2)
    
    #Testigos Oculares
    p = Prize.new(2,1)
    bc = NumericBadConsequence.new("Pierdes tus tesoros visibles", 0, 5, 0)
    @unusedMonsters << Monster.newMonsterLevelChangeAgainstCultistPlayer("Testigos Oculares", 6, bc, p, 2)
    
    #El gran cthulhu
    p = Prize.new(2, 5)
    bc = DeathBadConsequence.new("Hoy no es tu dia de suerte. Mueres")
    @unusedMonsters << Monster.newMonsterLevelChangeAgainstCultistPlayer("El gran cthulhu", 20, bc, p, 4)
    
    #Serpiente Politico
    p = Prize.new(2, 1)
    bc = NumericBadConsequence.new("Tu gobierno te recorta dos niveles", 2, 0, 0)
    @unusedMonsters << Monster.newMonsterLevelChangeAgainstCultistPlayer("Serpiente Politico", 8, bc, p, -2)
    
    #Felpuggoth
    vtesoros = Array.new
    htesoros = Array.new
    vtesoros << [TreasureKind::HELMET]
    vtesoros << [TreasureKind::ARMOR]
    htesoros << [TreasureKind::BOTHHANDS]
    htesoros << [TreasureKind::ONEHAND]
    htesoros << [TreasureKind::ONEHAND]
    p = Prize.new(1, 1)
    bc = SpecificBadConsequence.new("Pierdes tu casco y tu armadura visible. Pierdes tus manos ocultas.", 0, vtesoros, htesoros)
    @unusedMonsters << Monster.newMonsterLevelChangeAgainstCultistPlayer("Felpuggoth", 2, bc, p, 5)
    
    #Shoggoth
    p = Prize.new(4,2)
    bc = NumericBadConsequence.new("Pierdes dos niveles.", 2, 0, 0)
    @unusedMonsters << Monster.newMonsterLevelChangeAgainstCultistPlayer("Shoggoth", 16, bc, p, -4)
    
    #Lolitagooth
    p = Prize.new(1, 1)
    bc = NumericBadConsequence.new("Pintalabios negro. Pierdes dos niveles.", 2, 0, 0)
    @unusedMonsters << Monster.newMonsterLevelChangeAgainstCultistPlayer("Lolitagooth", 2, bc, p, 3)

    shuffleMonsters
    
  end
  
  def initCultistCardDeck
    @unusedCultists << Cultist.new("Sectario", 1)
    @unusedCultists << Cultist.new("Sectario", 2)
    @unusedCultists << Cultist.new("Sectario", 1)
    @unusedCultists << Cultist.new("Sectario", 2)
    @unusedCultists << Cultist.new("Sectario", 1)
    @unusedCultists << Cultist.new("Sectario", 1)
    
    shuffleCultist
  end
  
  def shuffleTreasures
    @unusedTreasures.shuffle!
  end
  
  def shuffleMonsters
    @unusedMonsters.shuffle!
  end
  
  def shuffleCultist
    @unusedCultists.shuffle!
  end
  
  ###########################################    PUBLICO     ##############################################

  public
  def nextTreasure
    
    if @unusedTreasures.empty?
      
      @unusedTreasures = @usedTreasures;
      self.shuffleTreasures;
      @usedTreasures.clear;
      
    end
    
    siguiente = @unusedTreasures.at(0)
    @unusedTreasures.delete_at(0)
    
    siguiente

  end
  
  def nextMonster
    
    if @unusedMonsters.empty?
      
      @unusedMonsters.
      self.shuffleMonsters;
      @usedMonsters.clear;
      
    end
    
    siguiente = @unusedMonsters.at(0)
    @unusedMonsters.delete_at(0)
    
    siguiente
    
    
  end
  
  def nextCultist
    @unusedCultists.delete_at(0)
  end
  
  def giveTreasureBack (t)
    @usedTreasures << t
  end
  
  def giveMonsterBack (m)
    @usedMonsters << m
  end
  
  def initCards
    initTreasureCardDeck
    initMonsterCardDeck
    initCultistCardDeck
  end
  
 end
end