using NUnit.Framework;
using PersonalGPATracker.TestingFramework;
using System;
using TechTalk.SpecFlow;

namespace PersonalGPATrackerTests
{
    [Binding]
    public class PersonalGPATrackerAddNewCourseSteps
    {
        [Before]
        public static void Setup()
        {
            GPATrackerAddPage.Initialize();
        }

        [After]
        public static void Teardown()
        {
            GPATrackerAddPage.EndTest();
        }

        [Given]
        public void GivenINavigateToTheCourseAddPage()
        {
            GPATrackerAddPage.Goto();
        }
        
        [Given]
        public void GivenIHaveEntered_CODE_AsTheCode(string code)
        {
            GPATrackerAddPage.Code = code;
        }
        
        [Given]
        public void GivenIHaveEntered_TITLE_AsTheTitle(string title)
        {
            GPATrackerAddPage.Title = title;
        }
        
        [Given]
        public void GivenIHaveSelected_CREDITHOURS_AsTheCreditHours(int creditHours)
        {
            GPATrackerAddPage.CreditHours = Convert.ToString(creditHours);
        }

        [Given]
        public void GivenIHaveSelected_LETTERGRADE_AsTheLetterGrade(string letterGrade)
        {
            GPATrackerAddPage.LetterGrade = letterGrade;
        }        
        
        [When]
        //I issue the Add Course command
        public void WhenIIssueTheAddCourseCommand()
        //public void WhenIPressAddCourse()
        {
            GPATrackerAddPage.IssueAddCourseCommand();
        }
        
        [Then]
        public void ThenThePageShouldGoToHomePageAndCourseAddedToList()
        {
            var courseListPageTitle = GPATrackerAddPage.PageTitle;
            Assert.That(courseListPageTitle, Is.EqualTo("Course List and GPA - My ASP.NET Application"));
        }
    }
}
