package window;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.LayoutManager;
import java.util.LinkedHashMap;
import java.util.Map;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;

import util.BoundingBox;
import util.ElementInfo;
import util.WindowUtil;

public class StatisticsTab extends JPanel{
	

	private static final long serialVersionUID = 1L;
	
	private Map<String, ElementInfo> elementsCount;
	private BoundingBox boundingBox;

	private JPanel cell11;
	private JPanel cell12;
	private JPanel cell21;
	private JPanel cell22;
	
	private BoxLayout bl11;
	private BoxLayout bl12;
	private BoxLayout bl21;
	private	BoxLayout bl22;
	
	
	public StatisticsTab(){
		
		this.elementsCount = new LinkedHashMap<>();
		initializeView();
		setVisible(true);
		
	}

	private void initializeView(){

		LayoutManager mgr = new GridLayout(2,2);
		setLayout(mgr);
		Border border = new EmptyBorder(WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE,WindowUtil.PADDING_VALUE);
		setBorder(border);

		cell11 = new JPanel();
		cell12 = new JPanel();
		cell21 = new JPanel();
		cell22 = new JPanel();
		
		initStructuresList();
		initValuesList();
		initAxisList();
		initCoordinatesList();
		
				
		add(cell11);
		add(cell12);
		add(cell21);
		add(cell22);

	}

	private void initCoordinatesList() {
		bl22 = new BoxLayout(cell22,BoxLayout.PAGE_AXIS);
		cell22.setLayout(bl22);

		TitledBorder border = new TitledBorder(new EmptyBorder(10,10,10,10), "Range");
		border.setTitleColor(Color.BLUE);
		border.setTitleJustification(2);
		cell22.setBorder(border);
		
	}

	private void initAxisList() {
		bl21 = new BoxLayout(cell21,BoxLayout.PAGE_AXIS);
		cell21.setLayout(bl21);

		TitledBorder border = new TitledBorder(new EmptyBorder(10,10,10,10), "Axis");
		border.setTitleColor(Color.BLUE);
		border.setTitleJustification(2);
		cell21.setBorder(border);
		
		cell21.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		cell21.add(new JLabel("x"));
		cell21.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		cell21.add(new JLabel("y"));
		cell21.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		cell21.add(new JLabel("z"));
	}

	private void initValuesList() {
		bl12 = new BoxLayout(cell12,BoxLayout.PAGE_AXIS);
		cell12.setLayout(bl12);
		TitledBorder border = new TitledBorder(new EmptyBorder(10,10,10,10), "Total (visible)");
		border.setTitleColor(Color.BLUE);
		border.setTitleJustification(2);
		cell12.setBorder(border);	
		
	}

	private void initStructuresList() {
		bl11 = new BoxLayout(cell11,BoxLayout.PAGE_AXIS);
		cell11.setLayout(bl11);
		TitledBorder border = new TitledBorder(new EmptyBorder(10,10,10,10), "Structures");
		border.setTitleColor(Color.BLUE);
		border.setTitleJustification(2);
		cell11.setBorder(border);
		
	}
	
	public void putElementsCount(){
		
		cell11.removeAll();
		cell12.removeAll();
		
		cell11.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		cell12.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		for(String element : this.elementsCount.keySet()){
			cell11.add(new JLabel(element));
			cell11.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		}
		
		for(ElementInfo info : this.elementsCount.values()){
			cell12.add(new JLabel(info.getTotal()+" ("+info.getVisible()+")"));
			cell12.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE))
;		}

	}
	
	public void putBoundingBox(){
		cell22.removeAll();
		
		cell22.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		cell22.add(new JLabel("["+this.boundingBox.getFromX()+","+this.boundingBox.getToX()+"]"));
		cell22.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		cell22.add(new JLabel("["+this.boundingBox.getFromY()+","+this.boundingBox.getToY()+"]"));
		cell22.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		cell22.add(new JLabel("["+this.boundingBox.getFromZ()+","+this.boundingBox.getToZ()+"]"));

	}
	
	
	public Map<String, ElementInfo> getElementsCount() {
		return elementsCount;
	}

	public void setElementsCount(Map<String, ElementInfo> elementsCount) {
		this.elementsCount.clear();
		this.elementsCount.putAll(elementsCount);
		this.putElementsCount();
	}
	


	public void setBoundingBox(BoundingBox boundingBox) {
		this.boundingBox = boundingBox;
		this.putBoundingBox();
	}
	
	
	public void setTestContent(){
		Map<String, ElementInfo> testMap = new LinkedHashMap<>();
		testMap.put("Vertexes", new ElementInfo(2015, 215));
		testMap.put("Edges", new ElementInfo(503, 12));
		testMap.put("Triangles", new ElementInfo(23, 0));
		testMap.put("Pyramids", new ElementInfo(415, 415));
		
		BoundingBox testBoundingBox = new BoundingBox(-0.56, 15.6, 1.2, 5.8, 0.2, 3.5);
		
		setElementsCount(testMap);
		setBoundingBox(testBoundingBox);
	}
}
