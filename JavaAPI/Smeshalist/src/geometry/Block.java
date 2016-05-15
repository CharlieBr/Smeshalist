package geometry;

public class Block {

	private Point3D v1;
	private Point3D v2;
	private Point3D v3;
	private Point3D v4;
	
	
	public Block(Point3D v1, Point3D v2, Point3D v3, Point3D v4) {
		setV1(v1);
		setV2(v2);
		setV3(v3);
		setV4(v4);
		
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


	public Point3D getV4() {
		return v4;
	}


	public void setV4(Point3D v4) {
		this.v4 = v4;
	}
	
	
	
	
	
}
