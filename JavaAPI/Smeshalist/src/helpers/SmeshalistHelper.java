package helpers;

import java.util.Random;

import structDefinitions.Structures.Point3D;
import structDefinitions.Structures.Properties;

public class SmeshalistHelper {

	public static Properties.Builder setProperties(String label, double quality, int groupId){
		Properties.Builder prop = Properties.newBuilder();
		prop.setGroupId(groupId);
		prop.setLabel(label);
		prop.setQuality(quality);
		
		return prop;
	}
	
	public static Point3D convertToPoint3D(geometry.Point3D point){
		Properties.Builder prop = setProperties(point.getLabel(), point.getQuality(), point.getGroupId());
		Point3D.Builder builder = Point3D.newBuilder();
		builder.setX(point.getX());
		builder.setY(point.getY());
		builder.setZ(point.getZ());
		builder.setProp(prop.build());
		return builder.build();
	}
	
	public static void addExtraInfo(geometry.Point3D point){
		Random rand = new Random();
		point.setGroupId(rand.nextInt(100));
		point.setLabel("label");
		point.setQuality(rand.nextDouble() * 100);

	}
}
