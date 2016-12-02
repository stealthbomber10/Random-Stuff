package weather.weatherSender;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

import java.awt.Color;
import java.awt.EventQueue;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;

import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import java.awt.Font;

public class PrintStreamPanel extends JPanel {
	final private JTextField textField;
	final private PrintStream ps;
	private JTextArea textArea;

	/**
	 * Create the panel.
	 */
	public PrintStreamPanel() {
		this(Color.WHITE, "", 170);
	}

	public PrintStreamPanel(Color fg, String title, int width) {
		this(fg, title, width, 18);
	}
	public PrintStreamPanel(Color fg, String title, int width, int fontSize) {
		setBackground(Color.BLACK);
		setLayout(null);

		textField = new JTextField();
		textField.setEditable(false);
		textField.setBackground(Color.BLACK);
		textField.setForeground(fg);
		textField.setBounds(6, 0, width, 28);
		add(textField);
		textField.setColumns(15);

		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(6, 25, width, 175);
		add(scrollPane);

		textArea = new JTextArea();
		textArea.setFont(new Font("Courier New", Font.PLAIN, fontSize));
		textArea.setEditable(false);
		scrollPane.setViewportView(textArea);
		textArea.setForeground(fg);
		textArea.setBackground(Color.BLACK);
		this.ps = new PrintStream(new OutputStream() {

			@Override
			public void write(int b) throws IOException {
				textArea.append("" + (char)b);
				textArea.setCaretPosition(textArea.getDocument().getLength());
			} });
		textField.setText(title);
	}

	public PrintStream getPrintStream() {
		return this.ps;
	}

	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					JFrame f = new JFrame("Demo");
					f.setBounds(100,100,225,300);
					PrintStreamPanel frame = new PrintStreamPanel(Color.YELLOW, "demo", 170);
					f.getContentPane().add(frame);
					f.setVisible(true);
					for (int i=0; i < 1000; ++i) {
						frame.getPrintStream().println(i);
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
}
