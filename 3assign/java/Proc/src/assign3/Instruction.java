package assign3;

public class Instruction {
	int inst_number;
	String operation, destination, operand1, operand2;
	String RRF_tag_dest, RRF_tag_op1, RRF_tag_op2;
	Integer data_dest, data_op1, data_op2;
	boolean ready_op1, ready_op2;
	boolean completed;
	
	public Instruction(int inst_number, String operation, String destination,
			String operand1, String operand2) {
		super();
		this.inst_number = inst_number;
		this.operation = operation;
		this.destination = destination;
		this.operand1 = operand1;
		this.operand2 = operand2;
	}

	public String getRRF_tag_dest() {
		return RRF_tag_dest;
	}

	public Integer getData_dest() {
		return data_dest;
	}

	public void setData_dest(Integer data_dest) {
		this.data_dest = data_dest;
	}

	public Integer getData_op1() {
		return data_op1;
	}

	public void setData_op1(Integer data_op1) {
		this.data_op1 = data_op1;
	}

	public Integer getData_op2() {
		return data_op2;
	}

	public void setData_op2(Integer data_op2) {
		this.data_op2 = data_op2;
	}

	public void setRRF_tag_dest(String rRF_tag_dest) {
		RRF_tag_dest = rRF_tag_dest;
	}

	public String getRRF_tag_op1() {
		return RRF_tag_op1;
	}

	public void setRRF_tag_op1(String rRF_tag_op1) {
		RRF_tag_op1 = rRF_tag_op1;
	}

	public String getRRF_tag_op2() {
		return RRF_tag_op2;
	}

	public void setRRF_tag_op2(String rRF_tag_op2) {
		RRF_tag_op2 = rRF_tag_op2;
	}

	public boolean isReady_op1() {
		return ready_op1;
	}

	public void setReady_op1(boolean ready_op1) {
		this.ready_op1 = ready_op1;
	}

	public boolean isReady_op2() {
		return ready_op2;
	}

	public void setReady_op2(boolean ready_op2) {
		this.ready_op2 = ready_op2;
	}

	public boolean isCompleted() {
		return completed;
	}

	public void setCompleted(boolean completed) {
		this.completed = completed;
	}
	
	
}
