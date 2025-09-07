<?php
$str = "hello world";
$str = str_replace(' ', '', $str);
$chars = str_split($str);
$freq = array_count_values($chars);
foreach ($freq as $char => $count) {
    echo "'$char' => $count\n";
}
?>
