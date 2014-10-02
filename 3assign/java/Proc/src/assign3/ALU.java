package assign3;

public class ALU {
	ReservationStation currentRS;
	private ReservationStation[] reservationStations;
	int eta; // time
    int latency_add;
    int latency_sub;
    int latency_mul;
    int latency_div;
    int latency_and;
    int latency_or;
    int latency_exor;
    
	public ALU(ReservationStation[] reservationStations, int l_add, int l_sub, int l_mul, int l_div, int  l_and, int l_or, int l_exor) {
		super();
		this.reservationStations = reservationStations;
		this.latency_add = l_add;
		this.latency_sub = l_sub;
		this.latency_mul = l_mul;
		this.latency_div = l_div;
		this.latency_and = l_and;
		this.latency_or = l_or;
		this.latency_exor = l_exor;
		
	}

	void initRS(ReservationStation rs, int clock) {
		currentRS = rs;
		Instruction inst = rs.getInstruction();
		switch (inst.operation) {
		case "ADD":
			eta = clock + this.latency_add;
			break;
		case "SUB":
			eta = clock + this.latency_sub;
			break;
		case "MUL":
			eta = clock + this.latency_mul;
			break;
		case "DIV":
			eta = clock + this.latency_div;
			break;
		case "AND":
			eta = clock + this.latency_and;
			break;
		case "OR":
			eta = clock + this.latency_or;
			break;
		case "EXOR":
			eta = clock + this.latency_exor;
			break;
			//  complete this
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
			case "ADD":
				int dest_data;
				dest_data = inst.getData_op1() + inst.getData_op2();
				inst.setData_dest(dest_data);
				break;
			case "SUB":
				int dest_data;
				dest_data = inst.getData_op1() - inst.getData_op2();
				inst.setData_dest(dest_data);
				break;
			case "MUL":
				int dest_data;
				dest_data = inst.getData_op1() * inst.getData_op2();
				inst.setData_dest(dest_data);
				break;
			case "DIV":
				int dest_data;
				dest_data = inst.getData_op1() / inst.getData_op2();
				inst.setData_dest(dest_data);
				break;
			case "AND":
				int dest_data;
				dest_data = inst.getData_op1() & inst.getData_op2();
				inst.setData_dest(dest_data);
				break;
			case "OR":
				int dest_data;
				dest_data = inst.getData_op1() | inst.getData_op2();
				inst.setData_dest(dest_data);
				break;
			case "EXOR":
				int dest_data;
				dest_data = inst.getData_op1() ^ inst.getData_op2();
				inst.setData_dest(dest_data);
				break;
				
			// complete this
			}
			return true;
		}
	}

}
