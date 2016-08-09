package util;

import communication.Communication.ComparisonOperator ;
import communication.Communication.QualityCondition;
import window.FiltersTab;

import javax.swing.*;

public class QualityEntry extends JPanel {

	private String leftValue;
	private String leftOperator;
	private String rightValue;
	private String rightOperator;

	public QualityEntry(String leftValue, String leftOperator, String rightValue, String rightOperator){
		this.leftValue = leftValue;
		this.leftOperator = leftOperator;
		this.rightValue = rightValue;
		this.rightOperator = rightOperator;

		this.initializeJPanel();
		this.setVisible(true);
	}

	private void initializeJPanel() {
		if (leftValue.compareTo("") != 0){
			this.add(new JLabel(leftValue));
			this.add(new JLabel(leftOperator));
		}
		this.add(new JLabel("QUALITY"));
		if (rightValue.compareTo("") != 0){
			this.add(new JLabel(rightOperator));
			this.add(new JLabel(rightValue));
		}
		this.add(Box.createHorizontalStrut(50));
		this.add(Box.createHorizontalGlue());
	}

	public QualityCondition getQualityCondition(){
		QualityCondition.Builder qualityConditionBuilder = QualityCondition.newBuilder();
		if (leftValue.compareTo("") != 0){
			qualityConditionBuilder.setLeftValue(new Double(leftValue));
			qualityConditionBuilder.setLeftOperator(FiltersTab.getComparisonOperator(leftOperator));
		}
		if (rightValue.compareTo("") != 0){
			qualityConditionBuilder.setLeftValue(new Double(rightValue));
			qualityConditionBuilder.setLeftOperator(FiltersTab.getComparisonOperator(rightOperator));
		}
		return qualityConditionBuilder.build();
	}

}
