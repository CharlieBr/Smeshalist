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

public class CoordinatesTab extends JPanel{

	private static final long serialVersionUID = -1279116248064986979L;
	
	private JScrollPane scrollPane;
	private JPanel scrollPaneContent;
	private JPanel controlsPanel;
	private JTextField valueTextField;
	private JTextField xTextField;
	private JTextField yTextField;
	private JTextField zTextField;
	private JComboBox<String> operatorsComboBox;
	private JComboBox<String> conjunctionComboBox;
	private JButton addButton;
	
	private BoxLayout mainLayout;
	private BoxLayout boxLayout;
	
	public CoordinatesTab(){
		this.initializeView();
		
		this.setVisible(true);
	}

	private void initializeView() {
		Border border = new EmptyBorder(WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE);
		this.setBorder(border);		
		this.mainLayout = new BoxLayout(this,BoxLayout.PAGE_AXIS);
		this.setLayout(mainLayout);

		valueTextField = new JTextField();
		valueTextField.setPreferredSize((new Dimension(30, 25)));
		xTextField = new JTextField();	
		xTextField.setPreferredSize((new Dimension(30, 25)));
		yTextField = new JTextField();	
		yTextField.setPreferredSize((new Dimension(30, 25)));
		zTextField = new JTextField();	
		zTextField.setPreferredSize((new Dimension(30, 25)));

		operatorsComboBox = new JComboBox<>();
		operatorsComboBox.addItem("<=");
		operatorsComboBox.addItem("<");
		operatorsComboBox.addItem(">=");
		operatorsComboBox.addItem(">");
		
		conjunctionComboBox = new JComboBox<>();
		conjunctionComboBox.addItem("AND");
		conjunctionComboBox.addItem("OR");
		
		addButton = new JButton("Add");
		
		addButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				addButtonPressed();
			}

		});
		
		controlsPanel = new JPanel();
		controlsPanel.add(valueTextField);
		controlsPanel.add(operatorsComboBox);
		controlsPanel.add(Box.createHorizontalStrut(50));
		controlsPanel.add(xTextField);
		controlsPanel.add(yTextField);
		controlsPanel.add(zTextField);
		controlsPanel.add(Box.createHorizontalStrut(50));
		controlsPanel.add(addButton);
		
		scrollPaneContent = new JPanel();
		boxLayout = new BoxLayout(scrollPaneContent, BoxLayout.PAGE_AXIS);
		scrollPaneContent.setLayout(boxLayout);
		
		scrollPaneContent.add(controlsPanel);
		scrollPaneContent.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		
		scrollPane = new JScrollPane(scrollPaneContent);
		scrollPane.setPreferredSize(new Dimension(WIDTH, 500));
		
		
		this.add(controlsPanel);
		this.add(scrollPane);
		this.add(conjunctionComboBox);
	}

	private void addButtonPressed() {
		JPanel newEntry = new JPanel();
		
		newEntry.add(new JLabel(valueTextField.getText()));
		newEntry.add(new JLabel(operatorsComboBox.getSelectedItem().toString()));
		newEntry.add(new JLabel(xTextField.getText() + "x"));
		newEntry.add(new JLabel(yTextField.getText() + "y"));
		newEntry.add(new JLabel(zTextField.getText() + "z"));
		newEntry.add(Box.createHorizontalStrut(50));		
		JButton button = new JButton("Delete");
		newEntry.add(button);
		
		scrollPaneContent.add(newEntry);
		scrollPaneContent.revalidate();
		scrollPaneContent.repaint();
	}
}
