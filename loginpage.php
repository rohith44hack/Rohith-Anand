<?php
session_start();

$valid_username = 'rohith';
$valid_password = 'scottaddictse';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (isset($_POST['username']) && isset($_POST['password'])) {
        $username = $_POST['username'];
        $password = $_POST['password'];

        if ($username === $valid_username && $password === $valid_password) {
            $_SESSION['loggedin'] = true;
            $_SESSION['username'] = $username;
        } else {
            $error = "Invalid username or password.";
        }
    }
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Login Page</title>
</head>
<body>
<?php if (isset($_SESSION['loggedin']) && $_SESSION['loggedin'] === true): ?>
    <h2>Welcome, <?php echo htmlspecialchars($_SESSION['username']); ?>!</h2>
    <p>You are now logged in.</p>
    <form method="post" action="loginpage.php">
        <input type="submit" name="logout" value="Logout">
    </form>
<?php else: ?>
    <h2>Login</h2>
    <?php if (!empty($error)) echo "<p style='color:red;'>$error</p>"; ?>
    <form method="POST" action="loginpagephp">
        <label>Username:</label>
        <input type="text" name="username" required><br><br>
        <label>Password:</label>
        <input type="password" name="password" required><br><br>
        <input type="submit" value="Login">
    </form>
<?php endif; ?>

<?php
if (isset($_POST['logout'])) {
    session_destroy();
    header("Location: loginpage.php");
    exit;
}
?>
</body>
</html>

