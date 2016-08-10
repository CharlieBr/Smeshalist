package util;

import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

public class SocketUtil {
	public static DatagramSocket socket;
	public static InetAddress IP;
	public static final int port = 8393;
	public static int CTMMessageLength = 1024;

	static {
		try {
			socket = new DatagramSocket();
			IP = InetAddress.getByName("localhost");
		}catch (SocketException e) {
			System.out.println("Socket creation failed.\n" + e.getMessage());
			System.exit(1);
		} catch (UnknownHostException e) {
			System.out.println(e.getMessage());
			System.exit(1);
		}

	}
}
