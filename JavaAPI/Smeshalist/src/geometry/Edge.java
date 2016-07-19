package geometry;

public class Edge {
	
	private Point3D v1;
	private Point3D v2;
	private double quality;
	private String label;
	private int groupId;
	
	
	public Edge(Point3D v1, Point3D v2) {
		setV1(v1);
		setV2(v2);
		quality = 0.0;
		label = "";
		groupId = 0;
	}


	public Point3D getV1() {
		return v1;
	}


	public void setV1(Point3D v1) {
		this.v1 = v1;
	}


	public Point3D getV2() {
		return v2;
	}


	public void setV2(Point3D v2) {
		this.v2 = v2;
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
