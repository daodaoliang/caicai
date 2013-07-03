/*
Navicat MySQL Data Transfer

Source Server         : 127.0.0.1
Source Server Version : 50524
Source Host           : localhost:3306
Source Database       : restaurantdb

Target Server Type    : MYSQL
Target Server Version : 50524
File Encoding         : 65001

Date: 2013-07-04 00:20:58
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `consume`
-- ----------------------------
DROP TABLE IF EXISTS `consume`;
CREATE TABLE `consume` (
  `consumeid` int(11) NOT NULL AUTO_INCREMENT COMMENT '食材消耗对应表ID',
  `dishesid` int(11) NOT NULL COMMENT '菜品ID',
  `materialid` int(11) NOT NULL COMMENT '食材ID',
  `consumecount` int(11) NOT NULL COMMENT '消耗数量',
  PRIMARY KEY (`consumeid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of consume
-- ----------------------------

-- ----------------------------
-- Table structure for `diningtable`
-- ----------------------------
DROP TABLE IF EXISTS `diningtable`;
CREATE TABLE `diningtable` (
  `id` char(4) NOT NULL COMMENT '餐桌表ID,对应为台号，4位',
  `tablename` varchar(20) NOT NULL COMMENT '餐桌表名称',
  `state` int(11) NOT NULL DEFAULT '0' COMMENT '餐桌状态，暂时规定0-为空闲，1-忙碌，其他备用',
  `guestnumber` int(11) NOT NULL DEFAULT '1' COMMENT '当前客人数量',
  `waiterid` varchar(10) DEFAULT NULL COMMENT '开桌的服务员编号',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of diningtable
-- ----------------------------

-- ----------------------------
-- Table structure for `dishes`
-- ----------------------------
DROP TABLE IF EXISTS `dishes`;
CREATE TABLE `dishes` (
  `dishesid` int(11) NOT NULL AUTO_INCREMENT COMMENT '菜品ID',
  `dishesname` varchar(30) NOT NULL COMMENT '菜品名称',
  `price` decimal(10,0) NOT NULL COMMENT '菜品价格',
  PRIMARY KEY (`dishesid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of dishes
-- ----------------------------

-- ----------------------------
-- Table structure for `material`
-- ----------------------------
DROP TABLE IF EXISTS `material`;
CREATE TABLE `material` (
  `materialid` int(11) NOT NULL AUTO_INCREMENT COMMENT '食材id',
  `materialname` varchar(30) NOT NULL COMMENT '食材名称',
  `materialtypeid` int(11) NOT NULL COMMENT '食材类型id',
  `count` int(11) NOT NULL COMMENT '食材保有量',
  `measurename` varchar(20) DEFAULT NULL COMMENT '食材度量单位名称',
  PRIMARY KEY (`materialid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of material
-- ----------------------------

-- ----------------------------
-- Table structure for `materialtype`
-- ----------------------------
DROP TABLE IF EXISTS `materialtype`;
CREATE TABLE `materialtype` (
  `materialtypeid` int(11) NOT NULL AUTO_INCREMENT COMMENT '食材类型ID',
  `materialtype` varchar(20) NOT NULL COMMENT '食材类型名称',
  PRIMARY KEY (`materialtypeid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of materialtype
-- ----------------------------

-- ----------------------------
-- Table structure for `member`
-- ----------------------------
DROP TABLE IF EXISTS `member`;
CREATE TABLE `member` (
  `memberid` int(11) NOT NULL AUTO_INCREMENT COMMENT '会员ID',
  `cardid` varchar(20) NOT NULL COMMENT '卡片编号',
  `name` varchar(20) NOT NULL COMMENT '会员姓名',
  `phone` varchar(20) NOT NULL COMMENT '会员电话',
  `idcard` varchar(20) NOT NULL COMMENT '会员身份证号',
  `starttime` datetime NOT NULL COMMENT '开卡时间',
  `expiretime` datetime DEFAULT NULL COMMENT '过期时间',
  `membertypeid` int(11) NOT NULL COMMENT '会员类型ID',
  `shopid` varchar(10) NOT NULL COMMENT '分店ID',
  PRIMARY KEY (`memberid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of member
-- ----------------------------

-- ----------------------------
-- Table structure for `membertype`
-- ----------------------------
DROP TABLE IF EXISTS `membertype`;
CREATE TABLE `membertype` (
  `membertypeid` int(11) NOT NULL,
  `typename` varchar(20) NOT NULL,
  PRIMARY KEY (`membertypeid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of membertype
-- ----------------------------

-- ----------------------------
-- Table structure for `order`
-- ----------------------------
DROP TABLE IF EXISTS `order`;
CREATE TABLE `order` (
  `orderid` varchar(20) NOT NULL COMMENT '订单ID',
  `orderstate` int(11) NOT NULL DEFAULT '0' COMMENT '订单状态，0为未结，1为已结',
  `begintime` datetime NOT NULL COMMENT '订单开始时间',
  `endtime` datetime DEFAULT NULL COMMENT '订单结束时间',
  `accounts` decimal(10,0) DEFAULT NULL COMMENT '应收金额',
  `paid` decimal(10,0) DEFAULT NULL COMMENT '实收金额',
  `tableid` char(4) NOT NULL COMMENT '餐桌编号',
  `memberid` varchar(20) DEFAULT NULL COMMENT '会员编号',
  PRIMARY KEY (`orderid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of order
-- ----------------------------

-- ----------------------------
-- Table structure for `orderdetail`
-- ----------------------------
DROP TABLE IF EXISTS `orderdetail`;
CREATE TABLE `orderdetail` (
  `detailid` int(11) NOT NULL AUTO_INCREMENT COMMENT '订单详情ID',
  `orderid` varchar(20) NOT NULL COMMENT '对应订单编号',
  `dishesid` int(11) NOT NULL COMMENT '所点菜品id',
  `dishescount` int(11) NOT NULL DEFAULT '1' COMMENT '所点菜品数量',
  `dishestype` int(11) NOT NULL DEFAULT '0' COMMENT '用于标示点菜或者退菜0-点菜，1-划菜，2-退菜',
  `handletime` datetime NOT NULL COMMENT '订单详细的操作时间',
  PRIMARY KEY (`detailid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of orderdetail
-- ----------------------------

-- ----------------------------
-- Table structure for `shop`
-- ----------------------------
DROP TABLE IF EXISTS `shop`;
CREATE TABLE `shop` (
  `shopid` varchar(20) NOT NULL COMMENT '分店ID',
  `shopname` varchar(20) NOT NULL COMMENT '分店名称',
  `shopaddress` varchar(100) NOT NULL COMMENT '分店地址',
  `telphonenumber` varchar(20) DEFAULT NULL COMMENT '座机编号',
  `cellphonenumber` varchar(20) DEFAULT NULL COMMENT '手机编号',
  PRIMARY KEY (`shopid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of shop
-- ----------------------------

-- ----------------------------
-- Table structure for `user`
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `userid` int(11) NOT NULL AUTO_INCREMENT COMMENT '用户id',
  `username` varchar(20) NOT NULL COMMENT '用户名称',
  `password` varchar(100) NOT NULL COMMENT '密码',
  `registertime` datetime NOT NULL COMMENT '注册时间',
  `	
function` binary(100) NOT NULL COMMENT '权限代码',
  `lastlogintime` datetime NOT NULL COMMENT '上次登录时间',
  `expiretime` datetime DEFAULT NULL COMMENT '过期时间',
  PRIMARY KEY (`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of user
-- ----------------------------
