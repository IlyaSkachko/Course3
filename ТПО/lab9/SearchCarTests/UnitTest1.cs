using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Edge;

namespace SearchCarTests
{
    public class Tests
    {
        private IWebDriver driver;
        [SetUp]
        public void Setup()
        {
            driver = new EdgeDriver("D:\\Data\\edgedriver_win64");
            driver.Navigate().GoToUrl("https://av.by/");
            driver.Manage().Window.Maximize();
        }
          
        [Test]
        public void Test1()
        {
            var catalogModficationBtn = driver.FindElement(By.XPath("//a[text() ='Каталог модификаций']"));
            catalogModficationBtn.Click(); 

            var carName = driver.FindElement(By.XPath("//a[@title ='BMW']"));
            carName.Click();

            Thread.Sleep(500);
            var carModel = driver.FindElement(By.XPath("//a[@title = 'M5']"));
            carModel.Click();

            Thread.Sleep(500);
            var carBody = driver.FindElement(By.XPath("//div[text() = 'E39, 1998...2003']"));
            carBody.Click();

            Thread.Sleep(500);
            var carEngine = driver.FindElement(By.XPath("//a[@title = '4.9 MT (400 л.с.)']"));
            carEngine.Click();
        }
    }
}