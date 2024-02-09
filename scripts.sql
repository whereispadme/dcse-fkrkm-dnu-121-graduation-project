set sql_safe_updates = 0;
set global foreign_key_checks = 0;

show databases;
create database graduateproject;

show tables;
use graduateproject;

drop table personaladmin;
drop table admin;

drop table personalclient;
drop table medicaldata;
drop table client;

drop table subscriptionclient;
drop table subscription;

create table admin
(
	admin_id integer auto_increment primary key not null,
	
    admin_login tinytext not null, 
	admin_password tinytext not null, 
    
    admin_lastname tinytext not null,
    admin_firstname tinytext not null,
    admin_middlename tinytext not null,
    
	admin_role tinytext not null
);

create table personaladmin
(
	personaladmin_admin_id integer auto_increment primary key not null,
	
    personaladmin_passport tinytext not null,
    personaladmin_telephone tinytext not null,
    personaladmin_adress tinytext not null,
    
    foreign key(personaladmin_admin_id) references admin(admin_id) on delete cascade 
);

create table client
(
	client_id integer auto_increment primary key not null,
    
    client_lastname tinytext not null,
    client_firstname tinytext not null,
    client_middlename tinytext not null,
	
    client_gender tinytext not null
);

create table personalclient
(
	personalclient_client_id integer auto_increment primary key not null,
	
    personalclient_passport tinytext not null,
    personalclient_telephone tinytext not null,
    personalclient_birthday date not null,
    
    foreign key(personalclient_client_id) references client(client_id) on delete cascade 
);

create table medicaldata
(
	medicaldata_сlient_id integer auto_increment primary key not null,
    
    medicaldata_institution tinytext not null,
    medicaldata_doctor tinytext not null,    
    
    medicaldata_dateissue date not null,
    medicaldata_dateexpiration date not null,
    
    medicaldata_decision tinytext not null,
    
    foreign key(medicaldata_сlient_id) references client(client_id) on delete cascade 
);

create table subscription
(
	subscription_id integer auto_increment primary key not null,	
    
    subscription_title tinytext not null,
    subscription_type tinytext not null,
    
    subscription_timestart time not null,
    subscription_timeend time not null,
    
    subscription_days tinytext not null,
    
    subscription_trainingamount varchar(2) not null,
    subscription_price float not null
);

create table subscriptionclient
(
	subscriptionclient_subscription_id integer primary key not null,
	subscriptionclient_admin_id integer not null,
    subscriptionclient_client_id integer not null,
    
    subscriptionclient_start date not null,
    subscriptionclient_end date not null,
    
    subscriptionclient_trainingleft varchar(2) not null,
	
    foreign key(subscriptionclient_subscription_id) references subscription(subscription_id) on delete cascade 
);

select * from admin;

INSERT INTO admin (admin_login, admin_password, admin_lastname, admin_firstname, admin_middlename, admin_role)
VALUES ('admin1', 'password1', 'Іванов', 'Олександр', 'Петрович', 'Адміністратор'),
       ('admin2', 'password2', 'Петренко', 'Марія', 'Іванівна', 'Адміністратор'),
       ('admin3', 'password3', 'Сидоренко', 'Андрій', 'Вікторович', 'Адміністратор'),
       ('admin4', 'password4', 'Коваленко', 'Тетяна', 'Олександрівна', 'Адміністратор'),
       ('admin5', 'password5', 'Захарченко', 'Василь', 'Ігорович', 'Адміністратор');

INSERT INTO admin (admin_login, admin_password, admin_lastname, admin_firstname, admin_middlename, admin_role)
VALUES ('mainlogin', 'mainpassword', 'Кущевський', 'Андрій', 'Петрович', 'Головний адміністратор');

INSERT INTO personaladmin (personaladmin_passport, personaladmin_telephone, personaladmin_adress)
VALUES ('926367412', '+380 (96) 523 38 73', 'вул. Макарова, 18');

INSERT INTO personaladmin (personaladmin_passport, personaladmin_telephone, personaladmin_adress)
VALUES ('123456789', '+380 (96) 312 31 23', 'вул. Робоча, 13а'),
       ('987654321', '+380 (97) 123 45 67', 'вул. Центральна, 5'),
       ('456789123', '+380 (98) 765 43 21', 'вул. Сонячна, 7'),
       ('321654987', '+380 (99) 987 65 43', 'вул. Зелена, 10'),
       ('987123654', '+380 (95) 246 81 37', 'вул. Польова, 2б');

INSERT INTO client (client_lastname, client_firstname, client_middlename, client_gender)
VALUES
    ('Петренко', 'Олена', 'Іванівна', 'Жіноча'),
    ('Сидорчук', 'Михайло', 'Олександрович', 'Чоловіча'),
    ('Ковальчук', 'Лілія', 'Володимирівна', 'Жіноча'),
    ('Іванчук', 'Олексій', 'Миколайович', 'Чоловіча'),
    ('Лисенко', 'Анастасія', 'Вікторівна', 'Жіноча');

INSERT INTO personalclient (personalclient_passport, personalclient_telephone, personalclient_birthday)
VALUES
    ('283679284', '+380 (97) 942 45 67', '2003-12-31'),
    ('905490812', '+380 (99) 235 65 43', '2002-08-15'),
    ('903457014', '+380 (98) 256 32 19', '2001-05-22'),
    ('290567023', '+380 (96) 212 22 33', '2004-07-10'),
    ('789245987', '+380 (95) 982 55 66', '2000-11-27');

INSERT INTO medicaldata (medicaldata_institution, medicaldata_doctor, medicaldata_dateissue, medicaldata_dateexpiration, medicaldata_decision)
VALUES
    ('Лікарня №1', 'Прокопчук В.І.', '2022-05-15', '2023-05-15', 'Здоровий'),
    ('Лікарня №2', 'Пилипенко О.В.', '2021-09-10', '2022-09-10', 'Здоровий'),
    ('Лікарня №1', 'Прокопчук В.І.', '2023-01-03', '2024-01-03', 'Обмеження'),
    ('Лікарня №1', 'Прокопчук В.І.', '2022-08-20', '2023-08-20', 'Здоровий'),
    ('Лікарня №2', 'Пилипенко О.В.', '2021-11-05', '2022-11-05', 'Здоровий');

INSERT INTO subscription (subscription_title, subscription_type, subscription_timestart, subscription_timeend, subscription_days, subscription_trainingamount, subscription_price)
VALUES
    ('Будній. Ранок.', 'Обмежений', '08:00', '12:00', 'Пн Вт Ср Чт Пт', '8', 1250.00),
    ('Будній. Вечір.', 'Обмежений', '17:00:00', '21:00:00', 'Пн Вт Ср Чт Пт', '12', 1450.00),
    ('Вихідний. Ранок.', 'Обмежений', '8:00', '12:00', 'Сб Вс', '8', 1300.00),
    ('Вихідний. Вечір.', 'Обмежений', '17:00', '21:00', 'Сб Вс', '12', 1200.00);
