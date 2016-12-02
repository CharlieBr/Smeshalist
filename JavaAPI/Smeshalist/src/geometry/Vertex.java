package geometry;

/**
 * 
 * @author ewa
 *
 * Class which provides internal application format for vertex structure.
 * Objects consist of Point3D point and properties: quality, label and groupId
 */
public class Vertex {
	private Point3D point;
	private double quality;
	private String label;
	private int groupId;

	/**
	 * 
	 * @param point Point3D object
	 * Class constructor
	 */
	public Vertex(Point3D point) {
		setPoint(point);
		quality = 0.0;
		label = "";
		groupId = 0;
	}

	/**
	 * 
	 * @return Point3D object from which vertex is built
	 */
	public Point3D getPoint() {
		return point;
	}

	/**
	 * 
	 * @param point Point3D object
	 * Sets point from which vertex structure will be built
	 */
	public void setPoint(Point3D point) {
		this.point = point;
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
	 * Sets the quality of the vertex structure
	 */
	public void setQuality(double quality) {
		this.quality = quality;
	}

	/**
	 * 
	 * @return label set for this object
	 */
	public String getLabel() {
		return label;
	}

	/**
	 * 
	 * @param label
	 * Sets string label for vertex structure
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
	 * Set the group ID for the object
	 */
	public void setGroupId(int groupId) {
		this.groupId = groupId;
	}
}
