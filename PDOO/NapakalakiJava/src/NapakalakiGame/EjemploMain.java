
package NapakalakiGame;

import Test.GameTester;
import GUI.*; 
import java.util.ArrayList;
import GUI.Dice;
public class EjemploMain {

    public static void main(String[] args) {
      Napakalaki game = Napakalaki.getInstance();
      /*GameTester test = GameTester.getInstance();
      
      // Poner el numero de jugadores con el que se quiera probar
      test.play(game, 2); */
      NapakalakiView napakalakiView = new NapakalakiView();
      Dice.createInstance(napakalakiView);
      
      
      
      ArrayList<String> names;
      PlayerNamesCapture namesCapture = new PlayerNamesCapture(napakalakiView, true);
      names = namesCapture.getNames();
      game.initGame(names);
      napakalakiView.setNapakalaki(game);
      napakalakiView.setVisible (true);
    }
}