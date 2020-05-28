import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day05_2015
{
    public static void main(String[] args) throws FileNotFoundException
    {
        File file = new File("Day05_2015.txt");
        Scanner scnr = new Scanner(file);
        int niceStrings = 0;
        int niceStrings2 = 0;

        while (scnr.hasNextLine())
        {
            int vowels = 0;
            boolean dblLetter = false;
            boolean dblOtherLetter = false;
            boolean badStrings = false;
            boolean repeatedPair = false;
            char prevChar = '\0';
            char prevChar2 = '\0';

            char[] chars = scnr.nextLine().toCharArray();
            
            for (char ch : chars)
            {
                if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
                    vowels++;
                if (ch == prevChar)
                    dblLetter = true;
                if (ch == prevChar2)
                    dblOtherLetter = true;
                
                String lastTwoChars = new StringBuilder().append(prevChar).append(ch).toString();
                
                if (lastTwoChars.equals("ab") || lastTwoChars.equals("cd") || lastTwoChars.equals("pq") || lastTwoChars.equals("xy"))
                    badStrings = true;

                prevChar2 = prevChar;
                prevChar = ch;
            }

            if (vowels >= 3 && dblLetter == true && badStrings == false)
                niceStrings++;

            for (int i = 0; i < chars.length - 3; i++)
            {
                for (int j = i + 2; j < chars.length - 1; j++)
                {
                    if (chars[i] == chars[j] && chars[i+1] == chars[j+1])
                        repeatedPair = true;
                }
            }

            if (dblOtherLetter == true && repeatedPair == true)
                niceStrings2++;
        }

        scnr.close();

        System.out.println("The number of nice strings in Santa's text file: " + niceStrings);
        System.out.println("The number of nice strings under the new rules: " + niceStrings2);
    }
}