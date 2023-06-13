package controller;

import com.alibaba.fastjson.JSON;
import service.TypeService;
import utils.ResultMap;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/delType")
public class DelTypeServlet extends HttpServlet {
    TypeService typeService = new TypeService();
    ResultMap resultMap = new ResultMap();
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            //        获取传递过来的tid
            String tid = req.getParameter("tid");
            typeService.delType(tid);
            resultMap.setStatus(true);
        }catch (Exception e){
            resultMap.setStatus(false);
            resultMap.setMessage(e.getMessage());
        }
//        格式化resultMap类型，变成json格式类型
        String json = JSON.toJSONString(resultMap);
        resp.setContentType("text/html;charset=utf-8");
//        将格式化好的数据返回给前端
        resp.getWriter().println(json);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doPost(req, resp);
    }
}
