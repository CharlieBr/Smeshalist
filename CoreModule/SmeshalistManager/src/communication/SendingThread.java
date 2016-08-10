package communication;

import util.SocketUtil;

import java.io.IOException;
import java.net.DatagramPacket;

public class SendingThread extends Thread{

	private Communication.ManagerToCoreMessage toCoreMessage;

	public SendingThread(Communication.ManagerToCoreMessage message){
		this.toCoreMessage = message;
	}

	@Override
	public void run(){
		byte[] messageBytes = toCoreMessage.toByteArray();
		DatagramPacket datagramPacket = new DatagramPacket(messageBytes, messageBytes.length, SocketUtil.IP, SocketUtil.port);
		try {
			SocketUtil.socket.send(datagramPacket);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
