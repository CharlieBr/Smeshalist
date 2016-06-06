package window;

import java.util.LinkedList;
import java.util.List;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JCheckBox;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;

import util.WindowUtil;

public class GroupsTab extends JScrollPane{

	private static final long serialVersionUID = 5805971516639326078L;
	
	private JPanel scrollPaneContent;
	private List<String> groups;
	private List<JCheckBox> groupsCheckBoxes;
	
	private BoxLayout boxLayout;
		
	public GroupsTab(){
		this.groups = new LinkedList<>();
		this.groupsCheckBoxes = new LinkedList<>();
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
		this.groups.clear();
		this.groups.addAll(groups);
		
		this.putGroups();
	}

	private void putGroups() {
		scrollPaneContent.removeAll();
		groupsCheckBoxes.clear();
		
		for (String groupName: groups){
			this.groupsCheckBoxes.add(new JCheckBox(groupName));
		}
		
		for (JCheckBox checkBox: groupsCheckBoxes){
			scrollPaneContent.add(checkBox);
			scrollPaneContent.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		}

	}

	
}
