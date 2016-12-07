<?php
ini_set('memory_limit', '-1'); 
function readln() {
    return fgets(STDIN);
}
$tn = readln();
for ($ti = 0; $ti < $tn; $ti++) { 

    $ln = explode(' ',readln());
    $n = $ln[0];
    $m = $ln[1];

    $g = array();
    for ($i=0; $i < $n; $i++) array_push($g, array());
    
    for ($i=0; $i < $m; $i++) { 
        $ln = explode(' ',trim(readln()));
        $ln[0]-=1;
        $ln[1]-=1; //$ln[1]--; nefunguje... proc?
        array_push($g[$ln[0]], $ln[1]);
        array_push($g[$ln[1]], $ln[0]);
    }
    $colors = explode(' ',trim(readln()));
    $seen = array();
    
    $dfs = function($a) use (&$g, &$dfs, &$seen, &$occ, &$size, &$colors, &$best) {
        $seen[$a] = true;
        $occ[$colors[$a]]++;
        $size++;
        $best = max($best, $occ[$colors[$a]]);
        foreach ($g[$a] as $b) {
            if($seen[$b]) continue;
            $seen[$b] = true;
            $dfs($b);
        }
    };
    $res = 0;
    for ($start=0; $start < $n; $start++) { 
        if($seen[$start]) continue;
        $size = 0; $best = 0;
        $occ = array();
        $dfs($start);
        $res += $size - $best;
    }
    echo "$res\n";
}
?>