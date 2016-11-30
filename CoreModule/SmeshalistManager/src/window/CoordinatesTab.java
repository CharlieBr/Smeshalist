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

import communication.Communication.CoordinatesFilter;
import util.CoordinatesEntry;
import util.WindowUtil;
import verify.InputVerifier;

public class CoordinatesTab extends JPanel{

	private static final long serialVersionUID = -1279116248064986979L;
	private static boolean changed;

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
	
	private List<CoordinatesEntry> conditionEntries;
	
	public CoordinatesTab(){
		this.changed = false;
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
		conjunctionComboBox.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CoordinatesTab.setChanged(true);
			}
		});
		
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
		controlsPanel.add(Box.createHorizontalStrut(30));
		controlsPanel.add(addButton);
		
		scrollPaneContent = new JPanel();
		boxLayout = new BoxLayout(scrollPaneContent, BoxLayout.PAGE_AXIS);
		scrollPaneContent.setLayout(boxLayout);
		
//		scrollPaneContent.add(controlsPanel);
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

		CoordinatesEntry newEntry = new CoordinatesEntry(xTextField.getText(), yTextField.getText(), zTextField.getText(), operatorsComboBox.getSelectedItem().toString(), valueTextField.getText());

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

		CoordinatesTab.setChanged(true);
	}
	
	private void deleteButtonPressed(CoordinatesEntry entry) {
		if (conditionEntries.contains(entry)){
			conditionEntries.remove(entry);
			scrollPaneContent.remove(entry);
		}
		
		scrollPaneContent.revalidate();
		scrollPaneContent.repaint();

		CoordinatesTab.setChanged(true);
		
	}

	public CoordinatesFilter getCoordinatesFilter() {
		CoordinatesFilter.Builder coordinatesFilterBuilder = CoordinatesFilter.newBuilder();
		for (CoordinatesEntry conditionEntry: conditionEntries){
			coordinatesFilterBuilder.addCoordinatesCondition(conditionEntry.getCoordinatesCondition());
		}

		coordinatesFilterBuilder.setConjunction(FiltersTab.getConjunction(conjunctionComboBox.getSelectedItem().toString()));
		return coordinatesFilterBuilder.build();
	}

	public static boolean isChanged() {
		return changed;
	}

	public static void setChanged(boolean changed) {
		CoordinatesTab.changed = changed;
	}
}
