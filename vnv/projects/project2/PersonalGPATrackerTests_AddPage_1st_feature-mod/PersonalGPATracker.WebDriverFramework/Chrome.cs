using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace PersonalGPATracker.WebDriverFramework
{
    public static class Chrome
    {
        private static string DRIVER_PATH = @"C:\ApplicationInstalled\chromedriver_win32";
        private static IWebDriver _page = null;

        public static string Code
        {
            set
            {
                var codeElement = _page.FindElement(By.Id("Code"));
                codeElement.Clear();
                codeElement.SendKeys(value);
            }
        }

        public static string Title
        {
            set
            {
                var titleElement = _page.FindElement(By.Id("Title"));
                titleElement.Clear();
                titleElement.SendKeys(value);
            }
        }

        public static string CreditHours
        {
            set
            {
                var creditHoursElement = _page.FindElement(By.Id("CreditHours"));                
                creditHoursElement.SendKeys(value);
            }
        }

        public static void ClickAddCourseButton()
        {
            var addCourseButton = _page.FindElement(By.CssSelector(
                @"body > div.container.body-content > form > div > div:nth-child(5) > div > input"));
            addCourseButton.Click();
        }

        public static string LetterGrade
        {
            set
            {
                var letterGradeElement = _page.FindElement(By.Id("LetterGrade"));                
                letterGradeElement.SendKeys(value);
            }
        }

        public static object PageTitle { get { return _page.Title; } }

        public static void Create()
        {
            _page = new ChromeDriver(DRIVER_PATH);
        }

        public static void Quit()
        {
            Thread.Sleep(2000);
            _page.Dispose();
            _page.Quit();
        }

        public static void Goto(string url)
        {
            _page.Navigate().GoToUrl(url);
        }
    }
}
