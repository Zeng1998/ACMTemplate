import java.io.*;
import java.util.StringTokenizer;
public class Main{
    static class InputReader{
        public BufferedReader reader;
        public StringTokenizer tokenizer;
        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }
        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {e.printStackTrace();}
            }
            return tokenizer.nextToken();
        }
        public int nextInt(){
            return Integer.parseInt(next());
        }
    }
    public static void main(String[] args) {
        InputReader cin=new InputReader(new BufferedInputStream(System.in));
    }
}
