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
  `consumeid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'ʳ�����Ķ�Ӧ��ID',
  `dishesid` int(11) NOT NULL COMMENT '��ƷID',
  `materialid` int(11) NOT NULL COMMENT 'ʳ��ID',
  `consumecount` int(11) NOT NULL COMMENT '��������',
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
  `id` char(4) NOT NULL COMMENT '������ID,��ӦΪ̨�ţ�4λ',
  `tablename` varchar(20) NOT NULL COMMENT '����������',
  `state` int(11) NOT NULL DEFAULT '0' COMMENT '����״̬����ʱ�涨0-Ϊ���У�1-æµ����������',
  `guestnumber` int(11) NOT NULL DEFAULT '1' COMMENT '��ǰ��������',
  `waiterid` varchar(10) DEFAULT NULL COMMENT '�����ķ���Ա���',
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
  `dishesid` int(11) NOT NULL AUTO_INCREMENT COMMENT '��ƷID',
  `dishesname` varchar(30) NOT NULL COMMENT '��Ʒ����',
  `price` decimal(10,0) NOT NULL COMMENT '��Ʒ�۸�',
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
  `materialid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'ʳ��id',
  `materialname` varchar(30) NOT NULL COMMENT 'ʳ������',
  `materialtypeid` int(11) NOT NULL COMMENT 'ʳ������id',
  `count` int(11) NOT NULL COMMENT 'ʳ�ı�����',
  `measurename` varchar(20) DEFAULT NULL COMMENT 'ʳ�Ķ�����λ����',
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
  `materialtypeid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'ʳ������ID',
  `materialtype` varchar(20) NOT NULL COMMENT 'ʳ����������',
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
  `memberid` int(11) NOT NULL AUTO_INCREMENT COMMENT '��ԱID',
  `cardid` varchar(20) NOT NULL COMMENT '��Ƭ���',
  `name` varchar(20) NOT NULL COMMENT '��Ա����',
  `phone` varchar(20) NOT NULL COMMENT '��Ա�绰',
  `idcard` varchar(20) NOT NULL COMMENT '��Ա���֤��',
  `starttime` datetime NOT NULL COMMENT '����ʱ��',
  `expiretime` datetime DEFAULT NULL COMMENT '����ʱ��',
  `membertypeid` int(11) NOT NULL COMMENT '��Ա����ID',
  `shopid` varchar(10) NOT NULL COMMENT '�ֵ�ID',
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
  `orderid` varchar(20) NOT NULL COMMENT '����ID',
  `orderstate` int(11) NOT NULL DEFAULT '0' COMMENT '����״̬��0Ϊδ�ᣬ1Ϊ�ѽ�',
  `begintime` datetime NOT NULL COMMENT '������ʼʱ��',
  `endtime` datetime DEFAULT NULL COMMENT '��������ʱ��',
  `accounts` decimal(10,0) DEFAULT NULL COMMENT 'Ӧ�ս��',
  `paid` decimal(10,0) DEFAULT NULL COMMENT 'ʵ�ս��',
  `tableid` char(4) NOT NULL COMMENT '�������',
  `memberid` varchar(20) DEFAULT NULL COMMENT '��Ա���',
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
  `detailid` int(11) NOT NULL AUTO_INCREMENT COMMENT '��������ID',
  `orderid` varchar(20) NOT NULL COMMENT '��Ӧ�������',
  `dishesid` int(11) NOT NULL COMMENT '�����Ʒid',
  `dishescount` int(11) NOT NULL DEFAULT '1' COMMENT '�����Ʒ����',
  `dishestype` int(11) NOT NULL DEFAULT '0' COMMENT '���ڱ�ʾ��˻����˲�0-��ˣ�1-���ˣ�2-�˲�',
  `handletime` datetime NOT NULL COMMENT '������ϸ�Ĳ���ʱ��',
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
  `shopid` varchar(20) NOT NULL COMMENT '�ֵ�ID',
  `shopname` varchar(20) NOT NULL COMMENT '�ֵ�����',
  `shopaddress` varchar(100) NOT NULL COMMENT '�ֵ��ַ',
  `telphonenumber` varchar(20) DEFAULT NULL COMMENT '�������',
  `cellphonenumber` varchar(20) DEFAULT NULL COMMENT '�ֻ����',
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
  `userid` int(11) NOT NULL AUTO_INCREMENT COMMENT '�û�id',
  `username` varchar(20) NOT NULL COMMENT '�û�����',
  `password` varchar(100) NOT NULL COMMENT '����',
  `registertime` datetime NOT NULL COMMENT 'ע��ʱ��',
  `	
function` binary(100) NOT NULL COMMENT 'Ȩ�޴���',
  `lastlogintime` datetime NOT NULL COMMENT '�ϴε�¼ʱ��',
  `expiretime` datetime DEFAULT NULL COMMENT '����ʱ��',
  PRIMARY KEY (`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of user
-- ----------------------------
