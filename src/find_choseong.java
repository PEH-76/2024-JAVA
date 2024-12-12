
import java.util.Scanner;

public class find_choseong {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		System.out.println("단어를 입력하십시오.");
		String word = input.nextLine();
		while(!word.equals("끝") && !word.equals("end")) { 

			choseong_print(word);
			System.out.println("단어를 입력하십시오.");
			word = input.nextLine();

		
		}
		System.out.println("종료합니다.");
		
	}
	
	
	public static char choseong(char sol_word) {
		
		int dec_sol_word = (int)sol_word;
		if(dec_sol_word >= 0xAC00 && dec_sol_word <= 0xAE4B) return 'ㄱ';
		else if(dec_sol_word >= 0xAE4C && dec_sol_word <= 0xB097) return 'ㄲ';
		else if(dec_sol_word >= 0xB098 && dec_sol_word <= 0xB2E3) return 'ㄴ';
		else if(dec_sol_word >= 0xB2E4 && dec_sol_word <= 0xB52F) return 'ㄷ';
		else if(dec_sol_word >= 0xB530 && dec_sol_word <= 0xB77B) return 'ㄸ';
		else if(dec_sol_word >= 0xB77C && dec_sol_word <= 0xB9C7) return 'ㄹ';
		else if(dec_sol_word >= 0xB9C8 && dec_sol_word <= 0xBC13) return 'ㅁ';
		else if(dec_sol_word >= 0xBC14 && dec_sol_word <= 0xBE5F) return 'ㅂ';
		else if(dec_sol_word >= 0xBE60 && dec_sol_word <= 0xC0AB) return 'ㅃ';
		else if(dec_sol_word >= 0xC0AC && dec_sol_word <= 0xC2F7) return 'ㅅ';
		else if(dec_sol_word >= 0xC2F8 && dec_sol_word <= 0xC543) return 'ㅆ';
		else if(dec_sol_word >= 0xC544 && dec_sol_word <= 0xC78F) return 'ㅇ';
		else if(dec_sol_word >= 0xC790 && dec_sol_word <= 0xC9DB) return 'ㅈ';
		else if(dec_sol_word >= 0xC9DC && dec_sol_word <= 0xCC27) return 'ㅉ';
		else if(dec_sol_word >= 0xCC28 && dec_sol_word <= 0xCE73) return 'ㅊ';
		else if(dec_sol_word >= 0xCE74 && dec_sol_word <= 0xD0BF) return 'ㅋ';
		else if(dec_sol_word >= 0xD0C0 && dec_sol_word <= 0xD30B) return 'ㅌ';
		else if(dec_sol_word >= 0xD30C && dec_sol_word <= 0xD557) return 'ㅍ';
		else if(dec_sol_word >= 0xD558 && dec_sol_word <= 0xD7A3) return 'ㅎ';
		else return sol_word;
	}
	
	public static char[] geulja(String word) {
		char[] word_to = new char[word.length()];
		for(int i = 0; i < word.length(); i ++) {
			word_to[i] = word.charAt(i);
		}
		return word_to;
	}
	
	public static void printings(char sol_choseong) {
		System.out.print(sol_choseong);
	}
	
	public static void choseong_print(String word) {
		char[] seperated = geulja(word);
		for(int i = 0; i < word.length(); i ++) {
			printings(choseong(seperated[i]));

		}
		System.out.println();
	}
}
