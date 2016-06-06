package window;

import java.util.LinkedList;
import java.util.List;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JCheckBox;
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;

import util.WindowUtil;

public class TypesTab extends JPanel{

	private static final long serialVersionUID = -8061746505157291652L;
	
	private List<String> structures;
	private List<JCheckBox> typeCheckBoxes;
	
	private BoxLayout mainLayout;
	
	public TypesTab(){
		structures = new LinkedList<>();
		typeCheckBoxes = new LinkedList<>();
		this.initializeView();
		this.setVisible(true);
	}

	private void initializeView() {
		mainLayout = new BoxLayout(this, BoxLayout.PAGE_AXIS);
		this.setLayout(mainLayout);
		
		Border border = new EmptyBorder(30,30,30,30);
		this.setBorder(border);

		
	}
	
	private void putStructures(){
		this.removeAll();
		this.typeCheckBoxes.clear();
		
		for (String structureName: structures){
			typeCheckBoxes.add(new JCheckBox(structureName));
		}
		
		for (JCheckBox checkBox: typeCheckBoxes){
			this.add(checkBox);
			this.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		}
	}

	public List<String> getStructures() {
		return structures;
	}

	public void setStructures(List<String> structures) {
		this.structures.clear();
		this.structures.addAll(structures);
		
		this.putStructures();
	}
	
}
