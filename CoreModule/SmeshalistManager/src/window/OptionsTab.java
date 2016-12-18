package window;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.plaf.basic.BasicArrowButton;
import javax.swing.plaf.metal.MetalScrollButton;

import communication.Communication;
import communication.Communication.ManagerToCoreMessage;
import communication.Communication.ManagerToCoreMessage.MTCMessageType;
import communication.Communication.OptionsInfo;
import communication.SendingThread;
import util.WindowUtil;

public class OptionsTab extends JPanel{
	
	private static final long serialVersionUID = 2544760396056394118L;

	private enum ColoringType {
		QUALITY_COLORING {
			@Override
			public String toString(){
				return "Quality coloring";
			}
		},
		GROUP_COLORING{
			@Override
			public String toString(){
				return "Group coloring";
			}
		};
	}
	private enum VisualisationMode {
		MODE_3D {
			@Override
			public String toString(){
				return "3D mode";
			}
		},
		MODE_2D{
			@Override
			public String toString(){
				return "2D mode";
			}
		};
	}

	private JCheckBox transparencyCheckBox;
	private JCheckBox renderingCheckBox;
	private JCheckBox showLabelsCheckBox;
	private JComboBox<ColoringType> coloringComboBox;
	private JComboBox<VisualisationMode> modeComboBox;
	private JSlider sensitivitySlider;
	private JButton applyButton;
	private JButton continueButton;
	private JButton abortButton;
	private JLabel treeName;
	private JButton snapshotButton;
	private JButton cleanButton;
	private JButton nextSnapshotButton;
	private JButton prevSnapshotButton;
	private JPanel breakpointButtonsContainer;
	private JPanel treeButtonsContainer;

	public OptionsTab(){
		initializeView();

		setVisible(true);
	}

