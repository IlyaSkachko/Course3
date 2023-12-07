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
    internal class SearchCarForModification
    {
        private IWebDriver driver;
        private string baseUrl = "https://av.by/catalog";

        public SearchCarForModification(IWebDriver driver)
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
        
        public void SearchCar(string carName, string carModel, string carBody, string carEngine)
        {
            var name = driver.FindElement(By.XPath($"//a[@title ='{carName}']"));
            name.Click();

            var model = driver.FindElement(By.XPath($"//a[@title = '{carModel}']"));
            model.Click();

            var body = driver.FindElement(By.XPath($"//div[text() = '{carBody}']"));
            body.Click();

            var engine = driver.FindElement(By.XPath($"//a[@title = '{carEngine}']"));
            engine.Click();
        }


        public bool isFound()
        {
            try
            {
                WebDriverWait wait = new WebDriverWait(driver, TimeSpan.FromSeconds(10));
                driver.FindElement(By.ClassName("modification"));
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
