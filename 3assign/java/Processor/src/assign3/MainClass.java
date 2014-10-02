package assign3;

import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;

public class MainClass {

	/**
	 * @param args
	 * @throws IOException 
	 */
	public static void main(String[] args) throws IOException {
		String filename = "/home/sid/acads/csdlab/3assign/test1.txt";
		Runnable r = new Runnable(filename, 10, 5, 10, null, null);
		r.readFile(filename);
		//r.start();
	}
	
}