package geometry;

public class TriangleFace {
	
	private Point3D v1;
	private Point3D v2;
	private Point3D v3;
	private double quality;
	private String label;
	private int groupId;
	
	public TriangleFace(Point3D v1, Point3D v2, Point3D v3) {
		setV1(v1);
		setV2(v2);
		setV3(v3);
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
	
	public Point3D getV3() {
		return v3;
	}
	
	public void setV3(Point3D v3) {
		this.v3 = v3;
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
