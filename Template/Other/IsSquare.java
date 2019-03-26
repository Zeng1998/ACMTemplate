import java.math.BigInteger;
import java.util.Scanner;

public class IsSquare {
    public static boolean check(BigInteger now){
        if(now.compareTo(BigInteger.ZERO)==0||now.compareTo(BigInteger.ONE)==0){
            return true;
        }
        if(now.mod(BigInteger.valueOf(3)).compareTo(BigInteger.valueOf(2))==0){
            return false;
        }
        String s = now.toString();
        if(s.length()%2==0){
            s = s.substring(0,s.length()/2+1);
        }else{ 			
            s = s.substring(0,(1+s.length())/2);
        }
        BigInteger res = BigInteger.ZERO;
        BigInteger m = new BigInteger(s);
        BigInteger two = new BigInteger("2");
        if(s == "1"){
            res = BigInteger.ONE;
        }else{
            while(now.compareTo(m.multiply(m)) < 0){
                m = (m.add(now.divide(m))).divide(two);
            }
            res = m;
        }
        if (res.multiply(res).compareTo(now) == 0){
            return true;
        }
        return false;
    }
}
