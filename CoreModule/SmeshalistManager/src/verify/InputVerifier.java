package verify;

import javax.swing.JComboBox;
import javax.swing.JTextField;

public class InputVerifier {

	public static boolean verifyQualityInput(JTextField v1TextField, JComboBox<String> v1ComboBox, JTextField v2TextField, JComboBox<String> v2ComboBox) {
		String v1Text = v1TextField.getText();
		String v2Text = v2TextField.getText();
		String comparator1 = v1ComboBox.getSelectedItem().toString();
		String comparator2 = v2ComboBox.getSelectedItem().toString();

		try{
			if ((v1Text.compareTo("") == 0) ^ (v2Text.compareTo("") == 0)){
				String vText = v1Text + v2Text;
				Double v = new Double(vText);
				return true;

			} else {
				Double v1 = new Double(v1Text);
				Double v2 = new Double(v2Text);

				if (comparator1.compareTo("=") == 0){
					if (comparator2.compareTo("=") == 0){
						return v1.compareTo(v2) == 0;
					} else {
						return false;
					}
				}

				return v1.compareTo(v2) < 0;
			}

		}catch(NumberFormatException e){
			return false;
		}

	}

	public static boolean verifyCoordinatesInput(JTextField valueTextField,
			JTextField xTextField, JTextField yTextField, JTextField zTextField) {
		
		String valueText = valueTextField.getText();
		String xText = xTextField.getText();
		String yText = yTextField.getText();
		String zText = zTextField.getText();

		try{
			new Double(valueText);
			new Double(xText);
			new Double(yText);
			new Double(zText);
			
			return true;
			
			
		}catch(NumberFormatException e){
			return false;
		}
		
		
	}

}
