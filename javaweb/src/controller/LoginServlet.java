package controller;

import bean.User;
import com.alibaba.fastjson.JSON;
import service.UserService;
import utils.ResultMap;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.sql.SQLException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    UserService userService=new UserService();
    ResultMap resultMap=new ResultMap();
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws SecurityException, IOException {
        resp.setContentType("text/html;charest=utf-8");
        System.out.println("进入了后台");
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        System.out.println(username + password);
        try {
            User user = userService.login(username, password);
            HttpSession session = req.getSession();
            session.setAttribute("user",user);
            if (user == null){
                System.out.println("账号或密码输入有误");
                resultMap.setStatus(false);
                resultMap.setMessage("账号或密码输入有误");
            }else{
                System.out.println("账号或密码输入正确");
                resultMap.setStatus(true);
                resultMap.setMessage("账号和密码输入正确");
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
        String json= JSON.toJSONString(resultMap);
        resp.getWriter().println(json);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws SecurityException, IOException {
        doPost(req, resp);
    }
}
