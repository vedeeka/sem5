<?php
function swap(&$a, &$b) {
    $temp = $a;
    $a = $b;
    $b = $temp;
}

function permute(&$str, $l, $r) {
    if ($l == $r) {
        echo implode("", $str) . "\n";
    } else {
        for ($i = $l; $i <= $r; $i++) {
            swap($str[$l], $str[$i]); // Swap
            permute($str, $l + 1, $r);
            swap($str[$l], $str[$i]); // Backtrack
        }
    }
}

$str = str_split("abc");
$n = count($str);
permute($str, 0, $n - 1);
?>
