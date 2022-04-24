<?php

$servername = "localhost";
$username = "id18719794_bot123";
$password = "jEN&Uhq7p2YA#H(a";
$dbname = "id18719794_battlebot";

$conn = mysqli_connect($servername, $username, $password, $dbname);

if (!$conn) {
    die("Connection failed: " . $conn->connect_error);
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
    </div> <br> <br>
    <?php
        if (isset($_POST['submit'])) {
            $sql = "SELECT command FROM `task` WHERE id = 1";
            $result = $conn->query($sql);

            if ($result->num_rows > 0) {
                
                while($row = $result->fetch_assoc()) {
                    echo '<div id="command">'. $row["command"] . "<br> Current Task: ";

                    switch($row["command"]) {
                        case 1:
                            echo "Line following";
                            break;
                        case 2:
                            echo "Pre-defined route";
                            break;
                        case 3:
                            echo "Stop";
                            break;
                        default:
                            echo "No command";
                            break;    
                    }
                }
                echo "</div>";
            } else {
                echo "0 results";
            }
        }

        $conn->close();
    ?>
</body>
</html>