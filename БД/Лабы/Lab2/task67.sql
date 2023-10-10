
CREATE PROFILE PF_SIACORE LIMIT
    FAILED_LOGIN_ATTEMPTS 7 -- ���������� ������� ����� � �������
    SESSIONS_PER_USER 3 -- ���������� ������ �� ������������
    PASSWORD_LIFE_TIME 60 -- ����� ����� ������
    PASSWORD_REUSE_TIME 365 -- ����� �� ���������� ������������� ������
    PASSWORD_LOCK_TIME 1 -- ����� ���������� ������
    CONNECT_TIME 180 -- ����� �����������
    IDLE_TIME 30; -- ����� �������



SELECT * FROM DBA_PROFILES;
SELECT * FROM DBA_PROFILES WHERE PROFILE = 'PF_SIACORE';
SELECT * FROM DBA_PROFILES WHERE PROFILE = 'DEFAULT';