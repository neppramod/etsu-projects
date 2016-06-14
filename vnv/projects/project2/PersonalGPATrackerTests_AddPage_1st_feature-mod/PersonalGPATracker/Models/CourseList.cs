using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PersonalGPATracker.Models
{
    public class CourseList
    {
        public List<Course> Courses { get; set; }

        public CourseList()
        {
            Courses = new List<Course>();
        }

        public double TotalQualityPoints
        {
            get
            {
                var total = 0.0;
                foreach(var course in Courses)
                {
                    total += course.QualityPoints;
                }
                return total;
            }
        }

        public double TotalCreditHours
        {
            get
            {
                var total = 0.0;
                foreach (var course in Courses)
                {
                    total += course.CreditHours;
                }
                return total;
            }
        }

        public double TotalGPA
        {
            get
            {
                if (TotalCreditHours == 0.0) return 0.0;
                return TotalQualityPoints / TotalCreditHours;
            }
        }
    }
}
