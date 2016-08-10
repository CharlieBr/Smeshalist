package window;

import javax.swing.JFrame;
import javax.swing.JTabbedPane;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class MainWindow extends JFrame {

	private static final long serialVersionUID = -8385942516800601932L;

	private static MainWindow INSTANCE;

	private JTabbedPane tabContainer;
	private StatisticsTab statisticsTab;
	private OptionsTab optionsTab;
	private FiltersTab filtersTab;

	private MainWindow() {
		this.setSize(500, 500);

		tabContainer = new JTabbedPane();
		tabContainer.setVisible(true);
		this.optionsTab = new OptionsTab();
		this.statisticsTab = new StatisticsTab();
		statisticsTab.setTestContent();
		this.filtersTab = new FiltersTab();

		tabContainer.addTab("Statistics", statisticsTab);
		tabContainer.addTab("Options", optionsTab);
		tabContainer.addTab("Filters", filtersTab);
		this.add(tabContainer);

		setVisible(true);
	}

	public static void main(String[] args) {
		
		try {
			MainWindow.setLookAndFeel();
		} catch (ClassNotFoundException | InstantiationException | UnsupportedLookAndFeelException | IllegalAccessException e) {
			e.printStackTrace();
		}

		MainWindow.getInstance();
	}

	public static MainWindow getInstance() {
		if (INSTANCE == null) {
			INSTANCE = new MainWindow();
		}
		return INSTANCE;
	}
	
	private static void setLookAndFeel() throws ClassNotFoundException, InstantiationException, IllegalAccessException, UnsupportedLookAndFeelException{
		UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
	}
}
