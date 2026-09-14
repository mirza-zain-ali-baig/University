create database class

create table students(
  Sname varchar(20),
  Stid int
);

insert into students(Sname,Stid) values ('M.Sohaib',13)
select *from students
delete from students
where Sname = 'M.Sohaib'