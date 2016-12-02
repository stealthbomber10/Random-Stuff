package weather.weatherSender;

import java.awt.Color;
import java.io.*;

import javax.swing.JFrame;

public class ViewInputStream extends FilterInputStream
{

    final private PrintStreamPanel psp;
    final private PrintStream ps;

    public ViewInputStream(InputStream in)
    {
        super(in);
        int width = 1500;
    	int height = 250;
        JFrame f = new JFrame("ViewInputStream");
		f.setBounds(500,500,width,height);//100,100,225,300);
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        psp = new PrintStreamPanel(Color.YELLOW, "Input:", height, 50);
        ps = psp.getPrintStream();
		f.getContentPane().add(psp);
		f.setVisible(true);
    }

    public int read() throws IOException
    {
		int nextInt = super.read();
    	ps.print(" " + Integer.toHexString(nextInt));
    	return nextInt;
    }

}
