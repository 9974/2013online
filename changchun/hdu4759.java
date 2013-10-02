import java.io.*;
import java.util.*;
import java.math.*;
class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int cas = in.nextInt();
        BigInteger one = BigInteger.ONE;
        BigInteger a, b, x, y;
        int n;
        for(int ca = 1; ca <= cas; ca++) {
            n = in.nextInt();
            a = in.nextBigInteger().subtract(one);
            x = in.nextBigInteger().subtract(one);
            b = in.nextBigInteger().subtract(one);
            y = in.nextBigInteger().subtract(one);
            boolean ok = false;
            BigInteger bit = BigInteger.valueOf(1).shiftLeft(n-1);
            a = a.xor(b);
            x = x.xor(y);
            for(int i = 0; i < n; i++) {
                if(a.equals(x) == true) {
                    ok = true;
                    break;
                }
                boolean t = a.testBit(0);
                a = a.shiftRight(1);
                if(t == true) a = a.xor(bit);
            }
            System.out.print("Case "+ca+": ");
            if(ok == true) 
                System.out.println("Yes");
            else 
                System.out.println("No");
        }
    }
}