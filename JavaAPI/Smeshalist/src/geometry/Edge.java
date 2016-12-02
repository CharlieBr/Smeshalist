package geometry;

/**
 * 
 * @author ewa
 * 
 * Class which provides internal application format for line structure.
 * Objects consist of two Point3D points and properties: quality, label and groupId.
 */
public class Edge {
	private Point3D v1;
	private Point3D v2;
	private double quality;
	private String label;
	private int groupId;

	/**
	 * 
	 * @param v1 first Point3D object
	 * @param v2 second Point3D object
	 * 
	 * Class constructor.
	 */
	public Edge(Point3D v1, Point3D v2) {
		setV1(v1);
		setV2(v2);
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
	 * @param v1 Point3D object to be set as a first point from which edge is built
	 */
	public void setV1(Point3D v1) {
		this.v1 = v1;
	}

	/**
	 * 
	 * @return second Point3D object from which edge structure is built
	 */
	public Point3D getV2() {
		return v2;
	}

	/**
	 * 
	 * @param v2 Point3D object to be set as a second point from which edge is built
	 */
	public void setV2(Point3D v2) {
		this.v2 = v2;
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
	 * Sets the quality of the edge structure
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
	 * Sets the string label of the edge structure
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
