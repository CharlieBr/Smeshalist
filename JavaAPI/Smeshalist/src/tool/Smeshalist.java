package tool;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

import geometry.Point2D;
import structDefinitions.Structures;
import structDefinitions.Structures.Block;
import structDefinitions.Structures.BlockSet;
import structDefinitions.Structures.Edge;
import structDefinitions.Structures.EdgeSet;
import structDefinitions.Structures.MessageInfo;
import structDefinitions.Structures.MessageInfo.Type;
import structDefinitions.Structures.Point3D;
import structDefinitions.Structures.Properties;
import structDefinitions.Structures.TriangleFace;
import structDefinitions.Structures.TriangleFaceSet;
import structDefinitions.Structures.Vertex;
import structDefinitions.Structures.VertexSet;
import helpers.SmeshialistHelper;

public class Smeshalist {
	private static Smeshalist instance = new Smeshalist();
	int mainWindowPort;
	InetAddress IPAddress;
	DatagramSocket socket = null;
	
	private double point2DSize;
	private double point3DSize;
	private double vertexSize;
	private double edgesSize;
	private double tiangleFacesSize;
	private double blocksSize;
	

	Set<Structures.Point2D> points2D = new HashSet<>();
	Set<Point3D> points3D = new HashSet<>();
	Set<Vertex> vertexes = new HashSet<>();
	Set<Edge> edges = new HashSet<>();
	Set<TriangleFace> triangleFaces = new HashSet<>();
	Set<Block> blocks = new HashSet<>();
	
