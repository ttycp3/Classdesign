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
$sql="select * from vw_collect where 用户名='{$username}'";
$result=mysqli_query($link,$sql);//执行语句
$num=mysqli_num_rows($result);//将HTML嵌入PHP中，实现从数据库中获得留言信息
?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <h1><?php echo $username;?>的收藏夹</h1>
</head>
<body>
<div><h3>
        <a href="baokan.php">报刊浏览</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <a href="003.php">个人订单</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <a href="tuichu.php">退出系统</a></h3></div>
<br/><br/>

<h2>收藏列表:</h2>
<table cellpadding="0" cellspacing="0" border="1" width="60%">
    <tr bgcolor="#8BBCC7">
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
        function tuiding() {
            $orderid=$_POST['order_id'];
           $spl="delete from collecty where mail_code='{$orderid}'";
            $result=mysqli_query($GLOBALS['link'],$spl);
            header("Location:shoucang.php");
        }
        function dingyue() {
            $username=$GLOBALS['username'];
            $orderid=$_POST['orderid'];
            $stime=$_POST['stime'];
            $etime=$_POST['etime'];
            $spl="insert into ordery values (NULL,'{$stime}','{$etime}',(select phone_number from users where user_name='{$username}'),(select user_address from users where user_name='{$username}'),'{$orderid}')";
            $result=mysqli_query($GLOBALS['link'],$spl);
//    header("Location:baokan.php");
        }
        ?>
        <form method="post">
            <div><input type="text" name="order_id" placeholder="邮发代号">
                <input type="submit" name='tuiding' class="button" value="取消收藏"></div></br>
            <div><input type="text" name="orderid"placeholder="邮发代号">&nbsp;&nbsp;&nbsp;
                <input type="date" name="stime"placeholder="开始时间">&nbsp;&nbsp;&nbsp;
                <input type="date" name="etime"placeholder="终止时间">&nbsp;&nbsp;&nbsp;
                <input type="submit" name='dingyue' class="button" value="订阅"></form>
        </div></br>
</body>
</html>
