<?

//connect to the database created server, username, password and database name
$conn = mysqli_connect('localhost', 'id18719794_bot123', 'jEN&Uhq7p2YA#H(a', 'id18719794_battlebot');
    if(!$conn){
        die('Connection Error' . mysqli_error($conn));
    }