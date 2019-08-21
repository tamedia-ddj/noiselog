<?
$noise=$_GET["noise"];
date_default_timezone_set('Europe/Zurich');
$date = date('m/d/Y h:i:s a', time());
$sensor = $_GET["sensor"];

$myFile = "values.txt";
$fh = fopen($myFile, 'w') or die("can't open file");
echo "date: ";
echo $date;
echo "/ sensor: ";
echo $sensor;
echo " / noise: ";
echo $noise;

$stringData = "$date; $sensor; $noise\n";
fwrite($fh, $stringData);
fclose($fh);

$myFile = "noiselog.csv";
$fh = fopen($myFile, 'a') or die("can't open file");

fwrite($fh, $stringData);
fclose($fh);
?>
