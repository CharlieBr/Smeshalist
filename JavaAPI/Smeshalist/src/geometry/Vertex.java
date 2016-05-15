package geometry;

public class Vertex {
	private double number;
	private Point3D point;
	
	
	public Vertex(Point3D point, double number) {
		setNumber(number);
		setPoint(point);
	}
	
	
	public double getNumber() {
		return number;
	}
	
	public void setNumber(double number) {
		this.number = number;
	}
	
	public Point3D getPoint() {
		return point;
	}
	
	public void setPoint(Point3D point) {
		this.point = point;
	}
	
	

}
