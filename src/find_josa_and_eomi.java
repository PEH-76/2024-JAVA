import java.util.Scanner;

class Josa_and_Eomi {
	String word;
	public Josa_and_Eomi(String word) {
		this.word = word;
	}
	public String Finder(String josa_or_eomi) {
		char[] word_to = new char[word.length()];
		for(int i = 0; i < word.length(); i ++) {
			word_to[i] = word.charAt(i);
		}
		if(/*(int)*/word_to[word.length()-1] >= 44032 && (int)word_to[word.length()-1] <= 55203 && ((int)word_to[word.length()-1] - 44032) % 28 != 0) {//받침 있음
			if(josa_or_eomi.equals("을/를") || josa_or_eomi.equals("를/을") || josa_or_eomi.equals("을") || josa_or_eomi.equals("를")) return "을";
			else if(josa_or_eomi.equals("이/가") || josa_or_eomi.equals("가/이") || josa_or_eomi.equals("가") || josa_or_eomi.equals("이")) return "이";
			else if(josa_or_eomi.equals("으로/로") || josa_or_eomi.equals("로/으로") || josa_or_eomi.equals("로") || josa_or_eomi.equals("으로")) {
				if(((int)word_to[word.length()-1] - 44032) % 28 == 8) {//ㄹ 받침
					return "로";
				}
				else return "으로";
			}
			else if(josa_or_eomi.equals("와/과") || josa_or_eomi.equals("과/와") || josa_or_eomi.equals("와") || josa_or_eomi.equals("과")) return "과";
			else if(josa_or_eomi.equals("랑/이랑") || josa_or_eomi.equals("이랑/랑") || josa_or_eomi.equals("랑") || josa_or_eomi.equals("이랑")) return "이랑";
			else if(josa_or_eomi.equals("여/이여") || josa_or_eomi.equals("이여/여") || josa_or_eomi.equals("여") || josa_or_eomi.equals("이여")) return "이여";
			else if(josa_or_eomi.equals("시여") || josa_or_eomi.equals("이시여/시여") || josa_or_eomi.equals("시여") || josa_or_eomi.equals("이시여")) return "이시여";
		}
		else if(word_to[word.length()-1] >= 44032 && (int)word_to[word.length()-1] <= 55203 && ((int)word_to[word.length()-1] - 44032) % 28 == 0){ //받침 없음
			if(josa_or_eomi.equals("을/를") || josa_or_eomi.equals("를/을") || josa_or_eomi.equals("을") || josa_or_eomi.equals("를")) return "를";
			else if(josa_or_eomi.equals("이/가") || josa_or_eomi.equals("가/이") || josa_or_eomi.equals("가") || josa_or_eomi.equals("이")) return "가";
			else if(josa_or_eomi.equals("으로/로") || josa_or_eomi.equals("로/으로") || josa_or_eomi.equals("로") || josa_or_eomi.equals("으로")) return "로";
			else if(josa_or_eomi.equals("와/과") || josa_or_eomi.equals("과/와") || josa_or_eomi.equals("와") || josa_or_eomi.equals("과")) return "와";
			else if(josa_or_eomi.equals("랑/이랑") || josa_or_eomi.equals("이랑/랑") || josa_or_eomi.equals("랑") || josa_or_eomi.equals("이랑")) return "랑";
			else if(josa_or_eomi.equals("여/이여") || josa_or_eomi.equals("이여/여") || josa_or_eomi.equals("여") || josa_or_eomi.equals("이여")) return "여";
			else if(josa_or_eomi.equals("시여") || josa_or_eomi.equals("이시여/시여") || josa_or_eomi.equals("시여") || josa_or_eomi.equals("이시여")) return "시여";
		}
		return "Error";
	}
	public void JosaEomiOutStr(String JosaEomi) {
		if(Finder(JosaEomi).equals("Error")) {
			System.out.println("Error");
		}
		else System.out.println(word + Finder(JosaEomi));
	}
}



public class find_josa_and_eomi {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner inputScanner = new Scanner(System.in);
		String wordInput = inputScanner.next();
		Josa_and_Eomi josaFind = new Josa_and_Eomi(wordInput);
		josaFind.JosaEomiOutStr("으로");
	}

}

