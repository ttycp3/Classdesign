package service;

import bean.Type;
import dao.TypeDao;

import java.sql.Date;
import java.sql.SQLException;
import java.util.List;
import java.util.UUID;

public class TypeService {
    TypeDao typeDao = new TypeDao();
    public List<Type> selectAllType() throws SQLException {
        return typeDao.selectAllType();
    }
    public void delType(String tid) throws SQLException {
        int num = typeDao.delType(tid);
        if (num == 0){
            System.out.println("删除类别失败");
        }
    }
    public void addType(String tname) throws SQLException {
//        获取随机的id
        String tid = UUID.randomUUID().toString();
//        获取当前的时间
        Date createdate = new Date(new java.util.Date().getTime());
//        调用dao层方法
        int num = typeDao.addType(tid,tname,createdate);
        if (num == 0){
            System.out.println("创建类别失败");
        }
    }
    public void editType(String tid,String tname) throws SQLException {
//        编辑完之后，需要更新时间
        Date createdate = new Date(new java.util.Date().getTime());
        int num = typeDao.editType(tid,tname,createdate);
        if (num == 0){
            System.out.println("编辑类别失败");
        }
    }
}