	private Smeshalist() {
		mainWindowPort = 8383;
		countPoint2dSetSize();
		countPoint3DSetSize();
		countVertexesSize();
		countEdgeSize();
		countTriangleFaceSize();
		countBlockSize();
		
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

	public static void destroySmeshialist(){
		instance.socket.close();
	}
	
	public void addGeometry(geometry.Point2D point) {
		Properties.Builder prop = SmeshialistHelper.setProperties(point.getLabel(), point.getQuality(), point.getGroupId());
		Structures.Point2D.Builder builder = Structures.Point2D.newBuilder();
		builder.setX(point.getX());
		builder.setY(point.getY());
		builder.setProp(prop.build());
		points2D.add(builder.build());
	}
	
	public void addGeometry(geometry.Point3D point){
		points3D.add(SmeshialistHelper.convertToPoint3D(point));
	}
	
	public void addGeometry(geometry.Vertex vertex){
		Properties.Builder prop = SmeshialistHelper.setProperties(vertex.getLabel(), vertex.getQuality(), vertex.getGroupId());
		Vertex.Builder builder = Vertex.newBuilder();
		builder.setPoint(SmeshialistHelper.convertToPoint3D(vertex.getPoint()));
		builder.setNumber(vertex.getNumber());
		builder.setProp(prop.build());
		vertexes.add(builder.build());
	}
	
	public void addGeometry(geometry.Edge edge){
		Properties.Builder prop = SmeshialistHelper.setProperties(edge.getLabel(), edge.getQuality(), edge.getGroupId());
		Edge.Builder builder = Edge.newBuilder();
		builder.setV1(SmeshialistHelper.convertToPoint3D(edge.getV1()));
		builder.setV2(SmeshialistHelper.convertToPoint3D(edge.getV2()));
		builder.setProp(prop.build());
		edges.add(builder.build());
	}
	
	public void addGeometry(geometry.TriangleFace triangleFace){
		Properties.Builder prop = SmeshialistHelper.setProperties(triangleFace.getLabel(), triangleFace.getQuality(), triangleFace.getGroupId());
		TriangleFace.Builder builder = TriangleFace.newBuilder();
		builder.setV1(SmeshialistHelper.convertToPoint3D(triangleFace.getV1()));
		builder.setV2(SmeshialistHelper.convertToPoint3D(triangleFace.getV2()));
		builder.setV3(SmeshialistHelper.convertToPoint3D(triangleFace.getV3()));
		builder.setProp(prop.build());
		triangleFaces.add(builder.build());
	}
	
	public void addGeometry(geometry.Block block){
		Properties.Builder prop = SmeshialistHelper.setProperties(block.getLabel(), block.getQuality(), block.getGroupId());
		Block.Builder builder = Block.newBuilder();
		builder.setV1(SmeshialistHelper.convertToPoint3D(block.getV1()));
		builder.setV2(SmeshialistHelper.convertToPoint3D(block.getV2()));
		builder.setV3(SmeshialistHelper.convertToPoint3D(block.getV3()));
		builder.setV4(SmeshialistHelper.convertToPoint3D(block.getV4()));
		builder.setProp(prop.build());
		blocks.add(builder.build());
	}

	/**
	 * send all structures stored in buffer to main window
	 */
	public void flushBuffer() {
		Structures.Point2DSet point2DSet = Structures.Point2DSet.newBuilder().addAllPoints(points2D).build();
		Structures.Point3DSet point3DSet = Structures.Point3DSet.newBuilder().addAllPoints(points3D).build();
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
		points3D.clear();
		vertexes.clear();
		edges.clear();
		triangleFaces.clear();
		blocks.clear();
		
	}
	
	
	public void breakpoint(){
		ByteArrayOutputStream aOutput = new ByteArrayOutputStream(10);
		MessageInfo.Builder builder = MessageInfo.newBuilder();
		builder.setType(Type.BREAKPOINT);
		MessageInfo message = builder.build();
		
		try {
			message.writeTo(aOutput);
			byte[] bytes = aOutput.toByteArray();
			DatagramPacket packet = new DatagramPacket(bytes, bytes.length, IPAddress, mainWindowPort);
			socket.send(packet);
			aOutput.close();
			
			byte[] responseBytes = new byte[10];
			DatagramPacket response = new DatagramPacket(responseBytes, responseBytes.length);
			socket.receive(response);
	
			
			MessageInfo feedback = MessageInfo.parseFrom(response.getData());
			if(feedback.getType() == Type.REJECTED){
				socket.close();
				System.exit(0);
			}
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	
	public void render(){
		ByteArrayOutputStream aOutput = new ByteArrayOutputStream(10);
		MessageInfo.Builder builder = MessageInfo.newBuilder();
		builder.setType(Type.RENDER);
		MessageInfo message = builder.build();
		try {
			message.writeTo(aOutput);
			byte[] bytes = aOutput.toByteArray();
			DatagramPacket packet = new DatagramPacket(bytes, bytes.length, IPAddress, mainWindowPort);
			socket.send(packet);
			aOutput.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		
	}
	
	
	
	private void countPoint2dSetSize(){
		Random r = new Random();

		for (int i=0; i<10; i++) {
			Point2D point = new Point2D();
			point.setLocation(r.nextInt(5), r.nextInt(5));
			point.setGroupId(r.nextInt(100));
			point.setLabel("label");
			point.setQuality(r.nextDouble()*100);
			addGeometry(point);
		}
		
		Structures.Point2DSet point2DSet = Structures.Point2DSet.newBuilder().addAllPoints(points2D).build();
		int size = point2DSet.getSerializedSize();
		point2DSize = (double) size/10.0;
		points2D.clear();
		
		
	}
	
	
	private void countPoint3DSetSize(){
		Random r = new Random();

		for (int i=0; i<10; i++) {
			geometry.Point3D point = new geometry.Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			SmeshialistHelper.addExtraInfo(point);
			addGeometry(point);
		}
		
		Structures.Point3DSet point3DSet = Structures.Point3DSet.newBuilder().addAllPoints(points3D).build();
		int size = point3DSet.getSerializedSize();
		point3DSize = (double) size/10.0;
		points3D.clear();
		
	}
	
	private void countVertexesSize(){
		Random r = new Random();
		
		for (int i=0; i<10; i++) {
			geometry.Point3D point = new geometry.Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			SmeshialistHelper.addExtraInfo(point);			
			geometry.Vertex v = new geometry.Vertex(point, r.nextDouble()*10-5);
			v.setGroupId(r.nextInt(100));
			v.setLabel("label");
			v.setQuality(r.nextDouble()*100);
			addGeometry(v);
		}
		
		VertexSet vertexSet = VertexSet.newBuilder().addAllVertexes(vertexes).build();
		int size = vertexSet.getSerializedSize();
		vertexSize = (double) size/10.0;
		vertexes.clear();
		
	}
	
	private void countEdgeSize(){
		Random r = new Random();

		for (int i=0; i<10; i++) {
			geometry.Point3D v1 = new geometry.Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			SmeshialistHelper.addExtraInfo(v1);
			geometry.Point3D v2 = new geometry.Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			SmeshialistHelper.addExtraInfo(v2);
			geometry.Edge edge = new geometry.Edge(v1, v2);
			edge.setGroupId(r.nextInt(100));
			edge.setLabel("label");
			edge.setQuality(r.nextDouble()*100);
			addGeometry(edge);
		}
		
		EdgeSet edgeSet = EdgeSet.newBuilder().addAllEdges(edges).build();
		int size = edgeSet.getSerializedSize();
		edgesSize = (double) size/10.0;
		edges.clear();
		
	}
	
	
	public void countTriangleFaceSize(){
		Random r = new Random();

		for (int i = 0; i < 10; i++) {

			double d = r.nextDouble() * 10 - 5;
			geometry.Point3D v1 = new geometry.Point3D(d, d, d);
			SmeshialistHelper.addExtraInfo(v1);
			geometry.Point3D v2 = new geometry.Point3D(d - 0.5, d - 0.6, d - 0.7);
			SmeshialistHelper.addExtraInfo(v2);
			geometry.Point3D v3 = new geometry.Point3D(d + 0.8, d + 0.9, d);
			SmeshialistHelper.addExtraInfo(v3);
			geometry.TriangleFace tf = new geometry.TriangleFace(v1, v2, v3);
			tf.setGroupId(r.nextInt(100));
			tf.setLabel("label");
			tf.setQuality(r.nextDouble()*100);
			addGeometry(tf);

		}
		
		TriangleFaceSet triangleFaceSet = TriangleFaceSet.newBuilder().addAllTriangleFaces(triangleFaces).build();
		int size = triangleFaceSet.getSerializedSize();
		tiangleFacesSize = (double) size/10.0;
		triangleFaces.clear();
		
	}
	
	
	public void countBlockSize(){
		
		Random r = new Random();
		
		for (int i=0; i<2; i++) {
			geometry.Point3D v1 = new geometry.Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			SmeshialistHelper.addExtraInfo(v1);
			geometry.Point3D v2 = new geometry.Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			SmeshialistHelper.addExtraInfo(v2);
			geometry.Point3D v3 = new geometry.Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			SmeshialistHelper.addExtraInfo(v3);
			geometry.Point3D v4 = new geometry.Point3D(r.nextDouble()*10-5, r.nextDouble()*10-5, r.nextDouble()*10-5);
			SmeshialistHelper.addExtraInfo(v4);
			geometry.Block b = new geometry.Block(v1, v2, v3, v4);
			b.setGroupId(r.nextInt(100));
			b.setLabel("label");
			b.setQuality(r.nextDouble()*100);
			addGeometry(b);
		}
		
		
		BlockSet blockSet = BlockSet.newBuilder().addAllBlocks(blocks).build();
		int size = blockSet.getSerializedSize();
		blocksSize = (double) size/10.0;
		blocks.clear();
		
	}
	

}
