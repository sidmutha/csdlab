package assign3;

import java.util.HashMap;
import java.util.Map;

public class ARF {
	int num_entries;
	Map<String, ARF_Entry> ARF_Map;
	

	public ARF(int num_entries) {
		this.num_entries = num_entries;
		ARF_Map = new HashMap<String, ARF_Entry>(num_entries);
		for(int i = 0; i < num_entries; i++){
			String name = "R" + i;
			ARF_Map.put(name, new ARF_Entry(name));
		}
	}
	public void setTag(String reg_name, String tag_name){
		getEntry(reg_name).setRRF_tag(tag_name);
	}
	public ARF_Entry getEntry(String reg_name){
		return ARF_Map.get(reg_name);
	}
	
	public boolean isBusy(String reg_name){
		return getEntry(reg_name).busy;
	}
	
	public Integer getData(String reg_name){
		return getEntry(reg_name).data;
	}
	public String getTag(String reg_name) {
		return getEntry(reg_name).RRF_tag;
	}
	
}