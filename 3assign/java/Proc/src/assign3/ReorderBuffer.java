package assign3;

import java.util.LinkedList;
import java.util.Queue;

public class ReorderBuffer {
	Queue<Instruction> reorderQueue;
	int max_entries;
	ARF arf;
	RRF rrf;
	ReorderBuffer(int max_entries, ARF arf,RRF rrf){
		reorderQueue = new LinkedList<Instruction>();
		this.max_entries = max_entries;
		this.arf = arf;
		this.rrf = rrf;
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
			if(inst.RRF_tag_dest.equals(arf.getEntry(inst.destination).RRF_tag)){
				arf.getEntry(inst.destination).busy = false;
			}
				
			rrf.getEntry(inst.RRF_tag_dest).busy = false;
			rrf.getEntry(inst.RRF_tag_dest).valid = true;
		}
	}
	  
}
