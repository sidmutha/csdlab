package assign3;

import java.util.Queue;

public class LoadStore {
	Queue<Instruction> loadQueue;
	Queue<Instruction> storeQueue;

	public void addStore(Instruction storeInst) {
		storeQueue.add(storeInst);
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
	
	//TODO: constructor with memory array

	public void tick() {
		// TODO: this function
	}
}
