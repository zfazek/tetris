<html>
<body>
<?php
$lines = $_POST["lines"];
$score = $_POST["score"];
if ($lines != "" &&
    $score != "" &&
    is_numeric($lines) &&
    is_numeric($score) &&
    strlen($lines) < 4 &&
    strlen($score) < 7 &&
    $lines > 0 &&
    $score > 0) {
    $timestamp = date("Y-m-d H:i:s");
    $myfile = fopen("score.txt", "a") or die("Unable to open file!");
    fwrite($myfile, $score . "\t" . $lines . "\t" . $timestamp . "\n");
    fclose($myfile);
}
?>
</body>
</html>
