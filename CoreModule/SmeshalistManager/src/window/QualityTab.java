package window;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;

import util.WindowUtil;

public class QualityTab extends JScrollPane{

	private static final long serialVersionUID = -7509751926352507679L;
	
	private JPanel scrollPaneContent;
	private JPanel controlsPanel;
	private JTextField v1TextField;
	private JTextField v2TextField;
	private JComboBox<String> v1ComboBox;
	private JComboBox<String> v2ComboBox;
	private JButton addButton;
	
	private BoxLayout boxLayout;

	public QualityTab(){
		this.initializeView();
				
		this.setVisible(true);
	}

	private void initializeView() {
		Border border = new EmptyBorder(WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE);
		this.setBorder(border);		

		v1TextField = new JTextField();
		v1TextField.setPreferredSize((new Dimension(50, 25)));
		v2TextField = new JTextField();	
		v2TextField.setPreferredSize((new Dimension(50, 25)));

		v1ComboBox = new JComboBox<>();
		v1ComboBox.addItem("<=");
		v1ComboBox.addItem("<");
		v1ComboBox.addItem("=");
		v1ComboBox.addItem(">");
		v1ComboBox.addItem(">=");
		v2ComboBox = new JComboBox<>();
		v2ComboBox.addItem("<=");
		v2ComboBox.addItem("<");
		v2ComboBox.addItem("=");
		v2ComboBox.addItem(">");
		v2ComboBox.addItem(">=");
		
		addButton = new JButton("Add");
		
		addButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				addButtonPressed();
			}

		});
		
		controlsPanel = new JPanel();
		controlsPanel.add(v1TextField);
		controlsPanel.add(v1ComboBox);
		controlsPanel.add(Box.createHorizontalStrut(50));
		controlsPanel.add(v2ComboBox);
		controlsPanel.add(v2TextField);
		controlsPanel.add(Box.createHorizontalStrut(50));
		controlsPanel.add(addButton);
		
		scrollPaneContent = new JPanel();
		boxLayout = new BoxLayout(scrollPaneContent, BoxLayout.PAGE_AXIS);
		scrollPaneContent.setLayout(boxLayout);
		
		scrollPaneContent.add(controlsPanel);
		scrollPaneContent.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		
		this.setViewportView(scrollPaneContent);
	}
	
	private void addButtonPressed() {
		JPanel newEntry = new JPanel();
		
		newEntry.add(new JLabel(v1TextField.getText()));
		newEntry.add(new JLabel(v1ComboBox.getSelectedItem().toString()));
		newEntry.add(new JLabel("QUALITY"));
		newEntry.add(new JLabel(v2ComboBox.getSelectedItem().toString()));
		newEntry.add(new JLabel(v2TextField.getText()));
		newEntry.add(Box.createHorizontalStrut(50));
		newEntry.add(Box.createHorizontalGlue());
		
		JButton button = new JButton("Delete");
		newEntry.add(button);
		
		scrollPaneContent.add(newEntry);
		scrollPaneContent.revalidate();
		scrollPaneContent.repaint();
	}
}