<%--
  Created by IntelliJ IDEA.
  User: syy
  Date: 2023/6/3
  Time: 14:30
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <meta charset="utf-8">
    <title></title>
    <script src="js/Vue.js"></script>
    <script src="js/index.js"></script>
    <script src="js/axios.js"></script>
    <link rel="stylesheet" href="css/index.css">
    <style>

    </style>
</head>
<body>
<div id="main">
    <el-table
            :data="staffList"
            align="center"
            style="width: 100%">
        <el-table-column
                prop="name"
                label="姓名"
                align="center"
        >
        </el-table-column>
        <el-table-column
                prop="sex"
                label="性别"
                align="center"
        >
        </el-table-column>
        <el-table-column
                prop="age"
                label="年龄"
                align="center"
        >
        </el-table-column>
    </el-table>
</div>
<script>
    new Vue({
        el:"#main",
        data:{
            staffList:[]
        },
        methods:{
            //    自定义的方法
            selectAllStaff: function () {
                //    向后台发请求
                var that = this;
                axios.get("selectAllStaff").then(function (res) {
                    //请求的结果放在res中
                    that.staffList = res.data.list;
                    console.log(res)
                })
            }
        },
        //    预加载函数一进入该页面就执行mounted方法
        mounted(){
            this.selectAllStaff()
        }
    })
</script>
</body>
</html>
