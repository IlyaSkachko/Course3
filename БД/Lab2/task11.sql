

ALTER SESSION SET "_ORACLE_SCRIPT" = TRUE;


CREATE TABLESPACE SIA_QDATA
DATAFILE 'SIA_QDATA'
SIZE 10M
OFFLINE;


SELECT TABLESPACE_NAME, STATUS, CONTENTS FROM DBA_TABLESPACES;

ALTER TABLESPACE SIA_QDATA ONLINE;

ALTER USER SIACORE QUOTA 2M ON SIA_QDATA;







CREATE TABLE SIA_T1
(
    ID NUMBER,
    NAME VARCHAR2(10)
) TABLESPACE SIA_QDATA;

INSERT INTO SIA_T1 VALUES (1, 'DW');
INSERT INTO SIA_T1 VALUES (2, 'WF');
INSERT INTO SIA_T1 VALUES (3, 'GB');

SELECT * FROM SIA_T1;
