package test;

import java.util.Random;

import geometry.Edge;
import geometry.Point2D;
import geometry.Point3D;
import geometry.TriangleFace;
import geometry.Vertex;
import geometry.Block;
import tool.Smeshalist;

public class App {

	public static void main(String[] args) {
		Smeshalist tool = Smeshalist.getInstance(8383);
		Random r = new Random();

		for (int i=0; i<10; i++) {
			Point2D point = new Point2D();
			point.setLocation(r.nextInt(5), r.nextInt(5));
			point.setGroupId(1);
			tool.addGeometry(point);
		}

		for (int i=0; i<10000; i++) {
			Point3D point = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			point.setGroupId(2);
			tool.addGeometry(point);
		}
		
		for (int i=0; i<10; i++) {
			Vertex v = new Vertex(new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5), r.nextDouble()*10-5);
			v.setGroupId(3);		
			tool.addGeometry(v);
		}
		
		for (int i=0; i<10; i++) {
			Point3D v1 = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			Point3D v2 = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			Edge edge = new Edge(v1, v2);
			edge.setGroupId(4);
			tool.addGeometry(edge);
		}
		
		for (int i=0; i<10; i++) {
			double d = r.nextDouble()*10-5;
			Point3D v1 = new Point3D(d, d, d);
			Point3D v2 = new Point3D(d-0.5, d-0.6, d-0.7);
			Point3D v3 = new Point3D(d+0.8, d+0.9, d);
			TriangleFace tf = new TriangleFace(v1, v2, v3);
			tf.setGroupId(5);
			tool.addGeometry(tf);
		}
		
		for (int i=0; i<2; i++) {
			Point3D v1 = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			Point3D v2 = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			Point3D v3 = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			Point3D v4 = new Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			Block b = new Block(v1, v2, v3, v4);
			b.setGroupId(6);
			tool.addGeometry(b);
		}
		
		System.out.println("Flush...");
		tool.flushBuffer();
		System.out.println("Render..");
		tool.render();
		System.out.println("Breakpoint...");
		tool.breakpoint();
		System.out.println("Destroy...");
		Smeshalist.destroySmeshialist();
		
	}

}
