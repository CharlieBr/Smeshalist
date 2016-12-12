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

import org.apache.log4j.Logger;

import helpers.SmeshalistHelper;
import structDefinitions.Structures.Block;
import structDefinitions.Structures.DataPackage;
import structDefinitions.Structures.Edge;
import structDefinitions.Structures.Header;
import structDefinitions.Structures.MessageInfo;
import structDefinitions.Structures.MessageInfo.Type;
import structDefinitions.Structures.Point3D;
import structDefinitions.Structures.Properties;
import structDefinitions.Structures.TriangleFace;
import structDefinitions.Structures.Vertex;


/**
 * Main API class which provide methods to add geometries for visualization algorithm
 * @author ewa
 *
 */
public class Smeshalist {

	private static final Logger logger = Logger.getLogger(Smeshalist.class.getName());
	
	private static Smeshalist instance;
	int mainWindowPort;
	InetAddress IPAddress;
	DatagramSocket socket = null;
	private static final int numberOfStructuresToSend = 200;
	List<Object> structuresToSend = new LinkedList<>();
	
	
	
	private Smeshalist(int portNumber ) {
		mainWindowPort = portNumber;

		try {
			socket = new DatagramSocket();
			IPAddress = InetAddress.getByName("localhost");
		} catch (UnknownHostException | SocketException e) {
			logger.error(e.getMessage());
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
	
	/**
	 * 
	 * @param portNumber
	 * @return instance of Smeshalist class. Tool is using port of given number to connect to main window
	 */
	public static Smeshalist getInstance(int portNumber){
		if(Objects.isNull(instance)){
			instance = new Smeshalist(portNumber);
		}
		return instance;
	}

	/**
	 * Method which is to be used after finishing work with tool. It provides proper socket closing.
	 */
	public static void destroySmeshalist() {
		instance.socket.close();
	}


	/**
	 * 
	 * @param vertex Vertex structure
	 * Method adds Vertex structure to internal data buffer that stores structures to send for visualization
	 */
	public void addGeometry(geometry.Vertex vertex) {
		Properties.Builder prop = SmeshalistHelper.setProperties(vertex.getLabel(), vertex.getQuality(),
				vertex.getGroupId());
		Vertex.Builder builder = Vertex.newBuilder();
		builder.setPoint(SmeshalistHelper.convertToPoint3D(vertex.getPoint()));
		builder.setProp(prop.build());
		structuresToSend.add(builder.build());
	}

	/**
	 * 
	 * @param edge Edge structure
	 * Method adds Edge structure to internal data buffer that stores structures to send for visualization
	 */
	public void addGeometry(geometry.Edge edge) {
		Properties.Builder prop = SmeshalistHelper.setProperties(edge.getLabel(), edge.getQuality(), edge.getGroupId());
		Edge.Builder builder = Edge.newBuilder();
		builder.setV1(SmeshalistHelper.convertToPoint3D(edge.getV1()));
		builder.setV2(SmeshalistHelper.convertToPoint3D(edge.getV2()));
		builder.setProp(prop.build());
		structuresToSend.add(builder.build());
	}

	/**
	 * 
	 * @param triangleFace TriangleFace structure
	 * Method adds TriangleFace structure to internal data buffer that stores structures to send for visualization 
	 */
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

	/**
	 * 
	 * @param block Block structure
	 * Method adds Block structure to internal data buffer that stores structures to send for visualization
	 */
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
	 * Send all structures stored in buffer to main window
	 */
	public void flushBuffer() {

		logger.info(structuresToSend.size() + " structures waiting to be sent when called flushBuffer()");
		
		if(structuresToSend.isEmpty()) return;
		
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
				boolean endOfData = false;
				List<Object> toBeSent = new LinkedList<>();
				
				while(feedback.getType() == Type.ACK && !structuresToSend.isEmpty()){
					dataBuffer = new ByteArrayOutputStream();
					
					

					if(structuresToSend.size() > numberOfStructuresToSend){
						toBeSent = new LinkedList<>(structuresToSend.subList(0, numberOfStructuresToSend));
						structuresToSend = new LinkedList<>(structuresToSend.subList(numberOfStructuresToSend, structuresToSend.size()));
						logger.info("Size of toBeSent: " + toBeSent.size());
						logger.info("Size of structuresToSend: " + structuresToSend.size());
					} else {

						endOfData = true;
						toBeSent = structuresToSend;
						structuresToSend = new LinkedList<>();
						logger.info("Last batch: " + toBeSent.size() + " left to send");
						

					}

					
					DataPackage.Builder dataPackageBuilder = DataPackage.newBuilder();
					
					
					for (Object structure: toBeSent){
						if (structure instanceof Vertex){
							dataPackageBuilder.addVertexes((Vertex)structure);
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
						else{
							logger.warn("Unknown data structure type");
						}
					}
					
					DataPackage dataPackage = dataPackageBuilder.build();					
					byte[] dataBytes = dataPackage.toByteArray();
					Header.Builder headerBuilder = Header.newBuilder();
					headerBuilder.setSizeOfData(dataBytes.length);
					headerBuilder.setEndOfData(endOfData);
					Header header = headerBuilder.build();
					byte[] headerBytes;
					aOutput = new ByteArrayOutputStream(64);
					header.writeTo(aOutput);
					headerBytes = aOutput.toByteArray();

					DatagramPacket headerPacket = new DatagramPacket(headerBytes, headerBytes.length, IPAddress, mainWindowPort);
					socket.send(headerPacket);
					aOutput.close();

					DatagramPacket dataPacket = new DatagramPacket(dataBytes, dataBytes.length, IPAddress, mainWindowPort);
					socket.send(dataPacket);
					dataBuffer.close();
					
					//ACK from Core
					responseBytes = new byte[10];
					response = new DatagramPacket(responseBytes, responseBytes.length);
					socket.receive(response);

					trimResponse = new byte[response.getLength()];
					for (int i=0; i<response.getLength(); i++) {
						trimResponse[i] = responseBytes[i];
					}

					feedback = MessageInfo.parseFrom(trimResponse);
					
					logger.info("---------------------->po ack");

				}
					
		} catch (IOException e) {
			logger.error(e.getMessage());
		}

	}

	
	
	/**
	 * Interrupts algorithm execution until proper option will be chosen in Smeshalist Manager window.
	 * In case continue option has been chosen algorithm is continued otherwise program is terminated.
	 * 
	 */
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
			logger.error(e.getMessage());
		}

	}

	/**
	 * Method forces rendering sent structures in main window 
	 * in case Dynamic rendering is turned off in Smeshalist Manager window.
	 */
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
			logger.error(e.getMessage());
		}

	}
	
	/**
	 * Method forces deleting all data from data structure tree in main window without affecting taken snapshots.
	 */
	public void clean() {
		ByteArrayOutputStream aOutput = new ByteArrayOutputStream(10);
		MessageInfo.Builder builder = MessageInfo.newBuilder();
		builder.setType(Type.CLEAN);
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
			if (feedback.getType() != Type.ACK) {
				socket.close();
				logger.error("Clean method feedback from CORE");
				System.exit(0);
			}

		} catch (IOException e) {
			logger.error(e.getMessage());
		}
	}

	

}
