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
$sql="select * from vw_paper";
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
        <a href="003.php">个人订单</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <a href="shoucang.php">查看收藏夹</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <a href="xiugai.php">信息修改</a>&nbsp;
        <a href="tuichu.php">退出系统</a></h3></div>
<br/><br/>

<h2>报刊信息:</h2>
<table cellpadding="0" cellspacing="0" border="1" width="60%">
    <tr bgcolor="#8BBCC7">
        <td>报刊名</td>
        <td>邮发代号</td>
        <td>刊期</td>
        <td>价格</td>
        <?php echo '<pre>';
        while($row=mysqli_fetch_array($result,MYSQLI_ASSOC))
        {?>
    <tr bgcolor="#FFFFFF">
        <td >&nbsp;<?php echo $row['报刊名'];?>&nbsp;</td>
        <td ><?php echo $row['邮发代号'];?></td>
        <td >&nbsp;<?php echo $row['刊期'];?>&nbsp;</td>
        <td >&nbsp;&nbsp;<?php echo $row['价格'];?>&nbsp;</td>
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
else if(array_key_exists('dingyue', $_POST)) {
    dingyue();
}
else if(array_key_exists('tianjia',$_POST)){
    tianjia();
}
else if(array_key_exists('shanchu',$_POST)){
    shanchu();
}
function tuiding() {
    $username=$GLOBALS['username'];
    $orderid=$_POST['order_id'];
    $spl="insert into collecty values(NULL,'{$username}',(select paper_name from newspaper where mail_code='{$orderid}'),'{$orderid}',(select frequency from newspaper where mail_code='{$orderid}'),(select price from newspaper where mail_code='{$orderid}'))";
    $result=mysqli_query($GLOBALS['link'],$spl);
}
function dingyue() {
    $username=$GLOBALS['username'];
    $orderid=$_POST['orderid'];
    $stime=$_POST['stime'];
    $etime=$_POST['etime'];
    $spl="insert into ordery values (NULL,'{$stime}','{$etime}',(select phone_number from users where user_name='{$username}'),(select user_address from users where user_name='{$username}'),'{$orderid}')";
    $result=mysqli_query($GLOBALS['link'],$spl);
}
function tianjia(){
    $papername=$_POST['papername'];
    $fre=$_POST['fre'];
    $price=$_POST['price'];
    $orderid=$_POST['order_id'];
    $spl="insert into newspaper values('{$papername}','{$orderid}','{$fre}','{$price}')";
    $result=mysqli_query($GLOBALS['link'],$spl);
    header("Location:baokan.php");
}
function shanchu(){
    $orderid=$_POST['order_id'];
    $spl="delete from newspaper where mail_code='{$orderid}'";
    $result=mysqli_query($GLOBALS['link'],$spl);
    header("Location:baokan.php");
}
?>
<form method="post">
    <div><input type="text" name="order_id" placeholder="邮发代号">
        <input type="submit" name='tuiding' class="button" value="收藏"></div></br>
    <div><input type="text" name="orderid"placeholder="邮发代号">&nbsp;&nbsp;&nbsp;
        <input type="date" name="stime"placeholder="开始时间">&nbsp;&nbsp;&nbsp;
        <input type="date" name="etime"placeholder="终止时间">&nbsp;&nbsp;&nbsp;
        <input type="submit" name='dingyue' class="button" value="订阅"></form>
</div></br>
<?php
$username=$GLOBALS['username'];
$spl="select is_admin from users where user_name='{$username}'";
$result=mysqli_query($GLOBALS['link'],$spl);
$rosw=mysqli_fetch_array($result,MYSQLI_ASSOC);
if($rosw['is_admin']) {
    echo '<h2>管理员功能:</h2>';
    echo '<form method="post"><div><input type="text" name="order_id" placeholder="邮发代号">&nbsp;<input type="text" name="papername" placeholder="报刊名">&nbsp;<input type="text" name="fre" placeholder="刊期">&nbsp;<input type="text" name="price" placeholder="价格">&nbsp;<input type="submit" name="tianjia" class="button" value="添加报刊"></div></br>';
    echo '<form method="post"><div><input type="text" name="order_id" placeholder="邮发代号">&nbsp;<input type="submit" name="shanchu" class="button" value="删除报刊">';
}
?>
</body>
</html>
