import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day02_2015
{
    public static void main(String[] args) throws FileNotFoundException
    {
        File file = new File("Day02_2015.txt");
        Scanner scnr = new Scanner(file);

        int paperFeet = 0;
        int ribbonFeet = 0;
        int l, w, h, lw, wh, lh, sFace, sSide1, sSide2;
        
        while (scnr.hasNextLine())
        {
            String[] dims = scnr.nextLine().split("x");
            l = Integer.parseInt(dims[0]);
            w = Integer.parseInt(dims[1]);
            h = Integer.parseInt(dims[2]);
            
            lw = l * w;
            wh = w * h;
            lh = l * h;
            sFace = lw;

            if (wh < sFace)
                sFace = wh;
            if (lh < sFace)
                sFace = lh;
            
            if (w < l)
            {
                sSide1 = w;
                sSide2 = l;
            }
            else
            {
                sSide1 = l;
                sSide2 = w;
            }
            if (h < sSide1)
            {
                sSide2 = sSide1;
                sSide1 = h;
            }
            else if (h < sSide2)
                sSide2 = h;
            
            paperFeet += 2*lw + 2*wh + 2*lh + sFace;
            ribbonFeet += 2*sSide1 + 2*sSide2 + l*w*h;
        }

    scnr.close();

    System.out.println("Total square feet of paper needed: " + paperFeet);
    System.out.print("Total feet of ribbon needed: " + ribbonFeet);
    }
}