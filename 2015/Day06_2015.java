import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day06_2015
{
    public static void main(String[] args) throws FileNotFoundException
    {
        // Guaranteed to initialize to 0
        int[][] grid = new int[1000][1000];
        int[][] grid2 = new int[1000][1000];

        File file = new File("Day06_2015.txt");
        Scanner scnr = new Scanner(file);

        while (scnr.hasNextLine())
        {
            String[] xList = scnr.nextLine().split("\\s");
            
            String[] xy = xList[xList.length - 3].split(",");
            int x1 = Integer.parseInt(xy[0]);
            int y1 = Integer.parseInt(xy[1]);
            String[] xy2 = xList[xList.length - 1].split(",");
            int x2 = Integer.parseInt(xy2[0]) + 1;
            int y2 = Integer.parseInt(xy2[1]) + 1;
            
            if (xList.length == 5)
            {
                if (xList[1].equals("on"))
                {
                    for (int i = x1; i < x2; i++)
                    {
                        for (int j = y1; j < y2; j++)
                        {
                            grid[i][j] = 1;
                            grid2[i][j]++;
                        }
                    }
                }
                else if (xList[1].equals("off"))
                {
                    for (int i = x1; i < x2; i++)
                    {
                        for (int j = y1; j < y2; j++)
                        {
                            grid[i][j] = 0;
                            if (grid2[i][j] > 0)
                                grid2[i][j]--;
                        }
                    }
                }
                else
                {
                    System.out.println("Error: 5list[1] returned incorrect string");
                    scnr.close();
                    return;
                }
            }
            else if (xList.length == 4)
            {
                for (int i = x1; i < x2; i++)
                {
                    for (int j = y1; j < y2; j++)
                    {
                        if (grid[i][j] == 0)
                            grid[i][j] = 1;
                        else if (grid[i][j] == 1)
                            grid[i][j] = 0;
                        else
                        {
                            System.out.println("Error: grid value not 0 or 1");
                            scnr.close();
                            return;
                        }

                        grid2[i][j] += 2;
                    }
                }
            }
            else
            {
                System.out.println("Error: bad list size returned");
                scnr.close();
                return;
            }
        }

        scnr.close();

        int lightCount = 0;
        int brightness = 0;

        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < 1000; j++)
            {
                if (grid[i][j] == 1)
                    lightCount++;
                brightness += grid2[i][j];
            }
        }
        
        System.out.println("Total number of lights turned on: " + lightCount);
        System.out.println("Cumulative light brightness: " + brightness);
    }
}