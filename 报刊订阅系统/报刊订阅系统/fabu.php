<?php
session_start();
header("Content-type: text/html; charset=utf-8");
global $user;
$re=$_POST["recever"];//获取recever
$comment=$_POST["neirong"];//获取留言
@date_default_timezone_set(PRC);//将数组变为字符串函数
$time=date("Y-m-d G:i:s");//获取时间，G为24小时制
$_SESSION["username"]=$user;//开启session
$user1=implode("",$_SESSION);//将数组转为字符串
$link=mysqli_connect("localhost","root","123456","liuyan");//连接数据库
mysqli_query($link,"set names utf8"); 
$sql="insert into text(sender,recever,comment,time) values('$user1','$re','$comment','$time')";
$result=mysqli_query($link,$sql);//执行语句
$sql1="insert into friend(me,friend) values('$user1','$re')";//将me，friend存入数据库
$result=mysqli_query($link,$sql1);//执行语句
if($recever=""||$comment="")
{
	echo "<script>alert('发布失败！');window.location='fabu.html';</script>";
}
else
{
	echo "<script>alert('发布成功！');window.location='fabu.html';</script>";
}
?>
