package main;

import window.MainWindow;

import javax.swing.UnsupportedLookAndFeelException;

public class Main {

	public static void main(String[] args) {

		try {
			MainWindow.setLookAndFeel();
		} catch (ClassNotFoundException | InstantiationException | UnsupportedLookAndFeelException | IllegalAccessException e) {
			System.out.println("Could not set LookAndFeel.\n" + e.getMessage());
		}

		MainWindow.getInstance();

	}
}
