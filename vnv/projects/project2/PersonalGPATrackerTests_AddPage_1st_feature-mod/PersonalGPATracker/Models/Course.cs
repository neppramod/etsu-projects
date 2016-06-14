using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PersonalGPATracker.Models
{
    public class Course
    {
        public string Code { get; set; }
        public string Title { get; set; }
        public int CreditHours { get; set; }
        public string LetterGrade { get; set; }
        public double GradePoints {
            get
            {
                var gradePoints = 0.0;
                switch (LetterGrade)
                {
                    case "A":
                        gradePoints = 4;
                        break;
                    case "A-":
                        gradePoints = 3.7;
                        break;
                    case "B+":
                        gradePoints = 3.3;
                        break;
                    case "B":
                        gradePoints = 3.0;
                        break;
                    case "B-":
                        gradePoints = 2.7;
                        break;
                    case "C+":
                        gradePoints = 2.3;
                        break;
                    case "C":
                        gradePoints = 2.0;
                        break;
                    case "C-":
                        gradePoints = 1.7;
                        break;
                    case "D+":
                        gradePoints = 1.3;
                        break;
                    case "D":
                        gradePoints = 1.0;
                        break;
                    case "F":
                    case "U":
                        gradePoints = 0.0;
                        break;
                }
                return gradePoints;
            }
        } // GradePoints

        public double QualityPoints
        {
            get
            {
                return CreditHours * GradePoints;
            }
        }
    }
}
