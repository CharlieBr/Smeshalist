package geometry;

public class Point3D {

	private double x;
	private double y;
	private double z;
	private double quality;
	private String label;
	private int groupId;
	
	public Point3D(double x, double y, double z){
		setX(x);
		setY(y);
		setZ(z);
		quality = 0.0;
		label = "";
		groupId = 0;
	}
	
	
	public double getX() {
		return x;
	}
	
	public void setX(double x) {
		this.x = x;
	}
	
	public double getY() {
		return y;
	}
	
	public void setY(double y) {
		this.y = y;
	}
	
	public double getZ() {
		return z;
	}
	
	public void setZ(double z) {
		this.z = z;
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
