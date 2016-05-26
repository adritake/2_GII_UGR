/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GUI;
import NapakalakiGame.Player;
import NapakalakiGame.CultistPlayer;
import NapakalakiGame.Treasure;
import NapakalakiGame.Napakalaki;
import java.awt.Component;
import java.util.ArrayList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;


/**
 *
 * @author pablo
 */
public class PlayerView extends javax.swing.JPanel {
    private Player playerModel;
    private Napakalaki napakalakiModel;
    /**
     * Creates new form PlayerViewe
     */
    public PlayerView() {
        initComponents();
    }
    
    public void setPlayer(Player model){
        playerModel = model;
        PlayerName.setText( playerModel.getName() );
        PlayerLevel.setText( Integer.toString(playerModel.getLevels()) );
        PlayerCombatLevel.setText( Integer.toString(playerModel.getCombatLevel()) );
        PlayerEnemy.setText( playerModel.getEnemy().getName() );
        
        if( playerModel instanceof CultistPlayer )
            Sectario.setText("Sectario");
        else
            Sectario.setText("No sectario");
        
        NSectarios.setText( Integer.toString( CultistPlayer.getTotalCultistPlayers() ));
        
        // Incluir instrucciones para actualizar su nombre, nivel, etc.
        // A continuación se actualizan sus tesoros
        this.fillTreasurePanel(VisibleTreasures,playerModel.getVisibleTreasures());
        this.fillTreasurePanel(HiddenTreasures,playerModel.getHiddenTreasures());
        
        PendingBadConsequence.setPendingBadConsequence( model.getPendingBadConsequence() );
                 
        
        
        
        repaint();
        revalidate();
    }
    
    
    public void setEnabledButtoms( boolean mode, boolean steal_mode ){
        
        StealTreasure.setVisible( steal_mode );
        MakeVisible.setVisible( mode );
        DiscardTreasures.setVisible( mode );
        DiscardAll.setVisible( mode );
            
    }
    
    
    public void setNapakalaki( Napakalaki n){
        
        napakalakiModel = n;
        
    }
    
    private ArrayList<Treasure> getSelectedTreasures(JPanel aPanel) {
        // Se recorren los tesoros que contiene el panel,
        //almacenando en un vector aquellos que están seleccionados.
        //Finalmente se devuelve dicho vector.
        TreasureView tv;
        ArrayList<Treasure> output = new ArrayList();
        for (Component c : aPanel.getComponents()) {
            tv = (TreasureView) c;
            if ( tv.isSelected() )
                output.add ( tv.getTreasure() );
        }
        return output;
    }
    
    private void fillTreasurePanel (JPanel aPanel, ArrayList<Treasure> aList) {
        // Se elimina la información antigua, si la hubiera
        aPanel.removeAll();
        // Se recorre la lista de tesoros construyendo y añadiendo sus vistas
        //al panel
        for (Treasure t : aList) {
            TreasureView aTreasureView = new TreasureView();
            aTreasureView.setTreasure (t);
            aTreasureView.setVisible (true);
            aPanel.add (aTreasureView);
        }
        
        // Se fuerza la actualización visual del panel
        aPanel.repaint();
        aPanel.revalidate();
    }
    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        PlayerNameLabel = new javax.swing.JLabel();
        PlayerLevelLabel = new javax.swing.JLabel();
        PlayerCombatLevelLabel = new javax.swing.JLabel();
        Sectario = new java.awt.Label();
        PlayerEnemyLabel = new javax.swing.JLabel();
        PlayerName = new java.awt.Label();
        PlayerEnemy = new java.awt.Label();
        PlayerLevel = new java.awt.Label();
        PlayerCombatLevel = new java.awt.Label();
        VisibleTreasures = new javax.swing.JPanel();
        HiddenTreasures = new javax.swing.JPanel();
        VisibleTreasuresLabel = new javax.swing.JLabel();
        HiddenTreasuresLabel = new javax.swing.JLabel();
        NSectariosLabel = new javax.swing.JLabel();
        NSectarios = new java.awt.Label();
        StealTreasure = new javax.swing.JButton();
        MakeVisible = new javax.swing.JButton();
        DiscardTreasures = new javax.swing.JButton();
        DiscardAll = new javax.swing.JButton();
        PendingBadConsequence = new GUI.PendingBadConsequenceView();

