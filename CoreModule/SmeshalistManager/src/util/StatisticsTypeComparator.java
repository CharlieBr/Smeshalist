package util;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by katarzyna on 18.12.16.
 */
public class StatisticsTypeComparator implements Comparator<String> {

	private static final Map<String, Integer> typeWeights;

	static {
		typeWeights = new HashMap<>();
		typeWeights.put("vertex",1);
		typeWeights.put("edge",2);
		typeWeights.put("face",3);
		typeWeights.put("block",4);
		typeWeights.put("all",5);
	}

	@Override
	public int compare(String o1, String o2) {
		return typeWeights.get(o1) - typeWeights.get(o2);
	}
}
