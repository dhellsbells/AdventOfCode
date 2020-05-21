import hashlib

secretKey = "ckczppom"
keyFollower = 1

while True:
    inputKey = secretKey + str(keyFollower)
    hashedKey = hashlib.md5(inputKey.encode())

    if hashedKey.hexdigest()[0:5] == "00000":
        print("The lowest positive number leading to the MD5 hash starting with at least 5 zeroes is: ", end = "")
        print(keyFollower)
        print("The AdventCoint MD5 hash for ", end = "")
        print(secretKey, end = "")
        print(" is: ", end = "")
        print(hashedKey.hexdigest())
        break
    else:
        keyFollower += 1

while True:
    inputKey = secretKey + str(keyFollower)
    hashedKey = hashlib.md5(inputKey.encode())

    if hashedKey.hexdigest()[0:6] == "000000":
        print("The lowest positive number leading to the MD5 hash starting with at least 6 zeroes is: ", end = "")
        print(keyFollower)
        print("The AdventCoint MD5 hash for ", end = "")
        print(secretKey, end = "")
        print(" is: ", end = "")
        print(hashedKey.hexdigest())
        break
    else:
        keyFollower += 1
        