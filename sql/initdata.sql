-- cmdterminal.`user`
INSERT INTO `user` VALUES (1, null, 'testuser', '25D55AD283AA400AF464C76D713C07AD', '', '', null, null, '0', '2023-02-18 23:33:25', '2023-02-21 13:44:37', '0', '1', '10000', null, null);
INSERT INTO `user` VALUES (2, null, 'testuser111', '25D55AD283AA400AF464C76D713C07AD', '', '', null, null, '0', '2023-02-19 00:10:03', '2023-02-19 00:10:03', '0', '0', '10000', null, null);
INSERT INTO `user` VALUES (3, null, 'testuser222', '25D55AD283AA400AF464C76D713C07AD', '', '', null, null, '0', '2023-02-19 00:10:39', '2023-02-19 00:10:39', '0', '0', '10000', null, null);
INSERT INTO `user` VALUES (4, null, 'testuser333', '25D55AD283AA400AF464C76D713C07AD', '', '', null, null, '0', '2023-02-19 00:13:15', '2023-02-19 00:13:15', '0', '0', '10000', null, null);
INSERT INTO `user` VALUES (5, null, 'admin', '25D55AD283AA400AF464C76D713C07AD', '', '', null, null, '0', '2023-02-22 13:19:14', '2023-02-22 13:19:14', '0', '0', '10000', null, null);


-- cmdterminal.`interface`
INSERT INTO `interface` VALUES (1, 'getBackground', '获取随机背景', 'https://api.btstu.cn/sjbz/api.php', 'Get', '{\"lx\":\"dongman\",\"format\":\"json\"}', NULL, NULL, 0, 0, '2023-2-18 23:41:35', '2023-2-22 14:25:25', 0);
INSERT INTO `interface` VALUES (2, 'getTranslate', '获取翻译结果', 'https://api.fanyi.baidu.com/api/trans/vip/translate', 'Get', '{\"appid\":\"20230217001565627\",\"key\":\"oBb8QjQvxqywMug9TJl5\"}', NULL, NULL, 0, 0, '2023-2-21 23:21:22', '2023-2-22 14:25:27', 0);
INSERT INTO `interface` VALUES (3, 'getBackendVersion', '获取后台版本信息', '后端写死的版本', 'Get', NULL, NULL, NULL, 0, 0, '2023-2-26 01:57:39', '2023-2-26 02:09:32', 0);
INSERT INTO `interface` VALUES (4, 'getCurrentWeather', '获取当前天气', 'https://restapi.amap.com/v3/weather/weatherInfo', 'Get', '{\"key\":\"7c6e4e0c5492e0907cedc46ac09a370b\"}', NULL, NULL, 0, 0, '2023-2-26 02:43:48', '2023-2-26 02:45:44', 0);
INSERT INTO `interface` VALUES (5, 'getFutureWeather', '获取未来天气', 'https://restapi.amap.com/v3/weather/weatherInfo', 'Get', '{\"key\":\"7c6e4e0c5492e0907cedc46ac09a370b\"}', NULL, NULL, 0, 0, '2023-2-26 02:45:19', '2023-2-26 02:45:45', 0);

-- cmdterminal.`log`
INSERT INTO `log` VALUES (1, 1, 'hello test1111', '0', '2023-02-26 01:11:33', '2023-02-26 01:11:33', '0');
INSERT INTO `log` VALUES (2, 1, 'background ', '0', '2023-02-26 13:35:42', '2023-02-26 13:35:42', '0');
INSERT INTO `log` VALUES (3, 1, 'background', '0', '2023-02-26 13:35:57', '2023-02-26 13:35:57', '0');
INSERT INTO `log` VALUES (4, 1, 'weather 南京 -f', '0', '2023-02-26 13:42:50', '2023-02-26 13:42:50', '0');
INSERT INTO `log` VALUES (5, 1, 'weather 天津 -f', '0', '2023-02-26 13:45:49', '2023-02-26 13:45:49', '0');
INSERT INTO `log` VALUES (6, 1, 'weather 杭州 -f', '0', '2023-02-26 13:52:06', '2023-02-26 13:52:06', '0');