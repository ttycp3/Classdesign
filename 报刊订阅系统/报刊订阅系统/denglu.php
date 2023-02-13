<?php
    session_start();
	header("Content-type: text/html; charset=utf-8");
    $user=$_POST["username"];
	$_SESSION["uesrname"]=$user;//session超全局变量
	$pwd=$_POST["password"];//获取密码
	if($user==""||$pwd=="")
	{
      echo "<script>alert('请输入用户名或密码！'); history.go(-1);</script>";  
	}
	else
	{
		$link=mysqli_connect("localhost","root","123456","newspaper_order");//连接数据库
        mysqli_query($link,"set names utf8"); 
        $sql = "select user_name,password from users where user_name = '$user' and password = '$pwd'";
		$result=mysqli_query($link,$sql);//执行sql语句
		$num=mysqli_num_rows($result);//统计影响结果行数，作为判断条件
		if($num)
		{
			echo "<script>alert('登录成功！');window.location='003.php';</script>";//登录成功页面跳转  
		}
		else
		{
			echo "<script>alert('用户名或密码不正确！');history.go(-1);</script>";  
	    }
	}
?>
