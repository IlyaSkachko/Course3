using Lab10.page;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Edge;

namespace Lab10.tests
{
    [TestClass]
    public class UnitTest1
    {
        private IWebDriver driver;
        private SearchCarForModification page;
        private Bookmark pageMark;


        [TestInitialize]
        public void Setup()
        {
            driver = new EdgeDriver("D:\\Data\\edgedriver_win64");
            page = new SearchCarForModification(driver);
            pageMark = new Bookmark(driver);
        }

        [TestMethod]
        public void TestMethod1()
        {
            page.Open();

            page.SearchCar("BMW", "M5", "E39, 1998...2003", "4.9 MT (400 ë.ñ.)");

            Assert.IsTrue(page.isFound());
        }


        [TestMethod]
        public void TestMethod2()
        {
            pageMark.Open();

            pageMark.AccountEnter("333320927", "bestman2003");
            pageMark.Add();
            pageMark.Delete();
            Assert.IsTrue(pageMark.isFound());
        }
    }
}