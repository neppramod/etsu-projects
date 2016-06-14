using PersonalGPATracker.WebDriverFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PersonalGPATracker.TestingFramework
{
    public static class GPATrackerAddPage
    {
        private const string Url = "http://localhost:9090/Course/Add";

        public static string Code { set { Chrome.Code = value; } }

        public static string Title { set { Chrome.Title = value; } }

        public static string CreditHours { set { Chrome.CreditHours = value; } }

        public static string LetterGrade { set { Chrome.LetterGrade = value; } }

        public static object PageTitle { get { return Chrome.PageTitle; } }

        public static void Initialize()
        {
            Chrome.Create();
        }

        public static void EndTest()
        {
            Chrome.Quit();
        }

        public static void Goto()
        {
            Chrome.Goto(Url);
        }

        public static void IssueAddCourseCommand()
        {
            Chrome.ClickAddCourseButton();
        }
    }
}
