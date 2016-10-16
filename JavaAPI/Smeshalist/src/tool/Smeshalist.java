package tool;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

import helpers.SmeshalistHelper;
import structDefinitions.Structures;
import structDefinitions.Structures.Block;
import structDefinitions.Structures.DataPackage;
import structDefinitions.Structures.Edge;
import structDefinitions.Structures.Header;
import structDefinitions.Structures.MessageInfo;
import structDefinitions.Structures.MessageInfo.Type;
import structDefinitions.Structures.Point2D;
import structDefinitions.Structures.Point3D;
import structDefinitions.Structures.Properties;
import structDefinitions.Structures.TriangleFace;
import structDefinitions.Structures.Vertex;

public class Smeshalist {
	
	private static Smeshalist instance;
	int mainWindowPort;
	InetAddress IPAddress;
	DatagramSocket socket = null;
	private static final int numberOfStructuresToSend = 500;
	List<Object> structuresToSend = new LinkedList<>();
	
	
	
	private Smeshalist(int portNumber ) {
		mainWindowPort = portNumber;

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
		if(Objects.isNull(instance)){
			instance = new Smeshalist(8383);
		}
		
		return instance;
	}
	
	public static Smeshalist getInstance(int portNumber){
		if(Objects.isNull(instance)){
			instance = new Smeshalist(portNumber);
		}
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
		structuresToSend.add(builder.build());
	}

	public void addGeometry(geometry.Point3D point) {
		structuresToSend.add(SmeshalistHelper.convertToPoint3D(point));
	}

	public void addGeometry(geometry.Vertex vertex) {
		Properties.Builder prop = SmeshalistHelper.setProperties(vertex.getLabel(), vertex.getQuality(),
				vertex.getGroupId());
		Vertex.Builder builder = Vertex.newBuilder();
		builder.setPoint(SmeshalistHelper.convertToPoint3D(vertex.getPoint()));
		builder.setNumber(vertex.getNumber());
		builder.setProp(prop.build());
		structuresToSend.add(builder.build());
	}

	public void addGeometry(geometry.Edge edge) {
		Properties.Builder prop = SmeshalistHelper.setProperties(edge.getLabel(), edge.getQuality(), edge.getGroupId());
		Edge.Builder builder = Edge.newBuilder();
		builder.setV1(SmeshalistHelper.convertToPoint3D(edge.getV1()));
		builder.setV2(SmeshalistHelper.convertToPoint3D(edge.getV2()));
		builder.setProp(prop.build());
		structuresToSend.add(builder.build());
	}

	public void addGeometry(geometry.TriangleFace triangleFace) {
		Properties.Builder prop = SmeshalistHelper.setProperties(triangleFace.getLabel(), triangleFace.getQuality(),
				triangleFace.getGroupId());
		TriangleFace.Builder builder = TriangleFace.newBuilder();
		builder.setV1(SmeshalistHelper.convertToPoint3D(triangleFace.getV1()));
		builder.setV2(SmeshalistHelper.convertToPoint3D(triangleFace.getV2()));
		builder.setV3(SmeshalistHelper.convertToPoint3D(triangleFace.getV3()));
		builder.setProp(prop.build());
		structuresToSend.add(builder.build());
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
		structuresToSend.add(builder.build());
	}

	
	/**
	 * send all structures stored in buffer to main window
	 */
	public void flushBuffer() {

		System.out.println(structuresToSend.size() + " structures waiting to be sent when called flushBuffer()");
		ByteArrayOutputStream aOutput = new ByteArrayOutputStream(10);
		ByteArrayOutputStream dataBuffer = new ByteArrayOutputStream();
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

			byte[] trimResponse = new byte[response.getLength()];
			for (int i=0; i<response.getLength(); i++) {
				trimResponse[i] = responseBytes[i];
			}

			MessageInfo feedback = MessageInfo.parseFrom(trimResponse);
			if (feedback.getType() == Type.ACK) {
				boolean endOfData = false;
				List<Object> toBeSent = new LinkedList<>();
				
				while(!structuresToSend.isEmpty()){
					dataBuffer = new ByteArrayOutputStream();
					
					

					if(structuresToSend.size() > numberOfStructuresToSend){
						toBeSent = new LinkedList<>(structuresToSend.subList(0, numberOfStructuresToSend));
						structuresToSend = new LinkedList<>(structuresToSend.subList(numberOfStructuresToSend, structuresToSend.size()));
						System.out.println("Size of toBeSent: " + toBeSent.size());
						System.out.println("Size of structuresToSend: " + structuresToSend.size());
					} else {

						endOfData = true;
						toBeSent = structuresToSend;
						structuresToSend = new LinkedList<>();
						System.out.println("Last batch: " + toBeSent.size() + " left to send");

					}

					
					DataPackage.Builder dataPackageBuilder = DataPackage.newBuilder();
					
					
					for (Object structure: toBeSent){
						if (structure instanceof Point2D){
							dataPackageBuilder.addPoints2D((Point2D)structure);
						}
						else if (structure instanceof Point3D){
							dataPackageBuilder.addPoints3D((Point3D)structure);
						}
						else if (structure instanceof Edge){
							dataPackageBuilder.addEdges((Edge)structure);
						}
						else if (structure instanceof TriangleFace){
							dataPackageBuilder.addFaces((TriangleFace)structure);
						}
						else if (structure instanceof Block){
							dataPackageBuilder.addBlocks((Block)structure);
						}
					}
					
					DataPackage dataPackage = dataPackageBuilder.build();					
					byte[] dataBytes = dataPackage.toByteArray();
					Header.Builder headerBuilder = Header.newBuilder();
					headerBuilder.setSizeOfData(dataBytes.length);
					headerBuilder.setEndOfData(endOfData);
					Header header = headerBuilder.build();
					System.out.println("Header sizeOfData: " + header.getSizeOfData());
					System.out.println("Header endOfData: " + header.getEndOfData());
					byte[] headerBytes;
					aOutput = new ByteArrayOutputStream(64);
					header.writeTo(aOutput);
					headerBytes = aOutput.toByteArray();

					DatagramPacket headerPacket = new DatagramPacket(headerBytes, headerBytes.length, IPAddress, mainWindowPort);
					socket.send(headerPacket);
					aOutput.close();
					
					//TODO check if ack is needed
					
					DatagramPacket dataPacket = new DatagramPacket(dataBytes, dataBytes.length, IPAddress, mainWindowPort);
					socket.send(dataPacket);
					dataBuffer.close();
					System.out.println("---------------------->sent");
					
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

			byte[] trimResponse = new byte[response.getLength()];
			for (int i=0; i<response.getLength(); i++) {
				trimResponse[i] = responseBytes[i];
			}
			
			MessageInfo feedback = MessageInfo.parseFrom(trimResponse);
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

	

}
