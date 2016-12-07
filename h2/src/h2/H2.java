package h2;

/**
 *
 * @author vaclav
 */
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.util.Map;
import java.util.SortedSet;
import java.util.TreeMap;
import java.util.TreeSet;

/**
 * Template shamelessly stolen from Petr
 */
public class H2 {

    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        TaskH solver = new TaskH();
        int tn = in.nextInt();
        for (int i = 0; i < tn; i++) {
            solver.solve(in, out);
        }
        out.close();
    }

    static class TaskH {

        static final Long INF = 1000000000000l;

        interface Comp {

            public boolean goLeft(Long a, Long b);
        }

        Map.Entry<Long, Long> binarySearch(TreeMap<Long, Long> dp, Comp comp) {
            Map.Entry<Long, Long> res = dp.lastEntry();
            Long from = dp.higherKey(-INF + 1);
            Long to = dp.lowerKey(INF - 1);
            while (from <= to) {
                Long avg = (from + to) / 2;
                Map.Entry<Long, Long> e1 = dp.ceilingEntry(avg);
                Map.Entry<Long, Long> e2 = dp.higherEntry(e1.getKey());
                if (e1.getValue() <= res.getValue()) res = e1;
                if (e2.getValue() <= res.getValue()) res = e2;

                if (comp.goLeft(e1.getValue(), e2.getValue())) to = avg - 1;
                else from = avg + 1;
            }
            return res;
        }

        public void solve(InputReader in, PrintWriter out) {
            int n = in.nextInt();
            long d = in.nextInt();
            long[] heights = new long[n];
            for (int i = 0; i < n; i++) {
                heights[i] = in.nextInt();
            }
            TreeSet<Long> relevant = new TreeSet();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n + 1; j++) {
                    relevant.add(heights[i] - d * j);
                    relevant.add(heights[i] + d * j);
                }
            }
            // for (Long x : relevant) out.print(x + " "); out.println();
            TreeMap<Long, Long> dp = new TreeMap(), dp2;

            dp.put(heights[0], 0l);
            dp.put(INF, INF);
            dp.put(-INF, INF);
            dp.put(INF - 1, INF - 1);
            dp.put(-INF + 1, INF - 1);

            for (int i = 1; i < n; i++) {
                //System.out.println(i + " " + dp.size());
                dp2 = new TreeMap();
                dp2.put(INF, INF);
                dp2.put(-INF, INF);
                dp2.put(INF - 1, INF - 1);
                dp2.put(-INF + 1, INF - 1);
                
                Map.Entry<Long,Long> bestLeft = binarySearch(dp, (a, b) -> (a <= b));
                Map.Entry<Long,Long> bestRight = binarySearch(dp, (a, b) -> (a < b));
                //.subSet(dp.higherKey(-INF) - d, true,dp.lowerKey(INF) + d, true)
                for (Long h2 : relevant.subSet(dp.higherKey(-INF + 1) - d, true, dp.lowerKey(INF - 1) + d, true)) {
                    Map.Entry<Long, Long> best;
                    if(h2 + d < bestLeft.getKey()) { // nalevo
                        best = dp.floorEntry(h2 + d);
                    } else if(h2 - d > bestRight.getKey()) { // napravo
                        best = dp.ceilingEntry(h2 - d);
                    } else {
                        best = bestLeft;
                    }
                    //out.println("I think: " + h2 + " = " + (best.getValue() + Math.abs(h2 - heights[i])));
                    dp2.put(h2, best.getValue() + Math.abs(h2 - heights[i]));
                    
                    /*
                    for (Map.Entry<Long, Long> e : dp.subMap(h2 - d, h2 + d + 1l).entrySet()) {
                        Long h1 = e.getKey();
                        //out.println(h2);
                        Long val = dp2.getOrDefault(h2, INF);
                        val = Math.min(val, e.getValue() + Math.abs(h2 - heights[i]));
                        dp2.put(h2, val);
                    }
                    */
                }
                /*out.println("b:" + bestLeft);
                out.println("b:" + bestRight);
                for (Map.Entry<Long, Long> e : dp2.entrySet()) {
                    out.println(e.getKey() + ": " + e.getValue());
                }
                out.println();*/
                dp = dp2;
            }

            Long res = dp.get(heights[n - 1]);
            if (res == null) res = -1l;
            out.println(res);
        }
    }

    static class InputReader {

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
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

    }
}
