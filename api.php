
<?php
//The robot gets the command from this file.....link  "https://battlebot.000webhostapp.com/api.php"
        $servername = "localhost";
        $username = "id18719794_bot123";
        $password = "jEN&Uhq7p2YA#H(a";
        $dbname = "id18719794_battlebot";

        // Create connection
        $conn = mysqli_connect($servername, $username, $password, $dbname);
        // Check connection
        if (!$conn) {
        die("Connection failed: " . mysqli_connect_error());
        }

        $sql = "SELECT command FROM task WHERE id = 1";
       // $result = mysqli_query($conn, $sql);

        if($statement = mysqli_prepare($conn, $sql)){
                    
            if(mysqli_stmt_execute($statement)){
                //echo 'Execution Successful';
            }else{
                die("Excution fail" . mysqli_error($conn));
            }
        } 

        mysqli_stmt_bind_result($statement, $command);
        mysqli_stmt_store_result($statement);

        //Check if there are results in the statement
        if(mysqli_stmt_num_rows($statement) != 0){

            while(mysqli_stmt_fetch($statement)){
                echo  $command;
            }
            mysqli_stmt_close($statement);

             mysqli_close($conn);
        }

    