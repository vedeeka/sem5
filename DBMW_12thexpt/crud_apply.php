<?php
$servername = "localhost";
$username = "root";  
$password = "";
$dbname = "batchd";

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) die("Connection failed: " . $conn->connect_error);


if (isset($_POST['action'])) {
  $sid = $_POST['sid'];
  $cname = $_POST['cname'] ?? '';
  $major = $_POST['major'] ?? '';
  $decision = $_POST['decision'] ?? '';

  if ($_POST['action'] == 'Add') {
    if (!empty($sid) && !empty($cname) && !empty($major) && !empty($decision)) {
      $sql = "INSERT INTO apply (sid, cname, major, decision) VALUES ('$sid', '$cname', '$major', '$decision')";
    } else {
      $sql = "";
      echo "<script>alert('Please fill all fields to add a record!');</script>";
    }
  } elseif ($_POST['action'] == 'Update') {
    $sql = "UPDATE apply SET cname='$cname', major='$major', decision='$decision' WHERE sid='$sid'";
  } elseif ($_POST['action'] == 'Delete') {
    $sql = "DELETE FROM apply WHERE sid='$sid'";
  }

  if (!empty($sql)) {
    if ($conn->query($sql) === TRUE) {
      echo "<script>alert('Operation successful!');</script>";
    } else {
      echo "<script>alert('Error: " . addslashes($conn->error) . "');</script>";
    }
  }
}

$result = $conn->query("SELECT * FROM apply");
?>

<!DOCTYPE html>
<html>
<head>
  <title>CRUD Form - Apply Table</title>

</head>
<body>

<h2>CRUD Operation on <em>apply</em> Table</h2>
<div class="container">

<form method="post">
  <div>
    <label>Sstudent ID (Required for All Operations):</label>
    <input type="number" name="sid" >
  </div>

  <div>
    <label>College Name (Required for Add/Update):</label>
    <input type="text" name="cname">
  </div>

  <div>
    <label>Major (Required for Add/Update):</label>
    <input type="text" name="major">
  </div>

  <div>
    <label>Decision (Required for Add/Update):</label>
    <input type="text" name="decision">
  </div>

  <div class="btn-group">
    <button type="submit" name="action" value="Add">➕ Add</button>
    <button type="submit" name="action" value="Update">✏️ Update by SID</button>
    <button type="submit" name="action" value="Delete">🗑️ Delete by SID</button>
  </div>
</form>

<h3>📋 Current Records</h3>
<table>
  <tr>
    <th>SID</th>
    <th>College Name</th>
    <th>Major</th>
    <th>Decision</th>
  </tr>
  <?php while($row = $result->fetch_assoc()) { ?>
  <tr>
    <td><?= htmlspecialchars($row['sid']) ?></td>
    <td><?= htmlspecialchars($row['cname']) ?></td>
    <td><?= htmlspecialchars($row['major']) ?></td>
    <td><?= htmlspecialchars($row['decision']) ?></td>
  </tr>
  <?php } ?>
</table>

</div>
</body>
</html>

<?php $conn->close(); ?>
