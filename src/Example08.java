import java.util.Scanner;

public class Example08 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
				
		System.out.println("당신의 이름을 입력하세요.");
		String name = input.nextLine();
		/*
		String name1 = input.next();
		String name2 = input.next();
		System.out.println("당신의 이름 : " + name1);
		System.out.println("당신의 이름 : " + name2);
		*///next()는 공백을 기준으로 계속 받아옴
		System.out.println("당신의 이름 : " + name);
	}

}
