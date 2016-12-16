package window;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JCheckBox;
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;

import communication.Communication.TypesFilter;
import util.WindowUtil;

public class TypesTab extends JPanel{

	private static final long serialVersionUID = -8061746505157291652L;
	private static boolean changed;
	
	private List<String> structures;
	private List<JCheckBox> typeCheckBoxes;
	
	private BoxLayout mainLayout;
	
	public TypesTab(){
		this.structures = new LinkedList<>();
		this.typeCheckBoxes = new LinkedList<>();
		TypesTab.changed = false;
		this.initializeView();
		this.setVisible(true);
	}

	private void initializeView() {
		mainLayout = new BoxLayout(this, BoxLayout.PAGE_AXIS);
		this.setLayout(mainLayout);
		
		Border border = new EmptyBorder(WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE);
		this.setBorder(border);

		List<String> structures = new LinkedList<>();
		structures.add("Vertex");
		structures.add("Edge");
		structures.add("Face");
		structures.add("Block");

		this.setStructures(structures);
	}
	
	private void putStructures(){
		this.removeAll();
		this.typeCheckBoxes.clear();

		for (String structureName: structures){
			JCheckBox structureCheckBox = new JCheckBox(structureName);
			structureCheckBox.setSelected(true);
			typeCheckBoxes.add(structureCheckBox);
		}
		
		for (JCheckBox checkBox: typeCheckBoxes){
			checkBox.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					TypesTab.setChanged(true);
				}
			});
			this.add(checkBox);
			this.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		}
	}

	private void setStructures(List<String> structures) {
		this.structures.clear();
		this.structures.addAll(structures);
		
		this.putStructures();
	}

	public TypesFilter getTypesFilter() {
		TypesFilter.Builder typesFilterBuilder = TypesFilter.newBuilder();
		Iterator<JCheckBox> iter = typeCheckBoxes.iterator();
		for (String structureType: structures){
			Boolean selected = iter.next().isSelected();
			typesFilterBuilder.putSelectedTypes(structureType, selected);

		}

		return typesFilterBuilder.build();

	}

	public static boolean isChanged() {
		return changed;
	}

	public static void setChanged(boolean changed) {
		TypesTab.changed = changed;
	}

    public void setInitContent() {
		this.removeAll();
		TypesTab.changed = false;
		this.initializeView();
		this.revalidate();
		this.repaint();
    }
}
