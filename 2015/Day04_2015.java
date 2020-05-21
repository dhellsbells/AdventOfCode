import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Day04_2015 {
    public static void main(String[] args) throws NoSuchAlgorithmException
    {
        String secretKey = "ckczppom";
        int keyFollower = 1;

        // Create MD5 digest instance
        MessageDigest md5 = MessageDigest.getInstance("MD5");

        while (true)
        {
            String inputKey = secretKey + String.valueOf(keyFollower);
            byte[] inputBytes = inputKey.getBytes(StandardCharsets.UTF_8);

            byte[] outputBytes = md5.digest(inputBytes);

            // Don't actually need to convert to hex. Just check the first 3 byte values.
            if (outputBytes[0] == 0 && outputBytes[1] == 0 && (outputBytes[2] >= 0 && outputBytes[2] < 16))
            {
                System.out.println("The lowest positive number leading to the MD5 hash starting with at least 5 zeroes is: " + keyFollower);
                break;
            }
            else
                keyFollower++;
        }

        while (true)
        {
            String inputKey = secretKey + String.valueOf(keyFollower);
            byte[] inputBytes = inputKey.getBytes(StandardCharsets.UTF_8);

            byte[] outputBytes = md5.digest(inputBytes);

            // Don't actually need to convert to hex. Just check the first 3 byte values.
            if (outputBytes[0] == 0 && outputBytes[1] == 0 && outputBytes[2] == 0)
            {
                System.out.println("The lowest positive number leading to the MD5 hash starting with at least 6 zeroes is: " + keyFollower);
                break;
            }
            else
                keyFollower++;
        }
    }
}