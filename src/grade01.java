import java.util.Scanner;

public class grade01 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		
		System.out.println("점수를 입력하십시오.");
		int num = input.nextInt();
		
		switch(num / 10) {
		case 10:
		case 9:
			System.out.println("A");
			break;
		case 8:
			System.out.println("B");
			break;
		case 7:
			System.out.println("C");
			break;
		case 6:
			System.out.println("D");
			break;
		default:
			System.out.println("F");
			break;
		}
		/*
		if (num >= 90) {
			System.out.println("A");
		}
		else if(num >= 80) {
			System.out.println("B");
		}
		else if(num >= 70) {
			System.out.println("C");
		}
		else if(num >= 60) {
			System.out.println("D");
		}
		else {
			System.out.println("F입니다.");	
		}
		*/
	}

}
