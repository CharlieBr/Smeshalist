package window;

import java.util.LinkedList;
import java.util.List;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;

public class FiltersTab extends JPanel{

	private static final long serialVersionUID = -4692062501127481100L;
	
//	private JPanel filtersPanel;
	private JButton applyButton;
	private JTabbedPane tabsContainer;
	private TypesTab typesTab;
	private GroupsTab groupsTab;
	private QualityTab qualityTab;
	private CoordinatesTab coordinatesTab;
	
	private BoxLayout mainLayout;
	private JPanel buttonContainer;
	
	public FiltersTab(){
		initializeView();
		this.setVisible(true);
	}

	private void initializeView() {
//		filtersPanel = new JPanel();
		mainLayout = new BoxLayout(this, BoxLayout.PAGE_AXIS);
		this.setLayout(mainLayout);
		
		//TODO to set the border or not to set the border - that's the question
		Border border = new EmptyBorder(0,0,0,0);
		this.setBorder(border);

		
		tabsContainer = new JTabbedPane(JTabbedPane.TOP);

		
		typesTab = new TypesTab();
		groupsTab = new GroupsTab();
		qualityTab = new QualityTab();
		coordinatesTab = new CoordinatesTab();
		
		this.setTestContent();
		
		tabsContainer.add("Types", typesTab);
		tabsContainer.add("Groups", groupsTab);
		tabsContainer.add("Quality", qualityTab);
		tabsContainer.add("Coordinates", coordinatesTab);
		
		this.add(tabsContainer);
		
		buttonContainer = new JPanel();
		buttonContainer.setBorder(new EmptyBorder(30, 0, 0, 0));
		applyButton = new JButton("Apply");
		buttonContainer.add(applyButton);
		
		this.add(buttonContainer);
	}

	private void setTestContent() {
		List<String> structures = new LinkedList<>();
		structures.add("Vertexes");
		structures.add("Edges");
		structures.add("Triangles");
		structures.add("Pyramids");
		
		typesTab.setStructures(structures);
		
		List<String> groups = new LinkedList<>();
		groups.add("0");
		groups.add("1");
		groups.add("2");
		groups.add("3");
		groups.add("4");
		groups.add("5");
		groups.add("6");
		groups.add("7");
		groups.add("8");
		groups.add("9");
		
		groupsTab.setGroups(groups);
	}

}
