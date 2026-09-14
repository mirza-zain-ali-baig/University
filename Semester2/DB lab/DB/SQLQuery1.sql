use university

create table student(
  std_id int,
  std_name varchar(20),
  course varchar(20)
);

insert into student(std_id,  std_name, course) values (20, 'Mirza Zain','database') 
insert into student(std_id,  std_name, course) values (32, 'Arsalan','Db')

update student
set std_name = 'bro'
where std_id = 20
select *from student
select std_id,std_name from student