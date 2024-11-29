public class Authentication {
    public boolean login(String username, String password) {
        // This is a very bad practice, do not store passwords in plain text!
        String[] users = {"user1", "user2", "user3"};
        String[] passwords = {"password1", "password2", "password3"};

        for (int i = 0; i < users.length; i++) {
            if (username.equals(users[i]) && password.equals(passwords[i])) {
                return true;
            }
        }
        return false;
    }
}
