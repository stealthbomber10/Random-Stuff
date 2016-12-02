package morsing.morse;

import java.io.*;
import java.util.Enumeration;

import gnu.io.*;

public class SerialComm {

	SerialPort serialPort;
	InputStream in;
	OutputStream out;

    public SerialComm()
    {
        super();
    }
    public boolean connect ( String portName ) throws Exception
    {
    	boolean success;

    	CommPortIdentifier portIdentifier;
    	try {
    		portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
    	} catch(NoSuchPortException e) {
    		System.out.println("ERROR: Port not found.");
    		System.out.println("Did you mean one of these?");
    		Enumeration ports = CommPortIdentifier.getPortIdentifiers();
        	while (ports.hasMoreElements()) {
        		CommPortIdentifier com = (CommPortIdentifier) ports.nextElement();
        		System.out.println("\t- " + com.getName());
        	}
    		return false;
    	}

        if ( portIdentifier.isCurrentlyOwned() )
        {
            System.out.println("Error: Port is currently in use");
            System.out.println("Make sure to terminate all your Java programs and close serial monitor.");
            success = false;
        }
        else
        {
        	CommPort commPort;
        	try {
        		commPort = portIdentifier.open(this.getClass().getName(),2000);
        	} catch(PortInUseException e) {
        		System.out.println("Error: Port is currently in use, apparently by '" + e.currentOwner + "'.");
        		System.out.println("Make sure to terminate all your Java programs and close serial monitor.");
        		System.out.println("Also, if you're on Mac, make sure that `/var/lock` exists.");
        		return false;
        	}

            if ( commPort instanceof SerialPort )
            {
                serialPort = (SerialPort) commPort;
                serialPort.setSerialPortParams(9600,SerialPort.DATABITS_8,SerialPort.STOPBITS_1,SerialPort.PARITY_NONE); // First parameter is baud rate for the port

                in = serialPort.getInputStream();
                out = serialPort.getOutputStream();
                success = true;
            }
            else
            {
                System.out.println("Error: Only serial ports are handled by this example.");
                success = false;
            }
        }
        return(success);
    }

    public void disconnect() {
    	serialPort.close();
    	try {
			in.close();
			out.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

    }

    public InputStream getInputStream() {
    	return(in);
    }

    public OutputStream getOutputStream() {
    	return(out);
    }

    // Example use
    public static void main ( String[] args )
    {
        try
        {
            SerialComm s = new SerialComm();
            s.connect("COM3"); // Adjust this to be the right port for your machine
            InputStream in = s.getInputStream();
            OutputStream out = s.getOutputStream();
            // InputStream and OutputStream are now available for use
            // insert code below to use them
            BufferedReader sys =
    				new BufferedReader(
    						new InputStreamReader(in));

            DataOutputStream os =
    				new DataOutputStream(
    						new BufferedOutputStream(out));

        }
        catch ( Exception e )
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
