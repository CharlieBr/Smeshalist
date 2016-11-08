package window;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.util.List;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JCheckBox;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;

import communication.Communication.Color;
import communication.Communication.GroupsFilter;
import util.CheckBoxEntry;
import util.WindowUtil;

public class GroupsTab extends JScrollPane{

	private static final long serialVersionUID = 5805971516639326078L;
	private static boolean changed;

	private JPanel scrollPaneContent;
	private List<String> groups;
	private List<CheckBoxEntry> groupsCheckBoxes;
	
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

	public void setGroups(Map<Integer, Color> groups) {
		TreeSet<Integer> sortedGroupNames = new TreeSet<>(groups.keySet());

		for (Integer groupName : sortedGroupNames) {
			if (!this.groups.contains(Integer.toString(groupName))) {
				this.groups.add(Integer.toString(groupName));
			}
		}

		for (String groupName : this.groups) {
			boolean found = false;
			for (CheckBoxEntry groupCheckBox : this.groupsCheckBoxes) {
				if (groupCheckBox.getCheckBoxText().compareTo(groupName) == 0){
					found = true;
					break;
				}
			}

			if (!found) {
				JCheckBox tmpCheckBox = new JCheckBox(groupName);
				tmpCheckBox.setSelected(true);
				tmpCheckBox.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						GroupsTab.setChanged(true);
					}
				});
				CheckBoxEntry groupCheckBox = new CheckBoxEntry(tmpCheckBox, groups.get(Integer.parseInt(groupName)));
				this.groupsCheckBoxes.add(groupCheckBox);

				scrollPaneContent.add(groupCheckBox);
				scrollPaneContent.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
			}
		}

	}

	public GroupsFilter getGroupsFilter() {
		GroupsFilter.Builder groupsFilterBuilder = GroupsFilter.newBuilder();
		Iterator<CheckBoxEntry> iter = groupsCheckBoxes.iterator();
		for (String groupName: groups){
			Boolean selected = iter.next().isCheckBoxSelected();
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
