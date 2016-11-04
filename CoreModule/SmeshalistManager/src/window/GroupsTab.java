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
import javax.swing.JScrollPane;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;

import communication.Communication.GroupsFilter;
import util.WindowUtil;

public class GroupsTab extends JScrollPane{

	private static final long serialVersionUID = 5805971516639326078L;
	private static boolean changed;

	private JPanel scrollPaneContent;
	private List<String> groups;
	private List<JCheckBox> groupsCheckBoxes;
	
	private BoxLayout boxLayout;
		
	public GroupsTab(){
		this.groups = new LinkedList<>();
		this.groupsCheckBoxes = new LinkedList<>();
		GroupsTab.changed = false;
		this.initializeView();
		this.setVisible(true);
	}

	private void initializeView() {
		Border border = new EmptyBorder(WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE);
		this.setBorder(border);		

		scrollPaneContent = new JPanel();
		boxLayout = new BoxLayout(scrollPaneContent, BoxLayout.PAGE_AXIS);
		scrollPaneContent.setLayout(boxLayout);
		this.setViewportView(scrollPaneContent);
		
	}

	public List<String> getGroups() {
		return groups;
	}

	public void setGroups(List<String> groups) {

		for (String groupName : groups) {
			if (!this.groups.contains(groupName)) {
				this.groups.add(groupName);
			}
		}

		for (String groupName : this.groups) {
			boolean found = false;
			for (JCheckBox groupCheckBox : this.groupsCheckBoxes) {
				if (groupCheckBox.getText().compareTo(groupName) == 0){
					found = true;
					break;
				}
			}

			if (!found) {
				JCheckBox groupCheckBox = new JCheckBox(groupName);
				groupCheckBox.setSelected(true);
				this.groupsCheckBoxes.add(groupCheckBox);
				groupCheckBox.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						GroupsTab.setChanged(true);
					}
				});
				scrollPaneContent.add(groupCheckBox);
				scrollPaneContent.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
			}
		}

	}

	public GroupsFilter getGroupsFilter() {
		GroupsFilter.Builder groupsFilterBuilder = GroupsFilter.newBuilder();
		Iterator<JCheckBox> iter = groupsCheckBoxes.iterator();
		for (String groupName: groups){
			Boolean selected = iter.next().isSelected();
			groupsFilterBuilder.putSelectedGroups(groupName, selected);
		}

		return groupsFilterBuilder.build();

	}
	public static boolean isChanged() {
		return changed;
	}

	public static void setChanged(boolean changed) {
		GroupsTab.changed = changed;
	}

	public void cleanGroupCheckboxes(){
		this.scrollPaneContent.removeAll();
		this.scrollPaneContent.repaint();
		this.groupsCheckBoxes.clear();
		this.groups.clear();
	}
	
}
