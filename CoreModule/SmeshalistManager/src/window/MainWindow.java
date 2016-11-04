package window;

import communication.Communication.CoreToManagerMessage;
import communication.Communication.OptionsInfo;
import util.SocketUtil;

import javax.swing.*;
import java.awt.event.WindowAdapter;

public class MainWindow extends JFrame {

	private static final long serialVersionUID = -8385942516800601932L;

	private static MainWindow INSTANCE;
	public static boolean running;

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
		this.setTitle("Smeshalist Manager");
		this.tabContainer = new JTabbedPane();
		this.tabContainer.setVisible(true);
		this.optionsTab = new OptionsTab();
		this.statisticsTab = new StatisticsTab();
		this.filtersTab = new FiltersTab();

		this.tabContainer.addTab("Statistics", statisticsTab);
		this.tabContainer.addTab("Options", optionsTab);
		this.tabContainer.addTab("Filters", filtersTab);
		this.add(tabContainer);

		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(java.awt.event.WindowEvent windowEvent) {
				MainWindow.running = false;
				SocketUtil.socket.close();
			}
		});

		MainWindow.running = true;
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

	public void handleReceivedData(CoreToManagerMessage toManagerMessage){
		switch(toManagerMessage.getMessageType()){
			case BREAKPOINT:
				this.optionsTab.breakpoint();
				break;
			case STATISTICS:
				this.statisticsTab.setBoundingBox(toManagerMessage.getStatisticsInfo().getBoundingBox());
				this.statisticsTab.setElementsCount(toManagerMessage.getStatisticsInfo().getElementsCount());
				this.filtersTab.setGroupsInfo(toManagerMessage.getStatisticsInfo().getGroupsInfo());
				break;
			default:
				break;
		}
	}

	public OptionsInfo getDefaults(){
		return optionsTab.getOptionsInfo();
	}

	public void cleanGroupCheckBoxes() {
		this.filtersTab.cleanGroupCheckBoxes();
	}
}
