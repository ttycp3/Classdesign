<%--
  Created by IntelliJ IDEA.
  User: syy
  Date: 2023/6/1
  Time: 16:47
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
  <meta charset="utf-8" />
  <title>二班</title>
  <script src="js/Vue.js"></script>
  <script src="js/index.js"></script>
  <script src="js/axios.js"></script>
  <link rel="stylesheet" href="css/index.css">
  <style>
    *{
      margin: 0px;
      padding: 0px;
    }
    html,body,#main,.el-container,.el-menu{
      height: 100%;
    }
    .el-header{
      background-color: #B3C0D1;
      color: #333;
      text-align: center;
      line-height: 60px;
    }

    .el-aside {
      background-color: #D3DCE6;
      color: #333;
      text-align: center;
      line-height: 200px;
    }

    .el-main {
      background-color: #E9EEF3;
      color: #333;
      text-align: center;
      line-height: 160px;
    }
    a{
      /*  去除下划线*/
      text-decoration: none;
    }
  </style>
</head>
<body>

<div id="main">
  <el-header>Header</el-header>
  <el-container>
    <el-aside width="200px">
      <el-menu  class="el-menu-vertical-demo" default-active="1">
        <el-menu-item index="1">
          <i class="el-icon-menu"></i>
          <a href="welcome.jsp" target="main">
          <span slot="title">欢迎页</span>
            </a>
        </el-menu-item>
        <el-menu-item index="2">
          <a target="main" href="staff.jsp">
            <i class="el-icon-document"></i>
            <span slot="title">患者管理</span>
          </a>
          <el-menu-item index="3">
            <a href="type.jsp" target="main">
              <i class="el-icon-tableware"></i>
              <span slot="title">类别管理</span>
            </a>
          </el-menu-item>
      </el-menu>

    </el-aside>
    <el-main>
      <iframe name="main" src="" width="100%" height="700px" ></iframe>
    </el-main>
  </el-container>
  </el-container>

</div>
<script>
  new Vue({
    el:"#main",
    data:{

    }
  })
</script>
</body>
</html>
