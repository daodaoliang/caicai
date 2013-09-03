/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50528
Source Host           : localhost:3306
Source Database       : restaurantdb

Target Server Type    : MYSQL
Target Server Version : 50528
File Encoding         : 65001

Date: 2013-09-03 20:21:42
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `memhanletype`
-- ----------------------------
DROP TABLE IF EXISTS `memhanletype`;
CREATE TABLE `memhanletype` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `handletype` int(11) NOT NULL,
  `handlename` varchar(20) NOT NULL,
  `value` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of memhanletype
-- ----------------------------
INSERT INTO `memhanletype` VALUES ('1', '1', '充值', '1');
INSERT INTO `memhanletype` VALUES ('2', '2', '消费扣款', '-1');
INSERT INTO `memhanletype` VALUES ('3', '3', '额度调整', '0');
INSERT INTO `memhanletype` VALUES ('4', '4', '转账转出', '-1');
INSERT INTO `memhanletype` VALUES ('5', '5', '转账转入', '1');
INSERT INTO `memhanletype` VALUES ('6', '6', '开卡', '0');
INSERT INTO `memhanletype` VALUES ('7', '7', '注销删除', '0');
INSERT INTO `memhanletype` VALUES ('8', '8', '退餐退款', '1');
