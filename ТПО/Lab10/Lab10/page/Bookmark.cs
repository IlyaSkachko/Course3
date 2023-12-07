using OpenQA.Selenium;
using OpenQA.Selenium.Edge;
using OpenQA.Selenium.Support.UI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab10.page
{
    internal class Bookmark
    {
        private IWebDriver driver;
        private string baseUrl = "https://cars.av.by/filter";

        public Bookmark(IWebDriver driver)
        {
            this.driver = driver;
        }

        public void Open()
        {
            driver.Navigate().GoToUrl(baseUrl);
            driver.Manage().Window.Maximize();
            driver.Manage().Timeouts().PageLoad = TimeSpan.FromSeconds(30);
            driver.Manage().Timeouts().ImplicitWait = TimeSpan.FromSeconds(30);
        }

        public void AccountEnter(string phoneNumber, string password)
        {
            var enterBtnNav = driver.FindElement(By.XPath("//span[text() = 'Войти']"));
            enterBtnNav.Click();

            var pNumber = driver.FindElement(By.XPath("(//input[@name = 'phone.number'])[1]"));
            pNumber.SendKeys(phoneNumber);

           
            var pass = driver.FindElement(By.XPath("(//input[@name = 'password'])[1]"));
            pass.SendKeys(password);

            var enterBtnAcc = driver.FindElement(By.XPath("//button[@class='button button--action' and span[@class='button__text' and text()='Войти']]"));
            enterBtnAcc.Click();
        }

        public void Add()
        {
            var markBtn = driver.FindElement(By.XPath("(//button[contains(@class, 'bookmark')])[1]"));
            markBtn.Click();
        }

        public void Delete()
        {
            var myMarksBtn = driver.FindElement(By.XPath("//a[@class='nav__link' and @href='https://av.by/profile/bookmarks']"));
            myMarksBtn.Click();

            var delMarkBtn = driver.FindElement(By.XPath("//button[@aria-busy='false']"));
            delMarkBtn.Click();
        
        }


        public bool isFound()
        {
            try
            {
                WebDriverWait wait = new WebDriverWait(driver, TimeSpan.FromSeconds(10));
                driver.FindElement(By.XPath("//h1[text()='У вас нет закладок']"));
                driver.Quit();
                return true;
            }
            catch (NoSuchElementException)
            {
                driver.Quit();
                return false;
            }
        }   
    }
}
