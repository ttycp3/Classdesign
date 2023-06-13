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

@WebServlet("/editType")
public class EditTypeServlet extends HttpServlet {
    TypeService typeService = new TypeService();
    ResultMap resultMap = new ResultMap();
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            //        获取传递过来的tid
            String tid = req.getParameter("tid");
//        获取传递过来的tname
            String tname = req.getParameter("tname");
            System.out.println("tid:"+tid+"tname:"+tname);
            typeService.editType(tid,tname);
            resultMap.setStatus(true);
        } catch (Exception e){
            resultMap.setStatus(false);
            resultMap.setMessage(e.getMessage());
        }
        String json = JSON.toJSONString(resultMap);
        resp.setContentType("text/html;charset=utf-8");
        resp.getWriter().println(json);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doPost(req, resp);
    }
}
