create database students

create table st_Name(
 id int ,
 names varchar(20),
 city varchar(10) 
);

ALTER TABLE dbo.st_Name
alter column id id INT;


EXEC sp_rename 'table_name.old_column_name', 'new_column_name', 'COLUMN';
create table st_2(
 id int,
 names1 varchar(20),
 city1 varchar(10) 

);

INSERT INTO st_Name values(1,'zain','Lahore')
INSERT INTO st_Name values(2,'z','Lhr')
INSERT INTO st_Name(id,names) values(1,'op');

INSERT INTO st_2 values(1,'zain','Lahore')
INSERT INTO st_2 values(2,'z','Lhr')
INSERT INTO st_2(id,names1) values(1,'op');




select *from st_Name