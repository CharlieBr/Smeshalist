package window;

import java.awt.*;
import java.math.BigDecimal;
import java.text.DecimalFormat;
import java.util.LinkedHashMap;
import java.util.Map;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;

import communication.Communication.BoundingBox;
import communication.Communication.ElementInfo;
import communication.Communication.ElementsCount;
import util.WindowUtil;

public class StatisticsTab extends JPanel{
	

	private static final long serialVersionUID = 1L;
	private static final String DEFAULT_DECIMAL_FORMAT = "0.0000";

	private ElementsCount elementsCount;
	private BoundingBox boundingBox;

	private JPanel cell11;
	private JPanel cell12;
	private JPanel cell21;
	private JPanel cell22;
	
	private BoxLayout bl11;
	private BoxLayout bl12;
	private BoxLayout bl21;
	private	BoxLayout bl22;

	private Font titleFont = new Font("Tahoma", Font.ITALIC, 22);
	private Font textFont = new Font("Tahoma", Font.PLAIN, 16);

	public StatisticsTab(){
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

		setInitContent();
	}

	private void initCoordinatesList() {
		bl22 = new BoxLayout(cell22,BoxLayout.PAGE_AXIS);
		cell22.setLayout(bl22);

		TitledBorder border = new TitledBorder(new EmptyBorder(10,10,10,10), "Range");
		border.setTitleFont(titleFont);
		border.setTitleColor(Color.BLUE);
		border.setTitleJustification(2);
		cell22.setBorder(border);
	}

	private void initAxisList() {
		bl21 = new BoxLayout(cell21,BoxLayout.PAGE_AXIS);
		cell21.setLayout(bl21);

		TitledBorder border = new TitledBorder(new EmptyBorder(10,10,10,10), "Axis");
		border.setTitleFont(titleFont);
		border.setTitleColor(Color.BLUE);
		border.setTitleJustification(2);
		cell21.setBorder(border);

		JLabel label;
		cell21.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		label = new JLabel("x");
		label.setFont(textFont);
		cell21.add(label);
		cell21.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		label = new JLabel("y");
		label.setFont(textFont);
		cell21.add(label);
		cell21.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		label = new JLabel("z");
		label.setFont(textFont);
		cell21.add(label);
	}

	private void initValuesList() {
		bl12 = new BoxLayout(cell12,BoxLayout.PAGE_AXIS);
		cell12.setLayout(bl12);
		TitledBorder border = new TitledBorder(new EmptyBorder(10,10,10,10), "Visible (total)");
		border.setTitleFont(titleFont);
		border.setTitleColor(Color.BLUE);
		border.setTitleJustification(2);
		cell12.setBorder(border);
	}

	private void initStructuresList() {
		bl11 = new BoxLayout(cell11,BoxLayout.PAGE_AXIS);
		cell11.setLayout(bl11);
		TitledBorder border = new TitledBorder(new EmptyBorder(10,10,10,10), "Structures");
		border.setTitleFont(titleFont);
		border.setTitleColor(Color.BLUE);
		border.setTitleJustification(2);
		cell11.setBorder(border);
	}
	
	public void putElementsCount(){
		cell11.removeAll();
		cell12.removeAll();
		
		cell11.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		cell12.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		for(String element : this.elementsCount.getElementInfosMap().keySet()){
			JLabel label = new JLabel(element);
			label.setFont(textFont);
			cell11.add(label);
			cell11.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		}
		
		for(ElementInfo info : this.elementsCount.getElementInfosMap().values()){
			JLabel label = new JLabel(info.getVisible()+" ("+info.getTotal()+")");
			label.setFont(textFont);
			cell12.add(label);
			cell12.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		}

		cell11.revalidate();
		cell11.repaint();
		cell12.revalidate();
		cell12.repaint();
	}
	
	public void putBoundingBox(){
		cell22.removeAll();

		DecimalFormat df = new DecimalFormat(DEFAULT_DECIMAL_FORMAT);
		JLabel label;

		cell22.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		label = new JLabel("["+df.format(new BigDecimal(this.boundingBox.getFromX()))+"; "+df.format(new BigDecimal(this.boundingBox.getToX()))+"]");
		label.setFont(textFont);
		cell22.add(label);
		cell22.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		label = new JLabel("["+df.format(new BigDecimal(this.boundingBox.getFromY()))+"; "+df.format(new BigDecimal(this.boundingBox.getToY()))+"]");
		label.setFont(textFont);
		cell22.add(label);
		cell22.add(Box.createVerticalStrut(WindowUtil.SPACING_VALUE));
		label = new JLabel("["+df.format(new BigDecimal(this.boundingBox.getFromZ()))+"; "+df.format(new BigDecimal(this.boundingBox.getToZ()))+"]");
		label.setFont(textFont);
		cell22.add(label);

		cell22.revalidate();
		cell22.repaint();
	}

	public void setElementsCount(ElementsCount elementsCount) {
		this.elementsCount = elementsCount;
		this.putElementsCount();
	}
	


	public void setBoundingBox(BoundingBox boundingBox) {
		this.boundingBox = boundingBox;
		this.putBoundingBox();
	}
	
	
	public void setInitContent(){
		BoundingBox.Builder bbBuilder = BoundingBox.newBuilder();
		bbBuilder.setFromX(0.0);
		bbBuilder.setToX(0.0);
		bbBuilder.setFromY(0.0);
		bbBuilder.setToY(0.0);
		bbBuilder.setFromZ(0.0);
		bbBuilder.setToZ(0.0);
		BoundingBox testBoundingBox = bbBuilder.build();
		
		setBoundingBox(testBoundingBox);
	}
}
