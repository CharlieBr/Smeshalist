package window;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.CompoundBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import javax.swing.plaf.basic.BasicArrowButton;
import javax.swing.plaf.metal.MetalScrollButton;

import communication.Communication.ManagerToCoreMessage;
import communication.Communication.ManagerToCoreMessage.MTCMessageType;
import communication.Communication.OptionsInfo;
import communication.SendingThread;
import util.WindowUtil;

public class OptionsTab extends JPanel{
	
	private static final long serialVersionUID = 2544760396056394118L;

	private GroupLayout mainLayout;
	private JCheckBox transparencyCheckBox;
	private JCheckBox renderingCheckBox;
	private JCheckBox showLabelsCheckBox;
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

	private boolean activeTree;

	public OptionsTab(){
		
		initializeView();

		setVisible(true);
	}

	private void initializeView(){
		mainLayout = new GroupLayout(this);
		mainLayout.setAutoCreateGaps(true);
		mainLayout.setAutoCreateContainerGaps(true);
		this.setLayout(mainLayout);

		treeName = new JLabel("None");
		activeTree = false;
		
		Border border = new EmptyBorder(WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE);
		setBorder(border);
		
		transparencyCheckBox = new JCheckBox("Transparent structures");
		transparencyCheckBox.setBorder(new EmptyBorder(0, 0, 10, 0));
		renderingCheckBox = new JCheckBox("Dynamic rendering");
		renderingCheckBox.setSelected(true);
		renderingCheckBox.setBorder(new EmptyBorder(0, 0, 10, 0));
		showLabelsCheckBox = new JCheckBox("Show labels");
		showLabelsCheckBox.setBorder(new EmptyBorder(0, 0, 10, 0));
		
		JLabel label = new JLabel("Mouse sensitivity");
		label.setBorder(new EmptyBorder(0, 0, 10, 0));
		sensitivitySlider = new JSlider(JScrollBar.HORIZONTAL, 0, 20, 1);
		sensitivitySlider.setMajorTickSpacing(5);
		sensitivitySlider.setMinorTickSpacing(1);
		sensitivitySlider.setValue(10);
		sensitivitySlider.setPaintTicks(true);
		sensitivitySlider.setPaintLabels(true);
		sensitivitySlider.setBorder(new EmptyBorder(0, 20, 20, 20));
		
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
		nextSnapshotButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				nextSnapshotButtonPressed();
			}
		});
		prevSnapshotButton = new JButton("Prev");
		prevSnapshotButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				prevSnapshotButtonPressed();
			}
		});

		breakpointButtonsContainer = new JPanel();
		breakpointButtonsContainer.add(continueButton);
		breakpointButtonsContainer.add(abortButton);
		breakpointButtonsContainer.setBorder(new CompoundBorder(new TitledBorder("Breakpoint"), new EmptyBorder(0, 100, 0, 100)));
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
		treeButtonsContainer.setBorder(new CompoundBorder(new TitledBorder("Structures Tree"), new EmptyBorder(0, 50, 0, 50)));

		mainLayout.setHorizontalGroup(
				mainLayout.createParallelGroup()
				.addComponent(transparencyCheckBox)
				.addComponent(renderingCheckBox)
				.addComponent(showLabelsCheckBox)
				.addGroup(mainLayout.createParallelGroup()
						.addComponent(label)
						.addComponent(sensitivitySlider)
						.addComponent(applyButtonContainer))
						.addComponent(breakpointButtonsContainer)
						.addComponent(treeButtonsContainer)
				);
		
		mainLayout.setVerticalGroup(
				mainLayout.createSequentialGroup()
				.addComponent(transparencyCheckBox)
				.addComponent(renderingCheckBox)
				.addComponent(showLabelsCheckBox)
				.addGroup(mainLayout.createSequentialGroup()
						.addComponent(label)
						.addComponent(sensitivitySlider)
						.addComponent(applyButtonContainer))
						.addComponent(breakpointButtonsContainer)
						.addComponent(treeButtonsContainer)

				);
	}

	private void prevSnapshotButtonPressed() {
		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.PREV_TREE);

		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();
	}

	private void nextSnapshotButtonPressed() {
		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.NEXT_TREE);

		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();
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
		return optionsInfo.build();
	}

	private void cleanButtonPressed() {
		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.CLEAN);

		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();

		MainWindow.getInstance().cleanGroupCheckBoxes();
	}

	private void snapshotButtonPressed() {
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
		this.treeName = new JLabel(treeName);
		cleanButton.setEnabled(treeName.compareTo("ACTIVE") != 0);

		treeButtonsContainer.revalidate();
		treeButtonsContainer.repaint();
	}
}
