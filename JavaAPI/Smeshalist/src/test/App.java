package test;

import java.awt.Point;
import java.util.Random;

import tool.Smeshalist;

public class App {

	public static void main(String[] args) {
		Smeshalist tool = Smeshalist.getInstance();
		Random r = new Random();

		for (int i=0; i<10; i++) {
			Point point = new Point(r.nextInt(100), r.nextInt(100));
			tool.addGeometry(point);
		}
		
		tool.flushBuffer();
	}

}
