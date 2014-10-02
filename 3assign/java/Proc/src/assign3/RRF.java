package assign3;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

public class RRF {
	int num_entries;
	Map<String, RRF_Entry> RRF_Map;
	

	public RRF(int num_entries) {
		this.num_entries = num_entries;
		RRF_Map = new HashMap<String, RRF_Entry>(num_entries);
		for(int i = 0; i < num_entries; i++){
			String tag_name = "S" + i;
			RRF_Map.put(tag_name, new RRF_Entry(tag_name));
		}
	}
	
	public boolean isValid(String reg_name){
		return getEntry(reg_name).valid;
	}
	
	public boolean isBusy(String reg_name){
		return getEntry(reg_name).busy;
	}
	
	public RRF_Entry getEntry(String reg_name){
		return RRF_Map.get(reg_name);
	}
	
	public boolean isFreeAvailable(){
		for(Entry<String, RRF_Entry> e : RRF_Map.entrySet()){
			if(e.getValue().busy == false){
				return true;
			}
		}
		return false;
	}
	public String getFreeRegister() {
		// TODO Auto-generated method stub
		String freeReg = null;
		for (Map.Entry<String, RRF_Entry> entry : RRF_Map.entrySet()) {
		    if(entry.getValue().busy == false){
		    	freeReg = entry.getKey();
		    	break;
		    }	
			//System.out.println("Key = " + entry.getKey() + ", Value = " + entry.getValue());
		}
		
		
		return freeReg;
	}

	public Integer getData(String tag) {
		return getEntry(tag).data;
	}

	public void setBusy(String dest_rreg, boolean b) {
		getEntry(dest_rreg).busy = b;
	}
	
	public void setValid(String dest_rreg, boolean b) {
		getEntry(dest_rreg).valid = b;
	}
}
