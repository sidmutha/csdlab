package assign3;

import java.util.Queue;
import java.util.Deque;
public class LoadStore {
	Queue<Instruction> loadQueue;
	Deque<Instruction> storeQueue;

	public void addStore(Instruction storeInst) {
		storeQueue.addFirst(storeInst);
		
	}

	public void addLoad(Instruction loadInst) {
		Instruction storeInst = null;
		for (Instruction inst : storeQueue) {
			// TODO: if inst is storing at same location as loadInst, cancel out
			// and use
			

		}
		if (storeInst != null) {
			// TODO
		}
	}

	public void tick() {

	}
}
