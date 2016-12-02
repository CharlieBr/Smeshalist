package geometry;

/**
 * 
 * @author ewa
 *
 * Class which provides internal application format for face structure.
 * Objects consist of three Point3D points and properties: quality, label and groupId.
 */
public class TriangleFace {
	private Point3D v1;
	private Point3D v2;
	private Point3D v3;
	private double quality;
	private String label;
	private int groupId;

	/**
	 * 
	 * @param v1 first Point3D object
	 * @param v2 second Point3D object
	 * @param v3 third Point3D object
	 * 
	 * Class constructor
	 */
	public TriangleFace(Point3D v1, Point3D v2, Point3D v3) {
		setV1(v1);
		setV2(v2);
		setV3(v3);
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
	 * @param v1 Point3D object to be set as a first point from which face is built
	 */
	public void setV1(Point3D v1) {
		this.v1 = v1;
	}

	/**
	 * 
	 * @return second Point3D object from which face structure is built
	 */
	public Point3D getV2() {
		return v2;
	}

	/**
	 * 
	 * @param v1 Point3D object to be set as a second point from which face is built
	 */
	public void setV2(Point3D v2) {
		this.v2 = v2;
	}

	/**
	 * 
	 * @return third Point3D object from which face structure is built
	 */
	public Point3D getV3() {
		return v3;
	}

	/**
	 * 
	 * @param v1 Point3D object to be set as a third point from which face is built
	 */
	public void setV3(Point3D v3) {
		this.v3 = v3;
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
	 * Sets the quality of the face structure
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
	 * Sets the string label of the face structure
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
	 * @param groupId
	 * Set group ID for the object
	 */
	public void setGroupId(int groupId) {
		this.groupId = groupId;
	}
}
