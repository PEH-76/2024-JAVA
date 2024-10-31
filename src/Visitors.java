
public class Visitors {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		String CityName[] = {"서울", "부산", "인천", "대전", "대구"};
		int Visitors[] = {599, 51, 46, 43, 27};
		
		for(int i = 0; i < CityName.length; i++) System.out.printf("%s: %d명\n", CityName[i], Visitors[i]);
	}

}
