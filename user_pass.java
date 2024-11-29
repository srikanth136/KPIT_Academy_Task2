// public class Authentication {
//     public boolean login(String username, String password) {
//         // This is a very bad practice, do not store passwords in plain text!
//         String[] users = {"user1", "user2", "user3"};
//         String[] passwords = {"password1", "password2", "password3"};

//         for (int i = 0; i < users.length; i++) {
//             if (username.equals(users[i]) && password.equals(passwords[i])) {
//                 return true;
//             }
//         }
//         return false;
//     }
// }


import java.security.NoSuchAlgorithmException;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.KeySpec;

import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.spec.SecretKeySpec;

import org.apache.commons.codec.binary.Base64;

public class Authentication {
    public boolean login(String username, String password) {
        // Securely store passwords using a hashing algorithm like bcrypt or Argon2
        String[] users = {"user1", "user2", "user3"};
        String[] hashedPasswords = {"hashed_password1", "hashed_password2", "hashed_password3"};

        for (int i = 0; i < users.length; i++) {
            // Use a secure comparison method
            String hashedInputPassword = hashPassword(password);
            return MessageDigest.isEqual(hashedInputPassword.getBytes(), hashedPasswords[i].getBytes());
        }
        return false;
    }

    private String hashPassword(String password) {
        int iterations = 10000;
        int keyLength = 256;
        // Use a secure hashing algorithm like bcrypt or Argon2
        KeySpec spec = new PBEKeySpec(password.toCharArray(), "salt_value".getBytes(), iterations, keyLength);
        SecretKeyFactory f = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA256");
        byte[] hash = f.generateSecret(spec).getEncoded();
        return Base64.encodeBase64String(hash);
    }
}
