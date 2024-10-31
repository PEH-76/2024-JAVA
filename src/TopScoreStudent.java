
public class TopScoreStudent {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		String[] names = {"Elena", "Suzie", "John", "Emily", "Neda", "Kate", "Alex", "Daniel", "Sam"};
		int[] scores = {65, 74, 23, 75, 68, 96, 88, 95, 54};
		
		int i = topIndex(scores);
		
		System.out.printf("1등: %s(%d)점", names[i], scores[i]);
		
	}
	
	public static int topIndex(int arr[]) {
		int topIndex = 0;
		for(int i = 0; i < arr.length; i++) {
			if(arr[topIndex] <= arr[i]) {
				topIndex = i;
			}
		}
		
		return topIndex;
	}

}
