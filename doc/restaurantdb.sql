/*
Navicat MySQL Data Transfer

Source Server         : 127.0.0.1
Source Server Version : 50524
Source Host           : localhost:3306
Source Database       : restaurantdb

Target Server Type    : MYSQL
Target Server Version : 50524
File Encoding         : 65001

Date: 2013-08-03 17:55:31
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
  `guestnumber` int(11) NOT NULL DEFAULT '0' COMMENT '当前客人数量',
  `waiterid` varchar(10) DEFAULT NULL COMMENT '开桌的服务员编号',
  `lastopentime` datetime DEFAULT NULL,
  `orderid` varchar(20) DEFAULT NULL,
  `relateid` char(4) DEFAULT NULL,
  `type` int(11) NOT NULL DEFAULT '0' COMMENT '0-正常，1-并台，2-拆台',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of diningtable
-- ----------------------------
INSERT INTO `diningtable` VALUES ('0201', '201号桌', '1', '5', null, null, '201308031754410201', null, '0');
INSERT INTO `diningtable` VALUES ('0202', '202号桌', '0', '0', null, null, '201308031750530202', '', '0');
INSERT INTO `diningtable` VALUES ('0203', '203号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0204', '204号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0205', '205号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0206', '206(并)', '0', '0', null, null, '', null, '0');
INSERT INTO `diningtable` VALUES ('0207', '207', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0208', '208号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0209', '209号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0210', '210号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0211', '211号桌', '0', '0', null, null, '201308031737150211', '', '0');
INSERT INTO `diningtable` VALUES ('0212', '212号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0213', '213号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0214', '214号桌', '0', '0', null, null, '', null, '0');
INSERT INTO `diningtable` VALUES ('0215', '215号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0216', '216号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0217', '217号桌', '0', '0', null, null, '', null, '0');
INSERT INTO `diningtable` VALUES ('0218', '218号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0219', '219号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0220', '220号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0221', '221号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0222', '222号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0223', '223号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0224', '224号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0225', '225号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0226', '226号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0227', '227号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0228', '228号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0229', '229号桌', '0', '1', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0230', '230号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0231', '231号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0232', '232号桌', '0', '0', null, null, null, null, '0');
INSERT INTO `diningtable` VALUES ('0233', '233号桌', '0', '0', null, null, null, null, '0');

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
) ENGINE=InnoDB AUTO_INCREMENT=4013 DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of dishes
-- ----------------------------
INSERT INTO `dishes` VALUES ('1001', '罐罐过桥米线', '22', './img/mixian.jpg', 'gggqmx', '3');
INSERT INTO `dishes` VALUES ('1002', '麻辣过桥米线', '26', null, 'mlgqmx', '3');
INSERT INTO `dishes` VALUES ('1003', '番茄过桥米线', '26', null, 'fqgqmx', '3');
INSERT INTO `dishes` VALUES ('1004', '麻辣鸡块过桥米线', '28', null, 'mljkgqmx', '3');
INSERT INTO `dishes` VALUES ('1005', '麻辣鱼片米线 ', '28', null, 'mlypmx', '3');
INSERT INTO `dishes` VALUES ('1006', '番茄大排米线 ', '28', null, 'fqdpgqmx', '3');
INSERT INTO `dishes` VALUES ('1007', '老坛酸菜过桥米线', '26', null, 'ltscgqmx', '3');
INSERT INTO `dishes` VALUES ('1008', '番茄贡丸过桥米线', '28', null, 'fqgwgqmx', '3');
INSERT INTO `dishes` VALUES ('1009', '加米线', '2', null, 'jmx', '3');
INSERT INTO `dishes` VALUES ('2003', '骨肉相连', '8', null, 'grxl', '2');
INSERT INTO `dishes` VALUES ('2004', '蒜蓉海带丝', '8', null, 'srhds', '2');
INSERT INTO `dishes` VALUES ('2005', '云南豆腐皮', '8', null, 'yndfp', '2');
INSERT INTO `dishes` VALUES ('2006', '地瓜丸', '8', null, 'dgw', '2');
INSERT INTO `dishes` VALUES ('2007', '老醋花生', '8', null, 'lchs', '2');
INSERT INTO `dishes` VALUES ('2013', '凉拌土豆丝', '8', null, 'lbtds', '2');
INSERT INTO `dishes` VALUES ('2014', '松花皮蛋', '9', null, 'shpd', '2');
INSERT INTO `dishes` VALUES ('3001', '农夫山矿泉水', '3', null, 'nfskqs', '1');
INSERT INTO `dishes` VALUES ('3004', '酸梅汁', '8', null, 'smz', '1');
INSERT INTO `dishes` VALUES ('3006', '可乐', '5', null, 'kl', '1');
INSERT INTO `dishes` VALUES ('3007', '雪碧', '5', null, 'xb', '1');
INSERT INTO `dishes` VALUES ('3010', '鲜果粒橙', '5', null, 'xglc', '1');
INSERT INTO `dishes` VALUES ('3012', '王老吉', '6', null, 'wlj', '1');
INSERT INTO `dishes` VALUES ('3013', '青岛啤酒', '8', null, 'qdpj', '1');
INSERT INTO `dishes` VALUES ('3015', '(套餐)红枣豆浆', '2', null, 'tchzdj', '1');
INSERT INTO `dishes` VALUES ('3017', '芒果C ', '8', null, 'mgc', '1');
INSERT INTO `dishes` VALUES ('3018', '红枣养颜豆浆 ', '8', null, 'hzyydj', '1');
INSERT INTO `dishes` VALUES ('3026', '茉莉蜜茶', '5', null, 'mlmc', '1');
INSERT INTO `dishes` VALUES ('3027', '(套餐)芒果C', '2', null, 'tcmgc', '1');
INSERT INTO `dishes` VALUES ('3028', '(套餐)酸梅汁', '2', null, 'tcsmz', '1');
INSERT INTO `dishes` VALUES ('3029', '葡萄汁', '8', null, 'ptz', '1');
INSERT INTO `dishes` VALUES ('3030', '冰糖雪梨汁', '8', null, 'btxlz', '1');
INSERT INTO `dishes` VALUES ('3031', '樱桃汁', '8', null, 'ytz', '1');
INSERT INTO `dishes` VALUES ('3032', '菠萝汁', '8', null, 'blz', '1');
INSERT INTO `dishes` VALUES ('3033', '(套餐)葡萄汁', '2', null, 'tcptz', '1');
INSERT INTO `dishes` VALUES ('3034', '(套餐)冰糖雪梨汁', '2', null, 'tcbtxlz', '1');
INSERT INTO `dishes` VALUES ('3035', '(套餐)樱桃汁', '2', null, 'tcytz', '1');
INSERT INTO `dishes` VALUES ('3036', '(套餐)菠萝汁', '2', null, 'tcblz', '1');
INSERT INTO `dishes` VALUES ('4002', '鹌鹑蛋', '1', null, 'acd', '4');
INSERT INTO `dishes` VALUES ('4003', '青菜', '1', null, 'qc', '4');
INSERT INTO `dishes` VALUES ('4004', '加汤', '2', null, 'jt', '4');
INSERT INTO `dishes` VALUES ('4005', '加鸡柳', '2', null, 'jjl', '4');
INSERT INTO `dishes` VALUES ('4006', '加肉卷', '2', null, 'jrk', '4');
INSERT INTO `dishes` VALUES ('4007', '加鸡块', '5', null, 'jjk', '4');
INSERT INTO `dishes` VALUES ('4008', '加鱼块', '5', null, 'jyk', '4');
INSERT INTO `dishes` VALUES ('4009', '加玉米', '1', null, 'jym', '4');
INSERT INTO `dishes` VALUES ('4010', '加火腿', '2', null, 'jht', '4');
INSERT INTO `dishes` VALUES ('4011', '加大排', '8', null, 'jdp', '4');
INSERT INTO `dishes` VALUES ('4012', '加肉酱', '2', null, 'jrj', '4');

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
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of member
-- ----------------------------
-- ----------------------------
-- Table structure for `memcarddetail`
-- ----------------------------
DROP TABLE IF EXISTS `memcarddetail`;
CREATE TABLE `memcarddetail` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `memcardid` varchar(20) NOT NULL,
  `handletype` int(11) NOT NULL,
  `handlemoney` decimal(10,0) DEFAULT NULL,
  `moremoney` decimal(10,0) DEFAULT NULL,
  `orderid` varchar(255) DEFAULT NULL,
  `relatecardid` varchar(255) DEFAULT NULL,
  `operatorid` int(11) NOT NULL,
  `handletime` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of memcarddetail
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
  `paytype` int(11) NOT NULL DEFAULT '0',
  `cardid` varchar(20) DEFAULT NULL,
  `operatorid` int(11) NOT NULL,
  PRIMARY KEY (`detailid`)
) ENGINE=InnoDB AUTO_INCREMENT=70 DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of orderdetail
-- ----------------------------
INSERT INTO `orderdetail` VALUES ('43', '201308031352520201', '3001', '1', '0', '2013-08-03 13:52:59', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('44', '201308031352520201', '3001', '1', '1', '2013-08-03 13:53:04', '0', '', '1');
INSERT INTO `orderdetail` VALUES ('45', '201308031352520201', '3001', '1', '0', '2013-08-03 13:55:07', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('46', '201308031352520201', '3001', '1', '1', '2013-08-03 13:55:12', '0', '', '1');
INSERT INTO `orderdetail` VALUES ('47', '201308031352520201', '3004', '2', '0', '2013-08-03 13:55:25', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('48', '201308031352520201', '3004', '2', '1', '2013-08-03 13:55:39', '0', '', '1');
INSERT INTO `orderdetail` VALUES ('49', '201308031357300201', '1002', '2', '0', '2013-08-03 13:57:42', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('50', '201308031357300201', '1002', '1', '1', '2013-08-03 13:58:15', '0', '', '1');
INSERT INTO `orderdetail` VALUES ('51', '201308031357300201', '1004', '2', '0', '2013-08-03 13:58:50', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('52', '201308031357300201', '1004', '1', '1', '2013-08-03 13:59:03', '0', '', '1');
INSERT INTO `orderdetail` VALUES ('53', '201308031357300201', '1004', '1', '1', '2013-08-03 13:59:20', '0', '', '1');
INSERT INTO `orderdetail` VALUES ('54', '201308031357300201', '1002', '1', '1', '2013-08-03 14:00:47', '0', '', '1');
INSERT INTO `orderdetail` VALUES ('55', '201308031357300201', '1001', '1', '0', '2013-08-03 14:01:24', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('56', '201308031357300201', '1004', '5', '0', '2013-08-03 14:01:32', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('57', '201308031357300201', '1004', '1', '1', '2013-08-03 14:01:48', '0', '', '1');
INSERT INTO `orderdetail` VALUES ('58', '201308031357300201', '1004', '1', '1', '2013-08-03 14:58:50', '0', '', '4129180');
INSERT INTO `orderdetail` VALUES ('59', '201308031357300201', '1004', '1', '1', '2013-08-03 15:00:12', '0', '', '197656988');
INSERT INTO `orderdetail` VALUES ('60', '201308031357300201', '1001', '1', '1', '2013-08-03 15:00:32', '0', '', '197656988');
INSERT INTO `orderdetail` VALUES ('61', '201308031357300201', '3001', '1', '0', '2013-08-03 15:00:44', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('62', '201308031357300201', '3001', '1', '1', '2013-08-03 15:00:54', '0', '', '197656988');
INSERT INTO `orderdetail` VALUES ('63', '201308031506150201', '3001', '1', '0', '2013-08-03 15:09:23', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('64', '201308031357300201', '1002', '1', '0', '2013-08-03 15:27:21', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('65', '201308031357300201', '1004', '2', '1', '2013-08-03 15:27:45', '0', '', '198472920');
INSERT INTO `orderdetail` VALUES ('66', '201308031627160201', '1001', '1', '0', '2013-08-03 16:27:34', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('67', '201308031627160201', '2003', '1', '0', '2013-08-03 16:27:34', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('68', '201308031627160201', '3001', '1', '0', '2013-08-03 16:27:34', '0', '', '0');
INSERT INTO `orderdetail` VALUES ('69', '201308031627160201', '2003', '1', '1', '2013-08-03 16:27:48', '0', '', '0');

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
INSERT INTO `orderinfo` VALUES ('201308031352520201', '0', '2013-08-03 13:52:59', null, '22', '22', '0201', '', '', '0', '1');
INSERT INTO `orderinfo` VALUES ('201308031357300201', '0', '2013-08-03 13:57:42', null, '299', '299', '0201', '', '', '0', '1');
INSERT INTO `orderinfo` VALUES ('201308031627160201', '0', '2013-08-03 16:27:34', null, '25', '25', '0201', '', '', '0', '1');

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
INSERT INTO `userinfo` VALUES ('2', '2', '3c59dc048e8850243be8079a5c74d079', '2013-07-06 17:28:50', 0x01010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000, '0000-00-00 00:00:00', null, '点菜宝001', '');
INSERT INTO `userinfo` VALUES ('3', '3', 'c16a5320fa475530d9583c34fd356ef5', '2013-07-06 17:28:50', 0x01010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000, '0000-00-00 00:00:00', null, '点菜宝002', '');
