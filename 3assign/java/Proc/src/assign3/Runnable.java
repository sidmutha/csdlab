package assign3;

import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;

public class Runnable {
	ReorderBuffer reorderBuffer;
	Queue<Instruction> allInstructionsQueue = new LinkedList<Instruction>();
	ReservationStation[] reservationStations;

	ARF arf;
	RRF rrf;
	int clock = 0;
	ALU[] aluArray;

	public Runnable(String filename, int reorderBufferSize, int numRS,
			int numRRF_Entries, Map<String, Integer> arfInit,
			Integer[] memoryArray) {
		// TODO: arfinit, memarray

		reorderBuffer = new ReorderBuffer(reorderBufferSize);
		readFile(filename);s
		reservationStations = new ReservationStation[numRS];
		arf = new ARF(8);
		rrf = new RRF(numRRF_Entries);
	}

	void readFile(String filename) {
		// TODO: read file and populate allInstructionsQueue
	}

	public void start() {
		while (!allInstructionsQueue.isEmpty()) {
			clock++;

			reorderBuffer.commitEntries();

			for (ALU a : aluArray) {
				a.doWork(clock);
			}

			for (ReservationStation r : reservationStations) {
				r.check(clock);
			}

			// do this for 'n' instructions?
			
			while (rrf.isFreeAvailable() && isRSAvailable()) {
				Instruction inst = allInstructionsQueue.poll();
				initInstruction(inst);
				assignToRS(inst);
			}

		}
	}

	/********/
	private void assignToRS(Instruction inst) {
		for (ReservationStation r : reservationStations) {
			if (r.isVacant())
				r.setInstruction(inst);
		}
	}

	private boolean isRSAvailable() {
		for (ReservationStation r : reservationStations) {
			if (r.isVacant())
				return true;
		}
		return false;
	}

	void initInstruction(Instruction inst) {
		String dest_rreg = rrf.getFreeRegister();

		inst.setRRF_tag_dest(dest_rreg);
		rrf.setBusy(dest_rreg, true);
		rrf.setValid(dest_rreg, false);

		if (arf.isBusy(inst.operand1)) {
			String tag = arf.getTag(inst.operand1);
			inst.setRRF_tag_op1(tag);
			if (rrf.isValid(tag)) {
				inst.setData_op1(rrf.getData(tag));
				inst.setReady_op1(true);
			}
		} else {
			inst.setData_op1(arf.getData(inst.operand1));
			inst.setReady_op1(true);
		}

		if (arf.isBusy(inst.operand2)) {
			String tag = arf.getTag(inst.operand2);
			inst.setRRF_tag_op2(tag);
			if (rrf.isValid(tag)) {
				inst.setData_op2(rrf.getData(tag));
				inst.setReady_op2(true);
			}
		} else {
			inst.setData_op2(arf.getData(inst.operand2));
			inst.setReady_op2(true);
		}
	}
}
