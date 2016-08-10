package window;

import util.SocketUtil;

import javax.swing.*;
import java.awt.event.WindowAdapter;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

public class MainWindow extends JFrame {

	private static final long serialVersionUID = -8385942516800601932L;

	private static MainWindow INSTANCE;

	private JTabbedPane tabContainer;
	private StatisticsTab statisticsTab;
	private OptionsTab optionsTab;
	private FiltersTab filtersTab;

	private MainWindow() {
		this.initializeView();

		this.setSize(500, 500);

		setVisible(true);
	}

	private void initializeView() {
		this.tabContainer = new JTabbedPane();
		this.tabContainer.setVisible(true);
		this.optionsTab = new OptionsTab();
		this.statisticsTab = new StatisticsTab();
		this.statisticsTab.setTestContent();
		this.filtersTab = new FiltersTab();

		this.tabContainer.addTab("Statistics", statisticsTab);
		this.tabContainer.addTab("Options", optionsTab);
		this.tabContainer.addTab("Filters", filtersTab);
		this.add(tabContainer);

		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(java.awt.event.WindowEvent windowEvent) {
				SocketUtil.socket.close();
			}
		});

	}

	public static MainWindow getInstance() {
		if (INSTANCE == null) {
			INSTANCE = new MainWindow();
		}
		return INSTANCE;
	}
	
	public static void setLookAndFeel() throws ClassNotFoundException, InstantiationException, IllegalAccessException, UnsupportedLookAndFeelException{
		UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
	}
}
