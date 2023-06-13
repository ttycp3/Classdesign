package dao;

import bean.Type;

import java.sql.Date;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class TypeDao {
    public List<Type> selectAllType() throws SQLException {
//        定义sql语句
        String sql = "select * from type";
//        存放参数
        Object[] obj = {};
//        执行查询sql语句
        ResultSet rs = JdbcBase.querySql(sql,obj);
        List<Type> list = new ArrayList<Type>();
        while (rs.next()){
            Type type = new Type();
//            rs.getString("tid")我从返回的二维表中获取tid的数据
//            type.setTid往type对象中存值
            type.setTid(rs.getString("tid"));
            type.setTname(rs.getString("tname"));
            type.setTime(rs.getDate("createdate"));
            list.add(type);
        }
        return list;
    }
    public int delType(String tid) throws SQLException {
//        定义sql语句
        String sql = "delete from type where tid = ?";
        Object[] obj = {tid};
//        执行sql语句
        int num = JdbcBase.updateSql(sql,obj);
        return num;
    }
    public int addType(String tid, String tname, Date createdate) throws SQLException {
//        定义sql语句
        String sql = "insert into type(tid,tname,createdate) value(?,?,?)";
        Object[] obj = {tid,tname,createdate};
        int num = JdbcBase.updateSql(sql,obj);
        return num;
    }
    public int editType(String tid,String tname,Date createdate) throws SQLException {
//        更新sql语句
        String sql = "update type set tname = ?,createdate = ? where tid = ?";
        Object[] obj = {tname,createdate,tid};
        int num = JdbcBase.updateSql(sql,obj);
        return num;
    }
}
