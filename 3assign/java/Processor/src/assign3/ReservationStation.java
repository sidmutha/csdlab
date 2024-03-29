package assign3;

public class ReservationStation {
	Instruction myInstruction;
	boolean vacant = true;
	RRF rrf;
	ARF arf;
	private boolean mark;
	public ReservationStation(Instruction myInstruction) {
		super();
		this.myInstruction = myInstruction;
	}

	public ReservationStation(ARF arf, RRF rrf) {
		super();
		this.arf = arf;
		this.rrf = rrf;
	}

	public Instruction getInstruction() {
		return myInstruction;
	}

	public void setInstruction(Instruction myInstruction) {
		this.myInstruction = myInstruction;
		this.vacant = false;
	}
	
	public boolean isVacant(){
		return this.vacant;
	}
	
	public void complete(){
		myInstruction.completed = true;
	}
	
	public void done(){
		vacant = true;
	}
	
	public boolean check(int clock){
		if(vacant)
			return true;
		
		if(myInstruction.ready_op1 == false){
			if(rrf.isValid(myInstruction.operand1)){
				myInstruction.ready_op1 = true;
			}else{
				return false;
			}
		}
		
		if(myInstruction.ready_op2 == false){
			if(rrf.isValid(myInstruction.operand2)){
				myInstruction.ready_op2 = true;
			}else{
				return false;
			}
		}
		
		return true;
	}

	public void setMark(boolean b) {
		this.mark = b;
	}
	
	public boolean isMarked() {
		return this.mark;
	}
}
