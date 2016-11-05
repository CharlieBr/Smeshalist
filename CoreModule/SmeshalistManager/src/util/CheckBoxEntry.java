package util;

import javax.swing.JPanel;
import javax.swing.JCheckBox;
import java.awt.Dimension;
import communication.Communication.Color;

public class CheckBoxEntry extends JPanel {
	private JCheckBox checkBox;
	private JPanel colorPanel;

	public CheckBoxEntry(JCheckBox checkBox, Color color){
		this.checkBox = checkBox;
		this.colorPanel = new JPanel();
		this.colorPanel.setMaximumSize(new Dimension(15,15));
		this.colorPanel.setBackground(new java.awt.Color(color.getR(), color.getG(), color.getB()));
	}

	public boolean isCheckBoxSelected(){
		return this.checkBox.isSelected();
	}

	public String getCheckBoxText(){
		return this.checkBox.getText();
	}
}
