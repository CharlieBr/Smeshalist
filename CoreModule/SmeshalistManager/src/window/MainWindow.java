package window;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

public class MainWindow extends JFrame{
	
	private static final long serialVersionUID = -8385942516800601932L;
	JTabbedPane tabContainer;
	StatisticsTab statisticsTab;
	OptionsTab optionsTab;
	FiltersTab filtersTab;
		
	public MainWindow(){
		this.setSize(500,500);

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

	public static void main(String[] args){
		new MainWindow();
	}
}
