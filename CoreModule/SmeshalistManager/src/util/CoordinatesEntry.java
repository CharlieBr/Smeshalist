package util;

import communication.Communication.CoordinatesCondition;
import window.FiltersTab;

import javax.swing.*;

public class CoordinatesEntry extends JPanel {

    private String x;
    private String y;
    private String z;
    private String operator;
    private String constant;

    public CoordinatesEntry(String x, String y, String z, String operator, String constant) {
        this.x = x;
        this.y = y;
        this.z = z;
        this.operator = operator;
        this.constant = constant;

        this.initializeJPanel();
        this.setVisible(true);
    }

    public CoordinatesCondition getCoordinatesCondition(){
        CoordinatesCondition.Builder coordinatesConditionBuilder = CoordinatesCondition.newBuilder();
        if (x.compareTo("") == 0){
            coordinatesConditionBuilder.setXValue(0.0);
        } else {
            coordinatesConditionBuilder.setXValue(new Double(x));
        }
        if (y.compareTo("") == 0){
            coordinatesConditionBuilder.setYValue(0.0);
        } else {
            coordinatesConditionBuilder.setYValue(new Double(y));
        }
        if (z.compareTo("") == 0){
            coordinatesConditionBuilder.setZValue(0.0);
        } else {
            coordinatesConditionBuilder.setZValue(new Double(z));
        }
        coordinatesConditionBuilder.setCoordinatesOperator(FiltersTab.getComparisonOperator(operator));
        coordinatesConditionBuilder.setConstant(new Double(constant));

        return coordinatesConditionBuilder.build();
    }

    private void initializeJPanel() {
        this.add(new JLabel(x + "x"));
        if (new Double(y) >= 0){
            this.add(new JLabel("+" + y + "y"));
        } else {
            this.add(new JLabel(y + "y"));
        }
        if (new Double(z) >= 0){
            this.add(new JLabel("+" + z + "z"));
        } else {
            this.add(new JLabel(z + "z"));
        }
        this.add(new JLabel(operator));
        this.add(new JLabel(constant));
        this.add(Box.createHorizontalStrut(50));
    }
}
