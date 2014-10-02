package assign3;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
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
			Integer[] memoryArray) throws IOException {
		// TODO: arfinit, memarray

		reorderBuffer = new ReorderBuffer(reorderBufferSize);
		readFile(filename);
		reservationStations = new ReservationStation[numRS];
		arf = new ARF(8);
		rrf = new RRF(numRRF_Entries);
	}

	boolean isNumeric(String str) {
		try {
			Integer.parseInt(str);
		} catch (NumberFormatException nfe) {
			return false;
		}
		return true;
	}

	void readFile(String filename) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader(filename));
		String currentLine;
		int i = 0;
		while ((currentLine = br.readLine()) != null) {
			i++;
			String[] tokens = currentLine.split(" ");

			Instruction inst = new Instruction(i, tokens[0], tokens[1],
					tokens[2], tokens[3]);

			if (isNumeric(tokens[2])) {
				inst.setData_op1(Integer.parseInt(tokens[2]));
				inst.setReady_op1(true);
			}

			if (isNumeric(tokens[3])) {
				inst.setData_op2(Integer.parseInt(tokens[3]));
				inst.setReady_op2(true);
			}

			allInstructionsQueue.add(inst);
		}
		br.close();
		System.out.println(allInstructionsQueue.size());
		while (!allInstructionsQueue.isEmpty()) {
			Instruction inst = allInstructionsQueue.poll();
			System.out.println(inst.operation + " " + inst.destination + " "
					+ inst.operand1 + " " + inst.operand2);

		}

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
			if (rrf.isFreeAvailable() && isRSAvailable()) {
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

		inst.setRRF_tag_dest(dest_rreg);
		rrf.setBusy(dest_rreg, true);
		rrf.setValid(dest_rreg, false);

	}
}
