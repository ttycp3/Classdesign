<?php
//show_source(__FILE__);
if (!session_id()) session_start();
global  $user;//定义$user
global $user1;
$_SESSION["username"]=$user;
$username=$_SESSION["uesrname"];
$user1=implode("",$_SESSION);//将session中的数组变为字符串元素
$link=mysqli_connect("localhost","root","123456","newspaper_order");//连接数据库
mysqli_query($link,"set names utf8"); 
$sql="select * from vw_order where 用户名='{$username}'";
$result=mysqli_query($link,$sql);//执行语句
$num=mysqli_num_rows($result);//将HTML嵌入PHP中，实现从数据库中获得留言信息
?>
	<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
    <h1>尊敬的<?php echo $username;?>,欢迎来到报刊订阅系统</h1>
</head>
  <body>
 <div><h3>
 	<a href="baokan.php">报刊浏览</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
         <a href="shoucang.php">查看收藏夹</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
         <a href="xiugai.php">信息修改</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 	<a href="tuichu.php">退出系统</a></h3></div>
 	<br/><br/>
 	
 	<h2>订单信息:</h2>
 	<table cellpadding="0" cellspacing="0" border="1" width="60%">
<tr bgcolor="#8BBCC7">
    <td>订单号</td>
	<td>报刊名</td>
	<td>起始时间</td>
	<td>终止时间</td>
    <td>收货地址</td>
	<?php echo '<pre>';
	while($row=mysqli_fetch_array($result,MYSQLI_ASSOC))
	{?>
		<tr bgcolor="#FFFFFF">
            <td ><?php echo $row['订单号'];?>&nbsp;</td>
	<td >&nbsp;<?php echo $row['报刊名'];?>&nbsp;</td>
	<td ><?php echo $row['起始时间'];?></td>
	<td >&nbsp;<?php echo $row['终止时间'];?>&nbsp;</td>
            <td >&nbsp;&nbsp;<?php echo $row['收货地址'];?>&nbsp;</td>
    <?php 
       }
       ?>
</tr>
</table>
 </br></br></br>
 <?php
 if(array_key_exists('tuiding', $_POST)) {
     tuiding();
 }
 else if(array_key_exists('zhuanding', $_POST)) {
     zhuanding();
 }
 function tuiding() {
     $orderid=$_POST['order_id'];
     $spl="delete from ordery where order_id='{$orderid}'";
     $result=mysqli_query($GLOBALS['link'],$spl);
     header("Location:003.php");
 }
 function zhuanding() {
     $orderid=$_POST['orderid'];
     $address=$_POST['address'];
     $spl="update ordery set order_address='{$address}' where order_id='{$orderid}'";
     $result=mysqli_query($GLOBALS['link'],$spl);
     header("Location:003.php");
 }
 ?>
 <form method="post">
         <div><input type="text" name="order_id" placeholder="订单号">
             <input type="submit" name='tuiding' class="button" value="退订"></div></br>
         <div><input type="text" name="orderid"placeholder="订单号">&nbsp;&nbsp;&nbsp;
             <input type="text" name="address"placeholder="地址">
             <input type="submit" name='zhuanding' class="button" value="转订"></form>
         </div></br>
</body>
</html>
