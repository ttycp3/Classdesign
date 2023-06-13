package filter;

import bean.User;

import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebFilter("/index.jsp")
public class IndexFilter implements Filter {
    @Override
    public void init(FilterConfig filterConfig) throws ServletException {

    }

    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
//        获取session对象
        HttpServletRequest req = (HttpServletRequest)servletRequest;
        HttpServletResponse resp = (HttpServletResponse)servletResponse;
        HttpSession session = req.getSession();
        User user = (User) session.getAttribute("user");
        if (user == null){
            resp.sendRedirect("login.jsp");
        }else {
            filterChain.doFilter(req,resp);
        }
    }

    @Override
    public void destroy() {

    }
}
