package tool;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.Set;

import javax.management.timer.TimerNotification;

import geometry.Point2D;
import helpers.SmeshalistHelper;
import structDefinitions.Structures;
import structDefinitions.Structures.Block;
import structDefinitions.Structures.BlockSet;
import structDefinitions.Structures.DataPackage;
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

public class Smeshalist {
	private static Smeshalist instance = new Smeshalist();
	int mainWindowPort;
	InetAddress IPAddress;
	DatagramSocket socket = null;

	private int point2DSize;
	private int point3DSize;
	private int vertexSize;
	private int edgesSize;
	private int tiangleFacesSize;
	private int blocksSize;

	List<Structures.Point2D> points2D = new LinkedList<>();
	List<Point3D> points3D = new LinkedList<>();
	List<Vertex> vertexes = new LinkedList<>();
	List<Edge> edges = new LinkedList<>();
	List<TriangleFace> triangleFaces = new LinkedList<>();
	List<Block> blocks = new LinkedList<>();

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

	public static void destroySmeshialist() {
		instance.socket.close();
	}

	public void addGeometry(geometry.Point2D point) {
		Properties.Builder prop = SmeshalistHelper.setProperties(point.getLabel(), point.getQuality(),
				point.getGroupId());
		Structures.Point2D.Builder builder = Structures.Point2D.newBuilder();
		builder.setX(point.getX());
		builder.setY(point.getY());
		builder.setProp(prop.build());
		points2D.add(builder.build());
	}

	public void addGeometry(geometry.Point3D point) {
		points3D.add(SmeshalistHelper.convertToPoint3D(point));
	}

	public void addGeometry(geometry.Vertex vertex) {
		Properties.Builder prop = SmeshalistHelper.setProperties(vertex.getLabel(), vertex.getQuality(),
				vertex.getGroupId());
		Vertex.Builder builder = Vertex.newBuilder();
		builder.setPoint(SmeshalistHelper.convertToPoint3D(vertex.getPoint()));
		builder.setNumber(vertex.getNumber());
		builder.setProp(prop.build());
		vertexes.add(builder.build());
	}

	public void addGeometry(geometry.Edge edge) {
		Properties.Builder prop = SmeshalistHelper.setProperties(edge.getLabel(), edge.getQuality(), edge.getGroupId());
		Edge.Builder builder = Edge.newBuilder();
		builder.setV1(SmeshalistHelper.convertToPoint3D(edge.getV1()));
		builder.setV2(SmeshalistHelper.convertToPoint3D(edge.getV2()));
		builder.setProp(prop.build());
		edges.add(builder.build());
	}

	public void addGeometry(geometry.TriangleFace triangleFace) {
		Properties.Builder prop = SmeshalistHelper.setProperties(triangleFace.getLabel(), triangleFace.getQuality(),
				triangleFace.getGroupId());
		TriangleFace.Builder builder = TriangleFace.newBuilder();
		builder.setV1(SmeshalistHelper.convertToPoint3D(triangleFace.getV1()));
		builder.setV2(SmeshalistHelper.convertToPoint3D(triangleFace.getV2()));
		builder.setV3(SmeshalistHelper.convertToPoint3D(triangleFace.getV3()));
		builder.setProp(prop.build());
		triangleFaces.add(builder.build());
	}

