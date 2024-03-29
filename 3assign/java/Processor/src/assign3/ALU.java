package assign3;

public class ALU {
	ReservationStation currentRS;
	private ReservationStation[] reservationStations;
	int eta; // time

	public ALU(ReservationStation[] reservationStations) {
		//TODO: add latencies
		
		super();
		this.reservationStations = reservationStations;
	}

	void initRS(ReservationStation rs, int clock) {
		currentRS = rs;
		Instruction inst = rs.getInstruction();
		switch (inst.operation) {
		case "add":
			eta = clock + 2;
			// TODO complete this
		}
	}

	public void doWork(int clock) {
		if (operate(clock)) { // it's time ;)
			if (currentRS != null) {
				currentRS.complete();
				currentRS.done();
			}
			for (ReservationStation r : reservationStations) {
				if (!(r.isVacant() || r.isMarked())) {
					initRS(r, clock);
					r.setMark(true);
					break;
				}
			}
		} else {
			return;
		}
	}

	private boolean operate(int clock) {
		// TODO do the operation and set result in inst
		if (clock != eta) {
			return false;
		} else {
			Instruction inst = currentRS.getInstruction();
			switch (inst.operation) {
			case "add":
				int dest_data;
				dest_data = inst.getData_op1() + inst.getData_op2();
				inst.setData_dest(dest_data);
				break;
			// TODO: complete this
			}
			return true;
		}
	}

}
