create database newspaper_order;
use newspaper_order;
create table users(
	phone_number char(11) primary key,
	user_name varchar(20) NOT NULL,
	user_address varchar(35) NOT NULL,
	password char(36) NOT NULL,
	email char(20) NOT NULL,
	postcode char(10) NOT NULL,
	is_admin tinyint default 0
	);
alter table users add constraint uk_cno unique(phone_number);
alter table users add constraint ukx_cno unique(user_name);
create index idx_number on users(phone_number);
create view vw_user as select user_name '姓名',phone_number '电话',user_address '住址',email '邮箱',postcode '邮编' from users;
insert into users(phone_number,user_name,user_address,password,email,postcode,is_admin) values
	('17771717171','ttycp3','school','10086','1004454362@qq.com','00010',1),
	('17771717161','ttycp33','schosol','10086','10044543r62@qq.com','00010',0),
	('17771717151','ttycp32','schodol','10086','100445rr4362@qq.com','00010',0),
	('17771717141','ttycp31','schfool','10086','100445436r2@qq.com','00010',0),
	('17771717131','ttycp13','scfhool','10086','10044r54362@qq.com','00010',0),
	('17771717121','ttyc1p3','schoosl','10086','100445436r2@qq.com','00010',0),
	('17771717111','tty1cp3','schools','10086','100rt44543r62@qq.com','00010',0),
	('17771717101','tt1ycp3','schoolss','10086','100445436r2@qq.com','00010',0),
	('17771717191','t1tycp3','schoorsl','10086','1004454362r@qq.com','00010',0);
create table newspaper(
	paper_name varchar(20) NOT NULL,
	mail_code varchar(20) primary key,
	frequency char(5) NOT NULL,
	price decimal(9,2)
	);
alter table newspaper add constraint pa_cno unique(paper_name);
alter table newspaper add constraint ma_cno unique(mail_code);
create index idx_paper on newspaper(mail_code);
create view vw_paper as select paper_name "报刊名",mail_code '邮发代号',frequency '刊期',price '价格' from newspaper;
insert into newspaper(paper_name,mail_code,frequency,price) values
	('nature','47-11a-1','月刊','49.9'),
	('nataure','47-111-1','月刊','19.9'),
	('natsure','47-1s11-1','月刊','29.9'),
	('naturea','47-d111-1','月刊','39.9'),
	('nastsure','47-1111-1','月刊','9.9'),
	('natusre','47-d11-1','年刊','409.9'),
	('natsre','47-11-1','周刊','49.9'),
	('natssure','47-1w1-1','半月刊','439.9');
create table ordery(
	order_id int UNSIGNED AUTO_INCREMENT,
	stime date,
	etime date, 
	phone_number char(11),
	order_address varchar(35) NOT NULL,
	mail_code varchar(20),
	CONSTRAINT pk_score_id PRIMARY KEY(order_id),
     CONSTRAINT fk_score_sno FOREIGN KEY(phone_number) REFERENCES users(phone_number),
     CONSTRAINT fk_score_cno FOREIGN KEY(mail_code) REFERENCES newspaper(mail_code)    
	 );
insert into ordery(order_id,stime,etime,phone_number,order_address,mail_code) values
	(NULL,'1990-01-11','1991-01-01','17771717171','school','47-11a-1');
create view vw_order as select order_id '订单号',user_name '用户名',paper_name '报刊名',stime '起始时间',etime '终止时间',order_address '收货地址' from ordery natural join newspaper natural join users;
create table collecty(
	collect_id int UNSIGNED AUTO_INCREMENT,
	user_name varchar(20) NOT NULL,
	paper_name varchar(20) NOT NULL,
	mail_code varchar(20),
	frequency char(5) NOT NULL,
	price decimal(9,2),
	CONSTRAINT pks_score_id PRIMARY KEY(collect_id),
     CONSTRAINT fks_score_sno FOREIGN KEY(user_name) REFERENCES users(user_name),
     CONSTRAINT fks_score_cno FOREIGN KEY(mail_code) REFERENCES newspaper(mail_code), 
     CONSTRAINT fksd_score_sno FOREIGN KEY(frequency) REFERENCES newspaper(frequency),
     CONSTRAINT fksd_score_cno FOREIGN KEY(price) REFERENCES newspaper(price),
     CONSTRAINT fkasd_score_cno FOREIGN KEY(paper_name) REFERENCES newspaper(paper_name)
	);
create view vw_collect as select user_name '用户名',paper_name "报刊名",mail_code '邮发代号',frequency '刊期',price '价格' from collecty;
