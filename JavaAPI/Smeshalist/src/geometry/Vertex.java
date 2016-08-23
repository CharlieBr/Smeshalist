package geometry;

public class Vertex {
	private double number;
	private Point3D point;
	private double quality;
	private String label;
	private int groupId;

	public Vertex(Point3D point, double number) {
		setNumber(number);
		setPoint(point);
		quality = 0.0;
		label = "";
		groupId = 0;
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

	public double getQuality() {
		return quality;
	}

	public void setQuality(double quality) {
		this.quality = quality;
	}

	public String getLabel() {
		return label;
	}

	public void setLabel(String label) {
		this.label = label;
	}

	public int getGroupId() {
		return groupId;
	}

	public void setGroupId(int groupId) {
		this.groupId = groupId;
	}
}
