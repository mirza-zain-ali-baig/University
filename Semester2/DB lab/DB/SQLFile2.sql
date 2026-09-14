USE DATABASE S_k

create TABLE Students(
 Std_id int primary key,
 Names varchar(10),
);
 
INSERT INTO Students values(1,'hassan')
INSERT INTO Students values(2,'syed')

create table Fees(
 std_id int foreign key references Students(Std_id),
 fees int
)

INSERT INTO Fees values(1,50000)
INSERT INTO Fees values(2,60000)

Select *from Students as s inner join Fees as f on s.Std_id = f.std_id

Select *from Fees