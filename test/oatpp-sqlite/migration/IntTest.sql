CREATE TABLE test_ints (
  f_int8    TINYINT,
  f_int16   SMALLINT,
  f_int32   MEDIUMINT,
  f_int64   BIGINT
);

CREATE TABLE test_numerics (
  f_number      NUMERIC,
  f_decimal     DECIMAL(10,5),
  f_bool        BOOLEAN,
  f_date        DATE,
  f_datetime    DATETIME
);

INSERT INTO test_numerics
(f_number, f_decimal, f_bool, f_date, f_datetime) VALUES (null, null, null, null, null);

INSERT INTO test_numerics
(f_number, f_decimal, f_bool, f_date, f_datetime) VALUES (0, 0, 0, 0, 0);

INSERT INTO test_numerics
(f_number, f_decimal, f_bool, f_date, f_datetime) VALUES (1, 1, 1, date('2020-09-03'), datetime('2020-09-03 23:59:59'));
