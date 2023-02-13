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
$sql="select * from vw_user where 姓名='{$username}'";
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
        <a href="003.php">个人订单</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <a href="tuichu.php">退出系统</a></h3></div>
<br/><br/>

<h2>个人信息:</h2>
<table cellpadding="0" cellspacing="0" border="1" width="60%">
    <tr bgcolor="#8BBCC7">
        <td>姓名</td>
        <td>电话</td>
        <td>住址</td>
        <td>邮箱</td>
        <td>邮编</td>
        <?php echo '<pre>';
        while($row=mysqli_fetch_array($result,MYSQLI_ASSOC))
        {?>
    <tr bgcolor="#FFFFFF">
        <td ><?php echo $row['姓名'];?>&nbsp;</td>
        <td >&nbsp;<?php echo $row['电话'];?>&nbsp;</td>
        <td ><?php echo $row['住址'];?></td>
        <td >&nbsp;<?php echo $row['邮箱'];?>&nbsp;</td>
        <td >&nbsp;&nbsp;<?php echo $row['邮编'];?>&nbsp;</td>
        <?php
        }
        ?>
    </tr>
</table>
</br></br></br>
<?php
if(array_key_exists('xm', $_POST)) {
    xm();
}
else if(array_key_exists('dh', $_POST)) {
    dh();
}
else if(array_key_exists('yb', $_POST)) {
    yb();
}
else if(array_key_exists('yx', $_POST)) {
    yx();
}
else if(array_key_exists('dz', $_POST)) {
    dz();
}
function xm() {
    $orderid=$_POST['mima'];
    $username=$GLOBALS['username'];
    $spl="update users set password='{$orderid}' where user_name='{$username}'";
    $result=mysqli_query($GLOBALS['link'],$spl);
    header("Location:xiugai.php");
}
function dz() {
    $username=$GLOBALS['username'];
    $address=$_POST['address'];
    $spl="update users set user_address='{$address}' where user_name='{$username}'";
    $result=mysqli_query($GLOBALS['link'],$spl);
    header("Location:xiugai.php");
}
function dh() {
    $username=$GLOBALS['username'];
    $address=$_POST['dianhua'];
    $spl="update users set phone_number='{$address}' where user_name='{$username}'";
    $result=mysqli_query($GLOBALS['link'],$spl);
    header("Location:xiugai.php");
}
function yx() {
    $username=$GLOBALS['username'];
    $address=$_POST['youxiang'];
    $spl="update users set email='{$address}' where user_name='{$username}'";
    $result=mysqli_query($GLOBALS['link'],$spl);
    header("Location:xiugai.php");
}
function yb() {
    $username=$GLOBALS['username'];
    $address=$_POST['youbian'];
    $spl="update users set postcode='{$address}' where user_name='{$username}'";
    $result=mysqli_query($GLOBALS['link'],$spl);
    header("Location:xiugai.php");
}
?>
<form method="post">
    <div><input type="password" name="mima" placeholder="密码">&nbsp;
        <input type="submit" name='xm' class="button" value="修改"></div></br>
    <div><input type="text" name="youxiang"placeholder="邮箱">&nbsp;&nbsp;&nbsp;
        <input type="submit" name='yx' class="button" value="修改"></div></br>
    <div><input type="text" name="youbian"placeholder="邮编">&nbsp;&nbsp;&nbsp;
        <input type="submit" name='yb' class="button" value="修改"></div></br>
        <input type="text" name="address"placeholder="地址">&nbsp;
        <input type="submit" name='dz' class="button" value="修改"></form>
</div></br>
<?php
$username=$GLOBALS['username'];
$spl="select (select is_admin from users where user_name='{$username}') is_admin,(select count(*) from users) totaluser,(select count(*) from newspaper) totalpaper,(select count(*) from ordery) totalorder";
$result=mysqli_query($GLOBALS['link'],$spl);
$rosw=mysqli_fetch_array($result,MYSQLI_ASSOC);
if($rosw['is_admin']) {
    echo '<h2>管理员功能:</h2>';
    ?>
   <table cellpadding="0" cellspacing="0" border="1" width="60%">
<tr bgcolor="#8BBCC7">
    <td>注册人数</td>
	<td>报刊数目</td>
	<td>订单数目</td>
	<?php echo '<pre>';
    ?><tr bgcolor="#FFFFFF">
    <td ><?php echo $rosw['totaluser'];?>&nbsp;</td>
    <td >&nbsp;<?php echo $rosw['totalpaper'];?>&nbsp;</td>
           <td >&nbsp;<?php echo $rosw['totalorder'];?>&nbsp;</td>
    <?php
    }
    ?>
</tr>
</table>
</body>
</html>