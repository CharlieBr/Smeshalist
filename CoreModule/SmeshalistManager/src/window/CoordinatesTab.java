package window;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;

import util.WindowUtil;
import verify.InputVerifier;

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
	
	private List<JPanel> conditionEntries;
	
	public CoordinatesTab(){
		this.initializeView();
		
		this.setVisible(true);
	}

	private void initializeView() {
		conditionEntries = new ArrayList<>();
		
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
				
		controlsPanel.add(xTextField);
		controlsPanel.add(new JLabel("x"));
		controlsPanel.add(Box.createHorizontalStrut(5));
		controlsPanel.add(yTextField);
		controlsPanel.add(new JLabel("y"));
		controlsPanel.add(Box.createHorizontalStrut(5));
		controlsPanel.add(zTextField);
		controlsPanel.add(new JLabel("z"));
		controlsPanel.add(Box.createHorizontalStrut(50));		
		controlsPanel.add(operatorsComboBox);
		controlsPanel.add(valueTextField);
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

		if (!InputVerifier.verifyCoordinatesInput(valueTextField, xTextField, yTextField, zTextField)){
			JOptionPane.showMessageDialog(MainWindow.getInstance(), "Wrong input!","Wrong input", JOptionPane.ERROR_MESSAGE);
			return;
		}
		
		JPanel newEntry = new JPanel();
		
		newEntry.add(new JLabel(xTextField.getText() + "x"));
		newEntry.add(new JLabel(yTextField.getText() + "y"));
		newEntry.add(new JLabel(zTextField.getText() + "z"));
		newEntry.add(new JLabel(operatorsComboBox.getSelectedItem().toString()));
		newEntry.add(new JLabel(valueTextField.getText()));
		newEntry.add(Box.createHorizontalStrut(50));		
		JButton deleteButton = new JButton("Delete");
		deleteButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				deleteButtonPressed(newEntry);
			}

		});
		newEntry.add(deleteButton);
		
		conditionEntries.add(newEntry);
		
		scrollPaneContent.add(newEntry);
		scrollPaneContent.revalidate();
		scrollPaneContent.repaint();
	}
	
	private void deleteButtonPressed(JPanel entry) {
		if (conditionEntries.contains(entry)){
			conditionEntries.remove(entry);
			scrollPaneContent.remove(entry);
		}
		
		scrollPaneContent.revalidate();
		scrollPaneContent.repaint();
		
	}
}
