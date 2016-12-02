package morsing.morse;

import java.io.*;
import java.util.Scanner;

public class SerialOutput {

	public static void main(String[] args) throws Exception {

		try
        {
            SerialComm s = new SerialComm();
            s.connect("COM3"); // Adjust this to be the right port
            InputStream in = s.getInputStream();
            OutputStream out = s.getOutputStream();
            Scanner reader = new Scanner(System.in);
            ViewOutputStream os = new ViewOutputStream(out);

            while (reader.hasNext()) {
            	String input = reader.nextLine();
            	for (int i = 0; i < input.length(); i++) {
            		os.write(input.charAt(i));
            	}
            	os.flush();
            }

        }
        catch ( Exception e )
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
	}

}
