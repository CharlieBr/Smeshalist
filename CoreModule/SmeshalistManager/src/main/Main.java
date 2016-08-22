package main;

import communication.Communication.ManagerToCoreMessage;
import communication.Communication.CoreToManagerMessage;
import communication.SendingThread;
import util.SocketUtil;
import window.MainWindow;

import javax.swing.UnsupportedLookAndFeelException;
import java.io.IOException;
import java.net.DatagramPacket;

public class Main {

	public static void main(String[] args) {

		try {
			MainWindow.setLookAndFeel();
		} catch (ClassNotFoundException | InstantiationException | UnsupportedLookAndFeelException | IllegalAccessException e) {
			System.out.println("Could not set LookAndFeel.\n" + e.getMessage());
		}

		MainWindow.getInstance();

		//send hello message
		ManagerToCoreMessage.Builder toCoreMessageBuilder = ManagerToCoreMessage.newBuilder();
		toCoreMessageBuilder.setMessageType(ManagerToCoreMessage.MTCMessageType.HELLO);

		ManagerToCoreMessage toCoreMessage = toCoreMessageBuilder.build();
		new SendingThread(toCoreMessage).start();

		while (MainWindow.running){
			try{
				byte[] responseBytes = new byte[SocketUtil.CTMMessageLength];
				DatagramPacket response = new DatagramPacket(responseBytes, responseBytes.length);
				SocketUtil.socket.receive(response);

				byte[] trimResponse = new byte[response.getLength()];
				System.arraycopy(responseBytes, 0, trimResponse, 0, response.getLength());

				CoreToManagerMessage toManagerMessage = CoreToManagerMessage.parseFrom(trimResponse);
				MainWindow.getInstance().handleReceivedData(toManagerMessage);

			} catch (IOException e){
				System.out.println("Receiving from socket failed.\n" + e.getMessage());
			}
		}

	}
}
