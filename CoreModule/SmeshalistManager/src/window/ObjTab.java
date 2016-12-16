package window;

import communication.Communication;
import communication.SendingThread;
import util.WindowUtil;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class ObjTab extends JPanel {

	private File importFile;
	private File exportFile;

	private JPanel importPanel;
	private JPanel exportPanel;
	private JFileChooser importFileChooser;
	private JFileChooser exportFileChooser;
	private JButton chooseImportFileButton;
	private JButton chooseExportFileButton;
	private JButton importButton;
	private JButton exportButton;
	private JTextArea importPathTextArea;
	private JTextArea exportPathTextArea;

	public ObjTab() {
		this.initializeView();
		this.setVisible(true);
	}

	private void initializeView() {
		this.setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
		this.setBorder(new EmptyBorder(WindowUtil.PADDING_VALUE, WindowUtil.PADDING_VALUE, WindowUtil.PADDING_VALUE, WindowUtil.PADDING_VALUE));

		importPanel = new JPanel();
		importPanel.setLayout(new BorderLayout(5,0));
		importPanel.setBorder(new TitledBorder("Import"));
		importPathTextArea = new JTextArea("Path:");
		importPathTextArea.setEditable(false);
		importPathTextArea.setFont(importPathTextArea.getFont().deriveFont(12f));

		JScrollPane importPathScrollPane = new JScrollPane(importPathTextArea, JScrollPane.VERTICAL_SCROLLBAR_NEVER, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		chooseImportFileButton = new JButton("Choose file");
		chooseImportFileButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				chooseImportFileButtonPressed();
			}
		});

		JPanel importCenter = new JPanel();
		importCenter.add(chooseImportFileButton);

		importButton = new JButton("Import");
		importButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				importButtonPressed();
			}
		});
		JPanel importButtonPanel = new JPanel();
		importButtonPanel.add(importButton);

		JPanel importSouth = new JPanel();
		importSouth.setLayout(new BorderLayout());
		importSouth.add(importPathScrollPane, BorderLayout.CENTER);
		importSouth.add(importButtonPanel, BorderLayout.EAST);

		JLabel importInfoLabel = new JLabel("Import structures from an OBJ file.");
		importInfoLabel.setFont(new Font("Tahoma", Font.ITALIC, 14));
		importInfoLabel.setBorder(new EmptyBorder(20,10,50,0));
		importPanel.add(importInfoLabel, BorderLayout.NORTH);
		importPanel.add(importCenter, BorderLayout.CENTER);
		importPanel.add(importSouth, BorderLayout.SOUTH);

		exportPanel = new JPanel();
		exportPanel.setLayout(new BorderLayout(5,0));
		exportPanel.setBorder(new TitledBorder("Export"));
		exportPathTextArea = new JTextArea("Path: ");
		exportPathTextArea.setEditable(false);
		exportPathTextArea.setFont(exportPathTextArea.getFont().deriveFont(12f));

		JScrollPane exportPathScrollPane = new JScrollPane(exportPathTextArea, JScrollPane.VERTICAL_SCROLLBAR_NEVER, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);

		chooseExportFileButton = new JButton("Choose file");
		chooseExportFileButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				chooseExportFileButtonPressed();
			}
		});

		JPanel exportCenter = new JPanel();
		exportCenter.add(chooseExportFileButton);

		exportButton = new JButton("Export");
		exportButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				exportButtonPressed();
			}
		});
		JPanel exportButtonPanel = new JPanel();
		exportButtonPanel.add(exportButton);

		JPanel exportSouth = new JPanel();
		exportSouth.setLayout(new BorderLayout());
		exportSouth.add(exportPathScrollPane, BorderLayout.CENTER);
		exportSouth.add(exportButtonPanel, BorderLayout.EAST);

		JLabel exportInfoLabel = new JLabel("Export structures from active tree to an OBJ file.");
		exportInfoLabel.setFont(new Font("Tahoma", Font.ITALIC, 14));
		exportInfoLabel.setBorder(new EmptyBorder(20,10,50,0));
		exportPanel.add(exportInfoLabel, BorderLayout.NORTH);
		exportPanel.add(exportCenter, BorderLayout.CENTER);
		exportPanel.add(exportSouth, BorderLayout.SOUTH);

		this.add(importPanel, BorderLayout.CENTER);
		this.add(Box.createVerticalStrut(10));
		this.add(exportPanel, BorderLayout.CENTER);
	}

	private void exportButtonPressed() {
		if (exportFile == null) {
			System.out.println("Choose export file first!");
			return;
		}

		Communication.ManagerToCoreMessage.Builder messageBuilder = Communication.ManagerToCoreMessage.newBuilder();
		messageBuilder.setMessageType(Communication.ManagerToCoreMessage.MTCMessageType.EXPORT);
		messageBuilder.setObjFilePath(exportFile.getPath());
		Communication.ManagerToCoreMessage message = messageBuilder.build();
		new SendingThread(message).start();

		System.out.println("Exporting structures tree to: " + exportFile.getPath());
	}

	private void chooseExportFileButtonPressed() {
		exportFileChooser = new JFileChooser(".");
		exportFileChooser.setDialogTitle("Choose where to save OBJ file");
		int returnedValue = exportFileChooser.showSaveDialog(null);

		if (returnedValue == JFileChooser.APPROVE_OPTION) {
			exportFile = exportFileChooser.getSelectedFile();
			exportPathTextArea.setText("Path: " + exportFile.getPath());
		} else {
			exportPathTextArea.setText("Path:");
		}
		this.revalidate();
		this.repaint();
	}

	private void importButtonPressed() {
		if (importFile == null) {
			System.out.println("Choose import file first!");
			return;
		}
		Communication.ManagerToCoreMessage.Builder messageBuilder = Communication.ManagerToCoreMessage.newBuilder();
		messageBuilder.setMessageType(Communication.ManagerToCoreMessage.MTCMessageType.IMPORT);
		messageBuilder.setObjFilePath(importFile.getPath());
		Communication.ManagerToCoreMessage message = messageBuilder.build();
		new SendingThread(message).start();

		System.out.println("Importing structures from: " + importFile.getPath());
	}

	private void chooseImportFileButtonPressed() {
		importFileChooser = new JFileChooser(".");
		importFileChooser.setDialogTitle("Choose OBJ file to import structures");
		FileNameExtensionFilter filter = new FileNameExtensionFilter("OBJ files", "obj");
		importFileChooser.setFileFilter(filter);

		int returnValue = importFileChooser.showOpenDialog(null);
		if (returnValue == JFileChooser.APPROVE_OPTION) {
			importFile = importFileChooser.getSelectedFile();
			importPathTextArea.setText("Path: " + importFile.getPath());
		} else {
			importPathTextArea.setText("Path:");
		}
		this.revalidate();
		this.repaint();
	}

    public void setInitContent() {
		this.removeAll();
		exportFile = null;
		importFile = null;
		this.initializeView();
		this.revalidate();
		this.repaint();
    }
}

