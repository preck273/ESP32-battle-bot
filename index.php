<?php

$servername = "localhost";
$username = "id18719794_bot123";
$password = "jEN&Uhq7p2YA#H(a";
$dbname = "id18719794_battlebot";

$conn = mysqli_connect($servername, $username, $password, $dbname);
if ($conn) {

} else if (!$conn) {
    echo "error";
}

if (isset($_POST['submit'])) {
    $value = $_POST['submit'];
    $sql = "UPDATE `task` SET command =" . $value . " WHERE id = 1";

    if ($stmt = $conn->prepare($sql)) {
        $stmt->execute()
            or die("Could not run query: " . $conn->error);
    } else {
        echo "error";
    }  
} 


?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>Battlebot</title>
</head>
<body>
    <div class="container">
        <h1> Battlebot Task</h1>
        <form action="" method="POST">                   
            <button type="submit" id="btn" name = "submit" value="1">Line Following</button><br><br>
            <button type="submit" id="btn" name = "submit" value = "2" >Pre-defined route</button> <br><br>
            <button type="submit" id="btn" name = "submit" value = "3" >Stop</button> 
        </form>
    </div>
        
</body>
</html>