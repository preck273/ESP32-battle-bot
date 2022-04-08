<?php

require_once "includes/connectToDb.php";

    //create table in the database name battlebot
    $db = "CREATE TABLE task 
    (
        id int not null auto_increment,
        command int(11) NOT NULL,
        CONSTRAINT pk_id PRIMARY KEY(id)

    )";

$statement = mysqli_prepare($conn, $db)or
die(mysqli_error($conn));
mysqli_stmt_execute($statement)or
die("There is an Error creating the Table");
echo ("Table created");
mysqli_stmt_close($statement);
mysqli_close($conn);
