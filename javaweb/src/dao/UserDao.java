package dao;

import bean.User;
import com.alibaba.fastjson.JSON;

import java.sql.Date;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

public class UserDao {
    public User login(String username, String password) throws SQLException {
        String sql="select * from user where username=? and password=?";
        Object[] obj={username,password};
        ResultSet rs=JdbcBase.querySql(sql,obj);
        User user = null;
        if(rs.next()){
            user = new User();
            user.setUsername(rs.getString("username"));
            user.setPassword(rs.getString("password"));

        }
        return user;
    }

    public List<User> selectAllStaff() throws SQLException {
//        定义sql语句
        String sql = "select * from user where type = 2";
//        传递参数
        Object[] obj = {};
//        执行sql语句
        ResultSet rs = JdbcBase.querySql(sql,obj);
        List<User> list = new ArrayList<>();
//        rs.next()判断有没有下一条记录，有则为true 没有则为false
        User user = null;
        while (rs.next()){
            user = new User();
            user.setUsername(rs.getString("username"));
            user.setPassword(rs.getString("password"));
            user.setName(rs.getString("name"));
            user.setType(rs.getInt("type"));
            user.setSex(rs.getString("sex"));
            int age = getAge(rs.getDate("birthday"));
            System.out.println("年龄");
            System.out.println(age);
            user.setAge(age);
            String json = JSON.toJSONString(user);
            System.out.println(json);
            list.add(user);//向list集合中添加对象
        }
        return list;
    }
    private int getAge(Date birth){
        //获取日历
        System.out.println("进入getAge");
        Calendar cal = Calendar.getInstance();
        int thisYear = cal.get(Calendar.YEAR);
        int thisMonth = cal.get(Calendar.MONTH);
        int dayOfMonth = cal.get(Calendar.DAY_OF_MONTH);
        cal.setTime(birth);
        int birthYear = cal.get(Calendar.YEAR);
        int birthMonth = cal.get(Calendar.MONTH);
        int birthdayOfMonth = cal.get(Calendar.DAY_OF_MONTH);
        int age = thisYear - birthYear;
        // 未足月
        if (thisMonth <= birthMonth) {
            // 当月
            if (thisMonth == birthMonth) {
                // 未足日
                if (dayOfMonth < birthdayOfMonth) {
                    age--;
                }
            } else {
                age--;
            }
        }
        return age;
    }
}
