/*
 * Reusing this for the weather station
 */

package weather.weatherSender;

import java.io.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MsgReceiver
{
	final private DataInputStream dataStream;
	//final private PrintStream ps;
	//final private ViewInputStream psp = new ViewInputStream(ps);

	static final private int MAGIC_NUM = '!';
	private String value;
	private int numValue;
	private char weather;
	private WeatherStation station = new WeatherStation();
	static private OutputStream out;

	static final private int DEBUG_STRING = 0x30; //UTF encoded String
	static final private int ERROR_STRING = 0x31; //UTF encoded String
	static final private int TIMESTAMP = 0x32; //4-Byte Integer
	static final private int POTENTIOMETER = 0x33; //2-Byte Integer
	static final private int RAW_TEMP = 0x34; //2 byte integer in Volts per Tick
	static final private int CONVERTED_TEMP = 0x35; //4-Byte Float in degrees C
	static final private int FILTERED_TEMP = 0x36; //4-Byte Float in degrees C


	public MsgReceiver(InputStream in) throws IOException
	{
		dataStream = new DataInputStream(new assign4.ViewInputStream(in));
	}

	public void run() throws IOException, Exception
	{
		while(true)
		{
			if(dataStream.available() > 0)
			{
				if(dataStream.readByte() == MAGIC_NUM)
				{
					byte type = dataStream.readByte();
					String inputData = readData(type);
					System.out.println(inputData);
				}
			}
		}
	}

	String readData(byte type) throws Exception
	{
		switch(type)
		{
			case DEBUG_STRING:
				System.out.print("Debug: ");
				return dataStream.readUTF();

			case ERROR_STRING:
				System.out.print("Error: ");
				return "!!!!! " + dataStream.readUTF();

			case TIMESTAMP:
				System.out.print("Timestamp: ");
				return Integer.toString(dataStream.readInt());

			case POTENTIOMETER:
				//
				//System.out.print("Potentiometer: ");
				//HTTPRequest //out.write()
				String value = Integer.toString(dataStream.readShort());
				numValue = Integer.parseInt(value);
				weather = station.sendGet(numValue);
				System.out.println(weather);
				out.write(MAGIC_NUM);
				out.write(weather);
				return value;

			case RAW_TEMP:
				System.out.print("Raw Temp: ");
				return Float.toString(dataStream.readShort());

			case CONVERTED_TEMP:
				System.out.print("Converted Temp: ");
				return Float.toString(readNextFourBytes());        //dataStream.readFloat());

			case FILTERED_TEMP:
				System.out.print("Filtered Temp: ");
				return Float.toString(readNextFourBytes());        //dataStream.readFloat());

			default:
				throw new IOException("Message type not recognized");
		}
	}

	private float readNextFourBytes() throws IOException
	{
		byte[] fourByte = new byte[4]; //Float conversion from Puneet Sachdeva
		for(int i = 0; i < 4; i++)
		{
			fourByte[i] = dataStream.readByte();
		}
		float temp = ByteBuffer.wrap(fourByte).order(ByteOrder.LITTLE_ENDIAN).getFloat();
		return temp;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
        try
        {
            SerialComm s = new SerialComm();
            s.connect("COM3"); // Adjust this to be the right port for your machine
            InputStream in = s.getInputStream();
            out = s.getOutputStream();
            MsgReceiver msgr = new MsgReceiver(in);
            msgr.run();
        }
        catch ( Exception e )
        {
            e.printStackTrace();
            System.exit(1);
        }

	}

}
