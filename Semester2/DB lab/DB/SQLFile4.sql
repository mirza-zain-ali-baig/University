create database UniStudent

create table record(
 S_Name varchar(20),
 Reg_No varchar(10),
 Courses varchar(20),
 Course_Code char(10),
 Offered_By char(10)
)
insert into record(S_name,Reg_No,Courses,Course_Code,Offered_By) values ('ali','01','DIP','1001','Mr.A') ,('Basit','02','DBMS','1002','Mr.X') , ('Akram','03','OS','1003','Mr.Y') ,('Asad','04','DBMS','1002','Mr.X') , ('Zeeshan','05','DIP','1001','Mr.A') , ('Muneer','06','OS','1003','Mr.Y') ,('Shafqat','07','NM','1004','Mr.H') , ('Ashan','08','OS','1002','Mr.Y') , ('Ikram','09','DIP','','') ,('Hassan','10','','','') 

update record
set Courses = 'AICT'
where Courses = 'OS'

update record
set Course_Code = '1000'
where Course_Code = '1003'



update record
set Course_Code = '1003',Courses = 'DB',Offered_By = 'Mr.Z'
where Reg_No = '10'

select *from record