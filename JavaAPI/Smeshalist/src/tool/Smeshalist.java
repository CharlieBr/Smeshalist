package tool;

import java.awt.Point;
import java.io.ByteArrayOutputStream;
import java.io.FileOutputStream;
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
import structDefinitions.Structures.Block;
import structDefinitions.Structures.BlockSet;
import structDefinitions.Structures.Edge;
import structDefinitions.Structures.EdgeSet;
import structDefinitions.Structures.Point3D;
import structDefinitions.Structures.Point3DSet;
import structDefinitions.Structures.TriangleFace;
import structDefinitions.Structures.TriangleFaceSet;
import structDefinitions.Structures.Vertex;
import structDefinitions.Structures.VertexSet;

public class Smeshalist {
	private static Smeshalist instance = new Smeshalist();
	int mainWindowPort;
	InetAddress IPAddress;
	DatagramSocket socket = null;

	Set<Point2D> points2D = new HashSet<>();
	Set<Point3D> points3D = new HashSet<>();
	Set<Vertex> vertexes = new HashSet<>();
	Set<Edge> edges = new HashSet<>();
	Set<TriangleFace> triangleFaces = new HashSet<>();
	Set<Block> blocks = new HashSet<>();
	
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
		points2D.add(builder.build());
	}
	
	public void addGeometry(geometry.Point3D point){
		points3D.add(convertToPoint3D(point));
	}
	
	public void addGeometry(geometry.Vertex vertex){
		Vertex.Builder builder = Vertex.newBuilder();
		builder.setPoint(convertToPoint3D(vertex.getPoint()));
		builder.setNumber(vertex.getNumber());
		vertexes.add(builder.build());
	}
	
	public void addGeometry(geometry.Edge edge){
		Edge.Builder builder = Edge.newBuilder();
		builder.setV1(convertToPoint3D(edge.getV1()));
		builder.setV2(convertToPoint3D(edge.getV2()));
		edges.add(builder.build());
	}
	
	public void addGeometry(geometry.TriangleFace triangleFace){
		TriangleFace.Builder builder = TriangleFace.newBuilder();
		builder.setV1(convertToPoint3D(triangleFace.getV1()));
		builder.setV2(convertToPoint3D(triangleFace.getV2()));
		builder.setV3(convertToPoint3D(triangleFace.getV3()));
		triangleFaces.add(builder.build());
	}
	
	public void addGeometry(geometry.Block block){
		Block.Builder builder = Block.newBuilder();
		builder.setV1(convertToPoint3D(block.getV1()));
		builder.setV2(convertToPoint3D(block.getV2()));
		builder.setV3(convertToPoint3D(block.getV3()));
		builder.setV4(convertToPoint3D(block.getV4()));
		blocks.add(builder.build());
	}

	/**
	 * send all structures stored in buffer to main window
	 */
	public void flushBuffer() {
		Point2DSet point2DSet = Point2DSet.newBuilder().addAllPoints(points2D).build();
		Point3DSet point3DSet = Point3DSet.newBuilder().addAllPoints(points3D).build();
		VertexSet vertexSet = VertexSet.newBuilder().addAllVertexes(vertexes).build();
		EdgeSet edgeSet = EdgeSet.newBuilder().addAllEdges(edges).build();
		TriangleFaceSet triangleFaceSet = TriangleFaceSet.newBuilder().addAllTriangleFaces(triangleFaces).build();
		BlockSet blockSet = BlockSet.newBuilder().addAllBlocks(blocks).build();
		
		ByteArrayOutputStream aOutput = new ByteArrayOutputStream(1024);
		try {
			point2DSet.writeTo(aOutput);
			byte[] bytes = aOutput.toByteArray();
			DatagramPacket packet = new DatagramPacket(bytes, bytes.length, IPAddress, mainWindowPort);
			socket.send(packet);
			aOutput.close();
			
			aOutput = new ByteArrayOutputStream(1024);
			point3DSet.writeTo(aOutput);
			bytes = aOutput.toByteArray();
			packet = new DatagramPacket(bytes, bytes.length, IPAddress, mainWindowPort);
			socket.send(packet);
			aOutput.close();
			
			aOutput = new ByteArrayOutputStream(1024);
			vertexSet.writeTo(aOutput);
			bytes = aOutput.toByteArray();
			packet = new DatagramPacket(bytes, bytes.length, IPAddress, mainWindowPort);
			socket.send(packet);
			aOutput.close();
			
			aOutput = new ByteArrayOutputStream(1024);
			edgeSet.writeTo(aOutput);
			bytes = aOutput.toByteArray();
			packet = new DatagramPacket(bytes, bytes.length, IPAddress, mainWindowPort);
			socket.send(packet);
			aOutput.close();
			
			aOutput = new ByteArrayOutputStream(1024);
			triangleFaceSet.writeTo(aOutput);
			bytes = aOutput.toByteArray();
			packet = new DatagramPacket(bytes, bytes.length, IPAddress, mainWindowPort);
			socket.send(packet);
			aOutput.close();
			
			aOutput = new ByteArrayOutputStream(1024);
			blockSet.writeTo(aOutput);
			bytes = aOutput.toByteArray();
			packet = new DatagramPacket(bytes, bytes.length, IPAddress, mainWindowPort);
			socket.send(packet);
			aOutput.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		points2D.clear();
	}
	
	private Point3D convertToPoint3D(geometry.Point3D point){
		Point3D.Builder builder = Point3D.newBuilder();
		builder.setX(point.getX());
		builder.setY(point.getY());
		builder.setZ(point.getZ());
		return builder.build();
	}
}