        PlayerNameLabel.setText("Nombre:");

        PlayerLevelLabel.setText("Nivel:");

        PlayerCombatLevelLabel.setText("Nivel de Combate:");

        Sectario.setText("label1");

        PlayerEnemyLabel.setText("Enemigo:");

        PlayerName.setText("label1");

        PlayerEnemy.setText("label1");

        PlayerLevel.setText("label1");

        PlayerCombatLevel.setText("label1");

        VisibleTreasures.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));

        HiddenTreasures.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        HiddenTreasures.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));

        VisibleTreasuresLabel.setText("Tesoros visibles");

        HiddenTreasuresLabel.setText("Tesoros ocultos");

        NSectariosLabel.setText("Nº Sectarios:");

        NSectarios.setText("label1");

        StealTreasure.setText("Steal Treasure");
        StealTreasure.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                StealTreasureActionPerformed(evt);
            }
        });

        MakeVisible.setText("Make Visible");
        MakeVisible.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                MakeVisibleActionPerformed(evt);
            }
        });

        DiscardTreasures.setText("Discard Treasures");
        DiscardTreasures.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                DiscardTreasuresActionPerformed(evt);
            }
        });

        DiscardAll.setText("Discard All Treasures");
        DiscardAll.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                DiscardAllActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(20, 20, 20)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addGap(10, 10, 10)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(layout.createSequentialGroup()
                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addGroup(layout.createSequentialGroup()
                                                .addComponent(PlayerNameLabel)
                                                .addGap(24, 24, 24)
                                                .addComponent(PlayerName, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                            .addComponent(Sectario, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addGroup(layout.createSequentialGroup()
                                                .addComponent(PlayerLevelLabel)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addComponent(PlayerLevel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                        .addGap(66, 66, 66)
                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addGroup(layout.createSequentialGroup()
                                                .addComponent(PlayerCombatLevelLabel)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addComponent(PlayerCombatLevel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                            .addGroup(layout.createSequentialGroup()
                                                .addComponent(NSectariosLabel)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addComponent(NSectarios, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                            .addGroup(layout.createSequentialGroup()
                                                .addComponent(PlayerEnemyLabel)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addComponent(PlayerEnemy, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))))
                                    .addComponent(HiddenTreasures, javax.swing.GroupLayout.PREFERRED_SIZE, 678, javax.swing.GroupLayout.PREFERRED_SIZE)))
                            .addComponent(VisibleTreasures, javax.swing.GroupLayout.PREFERRED_SIZE, 678, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addGroup(layout.createSequentialGroup()
                                .addGap(266, 266, 266)
                                .addComponent(VisibleTreasuresLabel)))
                        .addGap(18, 18, 18)
                        .addComponent(PendingBadConsequence, javax.swing.GroupLayout.PREFERRED_SIZE, 438, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(296, 296, 296)
                        .addComponent(HiddenTreasuresLabel))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(19, 19, 19)
                        .addComponent(StealTreasure, javax.swing.GroupLayout.PREFERRED_SIZE, 175, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(33, 33, 33)
                        .addComponent(MakeVisible, javax.swing.GroupLayout.PREFERRED_SIZE, 175, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(DiscardTreasures, javax.swing.GroupLayout.PREFERRED_SIZE, 175, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(26, 26, 26)
                        .addComponent(DiscardAll)
                        .addGap(356, 356, 356)))
                .addContainerGap(22, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(27, 27, 27)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(PlayerNameLabel)
                                .addComponent(PlayerEnemyLabel))
                            .addComponent(PlayerName, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(PlayerEnemy, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(21, 21, 21)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(Sectario, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(NSectariosLabel)
                            .addComponent(NSectarios, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(28, 28, 28)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(PlayerLevel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(PlayerCombatLevelLabel)
                                .addComponent(PlayerLevelLabel))
                            .addComponent(PlayerCombatLevel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 55, Short.MAX_VALUE)
                        .addComponent(VisibleTreasuresLabel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(VisibleTreasures, javax.swing.GroupLayout.PREFERRED_SIZE, 199, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(53, 53, 53)
                        .addComponent(HiddenTreasuresLabel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(HiddenTreasures, javax.swing.GroupLayout.PREFERRED_SIZE, 201, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(131, 131, 131))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(1, 1, 1)
                        .addComponent(PendingBadConsequence, javax.swing.GroupLayout.PREFERRED_SIZE, 296, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(DiscardAll)
                    .addComponent(StealTreasure)
                    .addComponent(MakeVisible)
                    .addComponent(DiscardTreasures))
                .addGap(26, 26, 26))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void MakeVisibleActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_MakeVisibleActionPerformed
        // TODO add your handling code here:
        ArrayList<Treasure> selHidden = getSelectedTreasures (HiddenTreasures);
        napakalakiModel.makeTreasuresVisible (selHidden);
        setPlayer (napakalakiModel.getCurrentPlayer());
        
            
    }//GEN-LAST:event_MakeVisibleActionPerformed

    private void StealTreasureActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_StealTreasureActionPerformed
        
        // TODO add your handling code here:      
        if( playerModel.stealTreasure() == null){
            JOptionPane.showMessageDialog(null, "No has podido robar nada.", "", JOptionPane.INFORMATION_MESSAGE);
         
       
        }
        else
            setPlayer(playerModel);
        repaint();
        
    }//GEN-LAST:event_StealTreasureActionPerformed

    private void DiscardTreasuresActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_DiscardTreasuresActionPerformed
        // TODO add your handling code here:
        ArrayList<Treasure> sel = getSelectedTreasures (HiddenTreasures);
        napakalakiModel.discardHiddenTreasures(sel);
        sel = getSelectedTreasures (VisibleTreasures);
        napakalakiModel.discardVisibleTreasures(sel);
        setPlayer (napakalakiModel.getCurrentPlayer());
    }//GEN-LAST:event_DiscardTreasuresActionPerformed

    private void DiscardAllActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_DiscardAllActionPerformed
        // TODO add your handling code here:
        playerModel.discardAllTreasures();
        setPlayer (napakalakiModel.getCurrentPlayer());
    }//GEN-LAST:event_DiscardAllActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton DiscardAll;
    private javax.swing.JButton DiscardTreasures;
    private javax.swing.JPanel HiddenTreasures;
    private javax.swing.JLabel HiddenTreasuresLabel;
    private javax.swing.JButton MakeVisible;
    private java.awt.Label NSectarios;
    private javax.swing.JLabel NSectariosLabel;
    private GUI.PendingBadConsequenceView PendingBadConsequence;
    private java.awt.Label PlayerCombatLevel;
    private javax.swing.JLabel PlayerCombatLevelLabel;
    private java.awt.Label PlayerEnemy;
    private javax.swing.JLabel PlayerEnemyLabel;
    private java.awt.Label PlayerLevel;
    private javax.swing.JLabel PlayerLevelLabel;
    private java.awt.Label PlayerName;
    private javax.swing.JLabel PlayerNameLabel;
    private java.awt.Label Sectario;
    private javax.swing.JButton StealTreasure;
    private javax.swing.JPanel VisibleTreasures;
    private javax.swing.JLabel VisibleTreasuresLabel;
    // End of variables declaration//GEN-END:variables
}
