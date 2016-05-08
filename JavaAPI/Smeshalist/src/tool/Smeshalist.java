package tool;

import java.awt.Point;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.HashSet;
import java.util.Set;

import structDefinitions.Point2DJSON.Point2D;
import structDefinitions.Point2DJSON.Point2DSet;

public class Smeshalist {
	private static Smeshalist instance = new Smeshalist();
	int mainWindowPort;
	InetAddress IPAddress;
	DatagramSocket socket = null;

	Set<Point2D> points = new HashSet<>();

	private Smeshalist() {
		mainWindowPort = 8383;
		try {
			socket = new DatagramSocket();
			IPAddress = InetAddress.getByName("localhost");
		} catch (UnknownHostException | SocketException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 
	 * @return instance of Smeshalist. Tool is using localhost:8383 address to
	 *         connect to main window
	 */
	public static Smeshalist getInstance() {
		return instance;
	}

	public void addGeometry(Point point) {
		Point2D.Builder builder = Point2D.newBuilder();
		builder.setX(point.getX());
		builder.setY(point.getY());
		points.add(builder.build());
	}

	/**
	 * send all structures stored in buffer to main window
	 */
	public void flushBuffer() {
		Point2DSet pointSet = Point2DSet.newBuilder().addAllPoints(points).build();
		ByteArrayOutputStream aOutput = new ByteArrayOutputStream(1024);
		try {
			pointSet.writeTo(aOutput);
			byte[] bytes = aOutput.toByteArray();
			DatagramPacket packet = new DatagramPacket(bytes, bytes.length, IPAddress, mainWindowPort);
			socket.send(packet);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		points.clear();
	}
}