	public void addGeometry(geometry.Block block) {
		Properties.Builder prop = SmeshalistHelper.setProperties(block.getLabel(), block.getQuality(),
				block.getGroupId());
		Block.Builder builder = Block.newBuilder();
		builder.setV1(SmeshalistHelper.convertToPoint3D(block.getV1()));
		builder.setV2(SmeshalistHelper.convertToPoint3D(block.getV2()));
		builder.setV3(SmeshalistHelper.convertToPoint3D(block.getV3()));
		builder.setV4(SmeshalistHelper.convertToPoint3D(block.getV4()));
		builder.setProp(prop.build());
		blocks.add(builder.build());
	}

	
	/**
	 * send all structures stored in buffer to main window
	 */
	public void flushBuffer() {
		int bytesLeft = 1024;
		boolean sended = false;
		ByteArrayOutputStream aOutput = new ByteArrayOutputStream(10);

		MessageInfo.Builder builder = MessageInfo.newBuilder();
		builder.setType(Type.DATA);
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
			if (feedback.getType() == Type.ACK) {
				List<Structures.Point2D> sendedPoints2D = new LinkedList<>();
				List<Structures.Point3D> sendedPoints3D = new LinkedList<>();
				List<Structures.Vertex> sendedVertexes = new LinkedList<>();
				List<Structures.TriangleFace> sendedFaces = new LinkedList<>();
				List<Structures.Edge> sendedEdges = new LinkedList<>();
				List<Structures.Block> sendedBlocks = new LinkedList<>();

				while (!sended) {
					while (bytesLeft >= point2DSize && !points2D.isEmpty()) {
						sendedPoints2D.add(points2D.remove(0));
						bytesLeft -= point2DSize;
					}

					while (bytesLeft >= point3DSize && !points3D.isEmpty()) {
						sendedPoints3D.add(points3D.remove(0));
						bytesLeft -= point3DSize;
					}

					while (bytesLeft >= vertexSize && !vertexes.isEmpty()) {
						sendedVertexes.add(vertexes.remove(0));
						bytesLeft -= vertexSize;
					}

					while (bytesLeft >= edgesSize && !edges.isEmpty()) {
						sendedEdges.add(edges.remove(0));
						bytesLeft -= edgesSize;
					}

					while (bytesLeft >= tiangleFacesSize && !triangleFaces.isEmpty()) {
						sendedFaces.add(triangleFaces.remove(0));
						bytesLeft -= tiangleFacesSize;
					}

					while (bytesLeft >= blocksSize && !blocks.isEmpty()) {
						sendedBlocks.add(blocks.remove(0));
						bytesLeft -= blocksSize;
					}

					DataPackage.Builder data = DataPackage.newBuilder();

					if (!sendedPoints2D.isEmpty()) {
						data.setPoints2D(Structures.Point2DSet.newBuilder().addAllPoints(sendedPoints2D).build());
					}

					if (!sendedPoints3D.isEmpty()) {
						data.setPoints3D(Structures.Point3DSet.newBuilder().addAllPoints(sendedPoints3D).build());
					}

					if (!sendedVertexes.isEmpty()) {
						data.setVertexes(VertexSet.newBuilder().addAllVertexes(sendedVertexes).build());
					}

					if (!sendedEdges.isEmpty()) {
						data.setEdges(EdgeSet.newBuilder().addAllEdges(sendedEdges).build());
					}

					if (!sendedFaces.isEmpty()) {
						data.setFaces(TriangleFaceSet.newBuilder().addAllTriangleFaces(sendedFaces).build());
					}

					if (!sendedBlocks.isEmpty()) {
						data.setBlocks(BlockSet.newBuilder().addAllBlocks(sendedBlocks).build());
					}
					
					if (points2D.isEmpty() && points3D.isEmpty() && vertexes.isEmpty() && edges.isEmpty()
							&& triangleFaces.isEmpty() && blocks.isEmpty()) {
						sended = true;
						data.setEndOfData(true);

					} else {
						bytesLeft = 1024;
						data.setEndOfData(false);
					}
					
					aOutput = new ByteArrayOutputStream(1024);
					data.build().writeTo(aOutput);
					bytes = aOutput.toByteArray();
					packet = new DatagramPacket(bytes, bytes.length, IPAddress, mainWindowPort);
					socket.send(packet);
					aOutput.close();

					sendedPoints2D.clear();
					sendedPoints3D.clear();
					sendedVertexes.clear();
					sendedFaces.clear();
					sendedEdges.clear();
					sendedBlocks.clear();
				}

			}

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	
	

	public void breakpoint() {
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
			if (feedback.getType() == Type.REJECTED) {
				socket.close();
				System.exit(0);
			}

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	public void render() {
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

	private void countPoint2dSetSize() {
		Random r = new Random();

		for (int i = 0; i < 10; i++) {
			Point2D point = new Point2D();
			point.setLocation(r.nextInt(5), r.nextInt(5));
			point.setGroupId(r.nextInt(100));
			point.setLabel("label");
			point.setQuality(r.nextDouble() * 100);
			addGeometry(point);
		}

		Structures.Point2DSet point2DSet = Structures.Point2DSet.newBuilder().addAllPoints(points2D).build();
		int size = point2DSet.getSerializedSize();
		point2DSize = size / 10;
		points2D.clear();

	}

	private void countPoint3DSetSize() {
		Random r = new Random();

		for (int i = 0; i < 10; i++) {
			geometry.Point3D point = new geometry.Point3D(r.nextDouble() * 10 - 5, r.nextDouble() * 10 - 5,
					r.nextDouble() * 10 - 5);
			SmeshalistHelper.addExtraInfo(point);
			addGeometry(point);
		}

		Structures.Point3DSet point3DSet = Structures.Point3DSet.newBuilder().addAllPoints(points3D).build();
		int size = point3DSet.getSerializedSize();
		point3DSize = size / 10;
		points3D.clear();

	}

	private void countVertexesSize() {
		Random r = new Random();

		for (int i = 0; i < 10; i++) {
			geometry.Point3D point = new geometry.Point3D(r.nextDouble() * 10 - 5, r.nextDouble() * 10 - 5,
					r.nextDouble() * 10 - 5);
			SmeshalistHelper.addExtraInfo(point);
			geometry.Vertex v = new geometry.Vertex(point, r.nextDouble() * 10 - 5);
			v.setGroupId(r.nextInt(100));
			v.setLabel("label");
			v.setQuality(r.nextDouble() * 100);
			addGeometry(v);
		}

		VertexSet vertexSet = VertexSet.newBuilder().addAllVertexes(vertexes).build();
		int size = vertexSet.getSerializedSize();
		vertexSize = size / 10;
		vertexes.clear();

	}

	private void countEdgeSize() {
		Random r = new Random();

		for (int i = 0; i < 10; i++) {
			geometry.Point3D v1 = new geometry.Point3D(r.nextDouble() * 10 - 5, r.nextDouble() * 10 - 5,
					r.nextDouble() * 10 - 5);
			SmeshalistHelper.addExtraInfo(v1);
			geometry.Point3D v2 = new geometry.Point3D(r.nextDouble() * 10 - 5, r.nextDouble() * 10 - 5,
					r.nextDouble() * 10 - 5);
			SmeshalistHelper.addExtraInfo(v2);
			geometry.Edge edge = new geometry.Edge(v1, v2);
			edge.setGroupId(r.nextInt(100));
			edge.setLabel("label");
			edge.setQuality(r.nextDouble() * 100);
			addGeometry(edge);
		}

		EdgeSet edgeSet = EdgeSet.newBuilder().addAllEdges(edges).build();
		int size = edgeSet.getSerializedSize();
		edgesSize = size / 10;
		edges.clear();

	}

	public void countTriangleFaceSize() {
		Random r = new Random();

		for (int i = 0; i < 10; i++) {

			double d = r.nextDouble() * 10 - 5;
			geometry.Point3D v1 = new geometry.Point3D(d, d, d);
			SmeshalistHelper.addExtraInfo(v1);
			geometry.Point3D v2 = new geometry.Point3D(d - 0.5, d - 0.6, d - 0.7);
			SmeshalistHelper.addExtraInfo(v2);
			geometry.Point3D v3 = new geometry.Point3D(d + 0.8, d + 0.9, d);
			SmeshalistHelper.addExtraInfo(v3);
			geometry.TriangleFace tf = new geometry.TriangleFace(v1, v2, v3);
			tf.setGroupId(r.nextInt(100));
			tf.setLabel("label");
			tf.setQuality(r.nextDouble() * 100);
			addGeometry(tf);

		}

		TriangleFaceSet triangleFaceSet = TriangleFaceSet.newBuilder().addAllTriangleFaces(triangleFaces).build();
		int size = triangleFaceSet.getSerializedSize();
		tiangleFacesSize = size / 10;
		triangleFaces.clear();

	}

	public void countBlockSize() {

		Random r = new Random();

		for (int i = 0; i < 2; i++) {
			geometry.Point3D v1 = new geometry.Point3D(r.nextDouble() * 10 - 5, r.nextDouble() * 10 - 5,
					r.nextDouble() * 10 - 5);
			SmeshalistHelper.addExtraInfo(v1);
			geometry.Point3D v2 = new geometry.Point3D(r.nextDouble() * 10 - 5, r.nextDouble() * 10 - 5,
					r.nextDouble() * 10 - 5);
			SmeshalistHelper.addExtraInfo(v2);
			geometry.Point3D v3 = new geometry.Point3D(r.nextDouble() * 10 - 5, r.nextDouble() * 10 - 5,
					r.nextDouble() * 10 - 5);
			SmeshalistHelper.addExtraInfo(v3);
			geometry.Point3D v4 = new geometry.Point3D(r.nextDouble() * 10 - 5, r.nextDouble() * 10 - 5,
					r.nextDouble() * 10 - 5);
			SmeshalistHelper.addExtraInfo(v4);
			geometry.Block b = new geometry.Block(v1, v2, v3, v4);
			b.setGroupId(r.nextInt(100));
			b.setLabel("label");
			b.setQuality(r.nextDouble() * 100);
			addGeometry(b);
		}

		BlockSet blockSet = BlockSet.newBuilder().addAllBlocks(blocks).build();
		int size = blockSet.getSerializedSize();
		blocksSize = size / 10;
		blocks.clear();

	}

}
