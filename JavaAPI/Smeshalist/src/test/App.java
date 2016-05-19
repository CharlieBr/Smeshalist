package test;

import java.awt.Point;
import java.util.Random;

import geometry.*;
import tool.Smeshalist;

public class App {

	public static void main(String[] args) {
		Smeshalist tool = Smeshalist.getInstance();
		Random r = new Random();

		for (int i=0; i<10; i++) {
			Point point = new Point(r.nextInt(5), r.nextInt(5));
			tool.addGeometry(point);
		}
		
		for (int i=0; i<10; i++) {
			Point3D point = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			tool.addGeometry(point);
		}
		
		for (int i=0; i<10; i++) {
			Vertex v = new Vertex(new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5), r.nextDouble()*10-5);
			tool.addGeometry(v);
		}
		
		for (int i=0; i<10; i++) {
			Point3D v1 = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			Point3D v2 = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			Edge edge = new Edge(v1, v2);
			tool.addGeometry(edge);
		}
		
		for (int i=0; i<10; i++) {
			double d = r.nextDouble()*10-5;
			Point3D v1 = new Point3D(d, d, d);
			Point3D v2 = new Point3D(d-0.5, d-0.6, d-0.7);
			Point3D v3 = new Point3D(d+0.8, d+0.9, d);
			TriangleFace tf = new TriangleFace(v1, v2, v3);
			tool.addGeometry(tf);
		}
		
		for (int i=0; i<2; i++) {
			Point3D v1 = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			Point3D v2 = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			Point3D v3 = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			Point3D v4 = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			Block b = new Block(v1, v2, v3, v4);
			tool.addGeometry(b);
		}
		
		tool.flushBuffer();
	}

}
