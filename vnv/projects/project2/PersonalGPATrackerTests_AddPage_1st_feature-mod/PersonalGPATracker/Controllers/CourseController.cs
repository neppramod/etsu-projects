using PersonalGPATracker.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace PersonalGPATracker.Controllers
{
    public class CourseController : Controller
    {
        private CourseList _courses = null;

        private void GetCourseList()
        {
            if (Session["CourseList"] != null)
            {
                _courses = (CourseList)Session["CourseList"];
            }
            else
            {
                _courses = new CourseList();
            }
        }

        public ActionResult Add()
        {
            return View();
        }

        [HttpPost]
        public ActionResult AddCourse(Course course)
        {
            GetCourseList();
            _courses.Courses.Add(course);
            Session["CourseList"] = _courses;
            return RedirectToAction("Index", "Home");
        }

        public ActionResult Edit(string id)
        {
            GetCourseList();
            var course = GetCourse(id);
            if(course == null)
            {
                return HttpNotFound(id + " was not found.");
            }
            return View(course);
        }

        [HttpPost]
        public ActionResult EditCourse(string oldCode, Course course)
        {
            GetCourseList();
            var oldCourse = GetCourse(oldCode);
            if (course == null)
            {
                View(course);
            }

            oldCourse.Code = course.Code;
            oldCourse.Title = course.Title;
            oldCourse.CreditHours = course.CreditHours;
            oldCourse.LetterGrade = course.LetterGrade;

            Session["CourseList"] = _courses;
            return RedirectToAction("Index", "Home");
        }

        public ActionResult Details(string id)
        {
            GetCourseList();
            var course = GetCourse(id);
            if (course == null)
            {
                return HttpNotFound(id + " was not found.");
            }
            return View(course);
        }

        public ActionResult Delete(string id)
        {
            GetCourseList();
            var course = GetCourse(id);
            if (course == null)
            {
                return HttpNotFound(id + " was not found.");
            }
            return View(course);
        }

        [HttpPost]
        public ActionResult DeleteCourse(string id)
        {
            GetCourseList();
            _courses.Courses.Remove(GetCourse(id));
            Session["CourseList"] = _courses;
            return RedirectToAction("Index", "Home");
        }

        private Course GetCourse(string code)
        {
            Course course = null;
            foreach(var c in _courses.Courses)
            {
                if(c.Code == code)
                {
                    course = c;
                    break;
                }
            }
            return course;
        }
    }
}