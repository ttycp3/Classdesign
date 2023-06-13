/*
Navicat MySQL Data Transfer

Source Server         : 本地连接
Source Server Version : 50545
Source Host           : localhost:3306
Source Database       : medicalcheck

Target Server Type    : MYSQL
Target Server Version : 50545
File Encoding         : 65001

Date: 2023-01-03 08:54:30
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for checkgroup
-- ----------------------------
DROP TABLE IF EXISTS `checkgroup`;
CREATE TABLE `checkgroup` (
  `gid` varchar(50) NOT NULL DEFAULT '' COMMENT '主键',
  `gname` varchar(255) DEFAULT NULL COMMENT '检查组名称',
  `createdate` date DEFAULT NULL COMMENT '创建日期',
  PRIMARY KEY (`gid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='检查组表';

-- ----------------------------
-- Records of checkgroup
-- ----------------------------
INSERT INTO `checkgroup` VALUES ('1', '心脏病检查', '2022-12-10');
INSERT INTO `checkgroup` VALUES ('2', '肺结核', '2022-12-10');

-- ----------------------------
-- Table structure for checkitem
-- ----------------------------
DROP TABLE IF EXISTS `checkitem`;
CREATE TABLE `checkitem` (
  `iid` varchar(50) NOT NULL DEFAULT '' COMMENT '主键',
  `iname` varchar(255) DEFAULT NULL COMMENT '检查项目名称',
  `createdate` date DEFAULT NULL COMMENT '创建日期',
  `tid` varchar(50) DEFAULT NULL COMMENT '类别',
  PRIMARY KEY (`iid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='检查类别表';

-- ----------------------------
-- Records of checkitem
-- ----------------------------
INSERT INTO `checkitem` VALUES ('1', '血常规检查', '2022-12-10', '1');
INSERT INTO `checkitem` VALUES ('2', '尿常规', '2022-12-10', '1');
INSERT INTO `checkitem` VALUES ('3', '便常规', '2022-12-10', '1');
INSERT INTO `checkitem` VALUES ('4', '便潜血', '2022-12-10', '1');
INSERT INTO `checkitem` VALUES ('5', '肝功能检查', '2022-12-10', '2');
INSERT INTO `checkitem` VALUES ('701e8db7-8306-4a84-a694-1233a8d16360', '心脑血管x光', '2022-12-23', '4');

-- ----------------------------
-- Table structure for item_group
-- ----------------------------
DROP TABLE IF EXISTS `item_group`;
CREATE TABLE `item_group` (
  `igid` varchar(50) NOT NULL DEFAULT '' COMMENT '主键',
  `gid` varchar(50) DEFAULT NULL COMMENT '检查组主键',
  `iid` varchar(50) DEFAULT NULL COMMENT '检查项主键',
  PRIMARY KEY (`igid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='关联表';

-- ----------------------------
-- Records of item_group
-- ----------------------------
INSERT INTO `item_group` VALUES ('1', '1', '1');
INSERT INTO `item_group` VALUES ('2', '1', '5');

-- ----------------------------
-- Table structure for type
-- ----------------------------
DROP TABLE IF EXISTS `type`;
CREATE TABLE `type` (
  `tid` varchar(50) NOT NULL DEFAULT '' COMMENT '主键',
  `tname` varchar(50) DEFAULT NULL COMMENT '类别名称',
  `createdate` date DEFAULT NULL COMMENT '创建日期',
  PRIMARY KEY (`tid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='检查类别表';

-- ----------------------------
-- Records of type
-- ----------------------------
INSERT INTO `type` VALUES ('1', '常规检查', '2022-12-10');
INSERT INTO `type` VALUES ('2', '生化检查', '2022-12-10');
INSERT INTO `type` VALUES ('3', '免疫检查6', '2022-12-22');
INSERT INTO `type` VALUES ('4', '心电图检查', '2022-12-10');
INSERT INTO `type` VALUES ('5', 'x光检查', '2022-12-10');
INSERT INTO `type` VALUES ('51b0ae44-49b5-4398-b535-bc4cea6e31f4', '测试数据3', '2022-12-22');
INSERT INTO `type` VALUES ('6', '测试数据1', '2022-12-01');

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `username` varchar(50) NOT NULL DEFAULT '' COMMENT '用户名',
  `password` varchar(10) DEFAULT NULL COMMENT '密码',
  `name` varchar(20) DEFAULT NULL COMMENT '姓名',
  `sex` varchar(10) DEFAULT NULL COMMENT '性别',
  `birthday` date DEFAULT NULL COMMENT '年龄',
  `type` int(11) DEFAULT NULL COMMENT '用户类型:1医护人员|2患者',
  PRIMARY KEY (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='用户表';

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES ('admin', '123', '管理员', '男', '1994-11-22', '1');
INSERT INTO `user` VALUES ('fq', '123', '冯七', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('fq1', '123', '冯七1', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('fq2', '123', '冯七2', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('ls', '123', '李四', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('ls1', '123', '李四1', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('ls2', '123', '李四2', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('ww', '123', '王五', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('ww1', '123', '王五1', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('ww2', '123', '王五2', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('zl', '123', '赵六', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('zl1', '123', '赵六1', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('zl2', '123', '赵六2', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('zs', '123', '张三', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('zs1', '123', '张三1', '男', '1994-11-22', '2');
INSERT INTO `user` VALUES ('zs2', '123', '张三2', '男', '1994-11-22', '2');
