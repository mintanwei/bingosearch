<html>
	<head>
		<title>Bingo!</title>
	</head>
	<body>
		<center>
			<h1>Bingo!</h1> <form method="get">
				<input type="text" name="q" />
				<input type ="submit" value="search" />
			</form>
		</center>
<?php
$tmp = $_GET["q"];
$max_img = $_GET["m"];
if ($max_img == "") {
	$max_img = 20;
}
if (file_exists("index/$tmp") && $tmp != "") {
	$fp = fopen("index/$tmp", "r");
	$cnt = 0;
	echo "<div style='position: relative;'>";
	echo "<table width='100%' class='ts'>";
	echo "<tbody>";
	while (!feof($fp) && $cnt < $max_img) {
		$id = fgets($fp);
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
		echo "<td align='left' width='17%' style='padding-top: 16px;'><img src='images/$tmp/$id'>";
		echo "<div><a href='$image_src'>查看原图</a>";
		echo "<a href='$page_url'>查看原页面</a></div>";
		echo "<div>$size $format</div>";
		echo "<div>$rank</div></td>";
		if ($cnt % 5 == 4) {
			echo "</tr>";
		}
		++ $cnt;
	}
	echo "</tbody>";
	echo "</table>";
	echo "</div>";
}
else if ($tmp != "") {
	$url = "http://images.google.com.hk/images?q=$tmp&start=0&ndsp=$max_img&hl=zh-CN";
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
		if (preg_match('/" target\\\x3d_blank",".*?",".*?","(.*?)","(.*?)"/', $cur, $m)) {
			$size = "$m[1]x$m[2] ";
		}
		else {
			echo "ERROR: IMAGE_SIZE NOT FOUND!\n";
		}
		# format
		if (preg_match('/times; \d*? - (\d*?k)","(.*?)"/', $cur, $m)) {
			$size = "$size $m[1]";
			$format = "$m[2]";
		}
		else {
			echo "ERROR: IMAGE_FORMAT NOT FOUND!\n";
		}
		if ($cnt % 5 == 0) {
			echo "<tr>";
		}
		echo "<td align='left' width='17%' style='padding-top: 16px;'><img src='$thubnail_src'>";
		echo "<div><a href='$image_src'>查看原图</a>";
		echo "<a href='$page_url'>查看原页面</a></div>";
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
}
?>
	</body>
</html>
