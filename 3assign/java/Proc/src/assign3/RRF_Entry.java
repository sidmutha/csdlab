package assign3;

public class RRF_Entry {
	public String tag;
	Integer data;
	public boolean busy = false, valid = false;

	public RRF_Entry(String tag) {
		this.tag = tag;
	}
	
	public boolean isBusy(){
		return this.busy;
	}

	public boolean isValid(){
		return this.valid;
	}
}
