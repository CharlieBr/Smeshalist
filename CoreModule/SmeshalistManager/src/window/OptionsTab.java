package window;

import javax.swing.GroupLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollBar;
import javax.swing.JSlider;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;

public class OptionsTab extends JPanel{
	
	private static final long serialVersionUID = 2544760396056394118L;

	private boolean transparentStructures;
	private boolean dynamicRendering;
	private double mouseSensitivity; 
	
	private GroupLayout mainLayout;
	private JCheckBox transparencyCheckBox;
	private JCheckBox renderingCheckBox;
	private JSlider sensitivitySlider;
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
		
		Border border = new EmptyBorder(30,30,30,30);
		setBorder(border);
		
		transparencyCheckBox = new JCheckBox("Transparent structures");
		transparencyCheckBox.setBorder(new EmptyBorder(0, 0, 20, 0));
		renderingCheckBox = new JCheckBox("Dynamic rendering");
		renderingCheckBox.setBorder(new EmptyBorder(0, 0, 20, 0));
		JLabel label = new JLabel("Mouse sensitivity");
		label.setBorder(new EmptyBorder(30, 0, 20, 0));
		sensitivitySlider = new JSlider(JScrollBar.HORIZONTAL, 0, 20, 1);
		sensitivitySlider.setMajorTickSpacing(5);
		sensitivitySlider.setMinorTickSpacing(1);
		sensitivitySlider.setPaintTicks(true);
		sensitivitySlider.setPaintLabels(true);
		sensitivitySlider.setBorder(new EmptyBorder(0, 20, 20, 20));
		
		continueButton = new JButton("Continue");
		abortButton = new JButton("Abort");
		buttonContainer = new JPanel();
		buttonContainer.add(continueButton);
		buttonContainer.add(abortButton);
		buttonContainer.setBorder(new EmptyBorder(100, 100, 20, 100));
		
		
		mainLayout.setHorizontalGroup(
				mainLayout.createParallelGroup()
				.addComponent(transparencyCheckBox)
				.addComponent(renderingCheckBox)
				.addGroup(mainLayout.createParallelGroup()
						.addComponent(label)
						.addComponent(sensitivitySlider))
						.addComponent(buttonContainer)
				);
		
		mainLayout.setVerticalGroup(
				mainLayout.createSequentialGroup()
				.addComponent(transparencyCheckBox)
				.addComponent(renderingCheckBox)
				.addGroup(mainLayout.createSequentialGroup()
						.addComponent(label)
						.addComponent(sensitivitySlider))
						.addComponent(buttonContainer)
				
				);
	
	}	
	public boolean isTransparentStructures() {
		return transparentStructures;
	}

	public void setTransparentStructures(boolean transparentStructures) {
		this.transparentStructures = transparentStructures;
	}

	public boolean isDynamicRendering() {
		return dynamicRendering;
	}

	public void setDynamicRendering(boolean dynamicRendering) {
		this.dynamicRendering = dynamicRendering;
	}

	public double getMouseSensitivity() {
		return mouseSensitivity;
	}

	public void setMouseSensitivity(double mouseSensitivity) {
		this.mouseSensitivity = mouseSensitivity;
	}
	
	
	
	
}
