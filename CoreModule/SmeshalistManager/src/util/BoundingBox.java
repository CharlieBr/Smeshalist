package util;

public class BoundingBox {
	private double fromX;
	private double toX;
	private double fromY;
	private double toY;
	private double fromZ;
	private double toZ;
	
	
	
	public BoundingBox(double fromX, double toX, double fromY, double toY, double fromZ, double toZ) {
		super();
		this.fromX = fromX;
		this.toX = toX;
		this.fromY = fromY;
		this.toY = toY;
		this.fromZ = fromZ;
		this.toZ = toZ;
	}
	
	
	public double getFromX() {
		return fromX;
	}
	public void setFromX(double fromX) {
		this.fromX = fromX;
	}
	public double getToX() {
		return toX;
	}
	public void setToX(double toX) {
		this.toX = toX;
	}
	public double getFromY() {
		return fromY;
	}
	public void setFromY(double fromY) {
		this.fromY = fromY;
	}
	public double getToY() {
		return toY;
	}
	public void setToY(double toY) {
		this.toY = toY;
	}
	public double getFromZ() {
		return fromZ;
	}
	public void setFromZ(double fromZ) {
		this.fromZ = fromZ;
	}
	public double getToZ() {
		return toZ;
	}
	public void setToZ(double toZ) {
		this.toZ = toZ;
	}
	
	
}
