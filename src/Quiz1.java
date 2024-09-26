import java.util.Scanner;

public class Quiz1 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		System.out.print("점수를 입력하세요.: ");
		double score = input.nextDouble();
		String grade;
		
		/*
		if(score >= 95) {
			grade = "A+";
			System.out.printf("%.2f점 -> %s", score, grade);
		}
		else if(score >= 90) {
			grade = "A";
			System.out.printf("%.2f점 -> %s", score, grade);
		}
		else if(score >= 85) {
			grade = "B+";
			System.out.printf("%.2f점 -> %s", score, grade);
		}
		else if(score >= 80) {
			grade = "B";
			System.out.printf("%.2f점 -> %s", score, grade);
		}
		else {
			grade = "C";
			System.out.printf("%.2f점 -> %s", score, grade);
		}
		*/
		
		switch((int)(score / 5)) {
		case 20 :
		case 19 :
			grade = "A+";
			System.out.printf("%.2f점 -> %s", score, grade);
			break;
		case 18 :
			grade = "A";
			System.out.printf("%.2f점 -> %s", score, grade);
			break;
		case 17 :
			grade = "B+";
			System.out.printf("%.2f점 -> %s", score, grade);
			break;
		case 16 :
			grade = "B";
			System.out.printf("%.2f점 -> %s", score, grade);
			break;
		default:
			grade = "C";
			System.out.printf("%.2f점 -> %s", score, grade);
			break;
		}
	}

}
