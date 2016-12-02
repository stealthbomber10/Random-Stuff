package weather.weatherSender;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;

public class WeatherStation {

    public static void main(String[] args) throws Exception {

    	//WeatherStation station = new WeatherStation();

    	//station.sendGet();

    }

    // HTTP GET request
    public char sendGet(int n) throws Exception {

        // Create a string that contains the URL for your location
    	String currentWeatherLink;
    	if (n < 341) {
    		currentWeatherLink = "https://api.darksky.net/forecast/d8f53667904955c9301c53bc501a29e8/38.649196,-90.306099?exclude=minutely,hourly,daily,alerts,flags";
    	}
    	else if (n > 682) {
    		currentWeatherLink = "https://api.darksky.net/forecast/d8f53667904955c9301c53bc501a29e8/40.101286,-75.383553?exclude=minutely,hourly,daily,alerts,flags";
    	}
    	else {
    		currentWeatherLink = "https://api.darksky.net/forecast/d8f53667904955c9301c53bc501a29e8/34.052234,-118.243685?exclude=minutely,hourly,daily,alerts,flags";
    	}

    	URL currentWeather = new URL(currentWeatherLink);

    	HttpURLConnection connection = (HttpURLConnection) currentWeather.openConnection();

    	connection.setRequestMethod("GET");

    	connection.setRequestProperty("User-Agent", "Mozilla/5.0");

    	Object received = connection.getResponseCode();
      //UNCOMMENT IF YOU ARE DEBUGGING TO GET RESPONSE CODES
      //System.out.println(" " + received);

    	InputStream in = connection.getInputStream();
    	DataInputStream data = new DataInputStream(in);
    	BufferedReader sys = new BufferedReader(new InputStreamReader(data));

    	String input = sys.readLine();

    	sys.close();

    	int start = input.indexOf("icon");
    	String icon = input.substring(start+6);
    	int end = icon.indexOf(",");
    	icon = icon.substring(0, end);
    	System.out.println(icon);

        char weatherChar = '\0';

        switch (icon) {
        case "\"clear-day\"":
        	weatherChar = 'S';
        	break;
        case "\"clear-night\"":
        	weatherChar = 'S';
        	break;
        case "\"rain\"":
        	weatherChar = 'P';
        	break;
        case "\"snow\"":
        	weatherChar = 'P';
        	break;
        case "\"sleet\"":
        	weatherChar = 'P';
        	break;
        case "\"wind\"":
        	weatherChar = 'W';
        	break;
        case "\"fog\"":
        	weatherChar = 'F';
        	break;
        case "\"cloudy\"":
        	weatherChar = 'C';
        	break;
        case "\"partly-cloudy-day\"":
        	weatherChar = 'C';
        	break;
        case "\"partly-cloudy-night\"":
        	weatherChar = 'C';
        	break;
        default:
        	weatherChar = 'Z';
        	break;
        }


        return weatherChar;

    }
}
