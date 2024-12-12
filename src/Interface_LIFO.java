import java.util.Random;

public class Interface_LIFO {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		FixedStack myStack1 = new FixedStack(10);
		
		System.out.println("스택: myStack1");
		System.out.println("push");
		myStack1.pushing();
		System.out.println("\npop");
		myStack1.popStr();
	}

}

interface IStack {
	public void push(int num);
	public int pop();
}

class FixedStack implements IStack {
	private int stack[];
	private int tos;
	private int size;
	
	FixedStack(int size) {
		this.size = size;
		stack = new int[size];
		tos = -1;
	}
	
	public void push(int item) {
		if(tos == stack.length-1) System.out.println("Stack is Full.");
		else stack[++tos] = item;
	}
	
	public int pop() {
		if(tos < 0) {
			System.out.println("Stack is Empty.");
			return 0;
		}
		else return stack[tos--];
	}
	
	public void pushing() {
		Random r = new Random();
		for(int i = 0;i < stack.length; i++) {
			int numbers = r.nextInt(size);
			System.out.print(numbers + " ");
			push(numbers);
		}
	}
	
	public void popStr() {
		for(int i = 0; i < stack.length; i++) {
			System.out.print(pop() + " ");
		}
	}
}