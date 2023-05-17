-- 加入请求体内容
alter table cmdterminal.`interface` add column `requestBody`  text null comment '请求体'
-- 更新错误字段iphone -> phone
alter table cmdterminal.`user` change column `iphone` `phone` varchar(128)  null comment '电话';