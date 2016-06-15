#ifndef PLAYER_H
#define PLAYER_H

#include "environment.h"

class Player{
    public:
      Player(int jug);
      Environment::ActionType Think();
      void Perceive(const Environment &env);
      double PodaAlfaBeta( const Environment & T, int jugador, bool jugadorMaximizador, int prof, Environment::ActionType & accion, double alfa, double beta );
    private:
      int jugador_;
      Environment actual_;
};
#endif
