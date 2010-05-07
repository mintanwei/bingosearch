<html>
	<head>
		<meta content="text/html; charset=UTF8">
		<title>Bingo!</title>
	</head>
	<body>
		<center>
			<h1><font color="blue" face="courier" size=8>B</font>
                <font color="#EA0000" face="courier" size=8>i</font>
				<font color="#EAC100" face="courier" size=8>n</font>
				<font color="blue" face="courier" size=8>g</font>
				<font color="green" face="courier" size=8>o</font>
				<font color="#EA0000" face="courier" size=8>!</font>
			</h1> 
			<form method="get">
				<input type="text" size=30 name="q" />
				<input type ="submit" value="Search Images" />
			</form>
		</center>
<?php
error_reporting(E_ERROR); 

$fp = fopen("query_log", "ar");
$query = urldecode(urlencode($_GET["q"]));
$ip = $_SERVER['REMOTE_ADDR'];
fwrite($fp, "$query $ip\n");
fclose($fp);

$max_img = $_GET["m"];
$start = $_GET["p"];

if ($max_img == "") {
	$max_img = 20;
}
if ($start == "") {
	$start = 0;
}

if (file_exists("index/$query") && $query != "") {
	$fp = fopen("index/$query", "r");
	$cnt = 0;
	echo "<div style='position: relative;'>";
	echo "<table width='100%' class='ts'>";
	echo "<tbody>";
	while (!feof($fp) && $cnt < $max_img) {
		$id = fgets($fp);
		$id = 20 * $start + $id;
		$thubnail_src = fgets($fp);
		$image_src = fgets($fp);
		$page_url = fgets($fp);
		$size = fgets($fp);
		$format = fgets($fp);
		$rank = fgets($fp);
		$blank = fgets($fp);
		if ($cnt % 5 == 0) {
			echo "<tr>";
		}
		echo "<td align='center' width='20%' style='padding-top: 16px;'>
			  <img src='images/$query/$id'>";
		echo "<div><a href='$image_src'><font color='blue'>查看原图</font></a>";
		echo "<a href='$page_url'><font color='green'> 查看原页面</font></a></div>";
		echo "<div>$size $format</div>";
		echo "<div>$rank</div></td>";
		if ($cnt % 5 == 4) {
			echo "</tr>";
		}
		++ $cnt;
	}
	fclose($fp);
	echo "</tbody>";
	echo "</table>";
	echo "</div>";
}

else if ($query != "") {
	$first_one = $start * 20;
	$url = "http://images.google.com.hk/images?q=$query&start=$first_one&ndsp=$max_img&hl=zh-CN";
	$contents = file_get_contents($url); 
	preg_match_all('/\["\/imgres\?.*?""]/', $contents, $matches);
	echo "<div style='position: relative;'>";
	echo "<table width='100%' class='ts'>";
	echo "<tbody>";
	$cnt = 0;
	foreach ($matches[0] as $cur) {
		# thumbnail
		if (preg_match('/" target\\\x3d_blank","(.*?)".*?(http:\/\/t\d.gstatic.com\/images)/', 
			          $cur, $m)) {
			$thubnail_src = "$m[2]?q=tbn:$m[1]";
		}
		else {
			echo "ERROR: THUMBNAIL NOT FOUND!";
		}
		# image_src
		if (preg_match('/imgurl\\\x3d(.*?)\\\x26/', $cur, $m)) {
			$image_src = "$m[1]";
		}
		else {
			echo "ERROR: IMAGE_SRC NOT FOUND!";
		}
		# page_url
		if (preg_match('/imgrefurl\\\x3d(.*?)\\\x26/', $cur, $m)) {
			$page_url = "$m[1]";
		}
		else {
			echo "ERROR: PAGE_URL NOT FOUND!";
		}
		# size
		if (preg_match('/"(\d*?) \&times; (\d*?) - (\d*?k)"/', $cur, $m)) {
			$size = "$m[1]x$m[2] $m[3]";
		}
		else {
			echo "ERROR: IMAGE_SIZE NOT FOUND!\n";
		}
		# format
		if (preg_match('/times; \d*? - \d*?k","(.*?)"/', $cur, $m)) {
			$format = "$m[1]";
		}
		else {
			echo "ERROR: IMAGE_FORMAT NOT FOUND!\n";
		}
		if ($cnt % 5 == 0) {
			echo "<tr>";
		}
		echo "<td align='center' width='20%' style='padding-top: 16px;'><img src='$thubnail_src'>";
		echo "<div><a href='$image_src'><font color='blue'>查看原图</font></a>";
		echo "<a href='$page_url'><font color='green'> 查看原页面</font></a></div>";
		echo "<div>$size $format</div>";
		echo "<div>$rank</div></td>";
		if ($cnt % 5 == 4) {
			echo "</tr>";
		}
		++ $cnt;
		if ($cnt >= $max_img) {
			break;
		}
	}
	echo "</tbody>";
	echo "</table>";
	echo "</div>";
}
if ($query != "" && $cnt == 0) {
	echo "<div align='center'><font color='red'>dangerous keyword</font></div>";
}
else if ($query != "" && $cnt != 0) {
	echo "<br>";
	if ($start == 0) {
		$next = $start + 1;
		echo "<div align='center'><a href='bingo.php?q=$query&p=$next'>Next &gt;&gt;</a></div>";
	}
	else {
		$next = $start + 1;
		$pre = $start - 1;
		echo "<div align='center'><a href='bingo.php?q=$query&p=$pre'>&lt;&lt; Previous</a>";
		echo "<a href='bingo.php?q=$query&p=$next'>&nbsp;&nbsp;Next &gt&gt</a></div>";
	}
}
?>
	</body>
</html>
