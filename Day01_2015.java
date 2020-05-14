import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day01_2015
{
    public static void main(String[] args) throws FileNotFoundException
    {
        File file = new File("Day01_2015.txt");
        Scanner scnr = new Scanner(file);
        int floor = 0;
        int position = 0;
        boolean setFinal = false;
        int finalPosition = 0;

        while(scnr.hasNext())
        {
            String tempChar = scnr.next();
            char[] tempArr = tempChar.toCharArray();
            for(Character j : tempArr)
            {
                if (j == '(')
                    floor++;
                else if (j == ')')
                    floor--;
                position++;
                if (floor == -1 && !setFinal)
                {
                    finalPosition = position;
                    setFinal = true;
                }
            }
        }

        scnr.close();
        System.out.println("The floor is: " + floor);
        System.out.print("The position of the first character that enters the basement is: " + finalPosition);
    }
}
