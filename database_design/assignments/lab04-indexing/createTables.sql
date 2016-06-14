--------------------------------------------------------
--  DDL for Table ACTIVITY
--------------------------------------------------------

  DROP TABLE "ACTIVITY" cascade constraints;
  create table activity as select * from Academy_Prep.activity;

  
 




--------------------------------------------------------
--  DDL for Table EXAM
--------------------------------------------------------

  DROP TABLE "EXAM" cascade constraints;
  create table exam as select * from Academy_Prep.exam;
 
  
 




--------------------------------------------------------
--  DDL for Table GUARDIAN
--------------------------------------------------------

  DROP TABLE "GUARDIAN" cascade constraints;
  create table guardian as select * from Academy_Prep.guardian;

  




--------------------------------------------------------
--  DDL for Table SCHOOL
--------------------------------------------------------

  DROP TABLE "SCHOOL" cascade constraints;
  create table school as select * from Academy_Prep.school;

  




--------------------------------------------------------
--  DDL for Table SCHOOL_APPLY
--------------------------------------------------------

  DROP TABLE "SCHOOL_APPLY" cascade constraints;
  create table school_apply as select * from Academy_Prep.school_apply;

  
 




--------------------------------------------------------
--  DDL for Table SCHOOL_ATTEND
--------------------------------------------------------

  DROP TABLE "SCHOOL_ATTEND" cascade constraints;
  create table school_attend as select * from Academy_Prep.school_attend;

  
 




--------------------------------------------------------
--  DDL for Table STUDENT
--------------------------------------------------------

  DROP TABLE "STUDENT" cascade constraints;
  create table student as select * from Academy_Prep.student;

  
 




--------------------------------------------------------
--  DDL for Table STUDENT_EXAM
--------------------------------------------------------

  DROP TABLE "STUDENT_EXAM" cascade constraints;
  create table student_exam as select * from Academy_Prep.student_exam;

  
 




--------------------------------------------------------
--  DDL for Table STUDENT_GUARDIAN
--------------------------------------------------------

  DROP TABLE "STUDENT_GUARDIAN" cascade constraints;
  create table student_guardian as select * from Academy_Prep.student_guardian;

  
 




--------------------------------------------------------
--  DDL for Table VOLUNTEER_WORK
--------------------------------------------------------

  DROP TABLE "VOLUNTEER_WORK" cascade constraints;
  create table volunteer_work as select * from Academy_Prep.volunteer_work;
  
  
 




--------------------------------------------------------
--  Constraints for Table ACTIVITY
--------------------------------------------------------

  ALTER TABLE "ACTIVITY" ADD PRIMARY KEY ("STUDENT_ID", "ACTIVITY_ID")  ENABLE;
 




--------------------------------------------------------
--  Constraints for Table STUDENT
--------------------------------------------------------

 
  ALTER TABLE "STUDENT" ADD PRIMARY KEY ("STUDENT_ID") ENABLE;
 
  ALTER TABLE "STUDENT" ADD UNIQUE ("SSN") ENABLE;
 




--------------------------------------------------------
--  Constraints for Table GUARDIAN
--------------------------------------------------------

 
  ALTER TABLE "GUARDIAN" ADD PRIMARY KEY ("GUARDIAN_ID") ENABLE;
 




--------------------------------------------------------
--  Constraints for Table SCHOOL_APPLY
--------------------------------------------------------

  ALTER TABLE "SCHOOL_APPLY" ADD PRIMARY KEY ("STUDENT_ID", "SCHOOL_ID") ENABLE;
 




--------------------------------------------------------
--  Constraints for Table STUDENT_EXAM
--------------------------------------------------------
 
  ALTER TABLE "STUDENT_EXAM" ADD PRIMARY KEY ("STUDENT_ID", "EXAM_ID", "TEST_DATE") ENABLE;
 




--------------------------------------------------------
--  Constraints for Table SCHOOL
--------------------------------------------------------
 
  ALTER TABLE "SCHOOL" ADD PRIMARY KEY ("SCHOOL_ID") ENABLE;
 




--------------------------------------------------------
--  Constraints for Table EXAM
--------------------------------------------------------

  ALTER TABLE "EXAM" ADD PRIMARY KEY ("EXAM_ID") ENABLE;
 




--------------------------------------------------------
--  Constraints for Table SCHOOL_ATTEND
--------------------------------------------------------

  ALTER TABLE "SCHOOL_ATTEND" ADD PRIMARY KEY ("STUDENT_ID", "SCHOOL_ID") ENABLE;
 
 




