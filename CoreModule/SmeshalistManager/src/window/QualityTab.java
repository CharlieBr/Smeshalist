package window;

import java.awt.*;
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

import communication.Communication.ComparisonOperator;
import communication.Communication.QualityCondition;
import communication.Communication.QualityFilter;
import util.QualityEntry;
import util.WindowUtil;
import verify.InputVerifier;

public class QualityTab extends JPanel{

	private static final long serialVersionUID = -7509751926352507679L;
	private static boolean changed;

	private JScrollPane scrollPane;
	private JPanel scrollPaneContent;
	private JPanel controlsPanel;
	private JTextField v1TextField;
	private JTextField v2TextField;
	private JComboBox<String> v1ComboBox;
	private JComboBox<String> v2ComboBox;
	private JButton addButton;
	
	private BoxLayout boxLayout;
	private BoxLayout mainLayout;
	
	private List<QualityEntry> conditionEntries;

	public QualityTab(){
		QualityTab.changed = false;
		this.initializeView();
				
		this.setVisible(true);
	}

	private void initializeView() {
		conditionEntries = new ArrayList<>();
		
		Border border = new EmptyBorder(WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE);
		this.setBorder(border);		
		this.mainLayout = new BoxLayout(this,BoxLayout.PAGE_AXIS);
		this.setLayout(mainLayout);

		v1TextField = new JTextField();
		v1TextField.setPreferredSize((new Dimension(50, 25)));
		v2TextField = new JTextField();	
		v2TextField.setPreferredSize((new Dimension(50, 25)));
		
		v1ComboBox = new JComboBox<>();
		v1ComboBox.addItem("<=");
		v1ComboBox.addItem("<");
		v1ComboBox.addItem("=");
		v2ComboBox = new JComboBox<>();
		v2ComboBox.addItem("<=");
		v2ComboBox.addItem("<");
		v2ComboBox.addItem("=");
		
		addButton = new JButton("Add");
		
		addButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				addButtonPressed();
			}

		});
		
		controlsPanel = new JPanel();
		controlsPanel.add(v1TextField);
		controlsPanel.add(v1ComboBox);
		controlsPanel.add(Box.createHorizontalStrut(10));
		controlsPanel.add(new JLabel("QUALITY"));
		controlsPanel.add(Box.createHorizontalStrut(10));
		controlsPanel.add(v2ComboBox);
		controlsPanel.add(v2TextField);
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
	}
	
	private void addButtonPressed() {

		if (!InputVerifier.verifyQualityInput(v1TextField,v1ComboBox,v2TextField,v2ComboBox)){
			JOptionPane.showMessageDialog(MainWindow.getInstance(), "Wrong input!","Wrong input", JOptionPane.ERROR_MESSAGE);
			return;
		}

		QualityEntry newEntry = new QualityEntry(v1TextField.getText(), v1ComboBox.getSelectedItem().toString(), v2TextField.getText(), v2ComboBox.getSelectedItem().toString());
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

		QualityTab.setChanged(true);
	}
	private void deleteButtonPressed(QualityEntry entry) {
		if (conditionEntries.contains(entry)){
			conditionEntries.remove(entry);
			scrollPaneContent.remove(entry);
		}
		
		scrollPaneContent.revalidate();
		scrollPaneContent.repaint();

		QualityTab.setChanged(true);
	}

	public QualityFilter getQualityFilter() {
		QualityFilter.Builder qualityFilterBuilder = QualityFilter.newBuilder();
		for (QualityEntry conditionEntry: conditionEntries){
			qualityFilterBuilder.addQualityCondition(conditionEntry.getQualityCondition());

		}
		return qualityFilterBuilder.build();
	}

	public static boolean isChanged() {
		return changed;
	}

	public static void setChanged(boolean changed) {
		QualityTab.changed = changed;
	}

    public void setInitContent() {
		this.removeAll();
		QualityTab.changed = false;
		this.conditionEntries.clear();
		this.initializeView();
		this.revalidate();
		this.repaint();

    }
}