	private void initializeView(){
		this.setLayout(new BorderLayout());

		treeName = new JLabel("ACTIVE");
		
		Border border = new EmptyBorder(WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE);
		setBorder(border);
		
		transparencyCheckBox = new JCheckBox("Transparent structures");
		transparencyCheckBox.setBorder(new EmptyBorder(10, 10, 10, 0));
		renderingCheckBox = new JCheckBox("Dynamic rendering");
		renderingCheckBox.setSelected(true);
		renderingCheckBox.setBorder(new EmptyBorder(10, 10, 10, 0));
		showLabelsCheckBox = new JCheckBox("Show labels");
		showLabelsCheckBox.setBorder(new EmptyBorder(10, 10, 10, 0));

		coloringComboBox = new JComboBox<>();
		coloringComboBox.addItem(ColoringType.GROUP_COLORING);
		coloringComboBox.addItem(ColoringType.QUALITY_COLORING);
		coloringComboBox.setBorder(new EmptyBorder(10,0,10,10));

		modeComboBox = new JComboBox<>();
		modeComboBox.addItem(VisualisationMode.MODE_3D);
		modeComboBox.addItem(VisualisationMode.MODE_2D);
		modeComboBox.setBorder(new EmptyBorder(10,0,10,10));

		sensitivitySlider = new JSlider(JScrollBar.HORIZONTAL, 0, 20, 1);
		sensitivitySlider.setMajorTickSpacing(5);
		sensitivitySlider.setMinorTickSpacing(1);
		sensitivitySlider.setValue(10);
		sensitivitySlider.setPaintTicks(true);
		sensitivitySlider.setPaintLabels(true);
		TitledBorder titledBorder = new TitledBorder("Mouse sensitivity");
		titledBorder.setBorder(new EmptyBorder(40,0,0,0));
		sensitivitySlider.setBorder(titledBorder);

		applyButton = new JButton("Apply");	
		applyButton.setBorder(new EmptyBorder(5,25,5,25));
		applyButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				applyButtonPressed();
				
			}
		});
		JPanel applyButtonContainer = new JPanel();
		applyButtonContainer.setBorder(new EmptyBorder(0,145,0,145));
		applyButtonContainer.add(applyButton);

		continueButton = new JButton("Continue");
		continueButton.setEnabled(false);
		continueButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				continueButtonPressed();
			}
		});
		abortButton = new JButton("Abort");
		abortButton.setEnabled(false);
		abortButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				abortButtonPressed();
			}
		});
		snapshotButton = new JButton("Snapshot");
		snapshotButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				snapshotButtonPressed();
			}
		});
		cleanButton = new JButton("Clean");
		cleanButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				cleanButtonPressed();
			}
		});
		nextSnapshotButton = new JButton("Next");
		nextSnapshotButton.setEnabled(false);
		nextSnapshotButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				nextSnapshotButtonPressed();
			}
		});
		prevSnapshotButton = new JButton("Prev");
		prevSnapshotButton.setEnabled(false);
		prevSnapshotButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				prevSnapshotButtonPressed();
			}
		});

		breakpointButtonsContainer = new JPanel();
		breakpointButtonsContainer.add(continueButton);
		breakpointButtonsContainer.add(abortButton);
		breakpointButtonsContainer.setBorder(new TitledBorder("Breakpoint"));
		treeButtonsContainer = new JPanel();
		treeButtonsContainer.setLayout(new BoxLayout(treeButtonsContainer,BoxLayout.PAGE_AXIS));
		JPanel treeButtonsPanel = new JPanel();
		treeButtonsPanel.add(snapshotButton);
		treeButtonsPanel.add(cleanButton);
		treeButtonsPanel.add(Box.createHorizontalStrut(30));
		treeButtonsPanel.add(prevSnapshotButton);
		treeButtonsPanel.add(nextSnapshotButton);
		treeButtonsContainer.add(treeName);
		treeButtonsContainer.add(treeButtonsPanel);
		treeButtonsContainer.setBorder(new TitledBorder("Structures Tree"));

		JPanel checkBoxesPanel = new JPanel();
		checkBoxesPanel.setLayout(new BoxLayout(checkBoxesPanel, BoxLayout.PAGE_AXIS));
		checkBoxesPanel.add(transparencyCheckBox);
		checkBoxesPanel.add(renderingCheckBox);
		checkBoxesPanel.add(showLabelsCheckBox);

		JPanel comboBoxesPanel = new JPanel();
		comboBoxesPanel.setLayout(new BorderLayout());
		comboBoxesPanel.add(coloringComboBox, BorderLayout.NORTH);
		comboBoxesPanel.add(modeComboBox, BorderLayout.SOUTH);

		JPanel visualisationOptionsPanel = new JPanel();
		visualisationOptionsPanel.setLayout(new BorderLayout());
		visualisationOptionsPanel.add(checkBoxesPanel, BorderLayout.WEST);
		visualisationOptionsPanel.add(comboBoxesPanel, BorderLayout.EAST);

		JPanel sliderPanel = new JPanel();
		sliderPanel.setLayout(new BoxLayout(sliderPanel, BoxLayout.PAGE_AXIS));
		sliderPanel.add(sensitivitySlider);
		sliderPanel.add(applyButtonContainer);

		JPanel optionsPanel = new JPanel();
		optionsPanel.setLayout(new BorderLayout());
		optionsPanel.add(visualisationOptionsPanel, BorderLayout.NORTH);
		optionsPanel.add(sliderPanel, BorderLayout.CENTER);
		optionsPanel.setBorder(new TitledBorder(""));

		Box box = Box.createVerticalBox();
		box.add(breakpointButtonsContainer);
		box.add(treeButtonsContainer);

		this.add(optionsPanel, BorderLayout.NORTH);
		this.add(box, BorderLayout.CENTER);
	}

	private void prevSnapshotButtonPressed() {
		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.PREV_TREE);

		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();

		MainWindow.getInstance().cleanGroupCheckBoxes();
	}

	private void nextSnapshotButtonPressed() {
		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.NEXT_TREE);

		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();

		MainWindow.getInstance().cleanGroupCheckBoxes();
	}

	private void applyButtonPressed(){

		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.OPTIONS);
		toCoreMessageBuilder.setOptionsInfo(this.getOptionsInfo());
		
		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();

	}

	public OptionsInfo getOptionsInfo() {
		OptionsInfo.Builder optionsInfo = OptionsInfo.newBuilder();
		optionsInfo.setDynamicRendering(renderingCheckBox.isSelected());
		optionsInfo.setShowLabels(showLabelsCheckBox.isSelected());
		optionsInfo.setTransparentStructures(transparencyCheckBox.isSelected());
		optionsInfo.setMouseSensitivity(sensitivitySlider.getValue() * 0.1);
		optionsInfo.setColoringType(getColoringType());
		optionsInfo.setVisualisationMode(getVisualisationMode());
		return optionsInfo.build();
	}

	private Communication.VisualisationMode getVisualisationMode() {
		switch(modeComboBox.getItemAt(modeComboBox.getSelectedIndex())) {
			case MODE_3D:
				return Communication.VisualisationMode.MODE_3D;
			case MODE_2D:
				return Communication.VisualisationMode.MODE_2D;
			default:
				System.out.println("Unsupported visualisation mode!");
				return null;
		}
	}

	private Communication.ColoringType getColoringType() {
		switch(coloringComboBox.getItemAt(coloringComboBox.getSelectedIndex())) {
			case QUALITY_COLORING:
				return Communication.ColoringType.QUALITY_COLORING;
			case GROUP_COLORING:
				return Communication.ColoringType.GROUPS_COLORING;
			default:
				System.out.println("Unsupported coloring type!");
				return null;
		}
	}

	private void cleanButtonPressed() {
		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.CLEAN);

		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();

		MainWindow.getInstance().cleanGroupCheckBoxes();
	}

	private void snapshotButtonPressed() {
		prevSnapshotButton.setEnabled(true);
		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.SNAPSHOT);

		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();
	}

	private void continueButtonPressed(){

		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.CONTINUE);
		
		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();
		continueButton.setEnabled(false);
		abortButton.setEnabled(false);

	}
	
	private void abortButtonPressed(){

		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.ABORT);
		
		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();

		continueButton.setEnabled(false);
		abortButton.setEnabled(false);

	}

	public void breakpoint(){
		abortButton.setEnabled(true);
		continueButton.setEnabled(true);
	}

	public void setTreeName(String treeName){
		this.treeName.setText(treeName);
		cleanButton.setEnabled(treeName.equals("ACTIVE"));
		nextSnapshotButton.setEnabled(!treeName.equals("ACTIVE"));

		treeButtonsContainer.revalidate();
		treeButtonsContainer.repaint();
	}

	public void setInitContent() {
		this.removeAll();
		this.initializeView();
		this.revalidate();
		this.repaint();
	}

	public void setOldestSnapshot(boolean oldestSnapshot) {
		prevSnapshotButton.setEnabled(!oldestSnapshot);
	}

}
