//call with$ javac test.java 
//and then $ test agr1 agr2 agr3
//in the comand line
public class test {
    public static void main(String[] args) {
        for (int i = 0; i < args.length; i++) {
            System.out.println(args[i]);
        }
    }
}
