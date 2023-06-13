<%--
  Created by IntelliJ IDEA.
  User: tty
  Date: 2023/6/1
  Time: 21:47
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <meta charset="utf-8">
    <title>登陆界面</title>
    <script src="js/Vue.js"></script>
    <script src="js/index.js"></script>
    <script src="js/axios.js"></script>
    <link rel="stylesheet" href="css/index.css">
    <style>
        body{
            display:flex;
            justify-content: center;
            align-items: center;
            height:700px;
        }
        .el-form{
            width:400px;
            height:200px;
        }
    </style>
</head>
<body>
<div id="main">
    <el-form :rules="rules" ref="ruleForm" :model="user" label-width="80px" >
        <el-form-item prop="username" label="账号">
            <el-input v-model="user.username"></el-input>
        </el-form-item>
        <el-form-item prop="password" label="密码">
            <el-input v-model="user.password"></el-input>
        </el-form-item>
        <el-form-item>
            <el-button type="primary" @click="login">登陆</el-button>
            <el-button>取消</el-button>
        </el-form-item>
    </el-form>
</div>
<script>
    new Vue({
        el:"#main",
        data:{
            user:{
                username:"",
                password:""
            },
            rules:{
                username:[
                    {
                        required:true,message:"请输入账号",trigger:"blur"
                    },{
                        min:3,max:9,message:"长度应该在3到9个字符之间",trigger:"blur"
                    }
                ],
                password:[
                    {
                        required:true,message:"请输入密码",trigger:"blur"
                    },{
                        min:3,max:9,message:"长度应该在3到9个字符之间",trigger:"blur"
                    }
                ]
            }
        },
        methods:{
            login: function () {
                this.$refs.ruleForm.validate(isSuccess => {
                    if (isSuccess) {
                        var username = this.user.username;
                        var password = this.user.password;
                        var that = this;
                        axios.get("login?username=" + username + "&password=" + password).then(function (res) {
                            if (res.data.status) {
                                location.href = "index.jsp"
                            } else {
                                that.$message.warning(res.data.message);
                            }
                        })
                    } else {
                        this.$message.warning("输入的内容不符合规则")
                    }
                })
            }
        }
    })
</script>
</body>
</html>