/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NapakalakiGame;

import java.util.ArrayList;
import GUI.Dice;
/**
 *
 * @author pablo
 */
public class Napakalaki {
    private ArrayList<Player> players = new ArrayList();
    private boolean primera_jugada = true;
    private Player currentPlayer= new Player();
    private Monster currentMonster=new Monster();
    private CombatResult result;
    private CardDealer dealer = CardDealer.getInstance();
    

    private Napakalaki() {
    }

    public static Napakalaki getInstance() {
        return NapakalakiHolder.INSTANCE;
    }

    private static class NapakalakiHolder {
        private static final Napakalaki INSTANCE = new Napakalaki();
    }

    private void initPlayers( ArrayList<String> names){

        for (String p:  names){
            Player pla = new Player(p);
            players.add(pla);
        }

    }

    public void initGame( ArrayList<String> players){

        dealer.initCards();
        this.initPlayers (players);
        this.setEnemies();
        this.nextTurn();
    }

    public boolean nextTurn(){

        boolean nextTurn = nextTurnAllowed();

        if( nextTurnAllowed() ){

            currentMonster = dealer.nextMonster();
            currentPlayer = this.nextPlayer();

            if( currentPlayer.isDead() ){ // Tanto los jugadores nuevos como los muertos tienen death a true
                currentPlayer.initTreasures();
            }
        }

        return nextTurn;
    }

    private Player nextPlayer(){

        int indice;


        if( primera_jugada ){
            primera_jugada = false;
            indice = (int)(Math.random() * players.size());

        }
        else{

           indice = players.indexOf(currentPlayer);

            if( indice == players.size()-1)
                indice = 0;
            else
                indice++;

        }

        currentPlayer = players.get(indice);

        return currentPlayer;
    }

    private boolean nextTurnAllowed(){

        return currentPlayer.validState();

    }

    private void setEnemies(){

        int indice;

        for( Player p: players){

            indice=(int)(Math.random() * players.size());

            while( indice == players.indexOf(p))
                indice=(int)(Math.random() * players.size() );

            p.setEnemy(players.get(indice));

        }

    }

    public CombatResult developCombat(){

       CombatResult combatResult = currentPlayer.combat( currentMonster );
       
       dealer.giveMonsterBack( currentMonster );
       
       CultistPlayer cp;
       
       if( combatResult == CombatResult.LOSEANDCONVERT){
           
           cp = new CultistPlayer(currentPlayer, CardDealer.getInstance().nextCultist());
           
           
           players.add(players.indexOf(currentPlayer),cp);
           
           for (Player pl: players){
               
               if(pl.getEnemy() == currentPlayer)
                   pl.setEnemy(cp);
           }
           
           currentPlayer = cp;
           
           
       }
       return combatResult;
       
    }




    public void discardVisibleTreasures( ArrayList<Treasure> treasures){

        for (Treasure t: treasures){

            currentPlayer.discardVisibleTreasure( t );
            dealer.giveTreasureBack( t );

        }
    }

    public void discardHiddenTreasures( ArrayList<Treasure> treasures){

        for (Treasure t: treasures){

            currentPlayer.discardHiddenTreasure( t );
            dealer.giveTreasureBack( t );

        }
    }




    public void makeTreasuresVisible( ArrayList<Treasure> treasures ){

        for(Treasure t: treasures)

            if( currentPlayer.canMakeTreasureVisible( t ) )
                currentPlayer.makeTreasureVisible( t );


    }

    public Player getCurrentPlayer(){

        return currentPlayer;
    }

    public Monster getCurrentMonster(){

        return currentMonster;
    }

    public boolean endOfGame( CombatResult result ){

        return result == CombatResult.WINGAME;

    }
}
