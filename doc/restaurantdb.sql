/*
Navicat MySQL Data Transfer

Source Server         : 127.0.0.1
Source Server Version : 50524
Source Host           : localhost:3306
Source Database       : restaurantdb

Target Server Type    : MYSQL
Target Server Version : 50524
File Encoding         : 65001

Date: 2013-07-20 01:31:40
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
  `lastopentime` datetime DEFAULT NULL,
  `orderid` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of diningtable
-- ----------------------------
INSERT INTO `diningtable` VALUES ('0001', '1号桌', '0', '1', '1', '2013-07-15 23:50:34', null);
INSERT INTO `diningtable` VALUES ('0002', '2号桌', '0', '3', '1', null, null);
INSERT INTO `diningtable` VALUES ('0003', '3号桌', '0', '2', '1111', null, null);
INSERT INTO `diningtable` VALUES ('0004', '4号桌', '0', '3', '3', null, null);
INSERT INTO `diningtable` VALUES ('0005', '5号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0006', '包间1', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0007', '包间2', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('1', '1', '0', '1', '0001', null, null);
INSERT INTO `diningtable` VALUES ('21', '21', '0', '1', '0001', null, null);
INSERT INTO `diningtable` VALUES ('8', '8', '0', '1', '0001', null, null);

-- ----------------------------
-- Table structure for `dishes`
-- ----------------------------
DROP TABLE IF EXISTS `dishes`;
CREATE TABLE `dishes` (
  `dishesid` int(11) NOT NULL AUTO_INCREMENT COMMENT '菜品ID',
  `dishesname` varchar(30) NOT NULL COMMENT '菜品名称',
  `price` decimal(10,0) NOT NULL COMMENT '菜品价格',
  `imagefile` varchar(255) DEFAULT NULL,
  `pinyin` varchar(200) DEFAULT NULL,
  `typeid` int(11) NOT NULL,
  PRIMARY KEY (`dishesid`)
) ENGINE=InnoDB AUTO_INCREMENT=3006 DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of dishes
-- ----------------------------
INSERT INTO `dishes` VALUES ('1', '罐罐过桥米线', '22', './img/mixian.jpg', 'gggqmx', '3');
INSERT INTO `dishes` VALUES ('2', '番茄过桥米线', '26', null, 'fqgqmx', '3');
INSERT INTO `dishes` VALUES ('3', '麻辣过桥米线', '26', null, 'mlgqmx', '3');
INSERT INTO `dishes` VALUES ('4', '老坛酸菜过桥米线', '26', null, 'ltscgqmx', '3');
INSERT INTO `dishes` VALUES ('5', '麻辣鸡块过桥米线', '28', null, 'mljkgqmx', '3');
INSERT INTO `dishes` VALUES ('6', '番茄大排过桥米线', '28', null, 'fqdpgqmx', '3');
INSERT INTO `dishes` VALUES ('7', '麻辣鱼片过桥米线', '28', null, 'mlypgqmx', '3');
INSERT INTO `dishes` VALUES ('8', '番茄贡丸过桥米线', '28', null, 'fqgwgqmx', '3');
INSERT INTO `dishes` VALUES ('1001', '姜汁松花蛋', '9', null, 'jzshd', '2');
INSERT INTO `dishes` VALUES ('1002', '老醋花生', '8', null, 'lchs', '2');
INSERT INTO `dishes` VALUES ('1003', '地瓜丸', '8', null, 'dgw', '2');
INSERT INTO `dishes` VALUES ('1004', '凉拌土豆丝', '8', null, 'lbtds', '2');
INSERT INTO `dishes` VALUES ('1005', '深海小海带', '8', null, 'shxhd', '2');
INSERT INTO `dishes` VALUES ('1006', '骨肉相连', '8', null, 'grxl', '2');
INSERT INTO `dishes` VALUES ('2001', '红枣养颜豆浆', '8', null, 'hzyydj', '1');
INSERT INTO `dishes` VALUES ('2002', '酸梅汁', '8', null, 'smz', '1');
INSERT INTO `dishes` VALUES ('2003', '雀巢芒果C', '8', null, 'qcmgc', '1');
INSERT INTO `dishes` VALUES ('2004', '加多宝', '6', null, 'jdb', '1');
INSERT INTO `dishes` VALUES ('2005', '可乐', '5', null, 'kl', '1');
INSERT INTO `dishes` VALUES ('2006', '农夫山泉', '3', null, 'nfsq', '1');
INSERT INTO `dishes` VALUES ('2007', '青岛啤酒', '8', null, 'qdpj', '1');
INSERT INTO `dishes` VALUES ('3001', '套餐A', '32', null, 'tca', '4');
INSERT INTO `dishes` VALUES ('3002', '套餐B', '32', null, 'tcb', '4');
INSERT INTO `dishes` VALUES ('3003', '套餐C', '36', null, 'tcc', '4');
INSERT INTO `dishes` VALUES ('3004', '套餐D', '36', null, 'tcd', '4');
INSERT INTO `dishes` VALUES ('3005', '套餐E', '36', null, 'tce', '4');

-- ----------------------------
-- Table structure for `dishestype`
-- ----------------------------
DROP TABLE IF EXISTS `dishestype`;
CREATE TABLE `dishestype` (
  `typeid` int(11) NOT NULL AUTO_INCREMENT,
  `typename` varchar(40) NOT NULL,
  `typeimage` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`typeid`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of dishestype
-- ----------------------------
INSERT INTO `dishestype` VALUES ('1', '饮料', './img/yinliao.jpg');
INSERT INTO `dishestype` VALUES ('2', '小吃', null);
INSERT INTO `dishestype` VALUES ('3', '米线', null);
INSERT INTO `dishestype` VALUES ('4', '套餐', null);

-- ----------------------------
-- Table structure for `login`
-- ----------------------------
DROP TABLE IF EXISTS `login`;
CREATE TABLE `login` (
  `machineid` varchar(10) NOT NULL,
  `userid` int(11) NOT NULL,
  PRIMARY KEY (`machineid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of login
-- ----------------------------
INSERT INTO `login` VALUES ('001', '1');

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
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of member
-- ----------------------------
INSERT INTO `member` VALUES ('1', '1', '1', '1', '1', '2013-07-07 15:23:57', null, '1', '1');

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
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of orderdetail
-- ----------------------------
INSERT INTO `orderdetail` VALUES ('6', '201307150037310001', '1', '1', '0', '2013-07-15 00:37:31');
INSERT INTO `orderdetail` VALUES ('7', '201307150038290001', '1', '0', '1', '2013-07-15 00:38:29');
INSERT INTO `orderdetail` VALUES ('8', '201307150039450001', '1', '1', '1', '2013-07-15 00:39:45');
INSERT INTO `orderdetail` VALUES ('9', '201307150126340001', '1', '1', '0', '2013-07-15 01:26:34');
INSERT INTO `orderdetail` VALUES ('10', '201307152240240001', '1001', '1', '0', '2013-07-15 22:40:24');
INSERT INTO `orderdetail` VALUES ('11', '201307160000030001', '1', '1', '0', '2013-07-16 00:00:03');
INSERT INTO `orderdetail` VALUES ('12', '201307190002141', '2001', '5', '0', '2013-07-19 00:02:14');
INSERT INTO `orderdetail` VALUES ('13', '201307190004290002', '2001', '2', '0', '2013-07-19 00:04:29');
INSERT INTO `orderdetail` VALUES ('14', '201307192246580001', '2001', '1', '1', '2013-07-19 22:46:58');
INSERT INTO `orderdetail` VALUES ('15', '201307192257060001', '2001', '1', '1', '2013-07-19 22:57:06');
INSERT INTO `orderdetail` VALUES ('16', '201307192330580001', '2001', '1', '0', '2013-07-19 23:30:58');
INSERT INTO `orderdetail` VALUES ('17', '201307192332250001', '1', '1', '0', '2013-07-19 23:32:25');
INSERT INTO `orderdetail` VALUES ('18', '201307192335370001', '1', '1', '0', '2013-07-19 23:35:37');
INSERT INTO `orderdetail` VALUES ('19', '201307200114410001', '2001', '1', '0', '2013-07-20 01:14:41');
INSERT INTO `orderdetail` VALUES ('20', '201307200114410001', '1001', '1', '0', '2013-07-20 01:14:41');
INSERT INTO `orderdetail` VALUES ('21', '201307200114410001', '1', '1', '0', '2013-07-20 01:14:41');
INSERT INTO `orderdetail` VALUES ('22', '201307200126060001', '2001', '1', '0', '2013-07-20 01:26:06');
INSERT INTO `orderdetail` VALUES ('23', '201307200126060001', '1001', '1', '0', '2013-07-20 01:26:06');
INSERT INTO `orderdetail` VALUES ('24', '201307200126060001', '1', '1', '0', '2013-07-20 01:26:06');
INSERT INTO `orderdetail` VALUES ('25', '201307200127500001', '2001', '1', '1', '2013-07-20 01:27:50');
INSERT INTO `orderdetail` VALUES ('26', '201307200127500001', '1001', '1', '1', '2013-07-20 01:27:50');
INSERT INTO `orderdetail` VALUES ('27', '201307200127500001', '1', '1', '1', '2013-07-20 01:27:50');

-- ----------------------------
-- Table structure for `orderinfo`
-- ----------------------------
DROP TABLE IF EXISTS `orderinfo`;
CREATE TABLE `orderinfo` (
  `orderid` varchar(20) NOT NULL COMMENT '订单ID',
  `orderstate` int(11) NOT NULL DEFAULT '0' COMMENT '订单状态，0为未结，1为已结',
  `begintime` datetime NOT NULL COMMENT '订单开始时间',
  `endtime` datetime DEFAULT NULL COMMENT '订单结束时间',
  `accounts` decimal(10,0) DEFAULT NULL COMMENT '应收金额',
  `paid` decimal(10,0) DEFAULT NULL COMMENT '实收金额',
  `tableid` char(4) NOT NULL COMMENT '餐桌编号',
  `memberid` varchar(20) DEFAULT NULL COMMENT '会员编号',
  `wasteid` varchar(30) NOT NULL,
  `paytype` int(11) NOT NULL DEFAULT '0',
  `userid` int(11) NOT NULL,
  PRIMARY KEY (`orderid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of orderinfo
-- ----------------------------
INSERT INTO `orderinfo` VALUES ('201307150037310001', '0', '2013-07-15 00:37:31', null, '0', '10', '0001', '', '0012013071500:00:24', '0', '0');
INSERT INTO `orderinfo` VALUES ('201307150038290001', '0', '2013-07-15 00:38:29', null, '0', '10', '0001', '', '', '0', '0');
INSERT INTO `orderinfo` VALUES ('201307150039450001', '0', '2013-07-15 00:39:45', null, '0', '10', '0001', '', '', '0', '0');
INSERT INTO `orderinfo` VALUES ('201307150126340001', '0', '2013-07-15 01:26:34', null, '0', '10', '0001', '', '0012013071500:00:25', '0', '0');
INSERT INTO `orderinfo` VALUES ('201307152240240001', '0', '2013-07-15 22:40:24', null, '0', '10', '0001', '', '0012013071500:00:26', '0', '1');
INSERT INTO `orderinfo` VALUES ('201307160000030001', '0', '2013-07-16 00:00:03', null, '22', '32', '0001', '', '0012013071600:00:30', '0', '1');
INSERT INTO `orderinfo` VALUES ('201307190002141', '0', '2013-07-19 00:02:14', null, '40', '50', '1', '', '', '0', '1');
INSERT INTO `orderinfo` VALUES ('201307190004290002', '0', '2013-07-19 00:04:29', null, '16', '26', '0002', '', '', '0', '1');
INSERT INTO `orderinfo` VALUES ('201307192246580001', '0', '2013-07-19 22:46:58', null, '-8', '-8', '0001', '', '', '0', '1');
INSERT INTO `orderinfo` VALUES ('201307192257060001', '0', '2013-07-19 22:57:06', null, '-8', '-8', '0001', '', '', '0', '1');
INSERT INTO `orderinfo` VALUES ('201307192330580001', '0', '2013-07-19 23:30:58', null, '8', '8', '0001', '', '', '0', '1');
INSERT INTO `orderinfo` VALUES ('201307192332250001', '0', '2013-07-19 23:32:25', null, '22', '22', '0001', '', '', '0', '1');
INSERT INTO `orderinfo` VALUES ('201307192335370001', '0', '2013-07-19 23:35:37', null, '22', '22', '0001', '', '', '0', '1');
INSERT INTO `orderinfo` VALUES ('201307200114410001', '0', '2013-07-20 01:14:41', null, '39', '39', '0001', '', '', '0', '1');
INSERT INTO `orderinfo` VALUES ('201307200126060001', '0', '2013-07-20 01:26:06', null, '39', '33', '0001', '', '', '0', '1');
INSERT INTO `orderinfo` VALUES ('201307200127500001', '0', '2013-07-20 01:27:50', null, '-39', '-33', '0001', '', '', '0', '1');

-- ----------------------------
-- Table structure for `packages`
-- ----------------------------
DROP TABLE IF EXISTS `packages`;
CREATE TABLE `packages` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `Packagesid` int(11) NOT NULL,
  `dishesid` int(11) NOT NULL,
  `dishescount` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of packages
-- ----------------------------
INSERT INTO `packages` VALUES ('1', '3001', '1', '1');
INSERT INTO `packages` VALUES ('2', '3001', '1005', '1');

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
-- Table structure for `userinfo`
-- ----------------------------
DROP TABLE IF EXISTS `userinfo`;
CREATE TABLE `userinfo` (
  `userid` int(11) NOT NULL AUTO_INCREMENT COMMENT '用户id',
  `username` varchar(20) NOT NULL COMMENT '用户名称',
  `password` varchar(100) NOT NULL COMMENT '密码',
  `registertime` datetime NOT NULL COMMENT '注册时间',
  `purview` binary(100) NOT NULL COMMENT '权限代码',
  `lastlogintime` datetime NOT NULL COMMENT '上次登录时间',
  `expiretime` datetime DEFAULT NULL COMMENT '过期时间',
  `nickname` varchar(20) DEFAULT NULL,
  `machineid` varchar(10) DEFAULT '',
  PRIMARY KEY (`userid`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of userinfo
-- ----------------------------
INSERT INTO `userinfo` VALUES ('1', '1', '6512bd43d9caa6e02c990b0a82652dca', '2013-07-06 17:28:50', 0x01000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000, '0000-00-00 00:00:00', null, '小强', '');
INSERT INTO `userinfo` VALUES ('2', '', '', '0000-00-00 00:00:00', 0x00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000, '0000-00-00 00:00:00', null, null, '');
