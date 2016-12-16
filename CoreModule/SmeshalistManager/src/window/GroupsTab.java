package window;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.util.List;

import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;

import communication.Communication.Color;
import communication.Communication.GroupsFilter;
import util.CheckBoxEntry;
import util.WindowUtil;

public class GroupsTab extends JPanel{

	private static final long serialVersionUID = 5805971516639326078L;
	private static boolean changed;
	private List<String> groups;
	private List<CheckBoxEntry> groupsCheckBoxes;
	private Map<String, Boolean> groupsVisibility;

	private JScrollPane scrollPane;
	private JPanel buttonsContainer;
	private JPanel scrollPaneContent;
	private JButton selectAllButton;
	private JButton clearSelectionButton;

	public GroupsTab(){
		this.groups = new LinkedList<>();
		this.groupsCheckBoxes = new LinkedList<>();
		this.groupsVisibility = new HashMap<>();
		GroupsTab.changed = false;
		this.initializeView();
		this.setVisible(true);
	}

	private void initializeView() {
		Border border = new EmptyBorder(WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE);
		this.setBorder(border);

		this.setLayout(new BorderLayout());

		selectAllButton = new JButton("Select all");
		selectAllButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				selectAllButtonPressed();
			}
		});
		clearSelectionButton = new JButton("Clear selection");
		clearSelectionButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				clearSelectionButtonPressed();
			}
		});
		buttonsContainer = new JPanel();
		buttonsContainer.add(selectAllButton);
		buttonsContainer.add(Box.createHorizontalStrut(20));
		buttonsContainer.add(clearSelectionButton);

		scrollPaneContent = new JPanel();
		scrollPaneContent.setLayout(new GridLayout(0,3));
		scrollPane = new JScrollPane(scrollPaneContent);

		this.add(buttonsContainer, BorderLayout.NORTH);
		this.add(scrollPane, BorderLayout.CENTER);
	}

	private void clearSelectionButtonPressed() {
		for (CheckBoxEntry checkBox : this.groupsCheckBoxes) {
			checkBox.setCheckBoxSelected(false);
		}
		setChanged(true);
		scrollPaneContent.revalidate();
		scrollPaneContent.repaint();
	}

	private void selectAllButtonPressed() {
		for (CheckBoxEntry checkBox : this.groupsCheckBoxes) {
			checkBox.setCheckBoxSelected(true);
		}
		setChanged(true);
		scrollPaneContent.revalidate();
		scrollPaneContent.repaint();
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
				if (this.groupsVisibility.containsKey(groupName)) {
					tmpCheckBox.setSelected(this.groupsVisibility.get(groupName));
				} else {
					tmpCheckBox.setSelected(true);
				}
				tmpCheckBox.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						GroupsTab.setChanged(true);
					}
				});
				CheckBoxEntry groupCheckBox = new CheckBoxEntry(tmpCheckBox, groups.get(Integer.parseInt(groupName)));
				groupCheckBox.setPreferredSize(new Dimension(50,25));
				this.groupsCheckBoxes.add(groupCheckBox);

				scrollPaneContent.add(groupCheckBox);
			}
		}

		scrollPaneContent.revalidate();
		scrollPaneContent.repaint();

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
		for (CheckBoxEntry checkBoxEntry: this.groupsCheckBoxes){
			this.groupsVisibility.put(checkBoxEntry.getCheckBoxText(),checkBoxEntry.isCheckBoxSelected());
		}
		this.scrollPaneContent.removeAll();
		this.groupsCheckBoxes.clear();
		this.groups.clear();
		this.scrollPaneContent.revalidate();
		this.scrollPaneContent.repaint();
	}

	public void setInitContent() {
		this.removeAll();
		this.groups.clear();
		this.groupsVisibility.clear();
		this.groupsCheckBoxes.clear();
		GroupsTab.changed = false;
		this.initializeView();
		this.revalidate();
		this.repaint();
	}
}
