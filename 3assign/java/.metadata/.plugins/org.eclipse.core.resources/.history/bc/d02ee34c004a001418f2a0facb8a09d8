package assign3;

import java.util.LinkedList;
import java.util.Queue;

public class ReorderBuffer {
	Queue<Instruction> reorderQueue;
	int max_entries;
	
	ReorderBuffer(int max_entries){
		reorderQueue = new LinkedList<Instruction>();
		this.max_entries = max_entries;
	}
	boolean addEntry(Instruction inst){
		if(reorderQueue.size() < max_entries)
			reorderQueue.add(inst);
		else
			return false;
		return true;
	}
	
	
	public void commitEntries() {
		while(reorderQueue.peek().isCompleted()){
			Instruction inst = reorderQueue.poll();
			// TODO: set arf/rrf bits
		}
	}
	  
}
