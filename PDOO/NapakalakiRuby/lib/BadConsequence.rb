module NapakalakiGame

  class BadConsequence

    attr_reader :text, :levels, :nVisible, :nHidden ,:specificHiddenTreasures, :specificVisibleTreasures
    attr_writer :nVisible, :nHidden, :specificHiddenTreasures, :specificVisibleTreasures

    private_class_method :new

    @@MAXTREASURES = 10

    def initialize(t,l,vt,ht,sht,svt)
      @text     = t
      @levels    = l
      @nVisible = vt
      @nHidden  = ht
      @specificHiddenTreasures = sht
      @specificVisibleTreasures = svt

    end


    def isEmpty
    
      empty = false
      if @nVisible == 0 and @nHidden == 0 and @specificHiddenTreasures.size==0 and @specificVisibleTreasures.size == 0
        empty = true
      end

      empty 
    end

      ###########################################    PRIVADO     ##############################################

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



      ###########################################    PUBLICO     ##############################################

    public
    def substractVisibleTreasure( t )

      posicion = @specificVisibleTreasures.index(t.type)

        if posicion != nil
          @specificVisibleTreasures.delete_at(posicion)
        end

        @nVisible = @nVisible -1
        if( @nVisible < 0)
          @nVisible= 0

        end


    end


    def substractHiddenTreasure( t )

      posicion = @specificHiddenTreasures.index(t.type)

        if posicion != nil
          @specificHiddenTreasures.delete_at(posicion)
        end

        @nHidden = @nHidden -1
        if( @nHidden < 0)
          @nHidden = 0

        end


    end



    def to_s
      
         "\n" + @text + "\nNiveles: #{@levels} \nTesoros visibles: #{@nVisible} \nTesoros ocultos: #{@nHidden}"

  
    end


    def interseccionTK( a , b)

      interseccion = Array.new

      for at in a

        for bt in b

          if at.type == bt and not contiene(interseccion, at)

            interseccion << at.type
          end


        end

      end

      interseccion

    end


    def adjustToFitTreasureList( v , h)

      ajuste = SpecificBadConsequence.new("",0,0,0)

      if @nVisible > v.size

        ajuste.nVisible = v.size

      end

      if @nHidden > h.size 

        ajuste.nHidden = h.size

      end


      ajuste.specificHiddenTreasures = interseccionTK( h , @specificHiddenTreasures)


      ajuste.specificVisibleTreasures = interseccionTK( v , @specificVisibleTreasures)

      ajuste

    end

    def self.MAXTREASURES

      @@MAXTREASURES

    end
  end
end