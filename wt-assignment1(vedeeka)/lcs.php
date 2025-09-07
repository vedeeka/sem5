<?php
function lcs($t1, $t2) {
    $m = strlen($t1);
    $n = strlen($t2);
    $L = array_fill(0, $m + 1, array_fill(0, $n + 1, 0));


    for ($i = 1; $i <= $m; $i++) {
        for ($j = 1; $j <= $n; $j++) {
            if ($t1[$i - 1] === $t2[$j - 1]) {
                $L[$i][$j] = $L[$i - 1][$j - 1] + 1;
            } else {
                $L[$i][$j] = max($L[$i - 1][$j], $L[$i][$j - 1]);
            }
        }
    }


    $i = $m;
    $j = $n;
    $lcs = '';
    while ($i > 0 && $j > 0) {
        if ($t1[$i - 1] === $t2[$j - 1]) {
            $lcs = $t1[$i - 1] . $lcs;
            $i--; $j--;
        } elseif ($L[$i - 1][$j] > $L[$i][$j - 1]) {
            $i--;
        } else {
            $j--;
        }
    }

    return $lcs;
}


$t1 = "gttcctaata";
$t2 = "cgataattgaga";
echo "Longest Common Subsequence: " . lcs($t1, $t2) . "\n";
?>