--------------------------------------------------------
--  Constraints for Table STUDENT_GUARDIAN
--------------------------------------------------------

  ALTER TABLE "STUDENT_GUARDIAN" ADD PRIMARY KEY ("STUDENT_ID", "GUARDIAN_ID") ENABLE;
 




--------------------------------------------------------
--  Constraints for Table VOLUNTEER_WORK
--------------------------------------------------------
 
  ALTER TABLE "VOLUNTEER_WORK" ADD PRIMARY KEY ("STUDENT_ID", "VOLUNTEER_WORK_ID") ENABLE;
 




--------------------------------------------------------
--  DDL for Index IDX_GUARDIAN_NAME
--------------------------------------------------------

  CREATE INDEX "IDX_GUARDIAN_NAME" ON "GUARDIAN" ("LAST_NAME", "FIRST_NAME");
 




--------------------------------------------------------
--  DDL for Index IDX_STUDENT_ENROLL_DATE
--------------------------------------------------------

  CREATE BITMAP INDEX "IDX_STUDENT_ENROLL_DATE" ON "STUDENT" ("ENROLL_DATE");
 




--------------------------------------------------------
--  DDL for Index IDX_SCHOOL_NAME
--------------------------------------------------------

  CREATE INDEX "IDX_SCHOOL_NAME" ON "SCHOOL" ("NAME");
 




--------------------------------------------------------
--  Ref Constraints for Table ACTIVITY
--------------------------------------------------------

  ALTER TABLE "ACTIVITY" ADD CONSTRAINT "FK_ACTIVITY_STUDENT_ID" FOREIGN KEY ("STUDENT_ID")
	  REFERENCES "STUDENT" ("STUDENT_ID") ENABLE;
 




--------------------------------------------------------
--  Ref Constraints for Table SCHOOL_APPLY
--------------------------------------------------------

  ALTER TABLE "SCHOOL_APPLY" ADD CONSTRAINT "FK_SCHOOL_APPLY_SCHOOL_ID" FOREIGN KEY ("SCHOOL_ID")
	  REFERENCES "SCHOOL" ("SCHOOL_ID") ENABLE;
 
  ALTER TABLE "SCHOOL_APPLY" ADD CONSTRAINT "FK_SCHOOL_APPLY_STUDENT_ID" FOREIGN KEY ("STUDENT_ID")
	  REFERENCES "STUDENT" ("STUDENT_ID") ENABLE;
 




--------------------------------------------------------
--  Ref Constraints for Table SCHOOL_ATTEND
--------------------------------------------------------

  ALTER TABLE "SCHOOL_ATTEND" ADD CONSTRAINT "FK_SCHOOL_ATTEND_SCHOOL_ID" FOREIGN KEY ("SCHOOL_ID")
	  REFERENCES "SCHOOL" ("SCHOOL_ID") ENABLE;
 
  ALTER TABLE "SCHOOL_ATTEND" ADD CONSTRAINT "FK_SCHOOL_ATTEND_STUDENT_ID" FOREIGN KEY ("STUDENT_ID")
	  REFERENCES "STUDENT" ("STUDENT_ID") ENABLE;
 




--------------------------------------------------------
--  Ref Constraints for Table STUDENT_EXAM
--------------------------------------------------------

  ALTER TABLE "STUDENT_EXAM" ADD CONSTRAINT "FK_STUDENT_EXAM_EXAM_ID" FOREIGN KEY ("EXAM_ID")
	  REFERENCES "EXAM" ("EXAM_ID") ENABLE;
 
  ALTER TABLE "STUDENT_EXAM" ADD CONSTRAINT "FK_STUDENT_EXAM_STUDENT_ID" FOREIGN KEY ("STUDENT_ID")
	  REFERENCES "STUDENT" ("STUDENT_ID") ENABLE;
 




--------------------------------------------------------
--  Ref Constraints for Table STUDENT_GUARDIAN
--------------------------------------------------------

  ALTER TABLE "STUDENT_GUARDIAN" ADD CONSTRAINT "FK_STUDENT_GUARDIAN_STUDENT_ID" FOREIGN KEY ("STUDENT_ID")
	  REFERENCES "STUDENT" ("STUDENT_ID") ENABLE;
 




--------------------------------------------------------
--  Ref Constraints for Table VOLUNTEER_WORK
--------------------------------------------------------

  ALTER TABLE "VOLUNTEER_WORK" ADD CONSTRAINT "FK_VOLUNTEER_WORK_STUDENT_ID" FOREIGN KEY ("STUDENT_ID")
	  REFERENCES "STUDENT" ("STUDENT_ID") ENABLE;
 



