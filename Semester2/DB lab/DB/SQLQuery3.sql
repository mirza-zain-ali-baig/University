create database people
drop table p1
create table p1(
  P_id int primary key,
  LastName char(10),
  FirstName char(10),
  PAddress char(100),
  City char(20)
);

insert into p1 values (1, 'Hansen','Christ','Timoteivn 10','Sandes'), (2,'Svendson', 'Tove', 'Borgvn','Sandes'),(3, 'Pertson', 'Michael', 'Storgt_20', 'sadnes'),(4, 'Pefnifn', 'wndnel', 'eifnigt_230', 'sadnes'), (5, 'enbfson', 'feichael', 'St3wr0', 'snes') 

insert into p1(P_id,FirstName,PAddress,City) values (9,'zain','street12','Lahore')

update p1 
set city = ''
where P_id = 1

delete from p1 -- it delete complete table data except structure
select *from p1

select LastName from p1
where PAddress = 'Borgvn'


-- dinstinct values from city

select distinct City from p1

select *from p1
where City = 'Sandes'

delete from p1
where FirstName = 'Tove';

select distinct City from p1

update p1
set City = 'sadnes'
where City = 'snes';