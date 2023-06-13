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
    <el-button type="primary" @click="openAddPanel">创建</el-button>
    <el-table
            :data="typeList"
            align="center"
            style="width: 100%">
        <el-table-column
                prop="tname"
                label="类别名称"
                align="center"
        >
        </el-table-column>
        <el-table-column
                prop="createdate"
                label="创建时间"
                align="center"
        >
        </el-table-column>
        <el-table-column
                label="操作"
                align="center"
        >
            <template slot-scope="scope">
                <el-button type="text" size="small" @click="openEditPanel(scope.row)">编辑</el-button>
                <el-button type="text" size="small" @click="openDelPanel(scope.row.tid)">删除</el-button>
            </template>
        </el-table-column>
    </el-table>
    <%--    删除提示--%>
    <el-dialog
            title="删除提示"
            :visible.sync="delVisible"
            width="30%">
        <span>确定删除吗？</span>
        <span slot="footer" class="dialog-footer">
    <el-button @click="delVisible = false">取 消</el-button>
    <el-button type="primary" @click="delType">确 定</el-button>
  </span>
    </el-dialog>
    <%--    删除提示--%>
    <%--    创建提示--%>
    <el-dialog
            title="创建提示"
            :visible.sync="addVisible"
            width="30%">
        <%--        内容部分--%>
        <el-form  :model="type"  label-width="100px" class="demo-ruleForm">
            <el-form-item prop="type" label="类别名称">
                <el-input v-model="type.tname"></el-input>
            </el-form-item>
        </el-form>
        <span slot="footer" class="dialog-footer">
    <el-button @click="addVisible = false">取 消</el-button>
    <el-button type="primary" @click="addType">确 定</el-button>
  </span>
    </el-dialog>
    <%--    创建提示--%>
    <%--    编辑提示--%>
    <el-dialog
            title="创建提示"
            :visible.sync="editVisible"
            width="30%">
        <%--        内容部分--%>
        <el-form  :model="type"  label-width="100px" class="demo-ruleForm">
            <el-form-item prop="type" label="类别名称">
                <el-input v-model="type.tname"></el-input>
            </el-form-item>
        </el-form>
        <span slot="footer" class="dialog-footer">
    <el-button @click="editVisible = false">取 消</el-button>
    <el-button type="primary" @click="editType">确 定</el-button>
  </span>
    </el-dialog>
    <%--    编辑提示--%>
</div>
<script>
    new Vue({
        el:"#main",
        data:{
            delVisible:false,
            addVisible:false,
            editVisible:false,
            tid:"",
            type:{
                tname:""
            },
            typeList:[]
        },
        methods:{
            //    自定义的方法
            selectAllType(){
                //    向后台发请求
                var that = this;
                axios.get("selectAllType").then(function (res) {
                    //请求的结果放在res中
                    console.log(res)
                    that.typeList = res.data.list;
                })
            },
            openDelPanel(tid){
                //    1、打开删除提示框
                this.delVisible = true
                //    2、给data里的tid赋值
                this.tid = tid
            },
            delType(){
                //    获取每一行的tid
                var that = this
                var tid = that.tid
                axios.get("delType?tid="+tid).then(function (res) {
                    if (res.data.status){//如果resultMap里面存放的status为true
                        //    关闭弹窗
                        that.delVisible = false
                        //    重新查一遍数据
                        that.selectAllType();
                    }else {//如果resultMap里面存放的status为false
                        //    关闭弹窗
                        that.delVisible = false
                        //    弹出错误提示信息
                        that.$message.warning(res.data.message);
                    }
                })

            },
            openAddPanel(){
                //让创建提示框可视化
                this.addVisible = true
            },
            addType(){
                //    获取输入的tname
                var that = this;
                var tname = that.type.tname;
                axios.get("addType?tname="+tname).then(function (res) {
                    if (res.data.status){//如果status为true
                        //    关闭创建提示框
                        that.addVisible = false
                        //    重新查询一遍数据
                        that.selectAllType()
                    }else {//如果status为false
                        //    关闭创建提示框
                        that.addVisible = false
                        //    弹出错误提示信息
                        that.$message.warning(res.data.message)
                    }
                })
            },
            openEditPanel(row){
                //    打开编辑弹出框
                this.editVisible = true
                //    让数据回显
                this.type = row
            },
            editType(){
                var that = this;
                //    获取类别名称
                var tname = that.type.tname
                //    获取类别id
                var tid = that.type.tid;
                //    向后台发请求
                axios.get("editType?tid="+tid+"&tname="+tname).then(function (res) {
                    if (res.data.status){//如果status为true
                        //    关闭编辑提示框
                        that.editVisible = false
                        //    重新查询一遍数据
                        that.selectAllType()
                    }else {//如果status为false
                        //    关闭编辑提示框
                        that.editVisible = false
                        //    弹出错误提示信息
                        that.$message.warning(res.data.message)
                    }
                })
            }
        },
        //    预加载函数一进入该页面就执行mounted方法
        mounted(){
            this.selectAllType()
        }
    })
</script>
</body>
</html>
