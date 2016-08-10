package window;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;

import javax.swing.GroupLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollBar;
import javax.swing.JSlider;
import javax.swing.border.Border;
import javax.swing.border.CompoundBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;

import communication.Communication.ManagerToCoreMessage;
import communication.Communication.ManagerToCoreMessage.MTCMessageType;
import communication.Communication.OptionsInfo;
import communication.SendingThread;
import util.SocketUtil;
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
	private JPanel buttonContainer;
	
	public OptionsTab(){
		
		initializeView();

		setVisible(true);
	}

	private void initializeView(){
		mainLayout = new GroupLayout(this);
		mainLayout.setAutoCreateGaps(true);
		mainLayout.setAutoCreateContainerGaps(true);
		this.setLayout(mainLayout);
		
		Border border = new EmptyBorder(WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE);
		setBorder(border);
		
		transparencyCheckBox = new JCheckBox("Transparent structures");
		transparencyCheckBox.setBorder(new EmptyBorder(0, 0, 20, 0));
		renderingCheckBox = new JCheckBox("Dynamic rendering");
		renderingCheckBox.setBorder(new EmptyBorder(0, 0, 20, 0));
		showLabelsCheckBox = new JCheckBox("Show labels");
		showLabelsCheckBox.setBorder(new EmptyBorder(0, 0, 20, 0));
		
		JLabel label = new JLabel("Mouse sensitivity");
		label.setBorder(new EmptyBorder(0, 0, 10, 0));
		sensitivitySlider = new JSlider(JScrollBar.HORIZONTAL, 0, 20, 1);
		sensitivitySlider.setMajorTickSpacing(5);
		sensitivitySlider.setMinorTickSpacing(1);
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
		continueButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				continueButtonPressed();
			}
		});
		abortButton = new JButton("Abort");
		abortButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				abortButtonPressed();
			}
		});
		buttonContainer = new JPanel();
		buttonContainer.add(continueButton);
		buttonContainer.add(abortButton);
		buttonContainer.setBorder(new CompoundBorder(new TitledBorder("Control"), new EmptyBorder(0, 100, 0, 100)));
		
		mainLayout.setHorizontalGroup(
				mainLayout.createParallelGroup()
				.addComponent(transparencyCheckBox)
				.addComponent(renderingCheckBox)
				.addComponent(showLabelsCheckBox)
				.addGroup(mainLayout.createParallelGroup()
						.addComponent(label)
						.addComponent(sensitivitySlider)
						.addComponent(applyButtonContainer))
						.addComponent(buttonContainer)
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
						.addComponent(buttonContainer)
				
				);
	}		
	
	private void applyButtonPressed(){
		OptionsInfo.Builder optionsInfo = OptionsInfo.newBuilder();
		optionsInfo.setDynamicRendering(renderingCheckBox.isSelected());
		optionsInfo.setShowLabels(showLabelsCheckBox.isSelected());
		optionsInfo.setTransparentStructures(transparencyCheckBox.isSelected());
		optionsInfo.setMouseSensitivity(sensitivitySlider.getValue() * 0.1);
		
		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.OPTIONS);
		toCoreMessageBuilder.setOptionsInfo(optionsInfo.build());
		
		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();

	}
	
	private void continueButtonPressed(){

		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.CONTINUE);
		
		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();

	}
	
	private void abortButtonPressed(){

		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(MTCMessageType.ABORT);
		
		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();

	}

	public void breakpoint(){
		//TODO handle brakpoint
	}
}
