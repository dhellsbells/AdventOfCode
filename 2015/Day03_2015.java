import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Day03_2015
{
    static private class Key
    {
        private final int x;
        private final int y;

        public Key(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        @Override
        public boolean equals(Object o)
        {
            if (this == o)
                return true;
            if (!(o instanceof Key))
                return false;
            Key key = (Key) o;

            return x == key.x && y == key.y;
        }

        @Override
        public int hashCode()
        {
            int result = x;
            result = 31 * result + y;
            return result;
        }
    }
    public static void main(String[] args) throws FileNotFoundException
    {
        File file = new File("Day03_2015.txt");
        Scanner scnr = new Scanner(file);

        int x, y, sx, sy, rx, ry;
        x = y = sx = sy = rx = ry = 0;
        
        Map<Key, Boolean> visitMap = new HashMap<Key, Boolean>();
        Map<Key, Boolean> visitMap2 = new HashMap<Key, Boolean>();

        Key initKey = new Key(0,0);
        visitMap.put(initKey, true);
        visitMap2.put(initKey, true);
        int uniqueVisits1 = 1, uniqueVisits2 = 1;
        boolean isSanta = true;

        while(scnr.hasNext())
        {
            String tempChar = scnr.next();
            char[] tempArr = tempChar.toCharArray();
            
            for(Character c : tempArr)
            {
                if (c == '<')
                {
                    x -= 1;
                    if (isSanta)
                        sx -= 1;
                    else
                        rx -= 1;
                }
                else if (c == '>')
                {
                    x += 1;
                    if (isSanta)
                        sx += 1;
                    else
                        rx += 1;
                }
                else if (c == '^')
                {
                    y += 1;
                    if (isSanta)
                        sy += 1;
                    else
                        ry += 1;
                }
                else if (c == 'v')
                {
                    y -= 1;
                    if (isSanta)
                        sy -= 1;
                    else
                        ry -= 1;
                }

                Key key1 = new Key(x, y);
                if (!visitMap.containsKey(key1))
                {
                    visitMap.put(key1, true);
                    uniqueVisits1++;
                }
                
                if (isSanta)
                {
                    Key key2 = new Key(sx, sy);
                    if (!visitMap2.containsKey(key2))
                    {
                        visitMap2.put(key2, true);
                        uniqueVisits2++;
                    }
                }
                else
                {
                    Key key2 = new Key(rx, ry);
                    if (!visitMap2.containsKey(key2))
                    {
                        visitMap2.put(key2, true);
                        uniqueVisits2++;
                    }
                }

                isSanta = !isSanta;
            }
        }

        scnr.close();

        System.out.println("Number of unique houses visited by Santa alone: " + uniqueVisits1);
        System.out.print("Number of unique houses visited by Santa and Robo-Santa: " + uniqueVisits2);
    }
}