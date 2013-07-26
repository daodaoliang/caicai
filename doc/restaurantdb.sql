/*
Navicat MySQL Data Transfer

Source Server         : 127.0.0.1
Source Server Version : 50524
Source Host           : localhost:3306
Source Database       : restaurantdb

Target Server Type    : MYSQL
Target Server Version : 50524
File Encoding         : 65001

Date: 2013-07-20 02:41:27
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
INSERT INTO `diningtable` VALUES ('0201', '201号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0202', '202号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0203', '203号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0204', '204号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0205', '205号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0206', '206号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0207', '207号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0208', '208号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0209', '209号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0210', '210号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0211', '211号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0212', '212号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0213', '213号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0214', '214号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0215', '215号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0216', '216号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0217', '217号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0218', '218号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0219', '219号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0220', '220号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0221', '221号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0222', '222号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0223', '223号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0224', '224号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0225', '225号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0226', '226号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0227', '227号桌', '0', '0', null, null, null);
INSERT INTO `diningtable` VALUES ('0228', '228号桌', '0', '0', null, null, null);

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
INSERT INTO `dishes` VALUES ('01001', '罐罐过桥米线', '20', './img/mixian.jpg', 'gggqmx', '3');
INSERT INTO `dishes` VALUES ('01002', '麻辣过桥米线', '22', null, 'mlgqmx', '3');
INSERT INTO `dishes` VALUES ('01003', '番茄过桥米线', '22', null, 'fqgqmx', '3');
INSERT INTO `dishes` VALUES ('01004', '麻辣鸡块过桥米线', '26', null, 'mljkgqmx', '3');
INSERT INTO `dishes` VALUES ('01005', '麻辣鱼片米线 ', '26', null, 'mlypmx', '3');
INSERT INTO `dishes` VALUES ('01006', '番茄大排米线 ', '26', null, 'fqdpgqmx', '3');
INSERT INTO `dishes` VALUES ('01007', '老坛酸菜过桥米线', '24', null, 'ltscgqmx', '3');
INSERT INTO `dishes` VALUES ('01008', '韩国泡菜过桥米线', '24', null, 'hgpcgqmx', '3');
INSERT INTO `dishes` VALUES ('01009', '加米线', '2', null, 'jmx', '3');
INSERT INTO `dishes` VALUES ('02003', '骨肉相连', '6', null, 'grxl', '2');
INSERT INTO `dishes` VALUES ('02004', '蒜蓉海带丝', '6', null, 'srhds', '2');
INSERT INTO `dishes` VALUES ('02005', '云南豆腐皮', '6', null, 'yndfp', '2');
INSERT INTO `dishes` VALUES ('02006', '地瓜丸', '8', null, 'dgw', '2');
INSERT INTO `dishes` VALUES ('02007', '老醋花生', '8', null, 'lchs', '2');
INSERT INTO `dishes` VALUES ('02013', '凉拌土豆丝', '6', null, 'lbtds', '2');
INSERT INTO `dishes` VALUES ('02014', '松花皮蛋', '9', null, 'shpd', '2');
INSERT INTO `dishes` VALUES ('03001', '农夫山矿泉水', '2', null, 'nfskqs', '1');
INSERT INTO `dishes` VALUES ('03004', '酸梅汁', '6', null, 'smz', '1');
INSERT INTO `dishes` VALUES ('03006', '可乐', '4', null, 'kl', '1');
INSERT INTO `dishes` VALUES ('03007', '雪碧', '4', null, 'xb', '1');
INSERT INTO `dishes` VALUES ('03010', '鲜果粒橙', '4', null, 'xglc', '1');
INSERT INTO `dishes` VALUES ('03012', '王老吉', '6', null, 'wlj', '1');
INSERT INTO `dishes` VALUES ('03013', '青岛啤酒', '6', null, 'qdpj', '1');
INSERT INTO `dishes` VALUES ('03015', '(套餐)红枣豆浆', '2', null, 'tchzdj', '1');
INSERT INTO `dishes` VALUES ('03017', '芒果C ', '6', null, 'mgc', '1');
INSERT INTO `dishes` VALUES ('03018', '红枣养颜豆浆 ', '6', null, 'hzyydj', '1');
INSERT INTO `dishes` VALUES ('03026', '茉莉蜜茶', '4', null, 'mlmc', '1');
INSERT INTO `dishes` VALUES ('03027', '套餐(芒果C)', '2', null, 'tcmgc', '1');
INSERT INTO `dishes` VALUES ('03028', '套餐(酸梅汁)', '2', null, 'tcsmz', '1');
INSERT INTO `dishes` VALUES ('04002', '鹌鹑蛋', '1', null, 'acd', '4');
INSERT INTO `dishes` VALUES ('04003', '青菜', '1', null, 'qc', '4');
INSERT INTO `dishes` VALUES ('04004', '加汤', '2', null, 'jt', '4');
INSERT INTO `dishes` VALUES ('04005', '加鸡柳', '2', null, 'jjl', '4');
INSERT INTO `dishes` VALUES ('04006', '加肉卷', '2', null, 'jrk', '4');
INSERT INTO `dishes` VALUES ('04007', '加鸡块', '5', null, 'jjk', '4');
INSERT INTO `dishes` VALUES ('04008', '加鱼块', '5', null, 'jyk', '4');
INSERT INTO `dishes` VALUES ('04009', '加玉米', '1', null, 'jym', '4');
INSERT INTO `dishes` VALUES ('04010', '加火腿', '2', null, 'jht', '4');
INSERT INTO `dishes` VALUES ('04011', '加大排', '8', null, 'jdp', '4');
INSERT INTO `dishes` VALUES ('04012', '加肉酱', '2', null, 'jrj', '4');

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
INSERT INTO `dishestype` VALUES ('4', '临时菜', null);
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
INSERT INTO `login` VALUES ('001', '0');

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
`balance` decimal(20,0) DEFAULT NULL COMMENT '账户余额',
  PRIMARY KEY (`memberid`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=gbk;

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
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of orderdetail
-- ----------------------------

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
INSERT INTO `userinfo` VALUES ('1', '1', '6512bd43d9caa6e02c990b0a82652dca', '2013-07-06 17:28:50', 0x01000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000, '0000-00-00 00:00:00', null, '管理员', '');
INSERT INTO `userinfo` VALUES ('2', '2', '3c59dc048e8850243be8079a5c74d079', '2013-07-06 17:28:50', 0x00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000, '0000-00-00 00:00:00', null, '点菜宝', '');
