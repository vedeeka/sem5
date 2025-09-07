<?php
$str = "abc";

for ($i = 0; $i < 3; $i++) {
    for ($j = 0; $j < 3; $j++) {
        if ($j == $i) continue;
        for ($k = 0; $k < 3; $k++) {
            if ($k == $i || $k == $j) continue;
            echo $str[$i] . $str[$j] . $str[$k] . "\n";
        }
    }
}
?>
