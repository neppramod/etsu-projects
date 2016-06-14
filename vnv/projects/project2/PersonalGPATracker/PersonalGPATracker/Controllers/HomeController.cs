using PersonalGPATracker.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace PersonalGPATracker.Controllers
{
    public class HomeController : Controller
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

        public ActionResult Index()
        {
            GetCourseList();
            return View(_courses);
        }

    }
}