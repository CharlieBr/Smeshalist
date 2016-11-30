package geometry;

/**
 * @author ewa
 *
 * Class which provides internal application format for tetrahedron structure.
 * Objects consist of four Point3D points and properties: quality, label and groupId.
 */
public class Block {
	private Point3D v1;
	private Point3D v2;
	private Point3D v3;
	private Point3D v4;
	private double quality;
	private String label;
	private int groupId;

	/**
	 * 
	 * @param v1 first Point3D object
	 * @param v2 second Point3D object
	 * @param v3 third Point3D object
	 * @param v4 fourth Point3d object
	 * 
	 * Class constructor
	 */
	public Block(Point3D v1, Point3D v2, Point3D v3, Point3D v4) {
		setV1(v1);
		setV2(v2);
		setV3(v3);
		setV4(v4);
		quality = 0.0;
		label = "";
		groupId = 0;
	}

	/**
	 * 
	 * @return first Point3D object from which face structure is built
	 */
	public Point3D getV1() {
		return v1;
	}

	/**
	 * 
	 * @param v1 Point3D object to be set as a third point from which block is built
	 */
	public void setV1(Point3D v1) {
		this.v1 = v1;
	}

	/**
	 * 
	 * @return second Point3D object from which block structure is built
	 */
	public Point3D getV2() {
		return v2;
	}

	/**
	 * 
	 * @param v2 Point3D object to be set as a second point from which block is built
	 */
	public void setV2(Point3D v2) {
		this.v2 = v2;
	}

	/**
	 * 
	 * @return third Point3D object from which block structure is built
	 */
	public Point3D getV3() {
		return v3;
	}

	/**
	 * 
	 * @param v3 Point3D object to be set as a third point from which block is built
	 */
	public void setV3(Point3D v3) {
		this.v3 = v3;
	}

	/**
	 * 
	 * @return fourth Point3D object from which block structure is built
	 */
	public Point3D getV4() {
		return v4;
	}

	/**
	 * 
	 * @param v4 Point3D object to be set as a fourth point from which block is built
	 */
	public void setV4(Point3D v4) {
		this.v4 = v4;
	}

	/**
	 * 
	 * @return quality set for this object
	 */
	public double getQuality() {
		return quality;
	}

	/**
	 * 
	 * @param quality
	 * Sets the quality of the block structure
	 */
	public void setQuality(double quality) {
		this.quality = quality;
	}

	/**
	 * 
	 * @return label which is set for this object
	 */
	public String getLabel() {
		return label;
	}

	/**
	 * 
	 * @param label
	 * Sets the string label of the block structure
	 */
	public void setLabel(String label) {
		this.label = label;
	}

	/**
	 * 
	 * @return group ID to which structure belongs
	 */
	public int getGroupId() {
		return groupId;
	}

	/**
	 * 
	 * @param groupId Set group ID for the object
	 */
	public void setGroupId(int groupId) {
		this.groupId = groupId;
	}
}
