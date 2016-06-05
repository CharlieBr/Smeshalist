package hello;

import javax.swing.JFrame;
import javax.swing.JLabel;

public class HelloWorld extends JFrame{

	private static final long serialVersionUID = 5545012903831096347L;

	HelloWorld() {

        JLabel jlbHelloWorld = new JLabel("Hello World");

        add(jlbHelloWorld);
        
        this.setSize(100,100);

        setVisible(true);
	}
	
	public static void main(String[] args){
		new HelloWorld();
	}
}
