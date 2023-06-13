package service;

import bean.User;
import dao.UserDao;

import java.sql.SQLException;
import java.util.List;

public class UserService {
    UserDao userDao=new UserDao();
    public User login(String username, String password) throws SQLException {
        return userDao.login(username,password);
    }
    public List<User> selectAllStaff() throws SQLException {
        return userDao.selectAllStaff();
    }
}
