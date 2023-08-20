-- 加入请求体内容
alter table stibel_init.`interface` add column `requestBody`  text null comment '请求体'
-- 更新错误字段iphone -> phone
alter table stibel_init.`user` change column `iphone` `phone` varchar(128)  null comment '电话';