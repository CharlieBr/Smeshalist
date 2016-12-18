package window;

import communication.Communication.GroupsInfo;
import communication.Communication.ManagerToCoreMessage;
import communication.Communication.ComparisonOperator;
import communication.Communication.CoordinatesFilter.Conjunction;
import communication.Communication.GroupsFilter;
import communication.Communication.TypesFilter;
import communication.Communication.QualityFilter;
import communication.Communication.CoordinatesFilter;
import communication.SendingThread;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
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
		mainLayout = new BoxLayout(this, BoxLayout.PAGE_AXIS);
		this.setLayout(mainLayout);
		
		tabsContainer = new JTabbedPane(JTabbedPane.TOP);

		
		typesTab = new TypesTab();
		groupsTab = new GroupsTab();
		qualityTab = new QualityTab();
		coordinatesTab = new CoordinatesTab();

		tabsContainer.add("Types", typesTab);
		tabsContainer.add("Groups", groupsTab);
		tabsContainer.add("Quality", qualityTab);
		tabsContainer.add("Coordinates", coordinatesTab);
		
		this.add(tabsContainer);
		
		buttonContainer = new JPanel();
		buttonContainer.setBorder(new EmptyBorder(10, 0, 0, 0));
		applyButton = new JButton("Apply");
		applyButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				applyButtonPressed();
			}
		});
		buttonContainer.add(applyButton);
		
		this.add(buttonContainer);
	}

	private void applyButtonPressed() {
		TypesFilter typesFilter = typesTab.getTypesFilter();
		GroupsFilter groupsFilter = groupsTab.getGroupsFilter();
		QualityFilter qualityFilter = qualityTab.getQualityFilter();
		CoordinatesFilter coordinatesFilter = coordinatesTab.getCoordinatesFilter();

		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(ManagerToCoreMessage.MTCMessageType.FILTERS);

		if (TypesTab.isChanged()){
			toCoreMessageBuilder.setTypesFilter(typesFilter);
		}
		if (GroupsTab.isChanged()){
			toCoreMessageBuilder.setGroupsFilter(groupsFilter);
		}
		if (QualityTab.isChanged()){
			toCoreMessageBuilder.setQualityFilter(qualityFilter);
		}
		if (CoordinatesTab.isChanged()){
			toCoreMessageBuilder.setCoordinatesFilter(coordinatesFilter);
		}
		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();

		TypesTab.setChanged(false);
		GroupsTab.setChanged(false);
		CoordinatesTab.setChanged(false);
		QualityTab.setChanged(false);

		this.groupsTab.updateGroupsVisibility();
	}

	public void setGroupsInfo(GroupsInfo groupsInfo){
		groupsTab.setGroups(groupsInfo.getAllGroupsMap());
	}

	public static ComparisonOperator getComparisonOperator(String operator) {
		switch (operator) {
			case "<":
				return ComparisonOperator.LESS;
			case "<=":
				return ComparisonOperator.LESS_OR_EQUAL;
			case ">":
				return ComparisonOperator.GREATER;
			case ">=":
				return ComparisonOperator.GREATER_OR_EQUAL;
			case "=":
				return ComparisonOperator.EQUAL;
			default:
				System.out.println("No such operator: " + operator);
				return null;
		}
	}

	public static Conjunction getConjunction(String conjunction){
		switch (conjunction){
			case "AND":
				return Conjunction.AND;
			case "OR":
				return Conjunction.OR;
			default:
				System.out.println("No such conjunction: " + conjunction);
				return null;
		}
	}

	public void cleanGroupCheckBoxes() {
		this.groupsTab.cleanGroupCheckboxes();
	}

	public void setInitContent() {
		this.typesTab.setInitContent();
		this.groupsTab.setInitContent();
		this.qualityTab.setInitContent();
		this.coordinatesTab.setInitContent();
	}
}
