<?php 
$conn = mysqli_connect("localhost","root","","batchd");
if(!$conn){
    die("Connection Failed: ".mysqli_connect_error());
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Textbook CRUD</title>
</head>
<body>

<!-- INSERT FORM -->
<form method="post" action="pract.php">
    <input type="text" name="book_isbn" placeholder="Enter ISBN"><br>
    <input type="text" name="book_title" placeholder="Enter Title"><br>
    <input type="text" name="author" placeholder="Enter Author"><br>
    <input type="text" name="publisher" placeholder="Enter Publisher"><br>
    <input type="submit" name="save" value="Save Data">
</form>

<?php
// INSERT
if(isset($_POST['save'])){
    $book_isbn = $_POST['book_isbn'];
    $book_title = $_POST['book_title'];
    $author = $_POST['author'];
    $publisher = $_POST['publisher']; 

    $query = "INSERT INTO textbook(book_isbn,book_title,author,publisher) 
              VALUES('$book_isbn','$book_title','$author','$publisher')";
    $result = mysqli_query($conn,$query);

    echo $result ? "Data Saved Successfully" : "Data Not Saved";
}

// DELETE
if(isset($_GET['delete'])){
    $id = $_GET['delete'];
    mysqli_query($conn,"DELETE FROM textbook WHERE book_isbn='$id'");
    echo "Data Deleted Successfully";
}

// FETCH FOR EDIT
if(isset($_GET['edit'])){
    $edit_id = $_GET['edit'];
    $res = mysqli_query($conn,"SELECT * FROM textbook WHERE book_isbn='$edit_id'");
    $row = mysqli_fetch_array($res);
?>

<!-- UPDATE FORM -->
<form method="post" action="pract.php">
    <input type="text" name="book_isbn" value="<?php echo $row['book_isbn']; ?>"><br>
    <input type="text" name="book_title" value="<?php echo $row['book_title']; ?>"><br>
    <input type="text" name="author" value="<?php echo $row['author']; ?>"><br>
    <input type="text" name="publisher" value="<?php echo $row['publisher']; ?>"><br>
    <input type="hidden" name="edit_isbn" value="<?php echo $row['book_isbn']; ?>">
    <input type="submit" name="update" value="Update Data">
</form>

<?php } ?>

<?php
// UPDATE
if(isset($_POST['update'])){
    $book_isbn = $_POST['book_isbn'];
    $book_title = $_POST['book_title'];
    $author = $_POST['author'];
    $publisher = $_POST['publisher'];
    $edit_isbn = $_POST['edit_isbn'];

    mysqli_query($conn,"UPDATE textbook 
                         SET book_isbn='$book_isbn',
                             book_title='$book_title',
                             author='$author',
                             publisher='$publisher'
                         WHERE book_isbn='$edit_isbn'");
    echo "Data Updated Successfully";
}

// DISPLAY DATA
$result = mysqli_query($conn, "SELECT * FROM textbook");
while($row = mysqli_fetch_array($result)){
    echo $row['book_isbn']." ".$row['book_title']." ".$row['author']." ".$row['publisher']." ";
?>
    <a href="pract.php?delete=<?php echo $row['book_isbn']; ?>">Delete</a> |
    <a href="pract.php?edit=<?php echo $row['book_isbn']; ?>">Edit</a>
    <br>
<?php } ?>

</body>
</html>
