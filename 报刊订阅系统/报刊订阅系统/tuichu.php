<?php
session_start();
unset($_SESSION["uesrname"]);
echo "<script>alert('退出成功！');window.location='denglu.html';</script>"; 
?>
