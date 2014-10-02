package assign3;

public class ARF_Entry {
	String reg_name;
	Integer data;
	boolean busy = false;
	String RRF_tag = "";
	
	public ARF_Entry(String name) {
		this.reg_name = name;
	}	

	public boolean isBusy(String reg_name){
		return this.busy;
	}

	public String getRRF_tag() {
		return RRF_tag;
	}

	public void setRRF_tag(String rRF_tag) {
		RRF_tag = rRF_tag;
	}

	public Integer getData() {
		return data;
	}

	public void setData(Integer data) {
		this.data = data;
	}

	public boolean isBusy() {
		return busy;
	}

	public void setBusy(boolean busy) {
		this.busy = busy;
	}
	
}

