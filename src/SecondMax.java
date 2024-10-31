
public class SecondMax {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		int[] numbers = {65, 74, 23, 75, 68, 98, 54};
		int secondTopIdx = getSecondTopIdx(numbers);
		System.out.println("배열: {65, 74, 23, 75, 68, 98, 54}");
		System.out.printf("두 번째로 큰 수: %d", numbers[secondTopIdx]);
	}
	
	public static int getSecondTopIdx(int[] arr) {
		int secondIdx = 0;
		int topIdx = getTopIndex(arr);
		for(int i = 0; i < arr.length; i++) {
			if(arr[secondIdx] <= arr[i]) {
				if(secondIdx == topIdx) {
					continue;
				}
				
				else {
					secondIdx = i;
				}
			}
		}
		
		return secondIdx;
		
		
		
	}
	
	public static int getTopIndex(int[] arr) {
		int topIdx = 0;
		for(int i = 0; i < arr.length; i++) {
			if(arr[topIdx] <= arr[i]) {
				topIdx = i;
			}
		}
		
		return topIdx;
	}

}
