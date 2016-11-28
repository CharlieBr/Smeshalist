package geometry;

/**
 *
 * @author ewa
 *
 * Class which stores point coordinates. All other structure objects from geometry package use one or more Point3D
 * objects to build the structure.
 */
public class Point3D {
	private double x;
	private double y;
	private double z;
	
	/**
	 * 
	 * @param x the x coordinate
	 * @param y the y coordinate
	 * @param z the z coordinate
	 * Class constructor.
	 */
	public Point3D(double x, double y, double z) {
		setX(x);
		setY(y);
		setZ(z);
	}

	/**
	 * 
	 * @return x coordinate
	 */
	public double getX() {
		return x;
	}

	/**
	 * 
	 * @param x 
	 * Methods sets x coordinate of the object
	 */
	public void setX(double x) {
		this.x = x;
	}

	/**
	 * 
	 * @return y coordinate of the object 
	 */
	public double getY() {
		return y;
	}

	/**
	 * 
	 * @param y
	 * Method sets y coordinate of the object
	 */
	public void setY(double y) {
		this.y = y;
	}

	/**
	 * 
	 * @return z coordinate of the object
	 */
	public double getZ() {
		return z;
	}

	/**
	 * 
	 * @param z
	 * Method sets z coordinate of the object
	 */
	public void setZ(double z) {
		this.z = z;
	}

}
