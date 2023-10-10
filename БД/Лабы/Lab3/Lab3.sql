

-- 1

select * from dba_pdbs;


-- 2

select * from v$instance;


-- 3

select * from v$option;

-- 4 cmd -> dbca


-- 5


select * from dba_pdbs;

-- 6

show con_name;

create tablespace SIA_PDB_TS
  datafile 'SIA_PDB_TS.dbf'
  size 10M
  autoextend on next 5M
  maxsize 50M;
    
    
create temporary tablespace SIA_PDB_TS_TEMP
    tempfile 'SIA_PDB_TS_TEMP.dbf'
    size 5M
    autoextend on
    next 2M
    maxsize 40M;
    
select * from dba_tablespaces;
    
drop tablespace SIA_PDB_TS including contents and datafiles;
drop tablespace SIA_PDB_TS_TEMP including contents and datafiles;
    
create role SIA_PDB_RL;

grant 
    connect,
    create session,
    alter session,
    create any table,
    drop any table,
    create any view,
    drop any view,
    create any procedure,
    drop any procedure
to SIA_PDB_RL;
    

select * from dba_roles;
drop role SIA_PDB_RL;

create profile SIA_PDB_PROFILE limit
    password_life_time 365
    sessions_per_user 3
    failed_login_attempts 7
    password_lock_time 1
    password_reuse_time 10
    connect_time 180;

select * from dba_profiles where PROFILE like '%SIA%';
drop profile SIA_PDB_PROFILE;

create user U1_SIA_PDB
    identified by 111
    default tablespace SIA_PDB_TS 
    quota unlimited on SIA_PDB_TS
    temporary tablespace SIA_PDB_TS_TEMP
    profile SIA_PDB_PROFILE
    account unlock
    password expire;
    

grant 
    SIA_PDB_RL,
    SYSDBA
to U1_SIA_PDB

drop user U1_SIA_PDB;

select global_name from global_name;

-- 7

-- подключение к пользователю


create table SIA_table (
    id int primary key,
    Name varchar(100) not null,
    Age int not null
);


insert into SIA_table values (  1, 'Ilya', 20 );
insert into SIA_table values (  2, 'Alexsandr', 43 );
insert into SIA_table values (  3, 'Valera', 37 );

select * from SIA_table;

drop table SIA_table;

-- 8

select * from dba_tablespaces where TABLESPACE_NAME like 'SIA%';
select * from dba_data_files;
select * from dba_roles where ROLE like 'SIA%';
select * from dba_sys_privs where GRANTEE like 'SIA%';
select * from dba_profiles where PROFILE like 'SIA%';
select * from dba_users where USERNAME like '%SIA%';


-- 9
alter session set container = CDB$ROOT;
SHOW CON_NAME;

create user C##SIA
    identified by 111;

grant 
    connect,
    create session,
    alter session,
    create any table,
    drop any table,
    SYSDBA
to C##SIA container = all





ALTER PLUGGABLE DATABASE SIA_PDB OPEN; 

-- Если можно создать две таблицы, значит они создаются в разных DB

-- Запускать в ConnectToCDB_Lab3
create table x (id int);
drop table x;

-- Запускать в ConnectToPDB_Lab3
create table x (id int);
drop table x;



-- 10
select s.sid, s.serial#, s.username, p.pdb_name
from v$session s
join v$pdbs p on s.con_id = p.con_id
where s.type = 'User'















