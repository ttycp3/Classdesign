package controller;

import bean.User;
import com.alibaba.fastjson.JSON;
import service.UserService;
import utils.ResultMap;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;

@WebServlet("/selectAllStaff")
public class SelectAllStaffServlet extends HttpServlet {
    UserService userService = new UserService();
    ResultMap resultMap = new ResultMap();
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        System.out.println("我进入到了患者管理后台");
        try {
            List<User> list = userService.selectAllStaff();
            //将集合装进resultMap对象中
            resultMap.setList(list);
            resultMap.setStatus(true);
        } catch (SQLException e) {
            e.printStackTrace();
            resultMap.setStatus(false);
            resultMap.setMessage("没有查询到数据");
        }
//        将数据传递给前端，前端和后台交互数据的类型是json格式的字符产{"name":"老六"}
        String json = JSON.toJSONString(resultMap);
//        避免页面出现乱码，需要设置响应的编码格式
        resp.setContentType("text/html;charset=utf-8");
        resp.getWriter().println(json);
        System.out.println(json);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doPost(req, resp);
    }
}
