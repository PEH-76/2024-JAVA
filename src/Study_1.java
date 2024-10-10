
public class Study_1 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		for(int die_1 = 1; die_1 <= 6; die_1 ++) {
			for(int die_2 = 1; die_2 <= 6; die_2 ++) {
				if(die_1 + die_2 == 10) {
					System.out.printf("(%d, %d)\n", die_1, die_2);
				}
			}
		}
	}

}
