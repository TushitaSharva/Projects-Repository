ALTER TABLE takes
ADD grade_point numeric(5, 3);
DO $$
BEGIN
IF EXISTS (SELECT grade FROM takes WHERE grade = 'A+')
THEN UPDATE takes SET grade_point = 10 WHERE grade = 'A+';
END IF;
IF EXISTS (SELECT grade FROM takes WHERE grade = 'A ')
THEN UPDATE takes SET grade_point = 9 WHERE grade = 'A ';
END IF;
IF EXISTS (SELECT grade FROM takes WHERE grade = 'A-')
THEN UPDATE takes SET grade_point = 8 WHERE grade = 'A-';
END IF;
IF EXISTS (SELECT grade FROM takes WHERE grade = 'B+')
THEN UPDATE takes SET grade_point = 7 WHERE grade = 'B+';
END IF;
IF EXISTS (SELECT grade FROM takes WHERE grade = 'B ')
THEN UPDATE takes SET grade_point = 6 WHERE grade = 'B ';
END IF;
IF EXISTS (SELECT grade FROM takes WHERE grade = 'B-')
THEN UPDATE takes SET grade_point = 5 WHERE grade = 'B-';
END IF;
IF EXISTS (SELECT grade FROM takes WHERE grade = 'C+')
THEN UPDATE takes SET grade_point = 4 WHERE grade = 'C+';
END IF;
IF EXISTS (SELECT grade FROM takes WHERE grade = 'C ')
THEN UPDATE takes SET grade_point = 3 WHERE grade = 'C ';
END IF;
IF EXISTS (SELECT grade FROM takes WHERE grade = 'C-')
THEN UPDATE takes SET grade_point = 2 WHERE grade = 'C-';
END IF;
END $$;